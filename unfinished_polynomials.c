#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1
#define MAX_CHAR 1024

struct _Element;
typedef struct _Element* Position;
typedef struct _Element{
    int coefficient;
    int exponent;
    Position next;
} Element;

int main(){
    
    char p1[MAX_CHAR]= {0};
    char p2[MAX_CHAR]= {0};
    Element Head1 = { .coefficient=0, .exponent=0, .next=NULL}; //list for 1st polynomial function, momentarily empty
    Element Head2 = { .coefficient=0, .exponent=0, .next=NULL}; //list for 2nd polynomial function momentarily empty
    
    FILE* file_pointer;
    file_pointer=fopen("polinom.txt","r");
    
    if(!file_pointer) printf("File failed to open!");
    
    fgets(p1,MAX_CHAR,file_pointer);//we read 1st line in the file, we got out 1st polynomial function, but in string form
    fgets(p2,MAX_CHAR,file_pointer);
    
    Position new = (Position)malloc(sizeof(Element));
    if (new == NULL) printf("Malloc nije uspješno alocirao memoriju!");
    
    do{
        sscanf(p1,"%dx^%d ", new->coefficient, new->exponent);
        
    }while(strlen(p1)!=0);
    
    return EXIT_SUCCESS;
}
