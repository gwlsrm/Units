// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "com_port_gw.h"

#include <boost/bind.hpp>
#include <boost/utility.hpp>
#include <boost/algorithm/string.hpp>

namespace ba = boost::asio;

namespace SerialOnBoost {
SerialPort::SerialPort()
    : m_serial_port(m_cont), m_timer(m_cont)
{

}

SerialPort::SerialPort(const std::string& port_name, std::size_t baud_rate, std::size_t timeout_ms)
    : SerialPort()
{
    open(port_name, baud_rate, timeout_ms);
}

void SerialPort::open(const std::string& port_name, std::size_t baud_rate, std::size_t timeout_ms)
{
    m_serial_port.open(port_name);
    // set serial port parameters
    m_serial_port.set_option(ba::serial_port_base::baud_rate(9600));
    m_serial_port.set_option( ba::serial_port_base::character_size(8));
    m_serial_port.set_option( ba::serial_port_base::flow_control(ba::serial_port_base::flow_control::none));
    m_serial_port.set_option( ba::serial_port_base::parity(ba::serial_port_base::parity::none));
    m_serial_port.set_option( ba::serial_port_base::stop_bits(ba::serial_port_base::stop_bits::one));
    // set timeout
    m_timeout = boost::posix_time::milliseconds(timeout_ms);
}


void SerialPort::write(const unsigned char* data, const std::size_t write_size)
{
    ba::write(m_serial_port, ba::buffer(data, write_size));
    //ba::write(m_serial_port, ba::buffer(data, write_size), ba::transfer_all());
}

int SerialPort::read(unsigned char* data, const std::size_t read_size)
{
    //ba::read(m_serial_port, ba::buffer(data, read_size), ba::transfer_all());
    if (m_timeout != boost::posix_time::seconds(0)) { //If timeout is set, start timer
        m_timer.expires_from_now(m_timeout);
        m_timer.async_wait(boost::bind(&SerialPort::timeout_expired,
                                       this,
                                       ba::placeholders::error
                                       )
                           );
    }

    ba::async_read(m_serial_port,
                   ba::buffer(data, read_size),
                   boost::bind(&SerialPort::read_completed,
                               this,
                               ba::placeholders::error,
                               ba::placeholders::bytes_transferred
                               )
                   );
    m_read_result = resultInProgress;
    m_bytes_transferred = 0;
    while(true)
    {
        m_cont.run_one(); //
        switch(m_read_result)
        {
        case resultSuccess:
            m_timer.cancel();
            return m_bytes_transferred;
        case resultTimeoutExpired:
            m_serial_port.cancel();
            throw SerialTimeoutException("Error in TimeutSerialBoost::read, timeout expired");
        case resultError:
            m_timer.cancel();
            m_serial_port.cancel();
            throw SerialException("Error in TimeutSerialBoost::read, read error");
        default: //if resultInProgress remain in the loop
            break;
        }
    }
}

void SerialPort::read_completed(const boost::system::error_code& error, const size_t transferred)
{
    if(error) {
        if(error != ba::error::operation_aborted)
            m_read_result = resultError;
    } else {
        if(m_read_result != resultInProgress)
            return;
        m_read_result = resultSuccess;
        this->m_bytes_transferred = transferred;
    }
}

void SerialPort::timeout_expired(const boost::system::error_code& error)
{
    if(m_read_result != resultInProgress)
        return;
    if(error != ba::error::operation_aborted)
        m_read_result = resultTimeoutExpired;
}
}





