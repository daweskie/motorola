#ifndef HIGHLEVEL_H_INCLUDED
#define HIGHLEVEL_H_INCLUDED

/**
 Sorosporkezelo
*/

// i soros
#include <sys/queue.h>

struct adat;

typedef void hl_fogadott_karakter(struct adat *hl_adat); //fogadott karaktereket kezelo típus

typedef int hl_elkuldott_karakter(struct adat *hl_adat, //elküldött adatokat kezelő típus
                int cim, int parancs, char *buff, int adat_hossz);


/**
    Általános keretnek a formátuma
*/
struct keret { // keret strukturaja
    int cim;
    int parancs;
    int adat_hossz;
    char *anyag;
    int ervennyesseg;
    TAILQ_ENTRY(keret) next;
};

struct adat { // adatok strukturaja
    char *soros_azonosito; //serial csatorna neve

    hl_fogadott_karakter *fogadott_karakter_k; //karakterek fogadása és egyesítése

    hl_elkuldott_karakter *kuldott_karakter_k; // keret küldése

    int hibas_keret; //összes kerethiba

    int tul_cs; //összes túlcsordulás

    int max_keret; //maximum beérkező keretek száma

    int mtu; // max keretméret

    int be_keret; //összes beérkezett keret száma

    int ki_keret; // összes elküldött keret száma

    TAILQ_HEAD(queuehead, keret) frame_queue; //keretek sorbanállási érvényességi ideje

    TAILQ_HEAD(poolhead, keret) frame_pool; // fel nem használt keretek számára fenttartott hely

    void *privi; // magánadatok helye a keretkezelőknek
};

/**
    high level soros modul
    -soros_azonosito | asznált soros csatorna neve
    -fogadott_karakter_k | karakterfogado funkcio cime
    -kuldott_karakter_k | keretkuldo funkcio cime
    -max_keret | beerkezo keretek sormérete
    -mtu | keretek maximális adatmérete (byte)
*/
struct adat *Init(char *soros_azonosito,l_fogadott_karakter fogadott_karakter_k,
                            hl_elkuldott_karakter kuldott_karakter_k,
                            int max_keret,int mtu);


int bezar(struct adat *hl_adat); //soros modul bezárása

int hozzaadfogadottkeret(struct adat *hl_adat,struct keret *hl_keret);


//


struct keret *kovetkezokeret(struct adat *hl_adat);

int keretkuldes(struct adat *hl_adat,
                   int cim, int parancs, char *buff, int buff_hossz);

struct keret *ujkeret(struct adat *hl_adat);

void visszakeret(struct adat *hl_adat, struct keret *hl_keret);

#endif // HIGHLEVEL_H_INCLUDED
