#ifndef SERIAL_PORT_LINAPI_H_INCLUDED
#define SERIAL_PORT_LINAPI_H_INCLUDED

#include <fcntl.h>
#include <termios.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>

bool openPort(const char *COM_name,speed_t speed);
int readData(unsigned char *buff,int size);
int sendData(unsigned char* buff,int len);
void closeCom(void);
void setRTS();
void clrRTS();


#endif // SERIAL_PORT_LINAPI_H_INCLUDED
