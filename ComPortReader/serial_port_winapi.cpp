// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "serial_port_winapi.h"
#include <stdexcept>
#include <cassert>

#ifndef __linux

using namespace std;

namespace SerialOnWinapi {

static int TIMEOUT = 1000;

SerialPort::SerialPort()
    : m_Handle(INVALID_HANDLE_VALUE)
{}

SerialPort::SerialPort(const std::string& port, int baudrate)
    : SerialPort()
{
    open(port, baudrate);
}

SerialPort::SerialPort(unsigned short numComPor, int baudrate)
{
    open(numComPor, baudrate);
}

SerialPort::SerialPort(SerialPort&& other)
    : m_Handle(other.m_Handle)
{
    other.m_Handle = INVALID_HANDLE_VALUE;
}

SerialPort& SerialPort::operator=(SerialPort&& other)
{
    m_Handle = other.m_Handle;
    other.m_Handle = INVALID_HANDLE_VALUE;
    return *this;
}


SerialPort::~SerialPort() {
    close();
}

bool SerialPort::isOK() const {
    return m_Handle != INVALID_HANDLE_VALUE;
}

 void SerialPort::open(const std::string& port, int baudrate) {
    close();

    m_Handle = CreateFile(port.c_str(), GENERIC_READ | GENERIC_WRITE,
        0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

    if (m_Handle == INVALID_HANDLE_VALUE) {
        throw SerialPortException("Serial port: connection error");
    }

    SetCommMask(m_Handle, EV_RXCHAR);
    SetupComm(m_Handle, 1500, 1500);

    COMMTIMEOUTS CommTimeOuts;
    CommTimeOuts.ReadIntervalTimeout = 0xFFFFFFFF;
    CommTimeOuts.ReadTotalTimeoutMultiplier = 0;
    CommTimeOuts.ReadTotalTimeoutConstant = TIMEOUT;
    CommTimeOuts.WriteTotalTimeoutMultiplier = 0;
    CommTimeOuts.WriteTotalTimeoutConstant = TIMEOUT;

    if(!SetCommTimeouts(m_Handle, &CommTimeOuts)) {
        CloseHandle(m_Handle);
        m_Handle = INVALID_HANDLE_VALUE;
        throw SerialPortException("Serial port: cannot set timeout");
    }

    DCB ComDCM;

    memset(&ComDCM, 0, sizeof(ComDCM));
    ComDCM.DCBlength = sizeof(DCB);
    GetCommState(m_Handle, &ComDCM);
    ComDCM.BaudRate = DWORD(baudrate);
    ComDCM.ByteSize = 8;
    ComDCM.Parity = NOPARITY;
    ComDCM.StopBits = ONESTOPBIT;
    ComDCM.fAbortOnError = TRUE;
    ComDCM.fDtrControl = DTR_CONTROL_DISABLE;
    ComDCM.fRtsControl = RTS_CONTROL_DISABLE;
    ComDCM.fBinary = TRUE;
    ComDCM.fParity = FALSE;
    ComDCM.fInX = FALSE;
    ComDCM.fOutX = FALSE;
    ComDCM.XonChar = 0;
    ComDCM.XoffChar = (unsigned char)0xFF;
    ComDCM.fErrorChar = FALSE;
    ComDCM.fNull = FALSE;
    ComDCM.fOutxCtsFlow = FALSE;
    ComDCM.fOutxDsrFlow = FALSE;
    ComDCM.XonLim = 128;
    ComDCM.XoffLim = 128;

    if(!SetCommState(m_Handle, &ComDCM)) {
        CloseHandle(m_Handle);
        m_Handle = INVALID_HANDLE_VALUE;
        throw SerialPortException("Serial port: cannot set parameters");
    }
}

void SerialPort::open(unsigned short numComPor, int baudrate) {
    string port = string("COM") + to_string(numComPor);
    open(port, baudrate);
}

 void SerialPort::close() {
    if (m_Handle != INVALID_HANDLE_VALUE) {
        CloseHandle(m_Handle);
        m_Handle = INVALID_HANDLE_VALUE;
    }
 }

 void SerialPort::write(const std::vector<unsigned char>& data) {
     write(&data[0], (DWORD)data.size());
}

 void SerialPort::write(const unsigned char* data, std::size_t sze) {
    if(m_Handle == INVALID_HANDLE_VALUE) {
        throw SerialPortException("Serial port: port is closed");
    }

    DWORD feedback;
    if (!WriteFile(m_Handle, &data[0], sze, &feedback, 0) || feedback != sze) {
        CloseHandle(m_Handle);
        m_Handle = INVALID_HANDLE_VALUE;
        throw SerialPortException("Serial port: cannot write data");
    }

    // In some cases it's worth uncommenting
    //FlushFileBuffers(m_Handle);
}

 bool SerialPort::read(std::vector<unsigned char>& data) {
    unsigned char* buf = &data[0];
    DWORD len = (DWORD)data.size();

    return read(buf, len);
}

bool SerialPort::read(unsigned char* buf, std::size_t len) {
    if (m_Handle == INVALID_HANDLE_VALUE) {
        return false;
    }

    DWORD begin_time = GetTickCount();
    DWORD feedback = 0;

    int attempts = 3;
    std::size_t last = len;
    while(last && (attempts || (GetTickCount() - begin_time) < (DWORD)TIMEOUT/3)) {
        if(attempts) attempts--;

        if(!ReadFile(m_Handle, buf, last, &feedback, NULL)) {
            CloseHandle(m_Handle);
            m_Handle = INVALID_HANDLE_VALUE;
            return false;
        }

        assert(feedback <= last);
        last -= feedback;
        buf += feedback;
    }

    return (0 == last);
}

std::vector<std::string> SerialPort::getComList()
{
    vector<string> serial;
    unsigned long i = 0;
    char physical[65536]; // device_name
    QueryDosDevice(NULL, physical, sizeof(physical));
    while(1) {
        char* nameDevice = &physical[i]; // текущее имя устройства
        int nLen = strlen(nameDevice); // длина имени устройства
        char* istr = strstr (nameDevice, "COM"); // ищем COM
        if (nLen > 3 && istr != NULL) {
            serial.push_back(nameDevice);
        }
        // Переходим к следующему символу терминатору
        while(physical[i] != '\0')
            i++;
        // Перескакиваем на следующую строку
        i++;
        // Список завершается двойным симмволом терминатором, так что если символ
        // NULL, мы дошли до конца
        if(physical[i] == '\0') {
            break;
        }
    }
    return serial;
}

int SerialPort::getPortNumberFromName(const std::string& port_name)
{
    // portname is COM1
    if (port_name.size() > 3) {
        return stol(port_name.substr(3));
    }
    return -1;
}


}
#endif // __linux
