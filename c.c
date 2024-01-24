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

int main(){
    
    Element Head={.country_name={0},.next=NULL,.p_tree=NULL};
    createList(&Head);
    
    
    return EXIT_SUCCESS;
}

int createList(c_Position c_current){
    
    char new_country_name[MAX_CHAR]={0};
    char file_w_towns[MAX_CHAR]={0};
    
    FILE* fp;
    fp=fopen("countries.txt","r");
    if(!fp){
        printf("File countries.txt failed to open!");
        return EXIT_FAILURE;
    }
    while(!feof(fp)){
        scanf("%s %s", new_country_name, file_w_towns);
        printf("%s %s\n",new_country_name,file_w_towns);
    }
    return EXIT_SUCCESS;
}
