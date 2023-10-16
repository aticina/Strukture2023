/*
1. Napisati program koji prvo proèita koliko redaka ima datoteka, tj. koliko ima studenata
zapisanih u datoteci. Nakon toga potrebno je dinamièki alocirati prostor za niz struktura
studenata (ime, prezime, bodovi) i uèitati iz datoteke sve zapise. Na ekran ispisati ime,
prezime, apsolutni i relativni broj bodova.
Napomena: Svaki redak datoteke sadrži ime i prezime studenta, te broj bodova na kolokviju.
relatvan_br_bodova = br_bodova/max_br_bodova*100

*/
#include <stdio.h>
#include <stdlib.h>
#define MAX_CHAR 2024

typedef struct student {
    char ime[MAX_CHAR];
    char prezime[MAX_CHAR];
    int bodovi;
} Student;

int main()
{

    int br_r = 0;
    char buffer[MAX_CHAR] = " ";

    Student* niz_studenata_pointer;
    niz_studenata_pointer = (Student*)malloc(MAX_CHAR * (sizeof(Student)));


    FILE* file_pointer;
    file_pointer = fopen("TekstualnaDadoteka1.txt", "r");

    if (file_pointer == NULL) {
        printf("Dadoteka se nije uspješno otvorila!");
    }

    while (!feof(file_pointer)) {
        fgets(buffer, MAX_CHAR, file_pointer);
        br_r++;
    }
    printf("Dadoteka ima %d redaka.", br_r);




    return 0;
}
1. Napisati program koji prvo proita koliko redaka ima datoteka, tj. koliko ima studenata
zapisanih u datoteci. Nakon toga potrebno je dinamiki alocirati prostor za niz struktura
studenata (ime, prezime, bodovi) i uitati iz datoteke sve zapise. Na ekran ispisati ime,
prezime, apsolutni i relativni broj bodova.
Napomena: Svaki redak datoteke sadri ime i prezime studenta, te broj bodova na kolokviju.
relatvan_br_bodova = br_bodova/max_br_bodova*100

*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_CHAR 2024
#define FILE_NOT_OPEN -1
#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

typedef struct student {
	char ime[MAX_CHAR];
	char prezime[MAX_CHAR];
	double bodovi;
} Student;
//student[counter].name ili *(student+i).name
//%.2lf za ispis realnog broja na dvi decimale
//za scanf dodajemo u ciljnu varijablu & npr. scanf("%s %lf",niz,&broj) za string nam to ne treba niti array jer je samo ime niza ili stringa pointer na tu varijablu
//int Broj_Redaka(FILE*,int); ovo je loše, ne prosljeđuj file pointer funkciji nego sve odradi u funkciji otvaranje i zatvaranje
int Broj_Redaka(int);
int Unos_Studenata_U_Niz(int);

int main()
{

	int br_r = 0;
	int i = 0;
	char buffer[MAX_CHAR] = " ";

	Student* niz_studenata_pointer;
	niz_studenata_pointer = (Student*)malloc(MAX_CHAR * (sizeof(Student))); //(Student*) je castanje tj. osigurava da je varijabla tog tipa
	//provjerimo je li memorija usjpešno alocirana tj. malloc vrati pointer ako je usješno, a NULL ako je neuspješno
	if(!niz_studenata)


	FILE* file_pointer;
	file_pointer = fopen("TekstualnaDadoteka1.txt", "r");

	if (file_pointer == NULL) {
		printf("Dadoteka se nije uspjesno otvorila!");
	}

	while (!feof(file_pointer)) {
		fgets(buffer, MAX_CHAR, file_pointer);
		br_r++;
	}
	printf("Dadoteka ima %d redaka.", br_r);



	while (i<=br_r) {
		fgets(buffer, MAX_CHAR, file_pointer);
		niz_studenata_pointer[i]->ime=
		i++;

	}

	fclose(file_pointer);
	free(niz_studenata_pointer);


	return 0;
}

int Broj_Redaka( int br_r) {

	char buffer[MAX_CHAR];
	FILE* file_pointer;
	file_pointer = fopen("TekstualnaDadoteka1.txt", "r");

	if (file_pointer == NULL) {
		printf("Dadoteka se nije uspjesno otvorila!");
		return FILE_NOT_OPEN;
	}

	while (!feof(file_pointer)) {
		fgets(buffer, MAX_CHAR, file_pointer);
		br_r++;
	}
	printf("Dadoteka ima %d redaka.", br_r);

	return br_r;
}
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define EXIT_SUCCCESS 0
#define EXIT_FAILURE 1
#define MAX_LENGTH 1000

struct osoba;
typedef struct osoba* Position;
typedef struct osoba {
	char ime[MAX_LENGTH];
	char prezime[MAX_LENGTH] = " ";
	int god_r = 0;
	Position next;
}Osoba;

int Menu(Position Head);
int AddOnBegining

int main() {

	Osoba Head = { .next = NULL,.ime = {0},.prezime = {0},.god_r = 0 }; //definiranje i inicijalizacija Head-a



	return EXIT_SUCCESS;
}

int Menu(Position Head) {

}

//srtcpy(string u koji kopiramo vrijednost, string iz kojeg kopiramo vrijednost)
//student->ime=ime ne radi jer su pokazivači lokacije, a mi želimo baratai vrijednostima
//perror print error? daje da printaš rečenicu
// -> koristimo kad baratamnmo pokazivačima, kada želimo ispisati vrijednost a ne lokaciju na koju pokazivač pokazuje
Position Person
//newPerson=CreatePerson();if(newPerson){newPerson->next=head->next ovdje naparvimo da naš novi član pokazuje na prvi neprazni(ne head)član u listi; head->next=newPerson; ovime head odspojimo od prethodne prve i kazemo da pokazuje na naš novi član}
//da su linije obrnute izgubli bi ostatak liste čim bi ga head pustio

//int AddOnEnd(Position head) jer hea govori di je cijela lista Position newPerson=NULL
//newPerson=CreatePerson(); head=FindLast(head); newPerson->next=head->next;head->next=newPerson prvo nađemo zadnji Position FindLast(Position head){while(head->next!=NULL){head=head->next}return head; zadnji head koji smo return je pok na zadnji član liste}
