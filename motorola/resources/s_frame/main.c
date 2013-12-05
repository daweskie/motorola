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

/*! \mainpage
Hello,

Ha idáig jutottál. akkor valószínűleg érdekel a soros port kezelés C-ben,
vagy hozzám jársz ProgII/ProgIII-r(e/a).\n

A feladat:\n

Készítenünk kell egy programot, amely:\n
1. \b Kliens módban emulál egy mikrokontroller alapú mérésadatgyűjtőt, amely
   hőmérséklet és nyomás értékeket mér.\n

2. \b Master módban a fenti mérésadatgyűjtőről soros porton keresztül ciklikusan
   lekérdezi és kijelzi a mért értékeket.\n

A programot mindkét módban el lehet inditani, célszerűen két gépen, majd egy
nullmodem kábellel összekötve őket, ki lehet próbálni a működést.\n

A program indítása:

master módban: \b programnév \b clientaddress \b master \n
kliens módban: \b programnév \b address

az első paraméter master módban azt a klienscímet jelenti,
amelyet le kell kérdeznie, kliens módban pedig azt,
amelyre érkező keretekre válaszolnia kell.

a második paraméter, ha master akkor master módban, ha bármi más, akkor kliens módban indul a program.

A használható billentyűparancsok a következők:\n\n

    \b Esc: kilépés a programból\n
Kliens:\n
    \b e: hőmérséklet inkrementálása\n
    \b x: hőmérséklet dekrementálása\n
    \b r: nyomás inkrementálása\n
    \b c: nyomás dekrementálása\n
    \b h: hiba flag ki/be kapcsolása. Ha be van kapcsolva, akkor a kliens
        hibás crc-vel küldi el a kereteket a soros portra, hogy teszteljük
        a hibás átvitelt.\n\n

A kommunikáció a Motorola rádiós keretformátumot használja, ami a következőképpen
néz ki:\n

\b n* \b 0x55  (n>1) legalább 1 db 0x55 \n
\b 0xff \n
\b 1 \n
\b address: a keret címzettje 1 byte \n
\b cmd: a keret parancsa 1 byte \n
\b dLen: adathossz 2 byte, LITTLE ENDIAN formátumban
        ( http://en.wikipedia.org/wiki/Endianness )
        lehet 0 is!\n
\b data: a keret adatai ha dlen 0, akkor nincs\n
\b crc: 2 byte crc az atvitel hibaellenőrzésére
        http://en.wikipedia.org/wiki/Cyclic_redundancy_check\n

A ritkábban változó paramétereket a global.h tartalmazza.

Windows alatt a soros portokat \b COMn név alatt találod (0<n<255), \n
míg POSIX rendszereken (Unix,Linux) a fix soros portok a \b /dev/ttySn (0 <= n < 255), \n
míg az usb/soros átalakítók által szolgáltatott portok a \b /dev/ttyUSBn (0 <= n < 255) néven találhatók.\n

Ha meg akarod érteni a programot, akkor a main.c-t kezd el olvasni, majd soronként
próbáld megemészteni. A kommentek reményeim szerint sokat segíthetnek.
Persze a Kernighan-Ritchie C programming ismerete elengedhetetlen.

http://www.lysator.liu.se/c/bwk-tutor.html

Ha találsz egy include file-t, ami nem <> között van, hanem "" között,
pl. \#include "packet.h", akkor lépj át arra és olvasd azt is.
Ezekben nem csak az adott modul változói, hanem az általa
prolongált függvények szignatúrája is megtalálható, tehát tudhatod, hogy
melyik függvényt melyik modulban keresd.

Ha az include file végére értél, lépj vissza a hívó file-ba.

A html könyvtárban a Doxygen-nel készült dokumentációt találod.

Jó szórakozást/tanulást.

Emlékeztetőül:
RS 232 jelszintek:
\image html rs232.png

Modem vezérlés
\image html serial1.png

Segédanyagok, információk a soros kommunikációval kapcsolatban: \n
http://www.beyondlogic.org/serial/serial.htm \n
http://www.eeherald.com/section/design-guide/esmod8.html \n
http://www.zytrax.com/tech/layer_1/cables/tech_rs232.htm \n
http://www.easysw.com/~mike/serial/serial.html \n
http://msdn.microsoft.com/en-us/library/ms810467.aspx \n

A programfejlesztés változásait (ChangeLog) alább találod, a megjegyzésekkel. Ezt úgy tudod használni, hogy megnézed
az egyes dátumoknál, hogy mi változott, majd alatta a megjegyzésben azt, hogy mi a változás tárgya.\n
pl.

    \verbatim
2009-05-07 14:38  zamek <---- ekkor történt a módosítás

        * client.c, global.h, kb.c, packet.c, serial.c, serialframe.depend: <---- ezek a file-ok változtak
          Windows platform <---- ez az ok
    \endverbatim

\b Changelog:

    \include ChangeLog

*/

/*!
    \author Zamek
    \version $Id: main.c,v 1.5 2009-05-08 06:16:09 zamek Exp $
*/
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "serial.h"
#include "client.h"
#include "master.h"
#include "kb.h"
#include "display.h"

/*! usage, ha nincs argumentuma a programnak, akkor kiírja, hogy kell
használni.
    @param prgName a programot ezzel a névvel indították
*/
void usage(char *prgName) {
    print("Használat, master módban: %s <klienscím> master\n",prgName);
    print("Használat, kliens módban: %s <klienscím>\n",prgName);
}

/*! a program belépési pontja
az 1. paraméter cím,
        Master módban a kérdezett kliens címe,
        Kliens módban a saját cím
a 2. paraméter ha master, akkor master módban indul, ha nincs,
    vagy nem master, akkor kliens módban indul a program
*/
int main (int argc, char *argv[]) {
    if (argc == 1) {  // nincs elég argumentum
        usage(argv[0]); // tájékoztató
        exit (EXIT_SUCCESS);  // kilépés
    }

    display_init();

    int portHandle = serialInit(DEVICE); // a soros port megnyitása

    if (!portHandle)        // ha nem sikerült
        return EXIT_FAILURE;    // hibával kilépés

    char clientAddress = atoi(argv[1]); // az 1. paraméter int-é alakítása

    if (argv[2] && strcmp(argv[2], "master") == 0) // a 2. paraméter vizsgálata
        polling(clientAddress, portHandle); // master mód
    else
        clientProcess(clientAddress,portHandle);  // kliens mód

    serialClose();  // soros port bezárása
    close_display();
    return EXIT_SUCCESS;  // kilépés
}







