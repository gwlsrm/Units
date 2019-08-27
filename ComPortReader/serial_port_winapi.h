#ifndef SERIAL_PORT_WINAPI_H_INCLUDED
#define SERIAL_PORT_WINAPI_H_INCLUDED

//#define NOMINMAX //иначе API windows определит макросы min и max, конфликтующие с std::max и std::min в vector
#include <string>
#include <vector>
#ifndef __linux
#include <windows.h>
#endif // __linux

namespace SerialOnWinapi {

class SerialPort {
public:
    SerialPort();
    explicit SerialPort(const std::string& port, int baudrate = 9600);
    explicit SerialPort(unsigned short numComPor, int baudrate = 9600);
    SerialPort(const SerialPort&) = delete;
    SerialPort& operator=(const SerialPort&) = delete;
    SerialPort(SerialPort&& other);
    SerialPort& operator=(SerialPort&& other);
    virtual ~SerialPort();

    bool isOK() const;

    void open(const std::string& port, int baudrate = 9600);
    void open(unsigned short numComPor, int baudrate = 9600);
    void close();

    void write(const std::vector<unsigned char>& data);
    void write(const unsigned char* data, std::size_t sze);
    bool read(std::vector<unsigned char>& data);
    bool read(unsigned char* buf, std::size_t len);

    // getters
    static int getPortNumberFromName(const std::string& port_name);
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
