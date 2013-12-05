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


/*! \file master.c

\author Zamek
\version $Id: master.c,v 1.5 2009-05-08 06:16:09 zamek Exp $

Master mód. Ciklikusan lekérdezi a mért értékeket, ellenőrzi a billentyűzetet és
feldolgozza a beérkező válaszcsomagokat ESC-re kilép
 */
#include <stdio.h>
#include "serial.h"
#include "packet.h"
#include "kb.h"
#include "display.h"

/* modul valtozok */
char clientAddress;
int requestCounter=0;
int answerCounter=0;
int requestType=0;
int fileHandle;
int serverTerm=0;
int serverPressure = 0;

/*! A következő kérés leküldése a kliensnek. Tesztelési célokból az összes parancsot ciklikusan leküldi.
A következő parancs kiváalasztása modulo módszerrel történik (az aktuális sorszám növelése után
modulo az parancsok számával).

*/
void sendRequest() {
    requestType = (requestType + 1) % (cmGetPressure+1); // a következő parancs kiszámítása

    ++requestCounter;  // kérések számának növelése

    switch (requestType) {
        case 0: sendPacket(fileHandle, clientAddress, cmPing, NULL, 0); // ping parancs
            return;
        case 1: sendPacket(fileHandle, clientAddress, cmGetTerm, NULL, 0); // hőmérséklet lekérése
            return;
        case 2: sendPacket(fileHandle, clientAddress, cmGetPressure, NULL, 0); // nyomás lekérése
            return;
    }
}

/*! status sor frissítése, a sor végén \\r van, igy marad a kurzor a sorban*/
void refreshServerStatus () {
 print(
"Hőmérséklet:%d, Nyomás:%d kérések:%d, válaszok:%d összes packet:%d, hibás packet:%d, overrun:%d\r",
            serverTerm, serverPressure, requestCounter, answerCounter,
            getAllPackets(), getErrorPackets(),getOverruns());
}

/*! egy válasz csomag feldolgozása*/
void processReceived() {
    Packet *packet = getNextPacket();
    if (!packet)        // NULL pointer, szorakoznak velunk
        return;
    if (packet->address == clientAddress) {    // errol a cimrol vartuk a valaszt
        ++answerCounter;
        switch (packet->cmd) {
            case cmPing : break;                // ping valasz, nincs teendo
            case cmGetTerm : serverTerm = (int) (*packet->data);  // az ertek int, a *data viszont char
                break;
            case cmGetPressure : serverPressure = (int) (*packet->data); // tipuskenyszer
                break;
        }
    }
    freePacket(); // jellezzuk, hogy feldolgoztuk az utolso csomagot
}

/*! Master módban ciklikusan lekérdezi a mért értékeket, ellenőrzi a billentyűzetet és
feldolgozza a beérkező válaszcsomagokat ESC-re kilép
    @param clientAddr a kérdezendő kliens címe
    @param fd a használható soros port kezelője
*/
void polling(char clientAddr, int fd) {
    char key;
    clientAddress = clientAddr;
    fileHandle = fd;
    while (1) {         // Végtelen ciklus
        sendRequest();  // a következő kérés kiküldése

        key = get_a_key();  // billentyű leütés ellenőrzése 0:nincs, !0:a kar. kódja

        switch (key) {
            case ESC:return;    // ESC, ki akar lépni
        }

        refreshServerStatus();  // status sor frissítás

        receiveByte(fd);

        if (isReceivePacket())  // új csomag ellenőrzés
            processReceived();  // van új csomag, fel kell dolgozni
    }
}








