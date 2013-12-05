/*
   SerialFrame
   Soros kommunkáció bemutató szoftver
   Copyright (C) 2009. Zidarics Zoltán (zamek@vili.pmmf.hu)

   Ez egy szabad szoftver; terjeszthető illetve módosítható a GNU
   Általános Közreadási Feltételek dokumentumában leírtak szerint -- 2.
   vagy későbbi verzió --, melyet a Szabad Szoftver Alapítvány ad ki.

   Ez a program abban a reményben kerül közreadásra, hogy hasznos lesz,
   de minden egyéb GARANCIA NÉLKÜL, az eladhatóságra vagy valamely célra
   való alkalmazhatóságra való származtatott garanciát is beleértve.
   További részletekért lásd a GNU Általános Közreadási Feltételek
   dokumentumát.

   A programmal együtt kellett, hogy érkezzen egy példány a GNU
   Általános Közreadási Feltételek dokumentumából is. Ha mégsem akkor
   ezt a Szabad Szoftver Alapítványnak küldött levélben jelezni kell.

   A szabad szoftver alapítvány címe:
   Free Software Foundation, Inc.,
   59 Temple Place, Suite 330,
   Boston, MA  02111-1307  USA.
*/

/*! \file serial.c

\author Zamek
\version $Id: serial.c,v 1.5 2009-05-08 06:16:09 zamek Exp $

Soros port kezelo modul

plaform fuggo, POSIX es win32

*/

#include "serial.h"
#include "packet.h"
#include "global.h"

int portHandler;       // a megnyitott port kezeloje

#ifdef WIN32
    #include <windows.h>

    /*! soros port inicializalasa
        @param device a kivant eszkoz neve
        @return 0:hiba !0: rendben, a megnyitott port kezeloje
    */
    int serialInit(char *device) {
        DCB dcbSerialParams = {0};
        COMMTIMEOUTS timeouts = {0};

        if (!device)
            return 0;

        portHandler = CreateFile(device,
                GENERIC_READ | GENERIC_WRITE,
                0, 0, OPEN_EXISTING,
                FILE_ATTRIBUTE_NORMAL, 0);
        if (portHandler == INVALID_HANDLE_VALUE)
            return 0;

        dcbSerialParams.BaudRate = BAUD;
        dcbSerialParams.ByteSize = DATABITS;
        dcbSerialParams.StopBits = ONESTOPBIT;
        dcbSerialParams.Parity = NOPARITY;
        dcbSerialParams.fDtrControl = DTR_CONTROL_DISABLE;
        dcbSerialParams.fRtsControl = RTS_CONTROL_DISABLE;


        if (!SetCommState(portHandler, &dcbSerialParams))
            return 0;

        timeouts.ReadIntervalTimeout = 50;
        timeouts.ReadTotalTimeoutConstant = 50;
        timeouts.ReadTotalTimeoutMultiplier = 10;

        timeouts.WriteTotalTimeoutConstant = 50;
        timeouts.WriteTotalTimeoutMultiplier = 10;

        return SetCommTimeouts(portHandler, &timeouts)
            ?  portHandler : 0;
    }

    /*! a soros port lezarasa   */
    void serialClose() {
        CloseHandle(portHandler); // visszaallitjuk a soros regi allapotat
    }

    /*! olvasas a soros portrol
        @param handler a soros port kezeloje
        @param buffer a puffer, amibe be lehet olvasni a portrol
        @param bufferLength a puffer hossza, ennel tobb karaktert nem lehet olvasni a portrol
        @return a belovasott karakterek szama
    */
    int readPort(int handler, unsigned char *buffer, int bufferLength) {
        int dwBytesRead = 0;
        if (!ReadFile(handler, buffer, bufferLength, &dwBytesRead, NULL))
            return 0;
        return dwBytesRead;
    }

    /*! iras a soros portra
        @param handler a soros port kezeloje
        @param buffer a puffer, amibol ki lehet kuldeni a portra
        @param bufferLength a puffer hossza, ennel tobb karaktert nem lehet kuldeni a portra
        @return a kikuldott karakterek szama
    */
    int writePort(int handler, unsigned char *buffer, int bufferLength) {
        int dwBytesWritten = 0;
        if (!WriteFile(handler, buffer, bufferLength, &dwBytesWritten, NULL))
            return 0;
        return dwBytesWritten;
    }

#else  // #ifdef WIN32
    #include <termios.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <unistd.h>
    #include <fcntl.h>
    #include <sys/signal.h>
    #include <sys/types.h>
    #include <string.h>
    #include <curses.h>

    #define _POSIX_SOURCE 1         //POSIX compliant source

    struct termios oldtio; // a regi soros port beallitasokat tartalmazza, serialClose visszaallitja
    volatile int receivedChar;

    /*! a kernel vett karakter eseten itt lep be */
    void signal_handler_IO (int status) {
        receivedChar = 1;
    }

    /*! soros port inicializalasa
        @param device a kivant eszkoz neve
        @return 0:hiba !0: rendben, a megnyitott port kezeloje
    */
    int serialInit(char *device) {
        struct sigaction saio;
		struct termios newtio;
        receivedChar = 0;

        if (!device)
            return 0;

        portHandler = open(device, O_RDWR | O_NOCTTY | O_NONBLOCK);
        if (portHandler < 0) {
            perror(device);
            return 0;
        }

        saio.sa_handler = signal_handler_IO;
        sigemptyset(&saio.sa_mask);
        saio.sa_flags = 0;
        saio.sa_restorer = NULL;
        sigaction(SIGIO,&saio,NULL);

        fcntl(portHandler, F_SETOWN, getpid());
        fcntl(portHandler, F_SETFL, FASYNC);

        tcgetattr(portHandler,&oldtio);
        tcgetattr(portHandler,&newtio);

        newtio.c_cflag &= CBAUD;
        newtio.c_cflag |= (CLOCAL | CREAD);
        newtio.c_cflag &= ~CSIZE;
        newtio.c_cflag |= CS8;

        if (PARITY==none) {
            newtio.c_cflag &= ~PARENB;
            newtio.c_iflag |= IGNPAR;
            newtio.c_iflag &= ~(INPCK|ISTRIP);
        }
        if (PARITY==even) {
            newtio.c_cflag |= PARENB;
            newtio.c_cflag &= ~PARODD;
            newtio.c_iflag |= INPCK;
        }

        if (PARITY==odd) {
            newtio.c_cflag |= PARENB | PARODD;
            newtio.c_iflag |= INPCK;
        }

        newtio.c_iflag &= ~IUCLC;

        if (STOPBITS == 1)
            newtio.c_cflag &= ~CSTOPB;
        else
            newtio.c_cflag |= CSTOPB;

        newtio.c_cflag &= ~CRTSCTS;

        newtio.c_oflag = ~OPOST;
        newtio.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
        newtio.c_cc[VMIN]=1;
        newtio.c_cc[VTIME]=0;

        cfsetispeed(&newtio, BAUD);

        tcflush(portHandler, TCIFLUSH);
        tcsetattr(portHandler,TCSANOW,&newtio);

        return portHandler;
    }

    /*! a soros port lezarasa   */
    void serialClose() {
        tcsetattr(portHandler, TCSANOW, &oldtio); // visszaallitjuk a soros regi allapotat
        close(portHandler); // port lezarasa
    }

    /*! olvasas a soros portrol
        @param handler a soros port kezeloje
        @param buffer a puffer, amibe be lehet olvasni a portrol
        @param bufferLength a puffer hossza, ennel tobb karaktert nem lehet olvasni a portrol
        @return a belovasott karakterek szama
    */
    int readPort(int handler, unsigned char *buffer, int bufferLength) {
        return read(handler, buffer, bufferLength);
    }

    /*! iras a soros portra
        @param handler a soros port kezeloje
        @param buffer a puffer, amibol ki lehet kuldeni a portra
        @param bufferLength a puffer hossza, ennel tobb karaktert nem lehet kuldeni a portra
        @return a kikuldott karakterek szama
    */
    int writePort(int handler, unsigned char *buffer, int bufferLength) {
        return write(handler, buffer, bufferLength);
    }

#endif // #ifdef WIN32
