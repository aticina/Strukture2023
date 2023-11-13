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

int main(){
    //we are putting operands on stack, when we receive an operator we pop two
    //operands, 1st one will be called operand 1 and second one will be called operand 2
    //result is pushed onto stack and so we do this till we have elements
    Stack Head={ .number=0, .next=NULL};
    readFromFile(&Head); //we are not sending Head-next cause stack is empty, so Head->next is NULL
    //Head by itself is nothing cause it is an empty element of type Stack, so we are sending it's address
    
    
  return EXIT_SUCCESS;
}

int readFromFile(Position current){
    
    char loaded_string[MAX_CHAR]={0};
    char* pointer_within_loaded_string = NULL; //with this we can move through string, without index
    pointer_within_loaded_string=loaded_string;
    double number_from_postfix=0;
    int checker=0;
    int status=0;
    char _operator={0};
    
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
    //and with each +=checker we iterate so in our example if we go through rest of function:
    //2.000000 2      0x7ffefa6169d0
    // ^we read a double 2.000000 from file plus empty space behind it, checker=2, status=2 
    //so we enter else, we are at loaded_string[0], we are ready to read a character(+,- or *)
    //
    //2.000000 1      0x7ffefa6169d2
    //2.000000 1      0x7ffefa6169d3
    //3.000000 1      0x7ffefa6169d4
    //-5.000000 2     0x7ffefa6169d5
    //3.000000 3      0x7ffefa6169d7
    //3.000000 1      0x7ffefa6169da
    //3.000000 1      0x7ffefa6169db
    //3.000000 1      0x7ffefa6169dc
    while(strlen(pointer_within_loaded_string)>0){
        //sscanf returns number of chracters read if successful and -1 if it failed
        // %n returns the number of characters that sscanf read in total in this turn
        // checker checks how many characters were read with sscanf in one go
        status=sscanf(pointer_within_loaded_string," %lf",&number_from_postfix);
        if(status==-1){
            printf("Failure at loading postfix.");
            return EXIT_FAILURE;
        }
        printf("\n %lf %d", number_from_postfix, status);
        printf("\t %p", pointer_within_loaded_string);
        
        if(number_from_postfix>=0 && status==1){
            //push();
            pointer_within_loaded_string+=2;
            printf("Pozitiva");
        }
        else if(number_from_postfix<0 && status==1){
            pointer_within_loaded_string+=2;
            printf("Negativa");
            
        }
        else if(status==0){
            printf("STATUS 0");
            sscanf(pointer_within_loaded_string," %c", &_operator);
            printf("Operator je: %c", _operator);
            //operation();
            pointer_within_loaded_string+=2;
        }
    }
    
    
    fclose(file_pointer);
    return EXIT_SUCCESS;
}
/*while/strlen(currentbuffer))>0){
status=sscanf(currentbuff, %lf %n",&number, &numbytes)
if(status!=1){
  sscanf(currentbuffer," %c %n", &operation, &numbytes)
  status=popandpreformoperation(head,operation,result)
  if(status !=EXIT_SUC)
    return EXIT_F

  number=*result
}
newstackelement=createstackelelmentt(number)
if(!newstackelement) return exit_value
}
current buffer+= numbytes
printf("I%sI <-->" currentbuffer):;
push(head, newstackelement)
}ovdje valjda zavrsava while
return checkstackandextractresult(head, result)
*/
