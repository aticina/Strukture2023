#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_CHAR 1000
#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1
#define MALLOC_FAIL -1

struct _Stack;
typedef struct _Stack* Position;
typedef struct _Stack{
    double number;
    Position next;
} Stack;

int readFromFile(Position);
int push(Position, double);
double pop(Position);
int operation(Position, char);

int main(){
    //we are putting operands on stack, when we receive an operator we pop two
    //operands, 1st one will be called operand 1 and second one will be called operand 2
    //result is pushed onto stack and so we do this till we have elements
    Stack Head={ .number=0, .next=NULL};
    readFromFile(&Head); //we are not sending Head-next cause stack is empty, so Head->next is NULL
    //Head by itself is nothing cause it is an empty element of type Stack, so we are sending it's address
    printf("Result is: %lf", Head.next->number);
    
  return EXIT_SUCCESS;
}

int readFromFile(Position current){ //current is &Head
    
    char loaded_string[MAX_CHAR]={0};
    char* pointer_within_loaded_string = NULL; //with this we can move through string, without index
    pointer_within_loaded_string=loaded_string;
    double number_from_postfix=0;
    int status=0;
    char operation_type = {0}; //ISSUE! IT SAYS OPERATION_TYPE IS INT FOR SOME REASON!
    
    FILE* file_pointer;
    file_pointer=fopen("postfiks.txt","r");
    if(!file_pointer){
        printf("File failed to open!");
        return EXIT_FAILURE;
    }
    
    //we are loading string from file to our buffer named loaded_string, buffer is string too
    fgets(loaded_string, MAX_CHAR, file_pointer); //so now we got whole postfix,operands and operatorss together
    //printf("%s",loaded_string); we loaded correctly
    
    //pointer_within_loaded_string will in first loop be pointing at loaded_string[0]
    //and with it we iterate so in our example +2 cause we are taking into account
    //the fact tha format we expect is that all operands and operators have to be 
    //separated by 1 space 
    //If we go through rest of function we see 2 case scenarios
    // 1st we load a double, status=1 (doesn't matter if double is positive or negative it reads as 1 it counts as one [index]in string)
    //2nd we don't load anything,status==0,so we load operator
   
    while(strlen(pointer_within_loaded_string)>0){
        //sscanf returns number of chracters read if successful and -1 if it failed
        // %n returns the number of characters that sscanf read in total in this turn
        // checker checks how many characters were read with sscanf in one go
        status=sscanf(pointer_within_loaded_string," %lf",&number_from_postfix);
        if(status==-1){
            printf("Failure at loading postfix.");
            return EXIT_FAILURE;
        }
        //printf("\n %lf %d", number_from_postfix, status);
        //printf("\t %p", pointer_within_loaded_string);
        
        if(status==1){
            push(current, number_from_postfix);
            pointer_within_loaded_string+=2;
        }
        else if(status==0){
            //printf("STATUS 0");
            sscanf(pointer_within_loaded_string," %c", operation_type);
            if(status==-1){
                printf("Failure at loading postfix.");
                return EXIT_FAILURE;
                
            }
            //printf("Operator je: %c", _operator);
            operation(current, operation_type);
            pointer_within_loaded_string+=2;
        }
    }
    
    
    fclose(file_pointer);
    return EXIT_SUCCESS;
}

int push(Position current, double number_from_postfix){//add at the beginning for linked lists==push in stack
    
    Position new = (Position)malloc(sizeof(Stack));
    if(new==NULL){
        printf("Malloc couldn't allocate memory!");
        return EXIT_FAILURE;
    }
    
    new->number=number_from_postfix;
    new->next=current->next;
    current->next=new;
    
    free(new);
    
    return EXIT_SUCCESS;
}

double pop(Position current){//it's like delete from the beginning

    double r_number=0;
    Position to_be_deleted = current->next;
    current->next=current->next->next;
    
    r_number=to_be_deleted->number;
    
    free(to_be_deleted);
    
    
    return r_number;
}

int operation(Position current, char operation_type){ //current is &Head
    
    double operand1=0;
    double operand2=0;
    
    switch(operation_type){
        
        case "+":
            operand1=pop(current);
            operand2=pop(current);
            push(current, operand1+operand2);
            break;
        
        case "-":
            operand1=pop(current);
            operand2=pop(current);
            push(current, operand2-operand1); //or 1-2 ?
            break;
            
        case "*":
            operand1=pop(current);
            operand2=pop(current);
            push(current, operand1*operand2);
            break;
            
        case "/":
            operand1=pop(current);
            operand2=pop(current);
            push(current, operand2/operand1);
            break;
    }
    return EXIT_SUCCESS;
}
