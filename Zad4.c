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

int polynomialFunctionInput(Position,Position);
int polynomialSum();
int polynomialProduct();

int main(){
    
    char p1[MAX_CHAR]= {0};
    char p2[MAX_CHAR]= {0};
    Element Head1 = { .coefficient=0, .exponent=0, .next=NULL}; //list for 1st polynomial function, momentarily empty
    Element Head2 = { .coefficient=0, .exponent=0, .next=NULL}; //list for 2nd polynomial function momentarily empty
    
    
    
    fgets(p1,MAX_CHAR,file_pointer);//we read 1st line in the file, we got out 1st polynomial function, but in string form
    fgets(p2,MAX_CHAR,file_pointer);
    
    Position new = (Position)malloc(sizeof(Element));
    if (new == NULL) printf("Malloc nije uspješno alocirao memoriju!");
    
    do{
        sscanf(p1,"%dx^%d ", new->coefficient, new->exponent);
        
    }while(strlen(p1)!=0);
    
    return EXIT_SUCCESS;
}

int polynomialFunctionInput(Position current1, Position current2){

    FILE* file_pointer;
    file_pointer=fopen("polinom.txt","r");
    
    if(!file_pointer) printf("File failed to open!");

    fclose(file_pointer);
}
/*sortirani unos u listu, pokušaj naći kodove od drugih da vidiš kako to funkcionira
i printaj polinome
zbrajanje 2 načina
1->zbrajanmo dok oba polinoma ne dodu do kraja(veznik i), 3 slučaja, ako su im eksponenti isti createandinsertafter(zove se u sva 3 slučaja)(unos u listu sa zbrojem)
ako mi je expo2 veći od expo 2 unosimo samo veći u polinom, ako expo 1 veći unosimo samo 1 u rezultantu listu;
current polinoma su prvi non-empty, currrent sume je head
ako nam od nekog polinoma ostane nešto kad jje drugi na nuli, onda to rješimo ispod tri uvjeta currentpoly1==NULL remainingpoly=poly 2 else remaining poly=poly2
programerski način
current poly1 i i 2 su prvi non-empty članovi, unsemo sve element 1 polinoma u listu sume te idemo po drugom polinomu i zbrajamo koeficijenete ako su im eksponentii isti, a samo dodamo novi član s novim eksponentom ako nije već u sum to samo doda u sumu lista

*/
OOOOOOOOOOOOOOOOOO
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

int polynomialFunctionInput(Position, Position);
int polynomialSum(Position,Position,Position);
int polynomialProduct(Position,Position,Position);


int main(){
    
    Element Head1 = { .coefficient=0, .exponent=0, .next=NULL}; //list for 1st polynomial function, momentarily empty
    Element Head2 = { .coefficient=0, .exponent=0, .next=NULL}; //list for 2nd polynomial function momentarily empty
    Element HeadS = { .coefficient=0, .exponent=0, .next=NULL}; //list for sum
    Element HeadP = { .coefficient=0, .exponent=0, .next=NULL}; //list for product
    
    polynomialFunctionInput(&Head1, &Head2);
    
    fgets(p1,MAX_CHAR,file_pointer);//we read 1st line in the file, we got out 1st polynomial function, but in string form
    fgets(p2,MAX_CHAR,file_pointer);
    
    Position new = (Position)malloc(sizeof(Element));
    if (new == NULL) printf("Malloc nije uspješno alocirao memoriju!");
    
    do{
        sscanf(p1,"%dx^%d ", new->coefficient, new->exponent);
        
    }while(strlen(p1)!=0);
    
    return EXIT_SUCCESS;
}

int polynomialFunctionInput(Position current1, Position current2){

    FILE* file_pointer;
    file_pointer=fopen("poly.txt","r");
    
    if(!file_pointer) printf("File failed to open!");

    while(feof(file_pointer)==0){
        
        Position new = (Position)malloc(sizeof(Element));
        fscanf(file_pointer,"%dx^%d", &new->coefficient, &new->exponent);
        
        if(current1->next==NULL){ //if list is empty, just add element
            current1->next=new;
            new->next=NULL;
            
        }
        if else(current1->next->exponent < new->exponent){
            //add new at beginning
            new->next=current->next;
            current->next=new;
        }
        if else(current->next->exponent > new->exponent){
            while(current->next->exponent > new->exponent){
                current=current->next;
            }
            if(current->exponent==new->exponent){
                current->coefficient=current->coefficient+new->coefficient;
                free(new); //since exponent are the same we will not add new element int he list, but
                //use it's coefficient to increase coefficient of element that is already in the list
            }
            else{
                //add before 
                current
            }
        }
    }
    fclose(file_pointer);
}
/*sortirani unos u listu, pokušaj naći kodove od drugih da vidiš kako to funkcionira
i printaj polinome
zbrajanje 2 načina
1->zbrajanmo dok oba polinoma ne dodu do kraja(veznik i), 3 slučaja, ako su im eksponenti isti createandinsertafter(zove se u sva 3 slučaja)(unos u listu sa zbrojem)
ako mi je expo2 veći od expo 2 unosimo samo veći u polinom, ako expo 1 veći unosimo samo 1 u rezultantu listu;
current polinoma su prvi non-empty, currrent sume je head
ako nam od nekog polinoma ostane nešto kad jje drugi na nuli, onda to rješimo ispod tri uvjeta currentpoly1==NULL remainingpoly=poly 2 else remaining poly=poly2
programerski način
current poly1 i i 2 su prvi non-empty članovi, unsemo sve element 1 polinoma u listu sume te idemo po drugom polinomu i zbrajamo koeficijenete ako su im eksponentii isti, a samo dodamo novi član s novim eksponentom ako nije već u sum to samo doda u sumu lista

*/
