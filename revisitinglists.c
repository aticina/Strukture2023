/*This is a linked list about cats, just for revising the code patterns for test*/
#define _CRT_SECURE_NO_WARNING
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1
#define MAX_CHAR 1024

struct cat;
typedef struct cat* Position;
typedef struct cat{
    char name[MAX_CHAR];
    int age;
    float weight_kg;
    double dimensions[2]; //height,length
    Position next;
} Cat;

int Menu(Position,char);
Position CreateMember();
int AddAtBeginning(Position);
int AddAtEnd(Position);
int AddAfter(Position);
int AddBefore(Position);
Position FindElement(Position);
Position Predecessor(Position);
int ShowList(Position);
int DeleteAll(Position);

int main(){
    
    Cat Head={.name={0},.age=0,.weight_kg=0.0,.dimensions[0]=0,.dimensions[1]=0,.next=NULL};
    char name_of_service='\0'; //THIS IS HOW WE INITIALIZE CHAR VARIABLES TO NOTHING!!!ALSO USE '' FOR CHAR AND "" FOR STRINGS
    
    while(!(name_of_service=='X')){
        printf("Welcome to linked list of cats :3 \n Please write down a letter represeting a service you want to use. We offer:\n"
        "A -Add a cat at the begining of the linked list\n"
        "a -Add a cat at the end of the linked list\n"
        "Y -add a cat after certain y member\n"
        "Z -add a cat before certain z member\n"
        "L -List all cats from the current linked list\n"
        "F -Find the cat\n"
        "D -Delete the cat from the linked list\n"
        "P -find predecessor\n"
        "S -find successor\n"
        "X -delete whole list and end session.\n");
        scanf(" %c", &name_of_service);
        printf("%c",name_of_service);
        Menu(&Head,name_of_service);
    }
    
    DeleteAll(&Head);
    
    return EXIT_SUCCESS;
}

int Menu(Position current, char name_of_service){
    //printf("WE IN MENU");
    switch(name_of_service){
        case 'A':
            //printf("We in A case");
            AddAtBeginning(current);
            break;
        case 'a':
            AddAtEnd(current);
            break;
        case 'Y':
            AddAfter(current);
            break;
        case 'Z':
            AddBefore(current);
                break;
        case 'L':
            ShowList(current->next);
            break;
        case 'F':
            FindElement(current->next);
            break;
        //case "D":
        case 'P':
            Predecessor(current->next);
            break;
        case 'S':
            Position temp=(Position)malloc(sizeof(Cat));
            temp=FindElement(current->next);
            if(temp==NULL){
                printf("There is no element you want to find successr of.");
                break;
            }
            else{
                printf("Successor is:\n");
                printf("-------\nName:%s\nAge:%d\nWeight(kg):%f\nHeight:%lf\nLength:%lf\n-------\n",temp->next->name,temp->next->age,temp->next->weight_kg,temp->next->dimensions[0],temp->next->dimensions[1]);
            }
            free(temp);
            break;
        case 'X':
            break;
    }
    return EXIT_SUCCESS;
}

Position CreateMember(){
    //printf("WE in CREATE");
    char name[MAX_CHAR]={0};
    int age=0;
    float weight_kg=0.0;
    double dimensions[2]={0}; //THIS IS HOW TO INITIALIZE DOUBLE TO NOTHING VALUE
    printf("\nName?\n");
    scanf("%s",name);
    printf("Age?\n");
    scanf("%d",&age);
    printf("Weight?\n");
    scanf("%f",&weight_kg);
    printf("Height?\n");
    scanf("%lf",&dimensions[0]);//WHY DID I NEED & FOR THIS?!
    printf("Length?\n");
    scanf("%lf",&dimensions[1]);
    Position new=(Position)malloc(sizeof(Cat));
     if (new == NULL) {
        printf("Malloc nije uspješno alocirao memoriju!");
        return NULL;
    }
    strcpy(new->name,name);
    new->age=age;
    new->weight_kg=weight_kg;
    for(int i=0; i<2; i++){
        new->dimensions[i]=dimensions[i];
    }
    return new;
    
}

int AddAtBeginning(Position current){
    //printf("WE IN FUNCtiON");
    Position new=CreateMember(); //no need for malloc cause CreateMember() will reserve memory instead
    new->next=current->next; //new element starts pointing at whatever head is pointing-be it NULL or member
    current->next=new; //we are chaging what head is pointing at aka value of head->next
    //free(new);
    return EXIT_SUCCESS;
}

int AddAtEnd(Position current){ //current is head
    while(current->next!=NULL){
        current=current->next;
    } //while loop ensures that current is last element in the list
    //cause when we go to check in for condition with last element
    //it will fail cause next pointer of last element is pointing at NULL
    //so current is last element of list for it won't enter loop and iterate to next
    Position new=CreateMember();
    current->next=new;
    new->next=NULL;
}

int AddAfter(Position current){ //current is head
    Position temp=(Position)malloc(sizeof(Cat));
    temp=FindElement(current->next);
    if(temp==NULL){
        printf("There is no such cat, we cannot proceed with adding process.");
        return EXIT_FAILURE;
    }
    else{
        Position new=CreateMember();
        new->next=temp->next;
        temp->next=new;
    }
    free(temp);
    return EXIT_SUCCESS;
}

int AddBefore(Position current){ //current is head
    
}
Position FindElement(Position current){ //current is head->next aka 1st real element
    char f_name[MAX_CHAR]={0};
    int f_age=0;
    printf("Input name and age of the cat you want to find(be it for data on the cat or for doing something else like adding, predecessor, successor etc.):\n");
    scanf("%s %d", f_name, &f_age);
    while(current!=NULL){
        if(!(strcmp(current->name,f_name)) && current->age==f_age){
            printf("-------\nName:%s\nAge:%d\nWeight(kg):%f\nHeight:%lf\nLength:%lf\n-------\n",current->name,current->age,current->weight_kg,current->dimensions[0],current->dimensions[1]);
            return current;
        }
        else{
            current=current->next;
        }
    }
    printf("There is no such cat.");
    return NULL;
}

Position Predecessor(Position predecessor){ //current is 1st non-empty element
    Position temp=(Position)malloc(sizeof(Cat));
    temp=FindElement(predecessor); //due to how FindElement does not receive head, but head next, it is impossble to ask to find predecessor of head
    if(temp==NULL){
        printf("There is no such cat, try again.");
        return NULL;
    }
    if(predecessor==temp){
        printf("This element is 1st in the linked list and as such does not have predecessor.");
        return NULL;
    }
    while(predecessor->next!=NULL){ //we don't need to go till predecessor is very last element cause predecessor by definition can't be last
        //so we are not checking if last element is predecessor cause that is impossible
        if(predecessor->next == temp){
            printf("Predecessor is:\n");
            printf("-------\nName:%s\nAge:%d\nWeight(kg):%f\nHeight:%lf\nLength:%lf\n-------\n",predecessor->name,predecessor->age,predecessor->weight_kg,predecessor->dimensions[0],predecessor->dimensions[1]);
            free(temp);
            return predecessor;
        }   
        else{
            predecessor=predecessor->next;
        }
    }
    printf("Unable to find predecessor despite knowing the element-system fail :/");
}
int ShowList(Position current){ //current is 1st non empty character
    if(current==NULL){
        printf("Empty list!");
        return EXIT_SUCCESS;
    }
    while(current!=NULL){
        printf("-------\nName:%s\nAge:%d\nWeight(kg):%f\nHeight:%lf\nLength:%lf\n-------\n",current->name,current->age,current->weight_kg,current->dimensions[0],current->dimensions[1]);
        current=current->next;
    }
    return EXIT_SUCCESS;
}

int DeleteAll(Position current){//current is head
    if(current==NULL){
        printf("There is nothing to delete!");
        return EXIT_FAILURE;
    }
    printf("nothing yet");
}

    }
    printf("nothing yet");
}
