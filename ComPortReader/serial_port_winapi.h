#ifndef SERIAL_PORT_WINAPI_H_INCLUDED
#define SERIAL_PORT_WINAPI_H_INCLUDED

//#define NOMINMAX //иначе API windows определит макросы min и max, конфликтующие с std::max и std::min в vector
#include <string>
#include <vector>
#ifndef __linux
#include <windows.h>

/**\file
\brief Class for work with serial (COM) port
*/

namespace SerialOnWinapi {

/**
    \brief wrapper for winapi functions to work with serial (COM) port

    Class can connect to serial port, read and write data
    It can obtain availiable serial port list
*/
class SerialPort {
public:
    /// do nothing. To work -- need to open serial port
    SerialPort();
    /// connects to serial port with COM1 description and baudrate
    explicit SerialPort(const std::string& port, int baudrate = 9600);
    /// connects to serial port with portnumber (e.g. 1 for COM1) and baudrate
    explicit SerialPort(unsigned short numComPor, int baudrate = 9600);
    SerialPort(const SerialPort&) = delete;
    SerialPort& operator=(const SerialPort&) = delete;
    SerialPort(SerialPort&& other);
    SerialPort& operator=(SerialPort&& other);
    virtual ~SerialPort();

    /// true if connected or connection was succesfull
    bool isOK() const;
    /// connect/reconnect to specified serial port (e.g. COM1)
    void open(const std::string& port, int baudrate = 9600);
    /// connect/reconnect to specified serial port number (e.g. 1 for COM1)
    void open(unsigned short numComPor, int baudrate = 9600);
    /// close connection to serial port
    void close();

    /// write vector of bytes to serial port
    void write(const std::vector<unsigned char>& data);
    /// write array of bytes to serial port
    void write(const unsigned char* data, std::size_t sze);
    /// read bytes to vector of byte. vector must have needed size
    bool read(std::vector<unsigned char>& data);
    /// read len bytes to array of byte. array must have needed size
    bool read(unsigned char* buf, std::size_t len);

    // getters
    /// converts string "COM1" to 1
    static int getPortNumberFromName(const std::string& port_name);
    /// obtain and returns number of availiable serial ports
    static std::vector<std::string> getComList();
private:
    HANDLE m_Handle;
};

struct SerialPortException : public std::exception {
    SerialPortException(const std::string & msg = "SerialException") : std::exception(), m_what(msg)
    {}
    ~SerialPortException() throw() {}
    const char * what() const throw() { return m_what.c_str(); }
private:
    const std::string m_what;
};

}

#endif // SERIAL_PORT_WINAPI_H_INCLUDED

#endif // __linux
