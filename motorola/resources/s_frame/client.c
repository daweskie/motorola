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

/*! \file client.c

\author Zamek
\version $Id: client.c,v 1.6 2009-05-08 06:16:09 zamek Exp $

Kliens mód. A soros portról a címére érkező keretekre válaszol, kezeli a billentyűzet parancsokat.

*/

#include <stdio.h>
#include "packet.h"
#include "serial.h"
#include "kb.h"
#include "display.h"

/* modul változók */

int clientPressure=0;    // Nyomas ertek
int clientTerm = 0;      // homerseklet ertek
char clientAddress;      // a sajat cimunk
int fileHandle;          // soros port kezeloje



/*! Ping parancsra(0) válasz */
void replyPing() {
    sendPacket(fileHandle, clientAddress, cmPing, NULL, 0);
}
/*! Hőmérséklet lekérdezés parancsra(1) válasz */
void replyTerm() {
    sendPacket(fileHandle,clientAddress,cmGetTerm, (unsigned char *) &clientTerm, sizeof(clientTerm));
}

/*! Nyomás lekérdezés parancsra(1) válasz */
void replyPressure() {
    sendPacket(fileHandle,clientAddress,cmGetPressure, (unsigned char *)&clientPressure,
                sizeof(clientPressure));
}

/*! státusz frissítése */
void refreshClientStatus() {
    print(
    "Hőmérséklet:%d, Nyomás:%d hiba flag:%s, össz.pckt:%d, hibás pckt:%d, overrun:%d\r",
            clientTerm, clientPressure,
            isErrorFlag() ? "be" : "ki",
            getAllPackets(), getErrorPackets(),getOverruns());
}

/*! Vett keret feldolgozása */
void processReceive() {
    Packet *packet = getNextPacket(); // az aktualis vett keret lekerese
    if (!packet)                      // valaki szorakozik NULL ertek
        return;

    if (packet->address == clientAddress) { // jo a cim, fel kell dolgozni
        switch (packet->cmd) {
            case cmPing : replyPing();   // ping parancs jott
                break;
            case cmGetTerm : replyTerm();  // homerseklet lekerdezes parancs jott
                break;
            case cmGetPressure : replyPressure();  // nyomas lekerdezes parancs jott
                break;
        }
    }
    freePacket();  // jelzes, hogy fel van dolgozva, johet a kovetkezo keret
}

/*! Kliens módban indították el a programot, várja a parancsokat és válaszol
    valamint a billentyűparancsok alapján állítja a nyomás, hőmérséklet és hiba flag-et.
    @param clientAddr az eszköz címe, csak az erre a címre érkezett parancsokra válaszol
    @param fd a soros port kezelője
*/
void clientProcess(char clientAddr, int fd) {
    char key=0;
    clientAddress = clientAddr;
    fileHandle = fd;
    while(1) {  // vegtelen ciklus
        receiveByte(fd);  // soros port olvasas

        if (isReceivePacket()) // van feldolgozásra váró keret?
           processReceive();    // dolgozzuk fel

        refreshClientStatus();  // frissites

        key = get_a_key(); // billentyu leutes ellenorzese

        switch (key) {
            case 0 : continue;
            case ESC : return;  // kilepes
            case 'e' :
            case 'E' : ++clientTerm;  // homerseklet novelese
                continue;
            case 'x' :
            case 'X' : --clientTerm;    // homerseklet csokkentese
                continue;
            case 'r' :
            case 'R' : ++clientPressure; // nyomas novelese
                continue;
            case 'c' :
            case 'C' : -- clientPressure; // nyomas csokkentese
                continue;
            case 'h' :
            case 'H' : toggleErrorFlag(); // hiba flag váltás
                continue;

        }
    } // while
}
