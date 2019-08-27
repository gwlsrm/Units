#ifndef SERIAL_PORT_LINAPI_H_INCLUDED
#define SERIAL_PORT_LINAPI_H_INCLUDED

#include <string>
#include <vector>

namespace SerialOnLinux {

class SerialPort {
public:
    SerialPort() = default;
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
    void write(const unsigned char* buf, std::size_t len);
    bool read(std::vector<unsigned char>& data);
    bool read(unsigned char* buf, std::size_t len);

    // getters
    static int getPortNumberFromName(const std::string& port_name);
    static std::vector<std::string> getComList();
    int getID() const {return mID;}
private:
    static constexpr int INVALID_HANDLE_VALUE = -1;
    int mID = INVALID_HANDLE_VALUE;
};

}

#endif // SERIAL_PORT_LINAPI_H_INCLUDED
