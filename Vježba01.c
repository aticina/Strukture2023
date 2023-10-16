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