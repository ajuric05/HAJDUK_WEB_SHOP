#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME (64)

struct osoba;
typedef struct osoba* pozicija;
typedef struct osoba {
	char ime[MAX_NAME];
	char prezime[MAX_NAME];
	int godinaRodenja;

	struct osoba* next;
}osoba;

osoba* UnosPocetak(osoba*);

int main() {

	


	return 0;
}

osoba* UnosPocetak(osoba* head) {

	osoba* q = malloc(sizeof(osoba));
	q->next = NULL;

	printf("Unesi ime ");
	scanf("%s", &q->ime);
	printf("Unesi prezime ");
	scanf("%s", &q->prezime);
	printf("Unesi godinu ");
	scanf("%d", &q->godinaRodenja);

	q->next = head;
	head = q;
	q = NULL;

	return head;



}