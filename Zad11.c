/*11. Prepraviti zadatak 10 na način da se formira hash tablica država. Tablica ima 11 mjesta, a
funkcija za preslikavanje ključ računa da se zbraja ASCII vrijednost prvih pet slova države zatim
računa ostatak cjelobrojnog dijeljenja te vrijednosti s veličinom tablice. Države s istim ključem se
pohranjuju u vezanu listu sortiranu po nazivu države. Svaki čvor vezane liste sadrži stablo
gradova sortirano po broju stanovnika, zatim po nazivu grada.*/
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1
#define HASH_SIZE 11
#define MAX_CHAR 1024

struct tree;
typedef struct tree* PositionTree;
typedef struct tree{
    int population;
    char city[MAX_CHAR];
    PositionTree left;
    PositionTree right;
} Tree;


struct list;
typedef struct list* PositionList;
typedef struct list
{
    char country[MAX_CHAR];
    PositionTree root;
    PositionList next;
} List;




int readFromFile(char* , PositionList, List[]);
PositionTree readCitiesFromFile(char*);
int sortList(PositionList, PositionList );
int insertAfter(PositionList , PositionList);
PositionTree sortTree(char*, int, PositionTree);
int printList(PositionList);
int printTreeInOrder(PositionTree);
int findBigger(char*, int, List[]);
int findMax(PositionTree);
PositionList findCountry(char*, PositionList);
int printCities(int, PositionTree);
int hashTab(List[],PositionList);
int hashNumber(char*);

int main()
{
    List head = { .country = 0 ,  .root = NULL, .next = NULL };
    char country[MAX_CHAR] = { 0 };
    int number = 0;

    List HashTabl[HASH_SIZE];

    for (int i = 0; i < HASH_SIZE; i ++)
	{
        HashTabl[i] = *InitializeList();
	}

    readFromFile("stateFile.txt", &head, HashTabl);
    
    for (int i = 0; i < HASH_SIZE; i++)
	{
		if (HashTabl[i].next != NULL)
		{
			printList(&HashTabl[i]);
		}
	}

    printf("\nChoose country: ");
    scanf("%s", country);
    printf("Insert number: ");
    scanf("%d", &number);
    findBigger(country, number, HashTabl);
    return EXIT_SUCCESS;
}



int readFromFile(char *filename, PositionList head, List HashTabl[])
{
    char buffer[MAX_CHAR] = { 0 };
    char fileCity[MAX_CHAR] = { 0 };
    int number;
    FILE *pDat;
    pDat=fopen(filename, "r");

    PositionList temp = NULL;

    if(!pDat)
    {
        perror("Cannot open the file!\n");
		return EXIT_FAILURE;
    }

    while(!feof(pDat))
    {  
        
        PositionList temp = NULL;
        temp = (List*)malloc(sizeof(List));
        temp->next = NULL;

        fgets(buffer, MAX_CHAR, pDat);

        if(sscanf(buffer, " %s %s",  temp->country, fileCity) == 2)
        {
            temp->root = NULL;
            temp->root = readCitiesFromFile(fileCity);
            
            hashTab(HashTabl, temp);
        }
    }

    fclose(pDat);

    return EXIT_SUCCESS;
}

PositionTree readCitiesFromFile(char* filename)
{
    char buffer[MAX_CHAR] = { 0 };
    char name[MAX_CHAR] = { 0 };
    int brojSt = 0;
    FILE *pDat;
    pDat=fopen(filename, "r");

    PositionTree root = NULL;

    if(!pDat)
    {
        perror("Cannot open the file!\n");
		return NULL;
    }

    while(!feof(pDat))
    {  
        fgets(buffer, MAX_CHAR, pDat);
        if(sscanf(buffer, " %s %d", name, &brojSt) == 2)
        {
            root = sortTree(name, brojSt, root);
        }
    }
    fclose(pDat);
    return root;
    
}

int sortList(PositionList new, PositionList head)
{
    PositionList temp = head;
    
    while (temp->next != NULL && strcmp(temp->next->country, new->country) < 0)
    {
        temp=temp->next;
    }
    if(temp->next == NULL || strcmp(temp->next->country, new->country) != 0)
    {   
        insertAfter(temp, new); 
    }
    else if(strcmp(temp->next->country, new->country) == 0)
    {
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

int insertAfter(PositionList temp, PositionList new)
{
    new->next = temp->next;
    temp->next = new;
}

PositionTree sortTree(char *name, int brojSt, PositionTree current)
{
    if(current == NULL)
    {
        current = (Tree*)malloc(sizeof(Tree));
        strcpy(current->city, name);
        current->population = brojSt;
        current->left = NULL;
        current->right = NULL; 
    }
    else if(brojSt < current->population)
        current->left = sortTree(name, brojSt, current->left);
    else if(brojSt > current->population)
        current->right = sortTree(name, brojSt, current->right);
    else if(brojSt == current->population)
    {
        if(strcmp(name, current->city) < 0)
            current->left = sortTree(name, brojSt, current->left);
        else if(strcmp(name, current->city) > 0)
            current->right = sortTree(name, brojSt, current->right);
        else
        {
            return current;
        }   
    }
    else
        free(current);

    return current;
}

int printList(PositionList head)
{
    PositionList temp = head->next;
    while(temp!=NULL)
    {
        
        printf("\n%s\n", temp->country);
        printTreeInOrder(temp->root);
        temp = temp->next;
    }
    return EXIT_SUCCESS;

}

int printTreeInOrder(PositionTree current)
{
    if(current == NULL){
        printTreeInOrder(current->left);
        printf("  %s = %d\n", current->city, current->population);
        printTreeInOrder(current->right);
    }
    return EXIT_SUCCESS;
}

int findBigger(char* country, int number, List HashTabl[])
{
    int num = hashNumber(country);
    PositionList chosenCountry = findCountry(country, &HashTabl[num]);
    int max = 0;
    if(chosenCountry == NULL)
    {
        printf("Country %s not found.\n", country);
        return EXIT_FAILURE;
    }
    max = findMax(chosenCountry->root);
    if (number > max)
    {
        printf("We did not find cities in %s that have larger population than %d.\n", country, number);
        return EXIT_FAILURE;
    }
    
    printf("\nCities in %s with larger population than %d:\n", chosenCountry->country, number);
    printCities(number, chosenCountry->root);

    return EXIT_SUCCESS;
}

int findMax(PositionTree current)
{
    int maxi = 0;
    if(current == NULL)
        return EXIT_SUCCESS;
    if(current->right == NULL)
        return current->population;
    maxi = findMax(current->right);

    return maxi;
}

PositionList findCountry(char* country, PositionList head)
{
    PositionList temp = head;
    while(temp->next!=NULL && strcmp(temp->next->country,country) != 0)
        temp=temp->next;
    return temp->next;
}

int printCities(int number, PositionTree current)
{
    if(current == NULL)
        return EXIT_SUCCESS;
    printCities(number, current->left);
    if(current->population >= number)
        printf("  %s = %d\n", current->city, current->population);
    printCities(number, current->right);

    return EXIT_SUCCESS;
}

int hashTab(List HashTabl[],PositionList new)
{
	int num = hashNumber(new->country);

    sortList(new, &HashTabl[num]);

	return EXIT_SUCCESS;
}

int hashNumber(char* country)
{
	int num = 0;
	num = country[0] + country[1] + country[2] + country[3] + country[4];

	return num % 11;
}

PositionList InitializeList()
{
    PositionList new = NULL;
    new = (List*)malloc(sizeof(List));
    strcpy(new->country ,  "");
    new->next = NULL;
    new->root = NULL;

    return new;

} 
