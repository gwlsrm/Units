#include "serial_port_linapi.h"
#include <iostream>
#include <list>
#include <chrono>
// for serial port
#define __linux
#include "container_output.h"
#ifdef __linux
#include <fcntl.h>
#include <termios.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/file.h>
#include <stdlib.h>
#include <dirent.h>
#include <linux/serial.h>


using namespace std;

namespace SerialOnLinux {

// получить список COM портов
static std::list<std::string> getComList();
// вспомогательные функции
static void probe_serial8250_comports(std::list<std::string>& comList, std::list<std::string> comList8250);
static void register_comport(std::list<std::string>& comList, std::list<std::string>& comList8250, const std::string& dir);
static std::string get_driver(const std::string& tty);

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
    : mID(other.mID)
{
    other.mID = INVALID_HANDLE_VALUE;
}

SerialPort& SerialPort::operator=(SerialPort&& other)
{
    mID = other.mID;
    other.mID = INVALID_HANDLE_VALUE;
    return *this;
}

void SerialPort::open(const std::string& port, int baudrate)
{
    mID = ::open(port.c_str(), O_RDWR | O_NOCTTY);
    if(mID < 0) {
        char *errmsg = strerror(errno);
        cerr << errmsg << endl;
        throw invalid_argument("Cannot connect to COM-port: " + port);
    }
    struct termios options; /*структура для установки порта*/
    memset(&options, 0, sizeof(options));
    tcgetattr(mID, &options); /*читает параметры порта*/

    /*setting port speed*/
    cfsetospeed (&options, baudrate);
    cfsetispeed (&options, baudrate);

    options.c_cc[VTIME]    = 20; /*Время ожидания байта 20*0.1 = 2 секунды */
    options.c_cc[VMIN]     = 0; /*минимальное число байт для чтения, read doesn't block*/


    options.c_cflag &= ~PARENB; /*NOPARITY бит четности не используется*/
    options.c_cflag &= ~CSTOPB; /*1 стоп бит */
    options.c_cflag &= ~CSIZE;  /*Размер байта*/
    options.c_cflag |= CS8;  /*8 бит*/
    options.c_cflag &=  ~CRTSCTS;       // no flow control

    options.c_lflag = 0;        // try: &=  ~CRTSCTS;       // no flow control
    options.c_oflag &= ~OPOST; /*Обязательно отключить постобработку, try: = 0*/

    options.c_cflag |=  CREAD | CLOCAL;     // turn on READ & ignore ctrl lines
    options.c_iflag &=  ~(IXON | IXOFF | IXANY);// turn off s/w flow ctrl
    options.c_lflag &=  ~(ICANON | ECHO | ECHOE | ISIG); // make raw

    // Flush Port, then applies attributes
    tcflush(mID, TCIFLUSH);
    tcsetattr(mID, TCSANOW, &options); /*сохронения параметров порта*/
}

void SerialPort::open(unsigned short numComPor, int baudrate) {
    string port = string("/dev/ttyUSB") + to_string(numComPor);
    open(port, baudrate);
}

SerialPort::~SerialPort()
{
    close();
}

void SerialPort::close()
{
    if (mID != INVALID_HANDLE_VALUE) {
        ::close(mID);
        //::flock(mID, LOCK_UN);  // free the port so that others can use it.
        mID = -1;
    }
}

bool SerialPort::isOK() const
{
    return mID == INVALID_HANDLE_VALUE;
}

void SerialPort::write(const unsigned char* buf, std::size_t len)
{
    if (mID == INVALID_HANDLE_VALUE) return;

    int n = ::write(mID, buf, len);
    if(n < 0) {
        char *errmsg = strerror(errno);
        cerr << errmsg << endl;
    }
}

void SerialPort::write(const std::vector<unsigned char>& data)
{
    write(&data[0], data.size());
}

std::ostream& print_int_carray(std::ostream& out, const unsigned char* ai, std::size_t sze) {
    bool first = true;
    out <<  '[';
    for (size_t i = 0; i < sze; ++i) {
      if (!first) {
        out << ',';
      }
      first = false;
      out << int(ai[i]);
    }
    return out << ']';
}

bool SerialPort::read(unsigned char* buf, std::size_t len)
{
    using namespace std::chrono;
    if (mID == INVALID_HANDLE_VALUE) return false;

    // simple
    /*
    int readed = ::read(mID, buf, len);
    if (readed == -1) {
        char *errmsg = strerror(errno);
        cerr << errmsg << endl;
        return false;
    } else {
        //cerr << readed << " of " << len << endl;
        return true;
    }
    */

    constexpr int TIMEOUT = 4000;
    auto begin_time = steady_clock::now();
    int attempts = 10;
    size_t last = len;
    while (last > 0 && attempts) { // while not all readed or attempts exists
        auto dur = steady_clock::now() - begin_time;
        if (duration_cast<milliseconds>(dur).count() > TIMEOUT) {
            cerr << "Reading timeout\n";
            break;
        }
        if (attempts) attempts--;
        int readed = ::read(mID, buf, last);
        if (readed == -1) {
            char *errmsg = strerror(errno);
            cerr << errmsg << endl;
            return false;
        }
        last -= readed;
//        cerr << readed << " of " << len << " last= " << last << ". readed_data = "
//             << hex;
//         print_int_carray(cerr, buf, readed) << dec << endl;
        buf += readed;
    }
    return (last <= 0);
}

bool SerialPort::read(std::vector<unsigned char>& data)
{
    unsigned char* buf = &data[0];
    size_t len = data.size();

    return SerialPort::read(buf, len);
}

int SerialPort::getPortNumberFromName(const std::string& port_name)
{
    // portname is /dev/ttyUSB0
    if (port_name.size() > 11) {
        return stol(port_name.substr(11));
    }
    return -1;
}

std::vector<std::string> SerialPort::getComList()
{
    list<string> l = SerialOnLinux::getComList();
    vector<string> serial{l.begin(), l.end()};
    return serial;
}


static std::string get_driver(const std::string& tty) {
    struct stat st;
    std::string devicedir = tty;

    // Append '/device' to the tty-path
    devicedir += "/device";

    // Stat the devicedir and handle it if it is a symlink
    if (lstat(devicedir.c_str(), &st)==0 && S_ISLNK(st.st_mode)) {
        char buffer[1024];
        memset(buffer, 0, sizeof(buffer));

        // Append '/driver' and return basename of the target
        devicedir += "/driver";

        if (readlink(devicedir.c_str(), buffer, sizeof(buffer)) > 0)
            return basename(buffer);
    }
    return "";
}

static void register_comport(std::list<std::string>& comList, std::list<std::string>& comList8250, const std::string& dir) {
    // Get the driver the device is using
    std::string driver = SerialOnLinux::get_driver(dir);

    // Skip devices without a driver
    if (driver.size() > 0) {
        std::string devfile = std::string("/dev/") + basename(dir.c_str());

        // Put serial8250-devices in a seperate list
        if (driver == "serial8250") {
            comList8250.push_back(devfile);
        } else
            comList.push_back(devfile);
    }
}

static void probe_serial8250_comports(std::list<std::string>& comList, std::list<std::string> comList8250) {
    struct serial_struct serinfo;
    std::list<std::string>::iterator it = comList8250.begin();

    // Iterate over all serial8250-devices
    while (it != comList8250.end()) {

        // Try to open the device
        int fd = open((*it).c_str(), O_RDWR | O_NONBLOCK | O_NOCTTY);

        if (fd >= 0) {
            // Get serial_info
            if (ioctl(fd, TIOCGSERIAL, &serinfo)==0) {
                // If device type is no PORT_UNKNOWN we accept the port
                if (serinfo.type != PORT_UNKNOWN)
                    comList.push_back(*it);
            }
            close(fd);
        }
        it ++;
    }
}

std::list<std::string> getComList(void) {
    int n;
    struct dirent **namelist;
    std::list<std::string> comList;
    std::list<std::string> comList8250;
    const char* sysdir = "/sys/class/tty/";
    // Scan through /sys/class/tty - it contains all tty-devices in the system
    n = scandir(sysdir, &namelist, NULL, NULL);
    if (n < 0)
        perror("scandir");
    else {
        while (n--) {
            if (strcmp(namelist[n]->d_name,"..") && strcmp(namelist[n]->d_name,".")) {

                // Construct full absolute file path
                std::string devicedir = sysdir;
                devicedir += namelist[n]->d_name;

                // Register the device
                register_comport(comList, comList8250, devicedir);
            }
            free(namelist[n]);
        }
        free(namelist);
    }
    // Only non-serial8250 has been added to comList without any further testing
    // serial8250-devices must be probe to check for validity
    probe_serial8250_comports(comList, comList8250);
    // Return the lsit of detected comports
    return comList;
}



}

#endif
