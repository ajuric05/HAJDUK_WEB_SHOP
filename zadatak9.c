#include<stdio.h>
#include<stdlib.h>
#define _CRT_SECURE_NO_WARNINGS
#define NO_MEMORY_ERROR -1
#define MIN 10
#define MAX 90

struct _stablo;
typedef struct _stablo* stabloPointer;
typedef struct _stablo
{
	int value;
	stabloPointer left;
	stabloPointer right; 
}stablo;

stabloPointer insertElement(int element, stabloPointer root);
stabloPointer allocateNew(int element);
stabloPointer replace(stabloPointer root);
int inOrder(stabloPointer root,FILE* fp);
int addition(stabloPointer root);
int* generateRandomString(int number);
int menu(int choice);

int main()
{
    int choice;

    while (1) {

        printf("\n");
		printf("Unesite vas odabir:\n");
        printf("\n");
		printf("1 -> predefinirani niz\n");
        printf("2 -> random generirani niz\n");
        printf("0 -> izlaz\n");
		printf("\n");
		printf("--> ");
		scanf("%d", &choice);
		printf("\n");
        if(choice == 0)
            break;
        menu(choice);     
    }
	return 0;
}

stabloPointer insertElement(int element,stabloPointer root)
{
	if(root == NULL) {
        return allocateNew(element);
	}
	if(root->value > element) {
        root->right = insertElement(element,root->right);
    }
	else if(root->value <= element) {
        root->left = insertElement(element,root->left);
    }
	return root;
}


stabloPointer allocateNew(int element)
{
	stabloPointer newNode = malloc(sizeof(stablo));
    if (newNode == NULL) {
        printf("Nije moguce alocirati memoriju!");
        return NULL;
    }
  	newNode->value = element;
  	newNode->left = NULL;
  	newNode->right = NULL;
  	return newNode;
}



int inOrder(stabloPointer root,FILE*fp)
{

	if (root == NULL) {
		return 0;
	}
   	inOrder(root->left,fp);
   	printf("%d ", root->value);
    fprintf(fp,"%d ",root->value);
   	inOrder(root->right,fp);
	return 0;
}
int addition(stabloPointer root) {

    if(!root)
        return 0;

    else
        return (root->value + addition(root->left) + addition(root->right));

}
stabloPointer replace(stabloPointer root){

    if(!root){
        return 0;
    }
    root->value = addition(root->right) + addition(root->left);

    replace(root->right);
    replace(root->left);


    return 0;

}
int* generateRandomString(int number){

    int i;
    int *arr;

    arr = (int*)malloc(number * sizeof(int));

    srand(time (NULL));
    for (i = 0; i < number ; i++) {

        arr[i] = MIN + (rand() % (MAX - MIN + 1));

        printf("%d \n",arr[i]);
    }
    return arr;
}

int menu(int choice){

    int i,n,m;
    FILE *fp1=NULL;
    FILE *fp2=NULL;
    fp1 = fopen("datoteka1.txt", "w");
    fp2 = fopen("datoteka2.txt", "w");

        switch (choice){

            case 1:
                stabloPointer root1 = NULL;

                int arr[]={2, 5, 7, 8, 11, 1, 4, 2, 3, 7};
                int n = sizeof(arr)/sizeof(arr[0]);
                for (i = 0 ; i < n ; i++){
                    root1 = insertElement(arr[i],root1);
                }

                printf("Vase stablo glasi: ");
                fprintf(fp1, "Prije funkcije (zad a)\n");
                inOrder(root1,fp1);

                replace(root1);
                printf("\n");

                printf("Nakon zamjene: ");
                fprintf(fp1, "\nNakon funkcije (zad b)\n");
                inOrder(root1,fp1);
                rewind(fp1);
                break;
            case 2:
                stabloPointer root2 = NULL;

                printf("Koliko random brojeva zelite?\n");
                scanf(" %d", &m);
        	    int *Arr = generateRandomString(m);
                for (i = 0 ; i < m ; i++){
                    root2 = insertElement(Arr[i],root2);
                }
                printf("Vase stablo glasi: ");
                fprintf(fp2, "Prije funkcije (zad a)\n");
                inOrder(root2,fp2);

                replace(root2);

                printf("\n");

                printf("Nakon zamjene: ");
                fprintf(fp2, "\nNakon funkcije (zad b)\n");
                inOrder(root2,fp2);
                rewind(fp2);
                break;
        }
		printf("\n");

    fclose(fp1);
    fclose(fp2);

    return 0;
}
