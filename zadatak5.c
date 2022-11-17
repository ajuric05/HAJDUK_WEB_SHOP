#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NEMOGUCA_ALOKACIJA -1
#define DATOTEKA_SE_NE_MOZE_OTVORITI -2
#define MAX 1024

struct _Lista;
typedef struct _Lista* Pozicija;
typedef struct _Lista{
    double broj;
    Pozicija sljedeci;
}Lista;

int dodajNaPocetak(Pozicija Head, double broj);
int citanjeIzDatoteke(char imeDatoteke[], Pozicija Stog);
int dodajIza(Pozicija Liste, Pozicija noviElement);
Pozicija stvoriNoviElement(double broj);
int izbrisiSveElemente(Pozicija Stog);
int izbrisiIza(Pozicija Head);
int izracunajPostfix(Pozicija Stog, char operator);
int Pop(Pozicija Stog, double* operator);
int ispisiListu(Pozicija Head);

int main(){

    char imeDatoteke[50];
    Lista Stog = { .broj = 0, .sljedeci = NULL};

    printf("Unesite ime datoteke iz koje zelite procitati postfix: \n");

    scanf(" %s", imeDatoteke);

    citanjeIzDatoteke(imeDatoteke, &Stog);

    return 0;
}

int citanjeIzDatoteke(char imeDatoteke[], Pozicija Stog){

    FILE* fp = NULL;
    double procitaniBroj = 0;
    int brojBajtova = 0;
    char* redak = NULL;
    int vrijednostFunkcije = 0;
    char operator=0, pomocniRedak[MAX] = { 0 };

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

    fgets(pomocniRedak, 1024, fp);

    printf("\nVas postfix: %s\n", pomocniRedak);

    redak = pomocniRedak;

    while(strlen(redak) > 0) {

        vrijednostFunkcije = sscanf(redak, "%lf %n", &procitaniBroj, &brojBajtova);

        if(vrijednostFunkcije == 1){

            vrijednostFunkcije = dodajNaPocetak(Stog, procitaniBroj);

            if (vrijednostFunkcije != 0)
                izbrisiSveElemente(Stog);
        }
        else{

            sscanf(redak, " %c %n", &operator, &brojBajtova);

            vrijednostFunkcije = izracunajPostfix(Stog, operator);

            if (vrijednostFunkcije != 0)
                izbrisiSveElemente(Stog);  
        }

        redak += brojBajtova;
    }

    printf("Rezultat Stoga:\n ");
    ispisiListu(Stog);

    fclose(fp);

    return 0;
}

Pozicija stvoriNoviElement(double broj)
{
	Pozicija noviElement = NULL;

	noviElement = (Pozicija)malloc(sizeof(Lista));

	if (!noviElement) {

		printf("Nije moguce alocirati trazenu memoriju!\n");
		return NULL;
	}

	noviElement->broj = broj;
	noviElement->sljedeci = NULL;

	return noviElement;
}

int dodajNaPocetak(Pozicija Head, double broj){

    Pozicija noviElement = NULL;

    noviElement = stvoriNoviElement(broj);

	if (!noviElement) {

		printf("Novi element nije moguce napraviti!\n");
		return EXIT_FAILURE;
	}

    dodajIza(Head, noviElement);

    return 0;
}

int dodajIza(Pozicija Liste, Pozicija noviElement){

    noviElement->sljedeci = Liste->sljedeci;
    Liste->sljedeci = noviElement;

    return 0;
}

int izbrisiIza(Pozicija Head){

    Pozicija privremena = NULL;

        privremena = Head->sljedeci;

        if(!privremena)
            return EXIT_FAILURE;

        Head->sljedeci = privremena->sljedeci;

        free(privremena);

    return EXIT_SUCCESS;
}

int izbrisiSveElemente(Pozicija Stog) {

	while (Stog->sljedeci != NULL) {

		izbrisiIza(Stog);
	}

	return EXIT_SUCCESS;
}

int Pop(Pozicija Stog, double* operator){

	if (Stog->sljedeci == NULL){

		printf("Vas postfix nije ispravan!\n");

		return EXIT_FAILURE;
	}

	*operator = Stog->sljedeci->broj;

    izbrisiIza(Stog);

	return 0;
}

int ispisiListu(Pozicija Head){

    while(Head->sljedeci != NULL){
        Head = Head->sljedeci;

        printf("%.2f\n", Head->broj);
    }

    return 0;
}

int izracunajPostfix(Pozicija Stog, char operator){

	double operator1 = 0;
	double operator2 = 0;
	int status = 0;
    double rezultat = 0;

	status = Pop(Stog, &operator2);
	if (status != 0)
		return -1;

	status = Pop(Stog, &operator1);
	if (status != 0)
		return -1;

	switch (operator) {

		case '+':
			rezultat = operator1 + operator2;
			break;

		case '-':
			rezultat = operator1 - operator2;
			break;

		case '*':
			rezultat = operator1 * operator2;
			break;

		case '/':
			if (operator2 == 0) {

				printf("Nije moguce dijeliti sa 0!\n");

				return EXIT_FAILURE;
			}

			else {
				rezultat = operator1 / operator2;
			    break;
            }

		default:
			break;
	}

    dodajNaPocetak(Stog, rezultat);

    return EXIT_SUCCESS;
}