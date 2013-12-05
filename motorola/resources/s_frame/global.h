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

/*! \file global.h

\author Zamek
\version $Id: global.h,v 1.5 2009-05-08 06:16:09 zamek Exp $

 Globális beállítások

Itt lehet a program működési környezetét beállítani. \n
Ezek: \n
    a soros kommunikáció paraméterei (port, baud rate, paritás, stb.) \n
    a használni kívánt platform (Windows, POSIX)

*/

#ifndef GLOBAL_H_INCLUDED
#define GLOBAL_H_INCLUDED

/*! a platform alapjan a hasznalni kivant soros port beallitasai */
#ifdef WIN32
    #include <windows.h>

    #define DEVICE "COM1"   // a használni kívánt soros port neve
    #define BAUD CBR_9600 // baud rate
    #define DATABITS 8      // adat bitek száma
    #define STOPBITS 1    // stop bitek száma
    #define PARITY NOPARITY     // paritás

#else
    #include <termios.h>

    enum Parity {none,even,odd};

    #define DEVICE "/dev/ttyUSB0"  // a használni kívánt soros port neve
    #define BAUD B9600          // baud rate
    #define DATABITS CS8            // adat bitek száma
    #define STOPBITS 1      // stop bitek száma
    #define PARITY none                 // paritás
#endif

/*! billentyu kodok */
#define ESC 0x1b  // esc-reŔ ki kell lepni a programbol

#endif // GLOBAL_H_INCLUDED
