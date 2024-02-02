#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1
#define EXIT_SYSTEM_FAILURE -3
#define MAX_CHAR 1024

struct student;
typedef struct student* Position;
typedef struct student {
	char name[MAX_CHAR];
	char surname[MAX_CHAR];
	int id;
	int grade;
	Position next;
} Student;

//function will open file studenti.txt, read data on name,surname,id
int ReadFromStudenti(Position);
int ReadFromPredmet1(Position);
int DeleteThem(Position);
int ShowList(Position);

int main() {

	Student Head = { .name = {0},.surname = {0},.id = 0,.grade = 0,.next = NULL };
	ReadFromStudenti(&Head);
	ReadFromPredmet1(&Head);
	DeleteThem(&Head);
	ShowList(&Head);


	return EXIT_SUCCESS;
}

int ReadFromStudenti(Position current) { //current is &Head

	char new_name[MAX_CHAR] = { 0 };
	char new_surname[MAX_CHAR] = { 0 };
	int new_id = 0;

	Position new = (Position)malloc(sizeof(Student));
	strcpy(new->name, "");
	strcpy(new->surname, "");
	new->id = 0;
	new->grade = 0;
	new->next = NULL;
	if (new == NULL) {
		printf("Malloc fail-1st malloc!");
		return EXIT_SYSTEM_FAILURE;
	}

	Position prev = (Position)malloc(sizeof(Student));
	prev = current;
	if (prev == NULL) {
		printf("Malloc fail!2nd");
		return EXIT_SYSTEM_FAILURE;
	}

	Position on_it = (Position)malloc(sizeof(Student));
	if (on_it == NULL) {
		printf("Malloc fail!3rd");
		return EXIT_SYSTEM_FAILURE;
	}
	on_it = current->next;

	Position safekeep = (Position)malloc(sizeof(Student));
	safekeep = current;
	if (safekeep == NULL) {
		printf("Malloc fail!4th");
		return EXIT_SYSTEM_FAILURE;
	}

	FILE* fp = NULL;
	fp = fopen("studenti.txt", "r");
	if (!fp) {
		printf("File studenti.txt failed to open.");
		return EXIT_SYSTEM_FAILURE;
	}

	
	while (!(feof(fp))) {

		fscanf(fp, "%s %s %d", new_surname, new_name, &new_id);
		strcpy(new->surname, new_surname);
		strcpy(new->name, new_name);
		new->id = new_id;

		prev = current;
		on_it = current->next;
		if (current->next == NULL) {
			current->next = new;
		}//we go from 1st non-empty
		else {
			prev = current;
			on_it = current->next;
			while (!((strcmp(new->surname, on_it->surname)) < 0)) {
				on_it = on_it->next;
				prev = prev->next;
			}
			//we found the place, insert in front of with help of prev
			new->next = on_it;
			prev->next = new;
		}
	 }

	free(prev);
	free(on_it);
	free(safekeep);
	fclose(fp);
	return EXIT_SUCCESS;
}

int ReadFromPredmet1(Position current) { //current is &Head
	//find element and add onto it
	int key_id = 0;
	int new_grade = 0;

	Position safekeep = (Position)malloc(sizeof(Student));
	safekeep = current;

	if (safekeep == NULL) {
		printf("Malloc fail!5th");
		return EXIT_SYSTEM_FAILURE;
	}

	if (current->next == NULL) {
		printf("This list is empty!");
		return EXIT_SYSTEM_FAILURE;
	}

	FILE* fp = NULL;
	fp = fopen("predmet1.txt", "r");
	if (!fp) {
		printf("File predmet1.txt failed to open.");
		return EXIT_SYSTEM_FAILURE;
	}

	current = current->next; //current is now 1st non empty character
	while (!(feof(fp))) {

		fscanf(fp, "%d %d", &key_id, &new_grade);

		current = safekeep;
		current = current->next;
		while (current->id != key_id) {
			current = current->next;
		}
		//we found element to which we will add grade
		current->grade = new_grade;
	}

	free(safekeep);
	fclose(fp);
	return EXIT_SUCCESS;
}

int DeleteThem(Position current) {
	printf("We are in deletethem");
	char delete_name[MAX_CHAR] = { 0 };

	Position prev = (Position)malloc(sizeof(Student));
	prev = current;
	if (prev == NULL) {
		printf("Malloc fail!6th");
		return EXIT_SYSTEM_FAILURE;
	}

	Position on_it = (Position)malloc(sizeof(Student));
	on_it = current->next;
	if (on_it == NULL) {
		printf("Malloc fail!7th");
		return EXIT_SYSTEM_FAILURE;
	}

	printf("Enter name you want to delete:\n");
	scanf("%s", delete_name);

	
	while (on_it != NULL){
		if (!(strcmp(on_it->name, delete_name))) {
			prev->next = on_it->next;
		}
		else {
			on_it = on_it->next;
			prev = prev->next;
		}
	}

	free(prev);
	free(on_it);
	return EXIT_SUCCESS;
}

int ShowList(Position current) {
	if (current->next == NULL) {
		printf("This list is empty. Noth");
		return EXIT_SYSTEM_FAILURE;
	}
	current = current->next;
	while (current != NULL) {
		printf("\n-----\nSurname:%s\nName:%s\nID:%d\nGrade:%d\n-----", current->surname, current->name, current->id, current->grade);
		current = current->next;
	}
	return EXIT_SUCCESS;
}
