#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DATOTEKA_SE_NE_MOZE_OTVORITI (-1)
#define NETOCNA_ALOKACIJA (-2)
#define PRAZNA_LISTA (-3)
#define OSOBA_NE_POSTOJI (-4)

struct _Osoba;
typedef struct _Osoba* Pozicija;
typedef struct _Osoba{
    char ime[50];
    char prezime[50];
    int godinaRodjenja;
    Pozicija sljedeci;
}Osoba;

int meni(Pozicija Head);              
int dodajNaPocetak(Pozicija Head);  
int dodajNaKraj(Pozicija Head);     
int izbrisiElement(Pozicija Head);  
int pronadiElement(Pozicija Head, char prezime[]);  
int ispisiListu(Pozicija Head); 
int brisanjeCijeleListe(Pozicija Head);

int main() {

    Osoba Head = { .ime = {0}, .prezime = {0}, .godinaRodjenja = 0, .sljedeci = NULL};

    meni(&Head);

    return 0;
}

int dodajNaPocetak(Pozicija Head) {

    Pozicija noviElement = NULL;

    noviElement = (Pozicija)malloc(sizeof(Osoba));

    if(!noviElement) {
        printf("Neuspjesna alokacija!!\n");
        return NETOCNA_ALOKACIJA;
    }

    printf("Ime: ");
    scanf(" %[^\n]", noviElement->ime);
    printf("\nPrezime: ");
    scanf(" %[^\n]", noviElement->prezime);
    printf("\nGodina rodjenja: ");
    scanf("%d", &(noviElement->godinaRodjenja));

    noviElement->sljedeci = Head->sljedeci;
    Head->sljedeci = noviElement;

    return 0;
}

int dodajNaKraj(Pozicija Head) {

    Pozicija noviElement = NULL;

    noviElement = (Pozicija)malloc(sizeof(Osoba));

    if(!noviElement) {
        printf("Neuspjesna alokacija!!\n");
        return NETOCNA_ALOKACIJA;
    }

    printf("Ime: ");
    scanf(" %[^\n]", noviElement->ime);
    printf("\nPrezime: ");
    scanf(" %[^\n]", noviElement->prezime);
    printf("\nGodina rodjenja: ");
    scanf("%d", &(noviElement->godinaRodjenja));

    while (Head->sljedeci != NULL)
        Head = Head->sljedeci;
    
    Head->sljedeci = noviElement;
    noviElement->sljedeci = NULL;

    return 0;
}

int ispisiListu(Pozicija Head) {

    if(Head->sljedeci == NULL) {                            
                                                            
        printf("Vasa lista je trenutno prazna.\n");         
        return PRAZNA_LISTA;
    }

    while(Head->sljedeci != NULL) {

        Head = Head->sljedeci;
        printf("\nIme: %s\nPrezime: %s\nGodina rodjenja: %d", Head->ime, Head->prezime, Head->godinaRodjenja);        
    }

    return 0;
}

int pronadiElement(Pozicija Head, char prezime[]) {
    
    while((Head->sljedeci != NULL) && ((strcmp(Head->prezime, prezime) != 0)))
        Head = Head->sljedeci;
        
    if(strcmp(Head->prezime, prezime) != 0)
        printf("Osoba ne postoji!\n");
    else
        printf("\nIme: %s\nPrezime: %s\nGodina rodjenja: %d\n", Head->ime, Head->prezime, Head->godinaRodjenja);
    
    return 0;
}

int izbrisiElement(Pozicija Head) {
    
    Pozicija privremena = NULL;
    char prezime[50];
    
    printf("Unesite prezime za brisanje: ");
    scanf(" %[^\n]", prezime);
    
    while((Head->sljedeci->sljedeci != NULL) && ((strcmp(Head->sljedeci->prezime, prezime) != 0)))       
        Head = Head->sljedeci;                                                                          
        
    if(strcmp(Head->sljedeci->prezime, prezime) != 0) {
        
        printf("Osoba ne postoji!\n");
        return OSOBA_NE_POSTOJI;
    }
        
    else {
        
        privremena = Head->sljedeci;
        Head->sljedeci = Head->sljedeci->sljedeci;
        
        free(privremena);
    }
    
    return 0;
}

/*int brisanjeCijeleListe(Pozicija Head) {

    Pozicija privremena = NULL;

    while(Head->sljedeci != NULL) {

        privremena = Head;
        Head = Head->sljedeci;

        free(privremena);
    }

    printf("Vasa lista je izbrisana!\n");

    return 0;
}*/

int meni(Pozicija Head) {
    
    int korisnikovUnos = 1;
    char prezime[50];
    
    while (korisnikovUnos != 0) {    
        
        printf("1-Ispis liste\n");
        printf("2-Dodavanje na pocetak\n");
        printf("3-Dodavanje na kraj\n");
        printf("4-Brisanje elementa\n");
        printf("5-Pronadji element\n");
        printf("0-Izlaz\n");
        printf("Unos: ");
        
        scanf("%d", &korisnikovUnos);

        printf("\n\n");
        
        if(korisnikovUnos == 1)
            ispisiListu(Head);
            
        else if(korisnikovUnos == 2)
            dodajNaPocetak(Head);
            
        else if(korisnikovUnos == 3)
            dodajNaKraj(Head);
            
        else if(korisnikovUnos == 4) 
           izbrisiElement(Head);
        
        else if(korisnikovUnos == 5) {
            
            printf("Unesite prezime za trazenje: ");
            scanf(" %[^\n]", prezime);
            pronadiElement(Head, prezime);
        }
        
        else if(korisnikovUnos == 0)
            printf("Dovidjenja!\n");
            
        else
            printf("Netocan unos!\n");
            
        printf("\n\n");
    }

    //brisanjeCijeleListe(Head);   

    return 0;
    
}
