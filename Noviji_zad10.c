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
-------------------------------------------------------
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1
#define MAX_CHAR 1024

//for countires that are linked list
struct element;
typedef struct element* c_Position;
typedef struct element{
    char country_name[MAX_CHAR];
    c_Position next;
    c_Position p_tree; //this will point to a root of attached tree
} Element;

//for towns that are in trees
struct node;
typedef struct node* t_Position;
typedef struct node{
    int population;
    char town_name[MAX_CHAR];
    t_Position left;
    t_Position right;
} Node;

int createList(c_Position);
//c_Position createListElement(c_Position, char[MAX_CHAR]);

int main(){
    
    Element Head={.country_name={0},.next=NULL,.p_tree=NULL};
    createList(&Head);
    
    
    return EXIT_SUCCESS;
}

int createList(c_Position c_current){
    
    char new_country_name[MAX_CHAR]={0};
    char file_w_towns[MAX_CHAR]={0};
    c_Position safekeep_Head=(c_Position)malloc(sizeof(Element));
    safekeep_Head=c_current; //this is variable that will always point at head of linked list
    
    FILE* fp = NULL;
    fp=fopen("countries.txt","r");
    if(!fp){
        printf("File countries.txt failed to open!");
        return EXIT_FAILURE;
    }
    while(!feof(fp)){
        fscanf(fp,"%s %s", new_country_name, file_w_towns);
        //createListElement(c_current, new_country_name); //c_current == &Head
        //printf("back");
        c_Position new_list_element=(c_Position)malloc(sizeof(Element));
        strcpy(new_list_element->country_name,new_country_name);
        new_list_element->next=NULL;
        new_list_element->p_tree=NULL;
        printf("%s %p %p \n", new_list_element->country_name, new_list_element->next, new_list_element->p_tree);
        //at this point we have element, now we need to sort it into preexisting list, we go from begining
        
        //this will check if list is empty and if yes add with no condition
        c_current=safekeep_Head; //with this we ensure that for each element we have a head to start from
        if(c_current->next==NULL){
            c_current->next=new_list_element;
        }
        else if(c_current->next!=NULL){//this c_current is &Head
            //we are going from 1st real/nonempty element
            
            while(c_current!=NULL && c_current->next!=NULL){ //2nd condition is so we don't deal with adding behind last in if loop
                if((strcmp(new_list_element->country_name,c_current->next->country_name))>0){
                    new_list_element->next=c_current->next;
                    c_current->next=new_list_element;
                }
                else if(c_current!=NULL && c_current->next==NULL){ //with 2nd condition we make sure we are at last element
                    c_current->next=new_list_element;
                    //we don't need new_list_element->next=NULL cause we initialized it like that already
                }
                else{
                    c_current=c_current->next;
                }
                
            }
        }
        showList(safekeep_Head);//safekeep_Head==&Head
        
    }
    free(safekeep_Head); //this is a pointer element we need temporarily
    fclose(fp);
    return EXIT_SUCCESS;
}

int showList(c_Position c_current) {

    if (c_current == NULL) { //checking if we got any list to go through to begin with, if not then this function is useless
        printf("This list is empty!");
        return EXIT_FAILURE;
    }

    while (c_current != NULL) {
        printf("\n");
        printf("\n ----- \n Country: %s Next: %p P-Tree: %p", c_current->country_name, c_current->next, c_current->p_tree);
        c_current = c_current->next;
    }

    return EXIT_SUCCESS;
}
/*c_Position createListElement(c_Position c_current, char new_country_name[MAX_CHAR]){ //c_current==&Head
    c_Position new_list_element=(c_Position)malloc(sizeof(Element));
    new_list_element->country_name=new_country_name;
    new_list_element->next=NULL;
    new_list_element->p_tree=NULL;
    printf("%s %p %p \n", new_list_element->country_name, new_list_element->next, new_list_element->p_tree);
    return new_list_element; //with this our list element is initialized and ready to be added sortedly
}*/
UUUUUUUUUUUUUUUUUUUUUUUUUU
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1
#define MAX_CHAR 1024

//for countires that are linked list
struct element;
typedef struct element* c_Position;
typedef struct element{
    char country_name[MAX_CHAR];
    c_Position next;
    c_Position p_tree; //this will point to a root of attached tree
} Element;

//for towns that are in trees
struct node;
typedef struct node* t_Position;
typedef struct node{
    int population;
    char town_name[MAX_CHAR];
    t_Position left;
    t_Position right;
} Node;

int createList(c_Position);
int showList(c_Position);
//c_Position createListElement(c_Position, char[MAX_CHAR]);

int main(){
    
    Element Head={.country_name={0},.next=NULL,.p_tree=NULL};
    createList(&Head);
    
    
    return EXIT_SUCCESS;
}

int createList(c_Position c_current){
    
    char new_country_name[MAX_CHAR]={0};
    char file_w_towns[MAX_CHAR]={0};
    c_Position safekeep_Head=(c_Position)malloc(sizeof(Element));
    safekeep_Head=c_current; //this is variable that will always point at head of linked list
    
    FILE* fp = NULL;
    fp=fopen("countries.txt","r");
    if(!fp){
        printf("File countries.txt failed to open!");
        return EXIT_FAILURE;
    }
    while(!feof(fp)){
        fscanf(fp,"%s %s", new_country_name, file_w_towns);
        //createListElement(c_current, new_country_name); //c_current == &Head
        //printf("back");
        c_Position new_list_element=(c_Position)malloc(sizeof(Element));
        strcpy(new_list_element->country_name,new_country_name);
        new_list_element->next=NULL;
        new_list_element->p_tree=NULL;
        printf("\n NEW ELEMENT %s %p %p \n", new_list_element->country_name, new_list_element->next, new_list_element->p_tree);
        //at this point we have element, now we need to sort it into preexisting list, we go from begining
        
        //this will check if list is empty and if yes add with no condition
        c_current=safekeep_Head; //with this we ensure that for each element we have a head to start from
        if(c_current->next==NULL){
            c_current->next=new_list_element;
        }
        else if(c_current->next!=NULL){//this c_current is &Head
            //we are going from 1st real/nonempty element
            printf("\n else if %p %p",c_current, c_current->next);
            
            while(c_current!=NULL){ 
                printf("\nwhile; new_list_element->country_name %s c_current-->next->country_name %s", new_list_element->country_name, c_current->next->country_name);
                if(c_current->next==NULL){ //with condition we make sure we are at last element
                    printf("\n adding behind; c_current->name %s c_current: %p c_current->next: %p", c_current->country_name, c_current, c_current->next);
                    c_current->next=new_list_element;
                    break; //it's okay to break here cause we don't need to loop anymore anyway, we walked through whole linked list
                    //we don't need new_list_element->next=NULL cause we initialized it like that already
                
                }
                else if((strcmp(new_list_element->country_name,c_current->next->country_name))<0){
                    new_list_element->next=c_current->next;
                    c_current->next=new_list_element;
                    break;
                }
                else{
                    c_current=c_current->next;
                }
                
            }
        }
        showList(safekeep_Head);//safekeep_Head==&Head
        
    }
    free(safekeep_Head); //this is a pointer element we need temporarily
    fclose(fp);
    return EXIT_SUCCESS;
}

int showList(c_Position c_current) {

    if (c_current == NULL) { //checking if we got any list to go through to begin with, if not then this function is useless
        printf("This list is empty!");
        return EXIT_FAILURE;
    }

    while (c_current != NULL) {
        printf("\n");
        printf("\n ----- \n Country: %s Next: %p P-Tree: %p", c_current->country_name, c_current->next, c_current->p_tree);
        c_current = c_current->next;
    }

    return EXIT_SUCCESS;
}
/*c_Position createListElement(c_Position c_current, char new_country_name[MAX_CHAR]){ //c_current==&Head
    c_Position new_list_element=(c_Position)malloc(sizeof(Element));
    new_list_element->country_name=new_country_name;
    new_list_element->next=NULL;
    new_list_element->p_tree=NULL;
    printf("%s %p %p \n", new_list_element->country_name, new_list_element->next, new_list_element->p_tree);
    return new_list_element; //with this our list element is initialized and ready to be added sortedly
}*/
pppppppppppppppppppppppppp
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1
#define MAX_CHAR 1024

//for countires that are linked list
struct element;
typedef struct element* c_Position;
typedef struct element{
    char country_name[MAX_CHAR];
    c_Position next;
    c_Position p_tree; //this will point to a root of attached tree
} Element;

//for towns that are in trees
struct node;
typedef struct node* t_Position;
typedef struct node{
    int population;
    char town_name[MAX_CHAR];
    t_Position left;
    t_Position right;
} Node;

int createList(c_Position);
int showList(c_Position);
int addInFrontOf(c_Position, c_Position, char[MAX_CHAR]);
c_Position findListElementByCountryName(c_Position, char[MAX_CHAR]);
c_Position findPreviousListElement(c_Position, c_Position);
//c_Position createListElement(c_Position, char[MAX_CHAR]);

int main(){
    
    Element Head={.country_name={0},.next=NULL,.p_tree=NULL};
    createList(&Head);
    showList(&Head);
    
    
    return EXIT_SUCCESS;
}

int createList(c_Position c_current){
    
    char new_country_name[MAX_CHAR]={0};
    char file_w_towns[MAX_CHAR]={0};
    c_Position safekeep_Head=(c_Position)malloc(sizeof(Element));
    safekeep_Head=c_current; //this is variable that will always point at head of linked list
    
    FILE* fp = NULL;
    fp=fopen("countries.txt","r");
    if(!fp){
        printf("File countries.txt failed to open!");
        return EXIT_FAILURE;
    }
    while(!feof(fp)){
        fscanf(fp,"%s %s", new_country_name, file_w_towns);
        //createListElement(c_current, new_country_name); //c_current == &Head
        //printf("back");
        c_Position new_list_element=(c_Position)malloc(sizeof(Element));
        strcpy(new_list_element->country_name,new_country_name);
        new_list_element->next=NULL;
        new_list_element->p_tree=NULL;
        printf("\n NEW ELEMENT %s %p %p \n", new_list_element->country_name, new_list_element->next, new_list_element->p_tree);
        //at this point we have element, now we need to sort it into preexisting list, we go from begining
        
        //this will check if list is empty and if yes add with no condition
        c_current=safekeep_Head; //with this we ensure that for each element we have a head to start from
        if(c_current->next==NULL){
            c_current->next=new_list_element;
            showList(safekeep_Head);
        }
        else{
            c_current=c_current->next; //so we are working with 1st nonempty element
            while(c_current!=NULL){
                printf("we in?");
                if((strcmp(new_list_element->country_name,c_current->country_name))<0){
                    addInFrontOf(safekeep_Head, new_list_element, c_current->country_name);
                    
                }
                c_current=c_current->next;
            }
        }
        /*else if(c_current->next!=NULL){//this c_current is &Head
            //we are going from 1st real/nonempty element
            printf("\n else if %p %p",c_current, c_current->next);
            
            while(c_current!=NULL){ 
                printf("\nwhile; new_list_element->country_name %s c_current-->next->country_name %s", new_list_element->country_name, c_current->next->country_name);
                if(c_current->next==NULL){ //with condition we make sure we are at last element
                    printf("\n adding behind; c_current->name %s c_current: %p c_current->next: %p", c_current->country_name, c_current, c_current->next);
                    c_current->next=new_list_element;
                    break; //it's okay to break here cause we don't need to loop anymore anyway, we walked through whole linked list
                    //we don't need new_list_element->next=NULL cause we initialized it like that already
                
                }
                else if((strcmp(new_list_element->country_name,c_current->next->country_name))<0){
                    new_list_element->next=c_current->next;
                    c_current->next=new_list_element;
                    break;
                }
                else{
                    c_current=c_current->next;
                }
                
            }
        }
        showList(safekeep_Head);//safekeep_Head==&Head*/
        
    }
    free(safekeep_Head); //this is a pointer element we need temporarily
    fclose(fp);
    return EXIT_SUCCESS;
}

int showList(c_Position c_current) {

    if (c_current == NULL) { //checking if we got any list to go through to begin with, if not then this function is useless
        printf("This list is empty!");
        return EXIT_FAILURE;
    }

    while (c_current != NULL) {
        printf("\n");
        printf("\n ----- \n Country: %s Next: %p P-Tree: %p", c_current->country_name, c_current->next, c_current->p_tree);
        c_current = c_current->next;
    }

    return EXIT_SUCCESS;
}
  /*int addInFrontOf(Position current) {

                    Position new = (Position)malloc(sizeof(Person));
                    new = CreateElement();
                    Position THEElement = findBySurname(current->next);
                    Position temp = findPreviousBySurname(current);
                    new->next = THEElement;
                    temp->next = new;

                    free(new);

                    return EXIT_SUCCESS;
                }*/
int addInFrontOf(c_Position c_current, c_Position new_list_element, char THE_country_name[MAX_CHAR]){
    // c_current je &Head, new_list_element je upravo to aka novi član koji dodajemo, THE_country_name je ime države ispred koje dodajemo novi član
    c_Position THE_list_element=findListElementByCountryName(c_current->next, THE_country_name);
    c_Position Previous_list_element=findPreviousListElement(c_current->next, THE_list_element);
    if(Previous_list_element==NULL){
        //this means THE element is 1st and has no previous so we do add at the begining thing
        new_list_element->next=c_current->next;
        c_current->next=new_list_element;
        return EXIT_SUCCESS;
    }
    new_list_element->next=THE_list_element;
    Previous_list_element->next=new_list_element;
    return EXIT_SUCCESS;
    
}

c_Position findListElementByCountryName(c_Position c_current, char THE_country_name[MAX_CHAR]){ //c_current is first non-empty element
    while(c_current!=NULL){
        if(!(strcmp(c_current->country_name,THE_country_name))){
            printf("Element found!");
            return c_current;
        }
        c_current=c_current->next;
    }
    printf("Unable to find element!");
    return NULL;
    
}

c_Position findPreviousListElement(c_Position c_current, c_Position THE_list_element){
    c_Position prev=(c_Position)malloc(sizeof(Element));
    prev=c_current;
    //c_current is 1st non-empty element, THE is element whose previous we are serching for
    if(c_current==THE_list_element){
        //this means that there is no previous of this element cause THE is 1st in the list so we do add at begining thing
        free(prev);
        return NULL;
    }
    c_current=c_current->next; //this is now 2nd nonempty element
    while(c_current!=NULL && (c_current!=THE_list_element)){
        prev=c_current;
        c_current=c_current->next;
    }
    return prev;
}
/*c_Position createListElement(c_Position c_current, char new_country_name[MAX_CHAR]){ //c_current==&Head
    c_Position new_list_element=(c_Position)malloc(sizeof(Element));
    new_list_element->country_name=new_country_name;
    new_list_element->next=NULL;
    new_list_element->p_tree=NULL;
    printf("%s %p %p \n", new_list_element->country_name, new_list_element->next, new_list_element->p_tree);
    return new_list_element; //with this our list element is initialized and ready to be added sortedly
}*/
