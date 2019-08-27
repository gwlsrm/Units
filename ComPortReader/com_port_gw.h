#ifndef COM_PORT_GW_H_INCLUDED
#define COM_PORT_GW_H_INCLUDED

#include "boost/asio.hpp"
#include "boost/asio/serial_port.hpp"
#include <boost/date_time/posix_time/posix_time.hpp>
#include <string>
#include <exception>

namespace SerialOnBoost {
class SerialException : public std::exception {
public:
    SerialException(const std::string & msg = "SerialException") : std::exception(), m_what(msg)
    {}
    ~SerialException() throw() {}
    const char * what() const throw() { return m_what.c_str(); }
private:
    const std::string m_what;
};

class SerialTimeoutException : public SerialException {
public:
    SerialTimeoutException(const std::string & msg = "SerialTimeoutException") : SerialException(msg)
    {}
};

class SerialPort {
public:
    SerialPort();
    explicit SerialPort(const std::string& port_name, std::size_t baud_rate = 9600,
                        std::size_t timeout_ms = 100);
    SerialPort(const SerialPort&) = delete;
    SerialPort& operator=(const SerialPort&) = delete;
    void open(const std::string& port_name, std::size_t baud_rate = 9600,
                        std::size_t timeout_ms = 100);
    // read && write
    void write(const unsigned char* data, const std::size_t write_size);
    int read(unsigned char* data, const std::size_t read_size);
private:
    enum ReadResult {resultInProgress = 0, resultSuccess = 1, resultError = 2, resultTimeoutExpired = 3};
    //boost::asio::io_context m_cont;
    boost::asio::io_service m_cont;
    boost::asio::serial_port m_serial_port;
    boost::asio::deadline_timer m_timer;
    boost::posix_time::time_duration m_timeout;
    ReadResult m_read_result;
    std::size_t m_bytes_transferred;
    // methods
    void read_completed(const boost::system::error_code& error, const size_t transferred);
    void timeout_expired(const boost::system::error_code & error);
};
}

#endif // COM_PORT_GW_H_INCLUDED
