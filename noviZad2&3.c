//OVO JE NAJNOVIJA VERZIJA KODA KOJA KOMBINIRA 2. I 3. ZADATAK, IMA MENU I CREATEELEMENT FUNKCIJE

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_CHAR 1000
#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1
#define MALLOC_FAIL -1


struct _Person; //deklaracija strukture, ali ne i inicijalizacija ->cilj je da možemo deklarirati pokazivač tipa _Person koji je dio strukture koja još nije inicijalizirana
typedef struct _Person* Position; //deklaracija pokazivača Position koji je tipa _Person, a korisiti se tako da svaki član jednostruke liste
//sadržava pokazivač na sljedeći član liste (s time da nitko ne pokazuje na head i zadnji član pokazuje na NULL). Tako da trenutno ne pokazuje na išta?
typedef struct _Person {
    char name[MAX_CHAR];//char element koji svaki član js liste ima
    char surname[MAX_CHAR];//char element koji svaki član js liste ima
    int birthYear;//int element koji svaki član js liste ime
    Position next;//tip varijable je Position, ime varijable je next? ILI Position je sam po sebi varijabla, ime pokazivača i ovo je specifičan način inicijalizacije da je
    //Position pokazivač koji pokazuje na adresu/vrijednost koja je u memoriji spremljena pod imenom next
} Person; //postavili smo typedef naravno

int Menu(Position, int);
Position CreateElement();
Position findPreviousBySurname(Position);
//Position findFollowingBySurname(Position); <-obsolete function, use next on whatever element you need to find them
int addElementAtTheBeginning(Position);
int showList(Position);
int addElementAtTheEnd(Position);
Position findBySurname(Position);
int deleteElement(Position);
int addInFrontOf(Position);
int addBehindOf(Position);
int writeListInFile(Position);
Person makeListFromFile();

int main() {

    int number_of_wanted_service = 0;
    Person Head = { .name = {0},.surname = {0},.birthYear = 0, .next = NULL, };//inicijalizacija Head-a sve na neutralnu vrijednost
    while (number_of_wanted_service >= 0) {
        printf("\n \n \n To exit the program enter any negative number! \n Choose service you want to access by providing coresponding number next to it in a written menu."
            "\n 1 -adds new element at the beginning of the list"
            "\n 2 -shows/outputs all list's elements"
            "\n 3 -adds new element at the end of the list"
            "\n 4 -searches list by surname"
            "\n 5 -deletes choosen list member"
            "\n 6 -adds new element in front of choosen element"
            "\n 7 -adds new element behind choosen element"
            "\n 8 -writes the list in a file"
            "\n 9 -makes a list by reading from a file \n");
        scanf("%d", &number_of_wanted_service);
        //printf("number_of_wanted_service is: %d", number_of_wanted_service);
        Menu(&Head, number_of_wanted_service);
    }



    return 0;
}

int Menu(Position Head, int number_of_wanted_service) {
    switch (number_of_wanted_service) {
    case 1:
        addElementAtTheBeginning(Head); //uzimamo Head, a ne &Head jer je Menu funkcija primila adresu pa je Head zapravo adresa
        return EXIT_SUCCESS;
        break;

    case 2:
        showList(Head->next);
        return EXIT_SUCCESS;
        break;

    case 3:
        addElementAtTheEnd(Head);
        return EXIT_SUCCESS;
        break;

    case 4:
        findBySurname(Head->next);
        return EXIT_SUCCESS;
        break;

    case 5:
        deleteElement(Head);
        return EXIT_SUCCESS;
        break;

    case 6:
        addInFrontOf(Head);
        return EXIT_SUCCESS;
        break;

    case 7:
        addBehindOf(Head);
        return EXIT_SUCCESS;
        break;

    case 8:
        writeListInFile(Head->next);
        return EXIT_SUCCESS;
        break;

    case 9:
        makeListFromFile();
        return EXIT_SUCCESS;
        break;



    default:
        printf("Number not recognized, please try again.");
        return EXIT_FAILURE;
    }

}

Position CreateElement() {

    char new_name[MAX_CHAR] = { 0 };
    char new_surname[MAX_CHAR] = { 0 };
    int new_birthYear = 0;

    Position new = (Position)malloc(sizeof(Person));
    if (new == NULL) {
        printf("Malloc nije uspješno alocirao memoriju!");
        //return MALLOC_FAIL;
    }
    printf("Name?\n");
    scanf("%s", new_name);
    printf("Surname?\n");
    scanf("%s", new_surname);
    printf("Year of birth? \n");
    scanf("%d", &new_birthYear);
    strcpy(new->name, new_name);
    strcpy(new->surname, new_surname);
    new->birthYear = new_birthYear;

    return new;

}

int addElementAtTheBeginning(Position current) {

    Position new;
    new = CreateElement();
    new->next = current->next; //novi član pokazuje na prethodni prvi član

    current->next = new; //head pokazuje na novi član
    //printf("\n %s \n %s \n %d \n %d", new_name, new->name, new_birthYear, new->birthYear);
    return EXIT_SUCCESS;
}

int showList(Position current) {

    if (current == NULL) { //checking if we got any list to go through to begin with, if not then this function is useless
        printf("This list is empty!");
        return EXIT_FAILURE;
    }

    while (current != NULL) {
        printf("\n");
        printf("\n ----- \n Name: %s \n Surname: %s \n Birth Year: %d \n -----", current->name, current->surname, current->birthYear);
        current = current->next;
    }

    return EXIT_SUCCESS;
}

int addElementAtTheEnd(Position current) {

    while (current->next != NULL) {
        current = current->next;
    }

    Position new;
    new = CreateElement();

    current->next = new;
    new->next = NULL;

    return EXIT_SUCCESS;
}

Position findBySurname(Position current) { //this current is 1st non-empty list memeber(one after Head)

    char wanted_surname[MAX_CHAR] = { 0 };
    printf("\n Please enter surname.");
    scanf("%s", wanted_surname);
    printf("Just checking if surname is in, here: %s", wanted_surname);

    if (current == NULL) { //checking if we got any list to go through to begin with, if not then this function is useless
        printf("This list is empty!");
        //return EXIT_FAILURE;
    }

    while (strcmp(current->surname, wanted_surname)) {
        current = current->next;
        if (current == NULL) {
            printf("Program was not able to find an element with that surname.");
            //return EXIT_FAILURE;
        }
    }
    printf("\n ----- \n Name: %s \n Surname: %s \n BirthYear:  %d \n ----- ", current->name, current->surname, current->birthYear);
    return current;
}

Position findPreviousBySurname(Position current) { //current is Head
    printf("In order to find the previous element program needs to be given information \n"
        "on which element you want to find previous of, that is defined by giving surname. \n"
        "Program will now call findBySurname function, please enter the surname. \n");
    Position THEElement = findBySurname(current->next);//THEElement will be at element whose prev we are searching for
    printf("OVO: %s", THEElement->surname);
    Position previous = current;
    //we are making an element previous that is firstly the same element
    //as the current
    current = current->next;//moving current for 1 place
    if (current == NULL) {
        printf("Empty list!");
        //return
    }
    if (current == THEElement) {
        printf("This element is first in the list, it does not have previous!");
        //return Head?
    }
    while (current != NULL && current != THEElement) {
        previous = current;
        current = current->next;
    }
    printf("prethodnik je %s \n %s \n ", previous->name, previous->surname);
    return previous;
}

int deleteElement(Position current) { //current is showing at Head(empty element)

    if (current->next == NULL) { //checking if we got any list to go through to begin with, if not then this function is useless
        printf("This list is empty!");
        return EXIT_FAILURE;
    }
    
    Position THEElement = findBySurname(current->next);
    Position temp = findPreviousBySurname(current);
    temp->next = THEElement->next;
    free(THEElement);
    
    return EXIT_SUCCESS;
}

/*Position findFollowingBySurname(Position current) {
    Position THEElement = findBySurname(current);
    Position following = THEElement->next;
    while(current!=NULL && current!=THEElement){
        current=current->next;
        following=current->next;
    
    if (following == NULL) {
        printf("This element is last one in the list, it does not have a following element.");
    }
    printf("Following element is \n %s \n %s \n %d", following->name, following->surname, following->birthYear);
    return following;
}THIS FUNCTION MAKES NO PRACTICAL SENSE, JUST USE CURRENT->NEXT->NEXT */

int addInFrontOf(Position current) {

    Position new = (Position)malloc(sizeof(Person));
    new = CreateElement();
    Position THEElement = findBySurname(current->next);
    Position temp = findPreviousBySurname(current);
    new->next = THEElement;
    temp->next = new;

    free(new);

    return EXIT_SUCCESS;
}

int addBehindOf(Position current) {
    
    Position new = (Position)malloc(sizeof(Person));
    new = CreateElement();
    Position THEElement = findBySurname(current->next);
    new->next = THEElement->next;
    THEElement->next = new;

    free(new);
    return EXIT_SUCCESS;
}

int writeListInFile(Position current){//curret is first non-empty element
    
    FILE* file_pointer;
    file_pointer=fopen("File_with_inputedlist.txt", "w");
    
    if(!file_pointer){
        printf("File did not open successfully!");
        return EXIT_FAILURE;
    }
    
    while(current!=NULL){
        fprintf(file_pointer,"\n\n %s \n %s \n %d", current->name, current->surname, current->birthYear);
        current=current->next;
    }
    
    fclose(file_pointer);
    return EXIT_SUCCESS;
}

Person makeListFromFile(){
    FILE* file_pointer;
    file_pointer=fopen("File_with_inputedlist.txt","r");
    
    if(!file_pointer){
        printf("File failed to open!");
        //return ?;
    }
    
    printf("U funkciji smo :3");
    
    Person Head = { .name = {0},.surname = {0},.birthYear = 0, .next = NULL, };
    while(!feof(file_pointer)){
        printf("U petlji smo takoder");
        Position new = (Position)malloc(sizeof(Person));
        fscanf(file_pointer,"\n\n %s \n %s \n %d", new->name, new->surname, &new->birthYear);
        Head.next=new;
        new->next=NULL;
        free(new);
    }
    
    showList(Head.next);
    
    fclose(file_pointer);
    return Head;
}
//------------------
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

Position Menu(int,Position,Position);
Position MakeDirectory(Position);
Position ChangeDirectory(Position,Position);


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
    
    Current=Menu(key_number,Current,&Head);
    }
    
    return EXIT_SUCCESS;
}

Position Menu(int key_number,Position Current,Position Root){
    
    switch (key_number){
    case 0:
        Current=MakeDirectory(Current);//current je promjenjiv, može biti root ali ne mora, ovisi o cd funkciji?
        break;
    case 1:
        Current=ChangeDirectory(Current,Root);
        break;
    /*case 2:
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
    printf("Check up: %s\n",Current->name);
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
    printf("Check up: %s\n",Current->name);
    return Current;
    
}

Position ChangeDirectory(Position Current,Position Root){
    printf("Check up: %s\n",Current->name);
    //char method=" ";
    char path[MAX_CHAR]=" ";
    printf("You are changing directory. Please enter path to wanted directory:\n");
    scanf("%s",path);
    
    /*printf("You are changing directory. Do you want to use absolute or relative path?\nEnter A for absolute or R for relative:\n");
    scanf("%c",&method);
    if(method=="A"){
        Current=Root;
        printf("Please enter the path")
    }
    else if(method=="R"){
        
    }
    else{
        printf("You made unrecognizable entry, please try again.");
        return Current;
    }*/
    Position ChangeDirectory(Position Current,Position Root){
    printf("Check up: %s\n",Current->name);
    //char method=" ";
    char path[MAX_CHAR]="";
    char dir_name[MAX_CHAR]="";
    int i=1;//we are starting with index 1 and skipping 1st chaaracter in the string cause we know it will be /
    Position safekeep_of_OG_Current=(Position)malloc(sizeof(Directory));
    safekeep_of_OG_Current=Current;
    printf("You are changing directory. Please enter path to wanted directory:\n");
    scanf("%s",path);//example: /Root/home/me
    
    if(!strcmp(path,Current->name)){//just checks if request is sensible, example, we expect "home" so no / to worry about
        printf("You already are in %s directory!", path);
        return Current;
    }
    

    for(i;i<strlen(path);i++){//strlen(path)=13, max i=12 which is last letter of the string anyway
        dir_name=""; //returning to empty string so we don't get "Roothome", but only "home"
        while(path[i]!='/'){
            strncat(dir_name,&path[i],1);
            i++;
        }
        printf("%s",dir_name);
        while(Current->next!=NULL && strcmp(dir_name,Current->name)){
            Current=Current->next;//searching through brothers first
            //from while we get out when Current->name=dir_name so we are in c+wanter directory, or when we go through all brothers
        }
        if(strcmp(dir_name,Current->name)){
            printf("There is no such directory!");
            return safekeep_of_OG_Current;
        }
    }
    printf("%s",Current->name);
    return Current;

    //how loop should work, but is not working->1st loop i=1,1st while(path[1] aka R != '/') TRUE so strncat adds 'R' to empty dir_name string
    //we iterate i so it is i=2, 2nd while(path[2] aka 'o' !='/')TRUE so strncat adds 'o' to dir_name, i=3, while TRUE, we add another letter to
    //dir_name, i=4, while TRUE, we add another letter to dir_name, i=5, while(path[5] aka '/' != '/') FALSE so we exit the while loop
    //afterwards we have i=5 and dir_name="Root"
    //2nd for loop i=6(cause i++ in for increased it from 5),entering while(path[6] aka 'h'!='/')TRUE and so on

    
}
