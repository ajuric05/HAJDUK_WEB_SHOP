#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DATOTEKA_SE_NE_MOZE_OTVORITI -1
#define NEMOGUCA_ALOKACIJA -2

struct _Lista;
typedef struct _Lista* Pozicija;
typedef struct _Lista{
    int broj;
    Pozicija sljedeci;
}Lista;

int citanjeIzDatoteke(char imeDatoteke[], Pozicija Stog);
int dodajNaPocetak(Pozicija Head, int broj);

int main(){



    return 0;
}

int citanjeIzDatoteke(char imeDatoteke[], Pozicija Stog){

    FILE* fp = NULL;
    int procitaniBroj = 0;
    int brojBajtova = 0;
    char* redak = NULL;

    fp = fopen(imeDatoteke, "r");

    redak = (char*)malloc(1024 * sizeof(char));

    if (!redak){
        printf("Memorija se ne moze alocirati");
        return NEMOGUCA_ALOKACIJA;
    }


    if(!fp) {
        printf("Dokument se ne moze otvoriti!\n");
        return DATOTEKA_SE_NE_MOZE_OTVORITI;
    }

    while(!feof(fp)) {

        fgets(redak, 1024, fp);

        if(sscanf(redak, "%d %n",&procitaniBroj, &brojBajtova) == 1){
            
        }
            
        
        redak += brojBajtova;
    }
    return 0;
}

int dodajNaPocetak(Pozicija Head, int broj) {

    Pozicija noviElement = NULL;

    noviElement = (Pozicija)malloc(sizeof(Lista));

    if(!noviElement) {
        printf("Neuspjesna alokacija!!\n");
        return NEMOGUCA_ALOKACIJA;
    }

    noviElement->broj = broj;

    noviElement->sljedeci = Head->sljedeci;
    Head->sljedeci = noviElement;

    return 0;
}
