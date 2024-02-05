#define _CRT_SECURE_NO_WARNING
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_CHAR 1024

struct el;
typedef struct el* Position;
typedef struct el{
    int value;
    Position next;
} El;

int addElementAtTheBeginning(Position);
int showList(Position);
int delete(Position);
int deleteAll(Position);

int main()
{
    printf("Hello World");
    El Head={.value=0, .next=NULL};
    addElementAtTheBeginning(&Head);
    addElementAtTheBeginning(&Head);
    addElementAtTheBeginning(&Head);
    showList(Head.next);
    //delete(&Head);
    //showList(Head.next);
    printf("\nOUT");
    deleteAll(&Head);
    showList(Head.next);
    return 0;
}

int addElementAtTheBeginning(Position zero_Element){
    Position new=(Position)malloc(sizeof(El));
    new->value=0;
    new->next=NULL;
    printf("\nnew_v: %d      new_next: %p", new->value, new->next);
    printf("\n Put value in new element");
    scanf("%d", &new->value);
    printf("\nnew_v: %d      new_next: %p", new->value, new->next);
    new->next=zero_Element->next;
    zero_Element->next=new;
    printf("\nnew_v: %d      new_next: %p", new->value, new->next);
    //free(new); //mislim da bi ovo uništilo listu
    return 0;
}
int showList(Position first_Element){
     if(first_Element==NULL) printf("Already an empty list!");
     while(first_Element!=NULL){
         printf("\n---\nValue: %d\n---\n", first_Element->value);
         first_Element=first_Element->next;
     }
     return 0;
}
int delete(Position zero_Element){
    int del_value=0;
    Position prev=(Position)malloc(sizeof(El));
    prev=zero_Element;
    Position on_it=(Position)malloc(sizeof(El));
    on_it=zero_Element->next;
    printf("\n enter value of element you want to delete");
    scanf("%d", &del_value);
    printf("\n kay, we will delete %d", del_value);
    while(on_it!=NULL && on_it->value!=del_value){
        on_it=on_it->next;
        prev=prev->next;
    }
    prev->next=on_it->next;
    free(on_it);
    return 0;
}
/*
int BrisiSve(Position P) 
{
	Position temp;
	while (P->next != NULL)
	{
		temp = P->next;
		P->next = temp->next;
		free(temp);
	}
	return EXIT_SUCCESS;
}*/
int deleteAll(Position zero_Element){
    printf("\nIN");
    Position on_it=(Position)malloc(sizeof(El));
    on_it=zero_Element->next;
    while(zero_Element->next!=NULL){
        on_it=zero_Element->next;
        zero_Element->next=on_it->next;
        free(on_it);
    }
    return 0;
}
