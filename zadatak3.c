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
int dodajIzaOsobe(Pozicija Head);
int dodajIspredOsobe(Pozicija Head);
int sortirajListu(Pozicija Head);    
int unesiListuUDatoteku(Pozicija Head, char imeDatoteke[]);
int citajIzDatoteke(char imeDatoteke[]);

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

    if(Head->sljedeci == NULL) {
        printf("Vasa lista je prazna! Pretrazivanje nije moguce!\n");
        return PRAZNA_LISTA;
    }
    
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

    if(Head->sljedeci == NULL) {
        printf("Lista je prazna! Brisnje nije moguce!\n");
        return PRAZNA_LISTA;
    }
    
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

int brisanjeCijeleListe(Pozicija Head) {

    Pozicija privremena = NULL;

    while(Head->sljedeci != NULL) {

        privremena = Head;
        Head = Head->sljedeci;

        free(privremena);
    }

    printf("Vasa lista je izbrisana!\n");

    return 0;
}

int dodajIzaOsobe(Pozicija Head) {

    Pozicija noviElement = NULL;
    char prezime[50];

    noviElement = (Pozicija)malloc(sizeof(Osoba));

    if(!noviElement) {
        printf("Neuspjesna alokacija!!\n");
        return NETOCNA_ALOKACIJA;
    }

    printf("Unesite prezime osobe iza koje zelite unjeti: ");
    scanf(" %[^\n]", prezime);

    while((Head->sljedeci != NULL) && ((strcmp(Head->prezime, prezime) != 0)))       
        Head = Head->sljedeci; 

    if(strcmp(Head->prezime, prezime) != 0) {       
        printf("Osoba ne postoji!\n");
        free(noviElement);
        return OSOBA_NE_POSTOJI;
    }
        
    else {        
        noviElement->sljedeci = Head->sljedeci;
        Head->sljedeci = noviElement;
    }

    printf("Ime: ");
    scanf(" %[^\n]", noviElement->ime);
    printf("\nPrezime: ");
    scanf(" %[^\n]", noviElement->prezime);
    printf("\nGodina rodjenja: ");
    scanf("%d", &(noviElement->godinaRodjenja));
    
    return 0;
}

int dodajIspredOsobe(Pozicija Head) {

    Pozicija noviElement = NULL;
    char prezime[50];

    noviElement = (Pozicija)malloc(sizeof(Osoba));

    if(!noviElement) {
        printf("Neuspjesna alokacija!!\n");
        return NETOCNA_ALOKACIJA;
    }

    printf("Unesite prezime osobe ispred koje zelite unjeti: ");
    scanf(" %[^\n]", prezime);

    while((Head->sljedeci->sljedeci != NULL) && ((strcmp(Head->sljedeci->prezime, prezime) != 0)))       
        Head = Head->sljedeci;                                                                          
        
    if(strcmp(Head->sljedeci->prezime, prezime) != 0) {       
        printf("Osoba ne postoji!\n");
        free(noviElement);
        return OSOBA_NE_POSTOJI;
    }
        
    else {       
        noviElement->sljedeci = Head->sljedeci;
        Head->sljedeci = noviElement;
    }

    printf("Ime: ");
    scanf(" %[^\n]", noviElement->ime);
    printf("\nPrezime: ");
    scanf(" %[^\n]", noviElement->prezime);
    printf("\nGodina rodjenja: ");
    scanf("%d", &(noviElement->godinaRodjenja));

    return 0;
}

int sortirajListu(Pozicija Head)
{
	Pozicija q = NULL;
	Pozicija preth_q = NULL;
	Pozicija pomocna = NULL;
	Pozicija kraj = NULL;
	while (Head->sljedeci != kraj)
	{
		preth_q = Head;
		q = Head->next;
		while (q->next != kraj)
		{
			if (strcmp(q->prezime, q->sljedeci->prezime) > 0)
			{
				pomocna = q->sljedeci;
				preth_q->sljedeci = pomocna;
				q->sljedeci = pomocna->sljedeci;
				pomocna->sljedeci = q;

				q = pomocna;
			}

			preth_q = q;
			q = q->sljedeci;
		}
		kraj = q;
	}
	ispisiListu(Head->sljedeci);
	return 0;
}

int unesiListuUDatoteku(Pozicija Head, char imeDatoteke[]) {

    FILE* fp = NULL;

    if(Head->sljedeci == NULL) {

        printf("Vasa lista je prazna! Unos u datoteku se prekida!\n");
        return PRAZNA_LISTA;
    }

    fp = fopen(imeDatoteke, "w");

    if(!fp) {
        printf("Datoteku nije moguce otvoriti!\n");
        return DATOTEKA_SE_NE_MOZE_OTVORITI;
    }

    while(Head->sljedeci != NULL) {
        Head = Head->sljedeci;

        fprintf(fp, "%s %s %d\n", Head->ime, Head->prezime, Head->godinaRodjenja);
    }

    printf("Vasa lista je unesena u datoteku!\n");

    fclose(fp);
   
    return 0;
}

int citajIzDatoteke(char imeDatoteke[]) {

    FILE* fp = NULL;
    char* linijaTeksta = NULL;
    int brojBajtova = 0;
    char* ime = NULL;
    char* prezime = NULL;
    int godinaRodjenja = 0;
    int brojac = 0;

    fp = fopen(imeDatoteke, "r");

    if(!fp) {
        printf("Datoteku nije moguce otvoriti!\n");
        return DATOTEKA_SE_NE_MOZE_OTVORITI;
    }

    linijaTeksta = (char*)malloc(1024 * sizeof(char));

    if(!linijaTeksta) {
        printf("Nije moguce alocirati memoriju!\n");
        return NETOCNA_ALOKACIJA;
    }

    ime = (char*)malloc(1024 * sizeof(char));

    if(!ime) {
        printf("Nije moguce alocirati memoriju!\n");
        return NETOCNA_ALOKACIJA;
    }

    prezime = (char*)malloc(1024 * sizeof(char));

    if(!prezime) {
        printf("Nije moguce alocirati memoriju!\n");
        return NETOCNA_ALOKACIJA;
    }


    while(!feof(fp)) {

        fgets(linijaTeksta, 1024, fp);

        brojac++;

        if(sscanf(linijaTeksta, "%s %s %d %n", ime, prezime, &godinaRodjenja, &brojBajtova) == 3) 
            printf("[%d] Ime: %s Prezime: %s Godina rodjenja: %d\n", brojac, ime, prezime, godinaRodjenja);
        
        linijaTeksta += brojBajtova;
    }
/*
    free(linijaTeksta);
    free(ime);
    free(prezime);
*/
    fclose(fp);

    return 0;
}

int meni(Pozicija Head) {
    
    int korisnikovUnos = 1;
    char prezime[50];
    char imeDatoteke[50];
    
    while (korisnikovUnos != 0) {    
        
        printf("1-Ispis liste\n");
        printf("2-Dodavanje na pocetak\n");
        printf("3-Dodavanje na kraj\n");
        printf("4-Brisanje elementa\n");
        printf("5-Pronadji element\n");
        printf("6-Dodaj iza osobe\n");
        printf("7-Dodaj ispred osobe\n");     
        printf("8-Sortiraj listu\n"); 
        printf("9-Unesi vezanu listu u datoteku\n");  
        printf("10-Procitaj Listu iz datoteke\n"); 
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

        else if(korisnikovUnos == 6)
            dodajIzaOsobe(Head);

        else if(korisnikovUnos == 7)
            dodajIspredOsobe(Head);

        else if(korisnikovUnos == 8)
            sortirajListu(Head);

        else if(korisnikovUnos == 9) {
            printf("Unesite ime datoteke: ");
            scanf(" %[^\n]", imeDatoteke);

            unesiListuUDatoteku(Head, imeDatoteke);
        }

        else if(korisnikovUnos == 10) {
            printf("Unesite ime datoteke: ");
            scanf(" %[^\n]", imeDatoteke);

            citajIzDatoteke(imeDatoteke);
        }

        else if(korisnikovUnos == 0)
            printf("Dovidjenja!\n");
            
        else
            printf("Netocan unos!\n");
            
        printf("\n\n");
    }

    //brisanjeCijeleListe(Head);    //funkcija crash-a program

    return 0;
}
