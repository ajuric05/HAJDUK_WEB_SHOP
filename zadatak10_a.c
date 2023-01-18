#define CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <malloc.h>

#define MAX (1024)
#define MEMORY_NOT_ALOCATED (-1)
#define FILE_NOT_OPEN (-2)

struct _tree;
typedef struct _tree* position_tree;
typedef struct _tree{
    char cityName[MAX];
    int population;
    position_tree left;
    position_tree right;
}tree;

struct _linkedList;
typedef struct _linkedList* position_list;
typedef struct _linkedList{
    char stateName[MAX];
    position_tree nextTree;
    position_list next;
}linkedList;

position_list createHeadList();
position_tree createTreeRoot();
int printList (linkedList states);
int insertIntoList (position_list newElement, position_list head);
position_list createListElement (char stateName[]);
int readFromFile (char fileName[], linkedList states);
int readFromAdditionalFiles (position_list head, char additionalFileName[]);
int printInOrder (position_tree root);
position_tree createTreeElement (char cityName[], int peopleNummber);
position_tree insertIntoTree (position_tree root, char cityName[], int population);
position_tree findCityByName (position_tree current, char cityName[]);
position_list findStateByName (position_list states, char stateName[]);
int menu (position_list states);

int main(){

    linkedList states = {.stateName = {"\0"}, .next = NULL, .nextTree = NULL};

    states.next = createHeadList();
    states.nextTree  = createTreeRoot();

    readFromFile("drzave.txt", states);

    printf("Lista drzava:\n\n");
    printList(states);

    menu(&states);

    return 0;
}

position_list createListElement (char stateName[]){

    position_list newElement = NULL;

    newElement = (position_list)malloc(sizeof(linkedList));

    if(!newElement){

        printf("Memorija za novi element se ne moze alocirati!!");
        return NULL;
    }

    strcpy(newElement->stateName, stateName);
    newElement->nextTree = createTreeRoot();
    newElement->next = NULL;

    return newElement;
}

position_list createHeadList(){

    position_list head = NULL;

    head = (position_list)malloc(sizeof(linkedList));

    if(!head){
        printf("Memorija za head element vezane liste se ne moze alocirati!!");
        return NULL;
    }

    strcpy(head->stateName,"");
    head->next = NULL;
    head->nextTree = NULL;
    head->next = NULL;

    return head;
}

position_tree createTreeRoot(){

    position_tree root = NULL;

    root = (position_tree)malloc(sizeof(tree));

    if(!root){
        printf("Memorija za root element stabla nije alocirana!!");
        return NULL;
    }

    root->left = NULL;
    root->right = NULL;
    root->population = 0;

    return root;
}

int printList (linkedList states){

    position_list current = states.next;

    while(current->next != NULL){

        current = current->next;
        printf("%s\n", current->stateName);
    }

    return 0;
}

int insertIntoList (position_list newElement, position_list head){

    if(head->next == NULL){
        head->next = newElement;
        newElement->next = NULL;
    }

    else{

        while (head->next != NULL && strcmp(head->next->stateName,newElement->stateName) < 0)
        {
            head = head->next;
        }
        
        newElement->next = head->next;
        head->next = newElement;
    }

    return 0;
}

int readFromFile (char fileName[], linkedList states){

    FILE* fp = NULL;
    char* buffer = NULL;
    char stateName[MAX] = {0};
    char additionalFileName[MAX] = {0};
    int byteNumber = 0;
    position_list newElement = NULL;
    position_list current = states.next;

    newElement = (position_list)malloc(sizeof(linkedList));

    if(!newElement){

        printf("Memorija za novi element se ne moze alocirati!!");
        return MEMORY_NOT_ALOCATED;
    }

    buffer = (char*)malloc(MAX*sizeof(char));

    if(!buffer){
        printf("Memorija za novi element se ne moze alocirati!!");
        return MEMORY_NOT_ALOCATED;
    }

    fp = fopen(fileName, "r");

    if (!fp)
    {
        printf("Datoteka se ne moze otvoriti!!");
        return FILE_NOT_OPEN; 
    }

    while(!feof(fp)){

        fgets(buffer, MAX, fp);

        if(sscanf(buffer, "%s %s %n", stateName, additionalFileName, &byteNumber) == 2){

            newElement = createListElement(stateName);

            insertIntoList(newElement, states.next);

            printf("Drzava: %s\nGradovi:\n", newElement->stateName);

            readFromAdditionalFiles(newElement, additionalFileName);

            buffer += byteNumber;
        }

        else{

            printf("DOGODILA SE GRESKA, MOLIMO PONOVNO UNESITE IME DATOTEKE!!");
        }
    }
    
    fclose(fp);

    return 0;
}

int readFromAdditionalFiles (position_list head, char additionalFileName[]){

    FILE* fp = NULL;
    char cityName[MAX] = {0};
    int population = 0;
    char* buffer = NULL;
    int byteNumber = 0;
    position_tree newElement = NULL;
    position_tree root = head->nextTree;

    buffer = (char*)malloc(MAX*sizeof(char));

    if(!buffer){

        printf("Memorija za buffer nije alocirana!!");
        return MEMORY_NOT_ALOCATED;
    }

    fp = fopen(additionalFileName, "r");

    if(!fp){

        printf("Datoteka nije otvorena!!");
        return FILE_NOT_OPEN;
    }

    while(!feof(fp)){

        fgets(buffer, MAX, fp);

        if(sscanf(buffer, "%s %d %n",cityName, &population, &byteNumber) == 2){

            newElement = createTreeRoot();

            newElement = insertIntoTree(root, cityName, population);

            buffer += byteNumber;
        }

        else{

            printf("DOGODILA SE GRESKA, MOLIMO PONOVNO UNESITE IME DATOTEKE!!");
        }
    }

    printInOrder(newElement);
    printf("\n");
    fclose(fp);

    return 0;
}

int readFromAdditionalfile(position_list head, char additionalFileName[]){

    FILE*fp = NULL;
    char cityName[MAX] = {0};
    int population = 0;
    char* buffer = NULL;
    int byteNumber = 0;
    position_tree newElement = NULL;
    position_tree root = head->nextTree;

    buffer = (char*)malloc(MAX*sizeof(char));

    if(!buffer){

        printf("Memorija se ne moze alocirati!!");
        return MEMORY_NOT_ALOCATED;
    }

    fp = fopen(additionalFileName, "r");

    if(!fp){

        printf("datoteka nije otvorena!!");
        return FILE_NOT_OPEN;
    }

    while (!feof(fp)){
        
        fgets(buffer, MAX, fp);

        if(sscanf(buffer, "%s %d %n",cityName, &population, &byteNumber) == 2){

            newElement = createTreeRoot();

            newElement = insertIntoTree(root, cityName, population);

            buffer += byteNumber;
        }

        else{
            printf("DOGODILA SE GRESKA, MOLIMO PONOVNO UNESITE IME DATOTEKE!!");           
        }
    }

    printInOrder(newElement);

    printf("\n");
    
    fclose(fp);

    return 0;
}

int printInOrder(position_tree root){

    if (root == NULL)
        return 0;

    printInOrder(root->left);

    if(root->population != 0)
        printf("Grad: %s    Populacija: %d\n", root->cityName, root->population);

    printInOrder(root->right);

    return 0;
}

position_tree createTreeElement (char cityName[], int peopleNummber){

    position_tree newElement = NULL;

    newElement = (position_tree)malloc(sizeof(tree));

    if(!newElement){

        printf("Memorija za novi element nije alocirana!!");

        return NULL;
    }

    strcpy(newElement->cityName, cityName);
    newElement->population = peopleNummber;
    newElement->left = NULL;
    newElement->right = NULL;

    return newElement;
}

position_tree insertIntoTree (position_tree root, char cityName[], int population){

    if(root == NULL)
        root = createTreeElement(cityName, population);

    if(root->population > population)
        root->left = insertIntoTree(root->left, cityName, population);

    else if(root->population < population)
        root->right = insertIntoTree(root->right, cityName, population);

    return root;
}

position_list findStateByName (position_list states, char stateName[]){

    position_list current = NULL;

    current = (position_list)malloc(sizeof(linkedList));

    if (!current){

        printf("Memorija za trenutacni clan nije alocirana!!");
        return NULL;
    }
     
    current = states->next;

    while(current->next != NULL && strcmp(current->next->stateName, stateName) != 0)
        current = current->next;

    if(strcmp(current->next->stateName, stateName) != 0){

        printf("Drzava ne postoji!!");
        return NULL;
    }

    current = current->next;

    return current;
}

position_tree findCityByName (position_tree current, char cityName[]){

    int i = 0;

    for(i = 0; i < 1; i++){
        
        if (current == NULL)
            return NULL;

        else if(strcmp(current->cityName, cityName) > 0)
            return findCityByName(current->left, cityName);

        else if(strcmp(current->cityName, cityName) < 0)
            return findCityByName(current->right, cityName);

        else 
            return current;    
    }

    return current;
}

int menu (position_list states){

    int key = 0;
    char stateName[MAX] = {0};
    char cityName[MAX] = {0};
    position_list currentList = NULL;
    position_tree currentTree = NULL;
    position_tree temp = NULL;

    currentList = (position_list)malloc(sizeof(linkedList));

    if(!currentList){

        printf("Memorija za trenutacni element liste nije alocirana!!");
        return MEMORY_NOT_ALOCATED;
    }

    currentTree = (position_tree)malloc(sizeof(tree));

    if(!currentTree){

        printf("Memorija za trenutacni element stabla nije alocirana!!");
        return MEMORY_NOT_ALOCATED;
    }

    temp = (position_tree)malloc(sizeof(tree));

    while(key != 2){

        printf("Zelite li pretrazivati drzave?\n");
        printf("1-DA\n2-NE\n");
        scanf("%d", &key);

        if(key == 1){

            printf("Unesite ime drzave: ");
            scanf("%s", stateName);

            currentList = findStateByName(states, stateName);

            if(!currentList)
                printf("Ta drzava ne postoji !!");

            else{

                printf("Drzava %s je pronadjena!\n", currentList->stateName);
                printf("Gradovi te drzave su:\n");
                printInOrder(currentList->nextTree);

                printf("Unesite ime grada: ");
                scanf("%s", cityName);

                temp = currentList->nextTree;

                currentTree = findCityByName(temp, cityName);

                if(!currentTree)
                    printf("Trazeni grad ne postoji!!\n");

                else
                    printf("Grad: %s\nPopulacija: %d\n", currentTree->cityName, currentTree->population);
            }    
        }

            else if(key == 2){

                printf("Dovidjenja!\n");
                return 0;
            }
    }

    return 0;
}