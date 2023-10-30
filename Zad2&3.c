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
Position findFollowingBySurname(Position);//<-obsolete function, use next on whatever element you need to find them
int addElementAtTheBeginning(Position);
int showList(Position);
int addElementAtTheEnd(Position);
Position findBySurname(Position);
int deleteElement(Position);
int addInFrontOf(Position);
int addBehindOf(Position);

int main() {

    int number_of_wanted_service = 0;
    Person Head = { .name = {0},.surname = {0},.birthYear = 0, .next = NULL, };//inicijalizacija Head-a sve na neutralnu vrijednost
    while (number_of_wanted_service >= 0) {
        printf("\n \n \n To exit the program enter any negative number! \n Choose service you want to access by providing coresponding number next to it in a written menu."
            "\n 1 -adds new element at the beginning of the list \n"
            "\n 2 -shows/outputs all list's elements"
            "\n 3 -adds new element at the end of the list"
            "\n 4 -searches list by surname"
            "\n 5 -deletes choosen list member"
            "\n 6 -finds previous"
            "\n 7 -finds following"
            "\n 8 -adds an element in front of choosen element"
            "\n 9 -adds an element behind the choosen element");
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
        findPreviousBySurname(Head);
        return EXIT_SUCCESS;
        break;

    case 7:
        findFollowingBySurname(Head->next);
        return EXIT_SUCCESS;
        break;

    case 8:
        addInFrontOf(Head);
        return EXIT_SUCCESS;
        break;

    case 9:
        addBehindOf(Head);
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
        //return EXIT_FAILURE;
    }
    Position THEElement = findBySurname(current->next);
    Position temp = findPreviousBySurname(current);
    temp->next = THEElement->next;
    free(THEElement);
}
}

Position findFollowingBySurname(Position current) {
    Position THEElement = findBySurname(current);
    Position following = THEElement->next;
    /*while(current!=NULL && current!=THEElement){
        current=current->next;
        following=current->next;
    }*/
    if (following == NULL) {
        printf("This element is last one in the list, it does not have a following element.");
    }
    printf("Following element is \n %s \n %s \n %d", following->name, following->surname, following->birthYear);
    return following;
}

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
    Position temp = findFollowingBySurname(current->next);
    new->next = temp;
    THEElement->next = new;

    free(new);
    return EXIT_SUCCESS;
}
zapis polinoma u datoteci V
1x^2 3x^3 4x^7 5x^5
mogu biti i negativni brojevi i nula, moramo ih poredati po padajućim eksponentima
slažemo ove u struct
imamo 4 liste (pol1,pol2,njihov zbroj,njihov umnožak)
i čitamo ih i spremamo iz datoteke
funk readFile(˛pol1,˛pol2,FILE*)
provjeri jemo li otvorili file
fgets-čita red u buffer iz kojeg kasnije čitamo što trebamo
%dx^%d %n ovako čitamo formatirano iz datoteke
sscanf
newel=createel-spremamo stvari u strukturu, pri unosu sortiramo
neka merge after funkcija

H-NULL
novi el stvorimo4x^2 
idemo u insert sorted pa unutri je
while(current->next!=NULL && current->next->exponent>newelement->exponent
current=current->next 
int mergeafter(position current, position newelemenmt){
newelement->next=current->next
current->next=newelement}
mergeafter(Position current, position newelement){
if(cur->next==NULL II cur->next->exponent!=newelement->exponent
insertafter(current,neweleement)

nama ti polinomi ne moraju biti maksimalno sređeni i skraćeni, moramo na to paziti u programu
koristimo i funkciju delete after

currentBuffer+=numbBytes čitamo iz buffera tako da mu hopsamo s adrese na adresu
