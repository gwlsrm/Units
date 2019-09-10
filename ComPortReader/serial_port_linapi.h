#ifndef SERIAL_PORT_LINAPI_H_INCLUDED
#define SERIAL_PORT_LINAPI_H_INCLUDED

#include <string>
#include <vector>

namespace SerialOnLinux {

/**
    \brief wrapper for linapi functions to work with serial (COM) port
    
    Class can connect to serial port, read and write data
    It can obtain availiable serial port list 
*/
class SerialPort {
public:
    /// do nothing
    SerialPort() = default;
    /// connects to serial port with /dev/ttyUSB0 description and baudrate
    explicit SerialPort(const std::string& port, int baudrate = 9600);
    /// connects to serial port with portnumber (e.g. 0 for /dev/ttyUSB0) and baudrate
    explicit SerialPort(unsigned short numComPor, int baudrate = 9600);
    SerialPort(const SerialPort&) = delete;
    SerialPort& operator=(const SerialPort&) = delete;
    SerialPort(SerialPort&& other);
    SerialPort& operator=(SerialPort&& other);
    virtual ~SerialPort();
    
    /// true if connected or connection was succesfull
    bool isOK() const;
    /// connect/reconnect to specified serial port (e.g. /dev/ttyUSB0)
    void open(const std::string& port, int baudrate = 9600);
    /// connect/reconnect to specified serial port number (e.g. 0 for /dev/ttyUSB0)
    void open(unsigned short numComPor, int baudrate = 9600);
    /// close connection to serial port
    void close();

    /// write vector of bytes to serial port
    void write(const std::vector<unsigned char>& data);
    /// write array of bytes to serial port
    void write(const unsigned char* buf, std::size_t len);
    /// read bytes to vector of byte. vector must have needed size
    bool read(std::vector<unsigned char>& data);
    /// read len bytes to array of byte. array must have needed size
    bool read(unsigned char* buf, std::size_t len);

    // getters
    /// converts string "/dev/ttyUSB0" to 0
    static int getPortNumberFromName(const std::string& port_name);
    /// obtain and returns number of availiable serial ports
    static std::vector<std::string> getComList();
    /// returns serial port id
    int getID() const {return mID;}
private:
    static constexpr int INVALID_HANDLE_VALUE = -1;
    int mID = INVALID_HANDLE_VALUE;
};

}

#endif // SERIAL_PORT_LINAPI_H_INCLUDED
