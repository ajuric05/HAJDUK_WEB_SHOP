#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DATOTEKA_SE_NE_MOZE_OTVORITI (-1)
#define NETOCNA_ALOKACIJA (-2)
#define PRAZNA_LISTA (-3)
#define OSOBA_NE_POSTOJI (-4)

struct _Polinom;
typedef struct _Polinom* Pozicija;
typedef struct _Polinom {
    int koeficijent;
    int eksponent;
    Pozicija slijedeci;
}Polinom;

int citanjeIzDoukumenta(char imeDokumenta[], Pozicija polinom1, Pozicija polinom2);
int unesiUListu(Pozicija polinom, Pozicija noviElement);
Pozicija kreirajElement(int koeficijent, int eksponent);
int zbrajanjePolinoma(Pozicija polinom1, Pozicija polinom2, Pozicija polinomRezultat);
int mnozenjePolinoma(Pozicija polinom1, Pozicija polinom2, Pozicija polinomRezultat);
int ispisiListu(Pozicija polinom);

int main() {

    Polinom polinom1 = {.koeficijent = 0, .eksponent = 0, .slijedeci = NULL};
    Polinom polinom2 = {.koeficijent = 0, .eksponent = 0, .slijedeci = NULL};
    Polinom polinom3 = {.koeficijent = 0, .eksponent = 0, .slijedeci = NULL};
    Polinom polinom4 = {.koeficijent = 0, .eksponent = 0, .slijedeci = NULL};
    char imeDokumenta[50];

    printf("Unesite ime dokumenta iz kojeg citamo polinome: ");
    scanf(" %[^\n]", imeDokumenta);

    citanjeIzDoukumenta(imeDokumenta, &polinom1, &polinom2);

    printf("\nPrije:\n");
    printf("\nPolinom 1: ");
    ispisiListu(&polinom1);
    printf("\nPolinom 2: ");
    ispisiListu(&polinom2);

    mnozenjePolinoma(&polinom1, &polinom2, &polinom3);

    printf("\nNakon:\n");
    printf("\nPolinom 1: ");
    ispisiListu(&polinom1);
    printf("\nPolinom 2: ");
    ispisiListu(&polinom2);

    zbrajanjePolinoma(&polinom1, &polinom2, &polinom4);

    printf("\n-------Mnozenje---------\n");
    ispisiListu(&polinom3);
    printf("\n-----Zbrajanje-------\n");
    ispisiListu(&polinom4);
    printf("\n");

    return 0;
}

int citanjeIzDoukumenta(char imeDokumenta[], Pozicija polinom1, Pozicija polinom2) {

    FILE* fp = NULL;
    int koef = 0;
    int eksp = 0;
    int brojBajtova = 0;
    char* redak = NULL;
    char statickiRedak[1024] = {0};
    Pozicija noviElement = NULL;

    fp = fopen(imeDokumenta, "r");

    if(!fp) {
        printf("Dokument se ne moze otvoriti!\n");
        return DATOTEKA_SE_NE_MOZE_OTVORITI;
    }

    redak = (char*)malloc(1024 * sizeof(char));

    if(!redak) {
        printf("Memorija za redak se ne moze alocirati!\n");
        return NETOCNA_ALOKACIJA;
    }

    fgets(statickiRedak, 1024, fp);

    redak = statickiRedak;

    while(strlen(redak) > 0) {

        sscanf(redak, "%d %d %n", &koef, &eksp, &brojBajtova);

        if(koef != 0) {
            noviElement = kreirajElement(koef, eksp);

            unesiUListu(polinom1, noviElement);

        }
        redak += brojBajtova;
    }

    fgets(statickiRedak, 1024, fp);

    redak = statickiRedak;

    while(strlen(redak) > 0) {

        sscanf(redak, "%d %d %n", &koef, &eksp, &brojBajtova);

        if(koef != 0){
            noviElement = kreirajElement(koef, eksp);

            unesiUListu(polinom2, noviElement);
        }
        redak += brojBajtova;
    }



    fclose(fp);

    return 0;
}

Pozicija kreirajElement(int koeficijent, int eksponent) {

    Pozicija noviElement = NULL;

    noviElement = (Pozicija)malloc(sizeof(Polinom));

    if(!noviElement) {
        printf("Memorija za novi element se ne moze alocirati!\n");
        return NULL;
    }

    noviElement->koeficijent = koeficijent;
    noviElement->eksponent = eksponent;
    noviElement->slijedeci = NULL;
    
    return noviElement;
}

int unesiUListu(Pozicija polinom, Pozicija noviElement) {

    if(polinom->slijedeci == NULL)
        polinom->slijedeci = noviElement;

    
    else {
        while(polinom->slijedeci && polinom->slijedeci->eksponent > noviElement->eksponent)
            polinom = polinom->slijedeci;
        if(polinom->slijedeci && polinom->slijedeci->eksponent == noviElement->eksponent){
            polinom->slijedeci->koeficijent += noviElement->koeficijent;
            free(noviElement);
        }
        else{
            noviElement->slijedeci = polinom->slijedeci;
            polinom->slijedeci = noviElement;
        }
    }

    return 0;
}

int ispisiListu(Pozicija polinom) {

    printf("Polinom: ");
    
    while (polinom->slijedeci != NULL) {

        polinom = polinom->slijedeci;
       
        if(polinom->slijedeci == NULL) {

            if(polinom->eksponent == 0)
                printf("%d", polinom->koeficijent);
            
            else
                printf("%dx^%d", polinom->koeficijent, polinom->eksponent);
        }

        else if(polinom->eksponent == 0)
            printf("%d + ", polinom->koeficijent);

        else
            printf("%dx^%d + ", polinom->koeficijent, polinom->eksponent);
    }

    return 0;
}

int mnozenjePolinoma(Pozicija polinom1, Pozicija polinom2, Pozicija polinomRezultat) {

    Pozicija noviElement = NULL;
    Pozicija privremena = polinom2;

    while(polinom1->slijedeci != NULL) { 

        polinom1 = polinom1->slijedeci;

        polinom2 = privremena;

        while(polinom2->slijedeci != NULL) {

            polinom2 = polinom2->slijedeci;

            noviElement = kreirajElement(polinom1->koeficijent * polinom2->koeficijent, polinom1->eksponent + polinom2->eksponent);

            unesiUListu(polinomRezultat, noviElement);
        }
        
    }

    return 0;
}

 int zbrajanjePolinoma(Pozicija polinom1, Pozicija polinom2, Pozicija polinomRezultat){  

    Pozicija temp;
    temp = polinom1;
    while(temp->slijedeci){
        unesiUListu(polinomRezultat, kreirajElement(temp->slijedeci->koeficijent, temp->slijedeci->eksponent));
        temp = temp->slijedeci;
    }
    temp = polinom2;
    while(temp->slijedeci){
        unesiUListu(polinomRezultat, kreirajElement(temp->slijedeci->koeficijent, temp->slijedeci->eksponent));
        temp = temp->slijedeci;
    }
    return 0;
 }