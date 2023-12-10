/*7. Napisati program koji pomoću vezanih listi (stabala) predstavlja strukturu direktorija.
Omogućiti unos novih direktorija i pod-direktorija, ispis sadržaja direktorija i
povratak u prethodni direktorij. Točnije program treba preko menija simulirati
korištenje DOS naredbi: 1- "md", 2 - "cd dir", 3 - "cd..", 4 - "dir" i 5 – izlaz.*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_CHAR 1000
#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

struct directory;
typedef struct directory* Position;
typedef struct directory{
    int value;
    Position parent;
    Position child;
} Directory;

int Menu(int,Position);
int MakeDirectory();


int main()
{
    int key_number=0;

    Directory Head={.value=0, .parent=NULL, .child=NULL};
    
    printf("Welcome to a program where you build your temporary directory. \n"
    "Enter a number to preform one of the following actions:\n"
    "0 -create directory\n"
    "1 -change directory\n"
    "2 -go back to parent directory\n"
    "3 -display files in the working directory\n"
    "4 -exit the program\n");
    
    scanf("%d", &key_number);
    
    Menu(key_number,&Head);
    
    return EXIT_SUCCESS;
}

int Menu(int key_number,Position current){
    
    switch key_number:
    case 0:
        break;
    case 1:
        break;
    case 2:
        break;
    case 3:
        break;
    case 4:
        exit(0);//void exit(status) is function that shuts down the program and closes all streams it used,
        //temporary data gets deleted, buffer/working memory gets flushed, it's in stdlib.h
        //it is of void type cause it cannot return anything to a process it just shut down
        //if we put status as 0 an exit() will give that to parent process/computer to let them know
        //proces was finished successfully, if we put 1 it means program encountered an error
        break;
        
    return EXIT_SUCCESS;
}
