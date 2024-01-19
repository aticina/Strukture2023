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
//int AddAtEnd(Position);
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
        //case "a":
        //case "Y":
        //case "Z":
        case 'L':
            ShowList(current->next);
            break;
        //case "F":
        //case "D":
        //case "P":
        //case "S":
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
