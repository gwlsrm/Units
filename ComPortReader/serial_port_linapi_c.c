#include "serial_port_linapi.h"

int F_ID = -1;
/*----------------------------------------------------------------------------
 Открыть COM порт
 COM_name: путь к устройству, например: /dev/ttyS0 или  /dev/ttyUSB0 - для USB
 speed: скорость, например: B9600, B57600, B115200
 ----------------------------------------------------------------------------*/
bool openPort(const char *COM_name,speed_t speed)
{
    F_ID = open(COM_name, O_RDWR | O_NOCTTY);
    if(F_ID == -1)
    {
        char *errmsg = strerror(errno);
        printf("%s\n",errmsg);
        return false;
    }
    struct termios options; /*структура для установки порта*/
    tcgetattr(F_ID, &options); /*читает пораметры порта*/

    cfsetispeed(&options, speed); /*установка скорости порта*/
    cfsetospeed(&options, speed); /*установка скорости порта*/

    options.c_cc[VTIME]    = 20; /*Время ожидания байта 20*0.1 = 2 секунды */
    options.c_cc[VMIN]     = 0; /*минимальное число байт для чтения*/


    options.c_cflag &= ~PARENB; /*бит четности не используется*/
    options.c_cflag &= ~CSTOPB; /*1 стоп бит */
    options.c_cflag &= ~CSIZE;  /*Размер байта*/
    options.c_cflag |= CS8;  /*8 бит*/

    options.c_lflag = 0;
    options.c_oflag &= ~OPOST; /*Обязательно отключить постобработку*/

    tcsetattr(F_ID, TCSANOW, &options); /*сохронения параметров порта*/

    return true;
}

/*----------------------------------------------------------------------------
 Прочитать данные из COM порта
 buff - буфер для принятых данных
 size - количество запрашиваемых байт
 ----------------------------------------------------------------------------*/
int readData(unsigned char *buff,int size)
{
    int n = read(F_ID, buff, size);
    if(n == -1)
    {
        char *errmsg = strerror(errno);
        printf("%s\n",errmsg);
    }
    return n;
}

/*----------------------------------------------------------------------------
 Отправить в COM порт данные
 buff - буфер данных для отправки
 size - количество отправляемых байт
 ----------------------------------------------------------------------------*/
int sendData(unsigned char* buff,int len)
{
    int n = write(F_ID, buff, len);
    if(n == -1)
    {
        char *errmsg = strerror(errno);
        printf("%s\n",errmsg);
    }
    return n;
}
/*----------------------------------------------------------------------------
 Закрыть COM порт
 ----------------------------------------------------------------------------*/
void closeCom(void)
{
    close(F_ID);
    F_ID = -1;
    return;
}
/*----------------------------------------------------------------------------
 Установить RTS
 ----------------------------------------------------------------------------*/
void setRTS()
{
    int status;
    ioctl(F_ID, TIOCMGET, &status);
    status |= TIOCM_RTS;
    ioctl(F_ID, TIOCMSET, &status);
}
/*----------------------------------------------------------------------------
Очистить RTS
 ----------------------------------------------------------------------------*/
void clrRTS()
{
    int status;
    ioctl(F_ID, TIOCMGET, &status);
    status &= ~TIOCM_RTS;
    ioctl(F_ID, TIOCMSET, &status);
}
