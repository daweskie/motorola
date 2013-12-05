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

/*! \file crc.c
CRC kalkulátor
    A CRC a keretek hiballenőrzésére szolgál.
    http://en.wikipedia.org/wiki/Cyclic_redundancy_check
*/

#include "crc.h"

#define WIDTH (8 * sizeof(Crc))
#define TOPBIT (1 << (WIDTH-1))

/*!
    átadott dLen hosszúságú data pufferre crc számítása
    @param data a puffer címe
    @param dLen a puffer hossza
    @return a számított crc
*/
Crc calcBuffer(char *data, int dLen) {
    Crc rmdr = 0;  // induló érték
    int bits;
    if (!data || !dLen) // a cím NULL pointer, vagy a puffer hossza 0
        return 0;

    char *begin = data; // a kezdőcím elmentése

    while (data-begin < dLen) {     // amíg a végére nem ér
        rmdr ^= ( *data << (WIDTH - 8));    // egy byte-tal balra léptet és kizáró vagy
        for (bits=8;bits >0;--bits)         // a felső 8 bit
            if (rmdr & TOPBIT)              // ha a legnagyobb súlyú bit 1
                rmdr = (rmdr << 1) ^ POLYNOMIAL;  // egyet léptet balra és kizáró vagy POLYNOMIAL
            else
                rmdr <<= 1;                 // ha a legnagyobb súlyú bit 0, egyet balra léptet
        data++;             // következő byte a pufferben
    }
    return rmdr;    // a számított crc
}

/*! byte-onkénti (on the fly) crc kalkuláció
    egy byte hozzáadása a crc-hez.
    @param crc a crc aktuális értéke
    @param b az aktuális byte
    @return a crc uj értéke
*/
int addCrcByte(Crc crc, unsigned char b) {
    int bits;
    crc ^= ( b << (WIDTH - 8));
    for (bits=8;bits >0;--bits)
        if (crc & TOPBIT)
            crc = (crc << 1) ^ POLYNOMIAL;
        else
            crc <<= 1;
    return crc;
}


/*! Crc értékek összehasonlítása
    @param crc1 az egyik crc értéke (pl. a vett keret küldött crc-je)
    @param crc2 a másik crc értéke  (pl. a keret vétele során byte-onként kalkulált crc)
    @return ha egyezik a kettő, akkor !0, ha nem, akkor 0*/
int checkCrc(Crc crc1, Crc crc2) {
    return crc1 == crc2;
}











