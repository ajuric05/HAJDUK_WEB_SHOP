#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

#define MAX (1024)


struct _Direktorij;
typedef struct _Direktorij* Pozicija;
typedef struct _Direktorij {

	char ime[MAX];
	Pozicija Sibling;
	Pozicija Dijete;
}Direktorij;

struct _Stog;
typedef struct _Stog* pozicijaStog;
typedef struct _Stog {

	Pozicija Dir;
	pozicijaStog Slijedeci;
}Stog;

//main  /
Pozicija kreirajNoviElement(char ime[]);    //
Pozicija unesiNoviElementUStablo(Pozicija Root, Pozicija noviElement);      //
pozicijaStog noviElementStoga(Pozicija elementDirektorija);     //
int ispisPoddirektorija(Pozicija Root);     //  
int Push(pozicijaStog Head, pozicijaStog noviElement);      //
Pozicija Pop(pozicijaStog Head, Pozicija trenutniClan);     //
Pozicija idiUPoddirektorij(Pozicija trenutniDir, char ime[], pozicijaStog Head);    //
int menu(Pozicija Root);

int main() {

    Direktorij korijenskiDirektorij = {.ime = "korijen", .Sibling = NULL, .Dijete = NULL};
    Pozicija korijen = &korijenskiDirektorij;

    menu(korijen);

    return 0;
}

Pozicija kreirajNoviElement(char ime[]) {

    Pozicija noviElement = NULL;

    noviElement = (Pozicija)malloc(sizeof(Direktorij));

    if(!noviElement) {

        printf("Memorija za novi element se ne moze alocirati!\n");
        return NULL;
    }

    strcpy(noviElement->ime, ime);
    noviElement->Dijete = NULL;
    noviElement->Sibling = NULL;

    return noviElement;
}

pozicijaStog noviElementStoga(Pozicija elementDriektorija) {
     
    pozicijaStog noviElement = NULL;

    noviElement = (pozicijaStog)malloc(sizeof(Stog));

    if(!noviElement) {

        printf("Memorija za novi element se ne moze alocirati!\n");
        return NULL;
    }

    noviElement->Dir = elementDriektorija;
    noviElement->Slijedeci = NULL;

    return noviElement;
}

Pozicija unesiNoviElementUStablo(Pozicija Root, Pozicija noviElement) {

    if(!Root)       //stablo prazno, samo vrati noviElement
        return noviElement;

    if(strcmp(Root->ime, noviElement->ime) < 0)
        Root->Sibling = unesiNoviElementUStablo(Root->Sibling, noviElement);
    
    else if(strcmp(Root->ime, noviElement->ime) > 0) {

        noviElement->Sibling = Root;
        return noviElement;
    }
    
    return Root;
}

int Push(pozicijaStog Head, pozicijaStog noviElement) {

    noviElement->Slijedeci = Head->Slijedeci;       //unos jedan iza drugoga
    Head->Slijedeci = noviElement;

    return 0;
}

Pozicija Pop(pozicijaStog Head, Pozicija trenutniClan) {

    pozicijaStog prviElement = NULL;
    Pozicija privremena = NULL;

    prviElement = Head->Slijedeci;

    if(!prviElement) {      

        printf("Ne postoji 'parent' direktorij ovoga direktorija!\n");
        return trenutniClan;
    }

    privremena = prviElement->Dir;

    Head->Slijedeci = prviElement->Slijedeci;
    free(prviElement);

    return privremena;
}

int ispisPoddirektorija(Pozicija Root) {

    Pozicija privremena = NULL;

    privremena = Root->Dijete;

    while(privremena) {

        printf(" %s\n", privremena->ime);
        privremena = privremena->Sibling;
    }

    return 0;
}

Pozicija idiUPoddirektorij(Pozicija trenutniDir, char ime[], pozicijaStog Head) {

    Pozicija privremena = NULL;
    pozicijaStog noviElement = NULL;

    privremena = trenutniDir->Dijete;


    while(privremena && strcmp(privremena->ime, ime))
        privremena = privremena->Sibling;


    if(privremena == NULL) {    //ostajemo u istom dir jer nismo nasli dir sa trazeni imenom

        printf("Ne postoji direktorij sa imenom: %s\n", ime);
        return trenutniDir;
    }

    else {

        noviElement = noviElementStoga(trenutniDir);
        Push(Head, noviElement);
        return privremena;
    }

    return privremena;
}

int menu(Pozicija korijen) {

    int brojNaredbe = 0;
    char ime[MAX] = { 0 };
    Pozicija noviDirektorij = NULL;

    Pozicija trenutniDirektorij = korijen;

    Stog Head = {.Dir = NULL, .Slijedeci = NULL};
    pozicijaStog stog = &Head;

    while(brojNaredbe != 5) {

        printf("1-md (make directory)\n");
        printf("2-cd dir(change directory)\n");
        printf("3-cd ..(make directory to parent)\n");
        printf("4-dir (directory)\n");
        printf("5-izlaz\n");
        printf("Unos: ");

        scanf("%d", &brojNaredbe);

        puts("");

        switch (brojNaredbe)
        {
        case 1: {

            printf("Unesite ime novog direktorija: ");
            scanf(" %[^\n]", ime);
            puts("");

            noviDirektorij = kreirajNoviElement(ime);
            korijen->Dijete = unesiNoviElementUStablo(korijen->Dijete, noviDirektorij);

            break;
        }
        case 2: {

            printf("Unesite ime direktorija u kojeg zelite prijeci: ");
            scanf(" %[^\n]", ime);
            puts("");

            trenutniDirektorij = idiUPoddirektorij(trenutniDirektorij, ime, stog);           

            break;
        }
        case 3: {

            trenutniDirektorij = Pop(stog, trenutniDirektorij);

            break;
        }
        case 4: {

            ispisPoddirektorija(korijen);

            break;
        }
       
        default:
            break;
        }
    }

    free(korijen->Dijete);

    return 0;
}