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

/*! \file packet.c keret kezelő függvények

\author Zamek
\version $Id: packet.c,v 1.7 2009-05-08 06:16:09 zamek Exp $

A soros portról érkező karaktereket dolgozza fel. Adminisztrálja a keret
állapotát és előállítja a következő crc helyes keretet. Statisztikai adatokat gyűjt a
vett keretek számáról (hibás/hibátlan)
*/
#include <stdlib.h>
#include <stdio.h>

#include "packet.h"
#include "macros.h"
#include "crc.h"
#include "serial.h"
#include "global.h"

// modul valtozok
volatile int packetValid=0;          // 0: nincs hasznalhato packet
int dIndex,                 // adat index
    overruns=0,             // packet "egymasbacsuszas"
    errorCounter=0,         // hibas packet szamlalo
    packetCounter=0,        // osszes packet szamlalo
    errorFlag = 0;          // hibas keret kuldes ki/be kapcsoloja

PacketState currentState = stNone; // veteli status

Packet *currentReceive = NULL,      // veteli packet ide erkeznek a karakterek
       *currentPacket = NULL;       // ebbol megy a feldolgozas

Crc recCrc,                   // a vett crc
    ofCrc;                    // a ropteben kalkulalt crc

/*! Egy csomag küldése a portra a megadott adatokkal
    crc-t számol a csomagra.
    @param fd a soros port kezelője
    @param address a cimzett
    @param cmd a parancs
    @param data a keretben leküldendő adat puffer címe NULL, ha nincs
    @param dLen az adat puffer hossza, ha 0, nincs adat
    @return 0:hiba, 1=ok
*/
int sendPacket(int fd, unsigned char address, unsigned char cmd, unsigned char *data, int dLen) {
    int i;
    Crc crc;
    unsigned char preamble=PREAMBLE_CHAR,
         ff = 0xff,one = 1,
         sc;
    if (fd < 0 || (dLen > 0 && !data))
        return 0;

    for (i=0;i<PREAMBLE_COUNTS;i++)
        writePort(fd, &preamble, 1); // n*0x55 kiküldés

    writePort(fd,&ff,1);         // 0xff kiküldés
    writePort(fd,&one,1);        // 1 kiküldés

    crc = 0;                     // CRC kalkuláció a címtől indul
    crc = addCrcByte(crc, address);
    writePort (fd,&address,1);   // cim kiküldés
    crc = addCrcByte(crc, cmd);
    writePort(fd,&cmd,1);        // Prancs kiküldés
    sc = dLen & 0xff;            // adathossz alsó byte
    crc = addCrcByte(crc, sc);
    writePort(fd, &sc, 1);       // adathossz alsó byte kiküldés
    sc = (dLen >> 8) & 0xff;     // adathossz felső byte
    crc = addCrcByte(crc, sc);
    writePort(fd, &sc, 1);       // adathossz felső byte kiküldés
    if (dLen > 0)                // ha van adat
        for (i=0;i<dLen;i++,data++) {
            crc = addCrcByte(crc, *data);
            writePort (fd,data,1);  // *data kiküldés
        }

    if (errorFlag) {    // szándékosan rossz crc-vel küldi el
        writePort(fd, &ff, 1);
        writePort(fd, &ff, 1);
    }
    else {
        sc = crc & 0xff;            // crc alsó byte
        writePort(fd, &sc, 1);      // crc alsó byte kiküldés
        sc = (crc >> 8) & 0xff;     // crc felső byte
        writePort(fd, &sc, 1);      // crc felső byte kiküldés
    }
    #ifdef POSIX
        tcflush(fd, TCIFLUSH);          // a pufferek ürítése
    #endif
    return 1;
}

/*! Egy új keret dinamikus allokálása */
Packet *createPacket(char addr) {
    Packet *result;
    packetValid =0;                     // nincs használható keret
    MALLOC(result, sizeof(Packet));     // keret allokálás
    result->address=addr;               // mezők feltöltése kezdeti értékkel
    result->dLen = 0;                   // nincs gondoskodó nagymama!
    result->data = NULL;
    return result;
}

/*! az utolso vett packet felszabadítása */
void freePacket() {
    if (currentPacket) {  // van allokalt packet
        if (currentPacket->data)  // van adat is a packet-ben
            FREE(currentPacket->data);
        FREE(currentPacket);
    }
    packetValid = 0;
}

/*! Soros portról karakterek vétele és feldolgozása. Kernel signal IO aktiválja
    A keretfelismerés folyamatábrája:
    \image html serial.png

    @param fd a soros port file leírója
*/
void receiveByte(int fd) {
    unsigned char c;

    if (fd <=0)
        return;

    while (readPort(fd,&c,1)) {
        switch (currentState) {

            case stNone :               // vár keret kezdetre
                if (c == PREAMBLE_CHAR)
                    currentState = st55;
                continue;

            case st55 :                 // legalább 1 0x55 jött
                if (c == PREAMBLE_CHAR) // már az n. 0x55 jött
                    continue;
                if (c == 0xff) {        // 0xff, váltás st1
                    currentState = st1;
                    continue;
                }
                else
                    break;              // 0x55 után nem 0xff jött, hiba

            case st1:                   // 1-et var
                if (c==1) {
                    ofCrc = 0;          // crc inicializálása
                    currentState = stAddress;
                    packetCounter++;    // egy packet kezdet
                    continue;
                }
                else
                    break;              // 0xff után nem 1 jött, hiba

            case stAddress:             // cimet var
                if (!currentReceive) {  // nincs fuggo packet
                    ofCrc = addCrcByte(ofCrc, c);  // a cimtől kezdődik a crc számítás
                    currentReceive = createPacket(c);
                    currentState = stCmd;
                    continue;
                }
                else                    // van függő keret, amelyet még nem dolgoztak fel
                    overruns++;         // hibaszámláló növelés és új keret-re várakozás
                break;

            case stCmd :                // parancsra vár
                ofCrc = addCrcByte(ofCrc, c);  // crc-hez hozzáadja
                currentReceive->cmd = c;        // a keretbe letárolja
                currentState = stDLenLo;
                continue;

            case stDLenLo :                     // adathossz alsó byte-ra vár
                ofCrc = addCrcByte(ofCrc, c);   // crc-hez hozzáadja
                currentReceive->dLen = (c & 0xff); // letárolja
                currentState = stDLenHi;
                continue;

            case stDLenHi :                     // adathossz felső byte-ra vár
                ofCrc = addCrcByte(ofCrc, c);   // crc-hez hozzáadja
                currentReceive->dLen |= (c & 0xff) << 8; // letárolja a felső byte helyre
                dIndex = 0;
                if (currentReceive->dLen > 0) {  // van adat
                    if (currentReceive->dLen <= MTU) { // adathossz jo
                        MALLOC(currentReceive->data,currentReceive->dLen);
                            // a hossznal megfelelő mennyiségű memória allokálása a keret data mezőjébe
                        currentState =  stData;
                    }
                    else                    // tul nagy adathossz!
                        break;

                }
                else  // nincs adat, crc jön
                    currentState =  stCrcLo;
                continue;

            case stData :
                ofCrc = addCrcByte(ofCrc, c);   // crc-hez hozzáadja
                *((currentReceive->data)+dIndex) = c;   // letárolja és előállítja a következő byte cjmét
                if (++dIndex >= currentReceive->dLen)   // lesz még adat
                    currentState = stCrcLo;             // adat vége, crc jön
                continue;

            case stCrcLo :              // crc alsó byte-ra vár
                recCrc = (c & 0xff);    // eltárolja
                currentState = stCrcHi;
                continue;

            case stCrcHi :              // crc felső byte-ra vár
                recCrc |=( c & 0xff) << 8;       // a felső byte-ra eltárolja
                if (checkCrc(recCrc, ofCrc)) {  // egyezik a vett crc a számítottal?
                    currentPacket = currentReceive; // eltrolja az új jó keretet
                    currentReceive = NULL;          // a vételi keretet törli
                    packetValid = 1;                // jo a keret
                    currentState = stNone;          // jöhet a következő
                    return;
                }
                break; // hibás a crc
        }
// hiba ág, akkor ér ide, ha valami hiba van break ágak.
        currentState = stNone;  // új keretet kezd
        if (currentReceive) {   // ha a keret vétele már elkezdődött és memória foglalás is történt
            if (currentReceive->data)  // ha adat is volt a megkezdett keretben
                FREE(currentReceive->data); // felszabadítja az adat területet
            FREE(currentReceive);           // felszabadítja a megkezdett keretet
            currentReceive = NULL;          // nincs megkezdett keret
        }
        ++errorCounter;             // hibás keret számláló növelése
    }
}

/*! ellenőrzés vett keretekre
    return: 0=nincs, !0 = van
 */
int isReceivePacket() {
    return packetValid && currentPacket != NULL;
}

/*! a következő helyes, vett keret elkérése */
Packet *getNextPacket() {
    return packetValid ? currentPacket : NULL;
}

/*! Az összes vett keretek számának lekérése */
int getAllPackets() {
    return packetCounter;
}

/*! a hibás keretek számának lekérése */
int getErrorPackets() {
    return errorCounter;
}

/*! a feldolgozás közben érkező (ezért eldobott) keretek számának lekérése */
int getOverruns() {
    return overruns;
}

/*! bekapcsolva szándékosan hibás crc-vel küldi el a csomagokat */
void toggleErrorFlag() {
    errorFlag = 1 - errorFlag;
}

/*! a hibás crc kapcsoló állapota
    @return 0:ki, !0: be
*/
int isErrorFlag() {
    return errorFlag;
}
