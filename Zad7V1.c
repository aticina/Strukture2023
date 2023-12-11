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
    char name[MAX_CHAR];
    Position next;//points at sibling directory
    Position child;//points at 1st of however many child directories(all children are in the contected list, new ones are added at the beginning)
} Directory;

Position Menu(int,Position);
Position MakeDirectory(Position);
//int ChangeDirectory(Position, char[]);


int main(){
    
    int key_number=0;

    Directory Head={.name=" ", .next=NULL, .child=NULL};
    Position Current=(Position)malloc(sizeof(Directory));
    Current=&Head;//so we always know where we are..?
    
    while(1){
    printf("Welcome to a program where you build your temporary directory. \n"
    "Enter a number to preform one of the following actions:\n"
    "0 -create directory\n"
    "1 -change directory\n"
    "2 -go back to parent directory\n"
    "3 -display files in the working directory\n"
    "4 -exit the program\n");
    
    scanf("%d", &key_number);
    
    Current=Menu(key_number,Current);
    }
    
    return EXIT_SUCCESS;
}

Position Menu(int key_number,Position Current){
    
    switch (key_number){
    case 0:
        Current=MakeDirectory(Current);//current je promjenjiv, može biti root ali ne mora, ovisi o cd funkciji?
        break;
    /*case 1:
        break;
    case 2:
        break;
    case 3:
        break;*/
    case 4:
        exit(0);//void exit(status) is function that shuts down the program and closes all streams it used,
        //temporary data gets deleted, buffer/working memory gets flushed, it's in stdlib.h
        //it is of void type cause it cannot return anything to a process it just shut down
        //if we put status as 0 an exit() will give that to parent process/computer to let them know
        //proces was finished successfully, if we put 1 it means program encountered an error
        break;
    }    
    return Current;
}

Position MakeDirectory(Position Current){//function receives directory
    printf("%s\n",Current->name);
    char new_name[MAX_CHAR]=" ";
    printf("You are creating a new directory which will be a sub-directory of a current working directory.\nEnter name of new directory: \n");
    scanf("%s",new_name);
    
    Position new_dir=(Position)malloc(sizeof(Directory));//we create free directory in dynamic memory-easy
    strcpy(new_dir->name,new_name); //we name it-easy, we just need a  name and that directory's position that malloc gives us
    new_dir->child=NULL;//drectory is new and as such it cannot have any children yet, so NULL children for it
    //hard part 1-we need to connect it into the tree by having current dir point have new dir as their newest
    //child, therefore child will be put at the begnning of connected list
    new_dir->next=Current->child; //new dir is pointing at current directories current 1st child, so old child won't get lost
    Current->child=new_dir;//current directory becomes a parent to new directory, it is no longer pointing to old child
    //instead it is pointing at new one which is pointing at old one
    //with this new directory has name, next and no children. If current directory has no children to begin with
    //new directory will point to NULL just like current used to, and current will point at new dir
    Current=new_dir;//this is so we immidenatly position ourselves in newly created directory, we cd but automatically
    printf("%s\n",Current->name);
    return Current;
    
}
