#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1
#define MAX_CHAR 1024

struct _tree;
typedef struct _tree *Position_tree;
typedef struct _tree
{

    char cityName[MAX_CHAR];
    int population;
    Position_tree left;
    Position_tree right;
} tree;

struct _linkedList;
typedef struct _linkedList *Position_list;
typedef struct _linkedList
{

    char stateName[MAX_CHAR];
    Position_tree nextTree;
    Position_list next;
} linkedList;

Position_tree createTreeRoot();
Position_list createHeadList();
int printList(linkedList states);
int insertIntoList(Position_list newElement, Position_list head);
Position_list createListElement(char stateName[]);
int readFromFile(char fileName[], linkedList states);
int readFromAdditionalFile(Position_list head, char additionalFile[]);
int printInorder(Position_tree root);
Position_tree creteTreeElement(char cityName[], int peopleNumb);
Position_tree insertIntoTree(Position_tree root, char cityName[], int population);
Position_tree findCityByName(Position_tree current, char cityName[]);
int Menu(linkedList states);
Position_list findStateByName(linkedList states, char stateName[]);

int main()
{

    linkedList states = {.stateName = {0}, .next = NULL, .nextTree = NULL};

    states.next = createHeadList();
    states.nextTree = createTreeRoot();

    readFromFile("stateFile.txt", states);

    printf("\nLista drzava:");
    printList(states);

    printf("Ovo je states.next %p", states.next);
    Menu(states);

    return EXIT_SUCCESS;
}

Position_tree createTreeRoot()
{

    Position_tree root = NULL;

    root = (Position_tree)malloc(sizeof(tree));

    if (!root)
    {

        printf("Malloc fail!");
        return NULL;
    }

    strcpy(root->cityName, "");
    root->left = NULL;
    root->right = NULL;
    root->population = 0;

    return root;
}

int insertIntoList(Position_list newElement, Position_list head)
{

    if (head->next == NULL)
    {

        head->next = newElement;
        newElement->next = NULL;
    }

    else
    {

        while (head->next != NULL && (strcmp(head->next->stateName, newElement->stateName) < 0))
            head = head->next;

        newElement->next = head->next;
        head->next = newElement;
    }

    return EXIT_SUCCESS;
}

Position_list createListElement(char stateName[])
{

    Position_list newElement = NULL;

    newElement = (Position_list)malloc(sizeof(linkedList));

    if (!newElement)
    {

        printf("Malloc fail!");
        return NULL;
    }

    strcpy(newElement->stateName, stateName);
    newElement->next = NULL;
    newElement->nextTree = createTreeRoot();

    return newElement;
}

int readFromFile(char fileName[], linkedList states)
{

    FILE *fp = NULL;
    char *buffer = NULL;
    char stateName[MAX] = {0};
    char additionalFile[MAX] = {0};
    int byteNumb = 0;
    Position_list newElement = NULL;
    Position_list current = states.next;

    newElement = (Position_list)malloc(sizeof(linkedList));

    if (!newElement)
    {

        printf("Malloc fail!");
        return EXIT_FAILURE;
    }

    buffer = (char *)malloc(MAX * sizeof(char));

    if (!buffer)
    {

        printf("Malloc fail!");
        return EXIT_FAILURE;
    }

    fp = fopen(fileName, "r");

    if (!fp)
    {

        printf("File se ne moze otvoriti!\n");
        return EXIT_FAILURE;
    }

    while (!feof(fp))
    {

        fgets(buffer, MAX, fp);

        if (sscanf(buffer, "%s %s %n", stateName, additionalFile, &byteNumb) == 2)
        {

            newElement = createListElement(stateName);

            insertIntoList(newElement, states.next);

            printf("\nDrzava: %s gradovi:", newElement->stateName);

            readFromAdditionalFile(newElement, additionalFile);

            buffer += byteNumb;
        }

        else
        {

            printf("Nesto nije uredu sa formatom vaseg filea!\nMolim, prmjenite format!\n");
            return EXIT_FAILURE;
        }
    }

    fclose(fp);

    return 0;
}

int readFromAdditionalFile(Position_list head, char additionalFile[])
{

    FILE *fp = NULL;
    char cityName[MAX] = {0};
    int population = 0;
    char *buffer = NULL;
    int byteNumb = 0;
    Position_tree newElement = NULL;
    Position_tree root = head->nextTree;

    buffer = (char *)malloc(MAX * sizeof(char));

    if (!buffer)
    {

        printf("Malloc fail!");
        return EXIT_FAILURE;
    }

    fp = fopen(additionalFile, "r");

    if (!fp)
    {

        printf("Fileu %s ne moze se pristupiti!\n", additionalFile);
        return EXIT_FAILURE;
    }

    while (!feof(fp))
    {

        fgets(buffer, MAX, fp);

        if (sscanf(buffer, "%s %d %n", cityName, &population, &byteNumb) == 2)
        {

            newElement = createTreeRoot();

            newElement = insertIntoTree(root, cityName, population);

            buffer += byteNumb;
        }

        else
        {

            printf("Nesto nije uredu sa formatom vaseg filea!\nMolim, prmjenite format!\n");
            return EXIT_FAILURE;
        }
    }

    printInorder(newElement);
    puts("");

    fclose(fp);

    return EXIT_SUCCESS;
}

int printInorder(Position_tree root)
{

    if (root == NULL)
        return 0;

    printInorder(root->left);

    if (root->population != 0)
        printf("\n\tGrad: %s    Populacija: %d", root->cityName, root->population);

    printInorder(root->right);

    return EXIT_SUCCESS;
}

Position_tree creteTreeElement(char cityName[], int peopleNumb)
{

    Position_tree newElement = NULL;

    newElement = (Position_tree)malloc(sizeof(tree));

    if (!newElement)
    {

        printf("Mealloc fail!");
        return NULL;
    }

    strcpy(newElement->cityName, cityName);
    newElement->population = peopleNumb;
    newElement->left = NULL;
    newElement->right = NULL;

    return newElement;
}

Position_list findStateByName(linkedList states, char stateName[])
{

    Position_list current = NULL;

    current = (Position_list)malloc(sizeof(linkedList));

    if (!current)
    {

        printf("Malloc fail!");
        return NULL;
    }

    current = states.next;
    //printf("Ovo je states.next %p", states.next);
    //printf("Ovo je current->next %s", current->next);
    if(!(strcmp(stateName, current->next))){
        return current->next;

    while (current->next != NULL && (strcmp(current->stateName, stateName))){
        current = current->next;
       // printf("Ovo je current %s", current);
        //printf("Ovo je current->next %s", current->next);

    if (!(strcmp(stateName, current->next->stateName)))
    {

        //printf("Ovo je stateName %s", stateName);
        //printf("Ovo je current->next->stateName %s", current->next->stateName);
        return current->next;
    } 
    }
   // printf("Ovo je states.next %p", states.next);
    //printf("Ovo je current->next", current->next);
    current = current->next;
    //printf("Ovo je current->next", current->next);
    return NULL;
}

Position_tree findCityByName(Position_tree current, char cityName[])
{

    int i = 0;

    for (i = 0; i < 1; i++)
    {

        if (current == NULL)
            return NULL;

        else if (strcmp(current->cityName, cityName) > 0)
            return findCityByName(current->left, cityName);

        else if (strcmp(current->cityName, cityName) < 0)
            return findCityByName(current->right, cityName);

        else
            return current;
    }

    return current;
}

int Menu(linkedList states)
{

    int key = 111;
    char stateName[MAX] = {0};
    char cityName[MAX] = {0};
    Position_list currentList = NULL;
    Position_tree currentTree = NULL;
    Position_tree temp = NULL;

    currentList = (Position_list)malloc(sizeof(linkedList));

    if (!currentList)
    {

        printf("Malloc fail!");
        return EXIT_FAILURE;
    }

    currentTree = (Position_tree)malloc(sizeof(tree));

    if (!currentTree)
    {

        printf("MAlloc fail!");
        return EXIT_FAILURE;
    }
    printf("\n");
    temp = (Position_tree)malloc(sizeof(tree));
        while (key)
        {
            key = 0;
            //system("cls");
            printf("\n\tOdaberite:");
            printf("\n\t\t 1 - Pretraga drzave");
            printf("\n\t\t 0 - Izlaz\n\t ");
            scanf("%d", &key);

            switch (key)
            {
            case 1:
                 printf("\n\nUnesite ime drzave: ");
            scanf(" %s", stateName);

            currentList = findStateByName(states, stateName);
            //printf("Ovo je currentList %s", currentList);
            if (!currentList)
                printf("\n\tTa drzava ne postoji!\n");

            else
            {
                printf("\n\tDrzava: %s je pronadjena!", currentList->stateName);
                printf("\n\tGradovi drzave su:\n");
                printInorder(currentList->nextTree);

                printf("\n\n\tUnesite ime grada: ");
                scanf(" %s", cityName);

                temp = currentList->nextTree;

                currentTree = findCityByName(temp, cityName);

                if (!currentTree)
                    printf("\n\tGrada nema!\n");

                else
                    printf("\n\tGrad: %s    Populacija: %d", currentTree->cityName, currentTree->population);
            }
                break;
            case 0:
                    printf("\n\t\tIzlaz....");
                    return EXIT_SUCCESS;
                // break;
            default:
                printf("\n\tPogresan unos!!!");
            }
            printf("\nPause\nPress any key to continue\n");
            getch();
        }

    return EXIT_SUCCESS;
}

Position_tree insertIntoTree(Position_tree root, char cityName[], int population)
{

    if (root == NULL)
    {

        root = (Position_tree)malloc(sizeof(tree));
        strcpy(root->cityName, cityName);
        root->population = population;
        root->left = NULL;
        root->right = NULL;
    }

    if (root->population > population)
        root->left = insertIntoTree(root->left, cityName, population);

    else if (root->population < population)
        root->right = insertIntoTree(root->right, cityName, population);

    return root;
}

Position_list createHeadList()
{

    Position_list head = NULL;

    head = (Position_list)malloc(sizeof(linkedList));

    if (!head)
    {

        printf("Malloc fail!");
        return NULL;
    }

    strcpy(head->stateName, "");
    head->next = NULL;
    head->nextTree = NULL;
    head->next = NULL;

    return head;
}

int printList(linkedList states)
{

    Position_list current = states.next;

    while (current->next != NULL)
    {

        current = current->next;
        printf("\n\t%s", current->stateName);
    }
    return EXIT_SUCCESS;
}