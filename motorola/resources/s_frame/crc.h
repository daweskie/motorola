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
\version $Id: crc.h,v 1.4 2009-05-08 06:16:09 zamek Exp $

*/
/*! CRC kalkulátor
    A CRC a keretek hiballenőrzésére szolgál.
    http://en.wikipedia.org/wiki/Cyclic_redundancy_check
*/
#ifndef CRC_H_INCLUDED
#define CRC_H_INCLUDED

#include <stdint.h>

#define POLYNOMIAL 0xd8  // a crc algoritmus szerint ezzel kell kizáró vagy kapcsolatba
                         // hozni az 1 es biteketet

typedef uint16_t Crc;  // a crc adattípusa. Az algoritmus ebből számítja ki, hogy
                       // hany bites crc legyen uint16_t esetén 16 bites crc lesz

/*!
    átadott dLen hosszúságú data pufferre crc számítása
    @param data a puffer címe
    @param dLen a puffer hossza
    @return a számított crc
*/
Crc calcBuffer(char *data, int dLen);

/*! byte-onkénti (on the fly) crc kalkuláció
    egy byte hozzáadása a crc-hez.
    @param crc a crc aktuális értéke
    @param b az aktuális byte
    @return a crc uj értéke
*/
int addCrcByte(Crc crc, unsigned char b);

/*! byte-onkénti (on the fly) crc kalkuláció
    - a számított és kapott crc összehasonlítása,
    - a folyamatban lévő on the fly kalkuláció lezárása

    @param crc1 a kapott crc érték
    @param crc2 az összehasonlítandó érték
    @return 0: hiba
            !0: crc rendben
*/
int checkCrc(Crc crc1, Crc crc2);

#endif // CRC_H_INCLUDED
