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
\version $Id: packet.h,v 1.4 2009-05-08 06:16:09 zamek Exp $

*/
#ifndef PACKET_H_INCLUDED
#define PACKET_H_INCLUDED

#define PREAMBLE_CHAR 'U'
#define PREAMBLE_COUNTS 5

#define MTU 1024    // maximal transmitting unit (maximalis packet adat meret )

/*! Vételi állapot */
typedef enum {
    /*! nincs még megkezdett keret */
    stNone,

    /*! már legalább egy 0x55 jött */
    st55,

    /*! 1-nek kell érkeznie */
    st1,
    /*! címnek kell érkeznie */
    stAddress,

    /*! parancsnak kell érkeznie*/
    stCmd,

    /*! adat hossz alsó byte-nak kell érkeznie*/
    stDLenLo,

    /*! adathossz felső byte-nak kell érkeznie*/
    stDLenHi,

    /*! adat byte-nak kell érkeznie*/
    stData,

    /*! crc alsó byte-nak kell érkeznie*/
    stCrcLo,

    /*! crc felső byte-nak kell érkeznie*/
    stCrcHi
    } PacketState;

/*! a keret adatai.
    Struktura http://www.lysator.liu.se/c/bwk-tutor.html#structure
*/
typedef struct {
    /*! address: a keret címzettje */
    char address;

    /*! a keret parancsa */
    char cmd;

    /*! a keretben lévő adatok hossza. Lehet 0 is! */
    int dLen;

    /*! a keret adata, ha dLen == 0, akkor NULL
        Pointer: http://www.lysator.liu.se/c/bwk-tutor.html#pointers
    */
    char *data;
} Packet;

/*! Egy csomag küldése a portra a megadott adatokkal
    crc-t számol a csomagra.
    @param fd a soros port kezelője
    @param address a cimzett
    @param cmd a parancs
    @param data a keretben leküldendő adat puffer címe NULL, ha nincs
    @param dLen: az adat puffer hossza, ha 0, nincs adat
    @return 0:hiba, 1=ok
*/
int sendPacket(int fd, unsigned char address, unsigned char cmd, unsigned char *data, int dLen);

/*! ellenőrzés vett csomagokra
    return: 0=nincs, !0 = van
 */
int isReceivePacket();

/*! az utolso vett packet felszabadítása
*/
void freePacket();

/*! a kovetkező helyes, vett csomag elkérése
    @return NULL=nincs , !NULL = van
*/
Packet *getNextPacket();

/*! Soros portról karakterek vétele és feldolgozása. Kernel signal IO aktiválja
    @param fd a soros port file leírója
*/
void receiveByte(int fd);

/*! Az összes vett keretek száma
    @return az érték
*/
int getAllPackets();

/*! A hibás keretek száma
    @return az érték
*/
int getErrorPackets();

/*! csomag egymásba csúszások száma
    @return az érték
*/
int getOverruns();

/*! bekapcsolva szándékosan hibás crc-vel küldi el a csomagokat */
void toggleErrorFlag();

/*! a hibás crc kapcsoló állapota
    @return 0:ki, !0: be
*/
int isErrorFlag();

#endif // PACKET_H_INCLUDED








