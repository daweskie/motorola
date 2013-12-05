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
/*!
\author Zamek
\version $Id: serial.h,v 1.5 2009-05-08 06:16:09 zamek Exp $
*/
#ifndef SERIAL_H_INCLUDED
#define SERIAL_H_INCLUDED

#include "global.h"

/*! parancsok amelyekre válaszol a kliens
 cmPing:    a kliens létezését teszteli, a kliensnek válaszolnia kell egy adat nélküli cmPing kerettel
 cmGetTerm: az aktuális hőmérséklet lekérdezése a klienstől 4 byte-os integer LITTLE ENDIAN formátum
 cmGetPressure: az aktuális nyomás lekérdezése a klienstől 4 byte-os integer LITTLE ENDIAN formátum
*/
typedef enum {
    cmPing=0, cmGetTerm, cmGetPressure
} Cmd;

/*! soros port inicializálása
    @param device a kivánt eszköz neve
    @return 0:hiba !0: rendben, a megnyitott port kezelője
*/
int serialInit(char *device);

/*! a soros port lezárása */
void serialClose();

/*! olvasás a soros portról
    @param handler a soros port kezelője
    @param buffer a puffer, amibe be lehet olvasni a portról
    @param bufferLength a puffer hossza, ennél több karaktert nem lehet olvasni a portról
    @return a belovasott karakterek száma
*/
int readPort(int handler, unsigned char *buffer, int bufferLength);

/*! iras a soros portra
    @param handler a soros port kezelője
    @param buffer a puffer, amibol ki lehet küldeni a portra
    @param bufferLength a puffer hossza, ennél több karaktert nem lehet küldeni a portra
    @return a kiküldött karakterek száma
*/
int writePort(int handler, unsigned char *buffer, int bufferLength);


#endif // SERIAL_H_INCLUDED
