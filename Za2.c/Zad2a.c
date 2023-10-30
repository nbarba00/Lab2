#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_LENGHT (50)
#define NO_PERSON_FOUND NULL
#define EMPTY_LIST -1
#define NO_PERSON_FOUND_INT -2
#define SINGLE_PERSON -3

struct _Person;
typedef struct _Person* Position;
typedef struct _Person {
	char name[MAX_LENGHT];
	char surname[MAX_LENGHT];
	int birthYear;
	Position next;
}Person;


Position createPerson();
Position findLast(Position head);
char* enterSurname();
int printPerson(Position person);
Position findPrevious(Position head);
int swapItems(Position first, Position second);
int insertAtFrontOfTheList(Position head);
int insertAtEndOfTheList(Position head);
int printList(Position firstItem);
Position findPerson(Position firstItem);
int deletePerson(Position head);
int insertAfterPerson(Position person);
int bubbleSort(Position firstItem);

int main() {
	Person head = { .name = {0},.surname = {0}, .birthYear = 0, .next = NULL };
	
	menu(&head);

	return EXIT_SUCCESS;
}

int menu(Position head) {
	char choice = '\0';
	Position person = NULL;
	Position previous = NULL;
	while (1) {
		printf("Enter: A(Add to the front of the list)\n\tE(Add to the end of the list)\n\tP(Print list items)\n\tS(search item in list by surname)\n\tD(delete a item from list)\n\tF(add item to the list after some specified item)\n\tB(add item to the list before some specified item)\n\tO(sort items in list by surname)\n\tW(write items in list to the file)\n\tR(Read items in list from the file)\n\tX(exit program)\n");
		scanf("%c", &choice);
		switch (choice) {
			//add item to the front of the List
		case 'A':
		case 'a':
			insertAtFrontOfTheList(head);
			continue;
			//add item to the end of the list
		case 'E':
		case 'e':
			insertAtEndOfTheList(head);
			continue;
			//printf list items...
		case 'P':
		case 'p':
			printList(head->next);
			continue;
			//search item in list by surname
		case 'S':
		case 's':
			person=findPerson(head->next);
			person ? printPerson(person) : printf("Can't find  person with that surname!\n");
			continue;
			//delete a item from list
		case 'D':
		case 'd':
			switch (deletePerson(head)) {
			case EXIT_SUCCESS:
				printf("Deleted!\n");
				break;
			case EMPTY_LIST:
				printf("List is empty!\n");
				break;
			case NO_PERSON_FOUND_INT:
				printf("Can't find person with that surname!\n");
				break;
			default:
				break;
			}
			continue;
			//add item to the list after some specified item
		case 'F':
		case 'f':
			person = findPerson(head->next);
			person ? insertAfterPerson(person) : printf("Can't...!\n");
			continue;
			// add item to the list before some specified item
		case 'B':
		case 'b':
			previous = findPrevious(head->next);
			previous insertAfterPerson(previous); printf("Can't find  person with that surname!\n");
			continue;
			//sort items in list by surname
		case 'O':
		case 'o':
			switch (bubbleSort(head->next)) {
			case EXIT_SUCCESS:
				printf("Sorted!\n");
				printList(head->next);
				break;
			case EMPTY_LIST:
				printf("List is empty!\n");
				break;
				case SINGLE_PERSON:
				printf("Single person in list!\n");
				break;
			default:
				break;
			}
			continue;
			//write items in list to the file
		case 'W':
		case 'w':
			/* person = findPerson(head->next);
			person ? printPerson(person) : printf("Can't find  person with that surname!\n"); */
			continue;
			//Read items in list from the file
		case 'R':
		case 'r':
			/* person = findPerson(head->next);
			person ? printPerson(person) : printf("Can't find  person with that surname!\n"); */
			continue;
			//exit program
		case 'X':
		case 'x':
			break;
		default:
			printf("Wrong letter!\n");
			continue;
		}
		break;
	}
	return EXIT_SUCCESS;
}

int insertAtFrontOfTheList(Position head) {
	Position newPerson = NULL;
	
	newPerson = createPerson();

	if (newPerson) {
		newPerson->next = head->next;
		head->next = newPerson;
	}
	
	return EXIT_SUCCESS;
}

int insertAtEndOfTheList(Position head) {
	Position newPerson = NULL;
	Position last = NULL;

	newPerson = createPerson();

	if (newPerson) {
		last = finLast(head);
		newPerson->next = last->next;
		last->next = newPerson;
	}

	return EXIT_SUCCESS;
}

int printList(Position firstItem) {
	Position current = firstItem;

	if (!firstItem) {
		printf("Empty list!\n");
	}

	while (current) {
		printPerson(current);
		current = current->next;
	}

	return EXIT_SUCCESS;
}

Position findPerson(Position firstItem)
{
	Position current = firstItem;
	char surname[MAX_LENGHT] = { 0 };

	if (!firstItem) {
		printf("Empty list!\n");
		return NO_PERSON_FOUND;
	}

	strcpy(surname, enterSurname());
	do {
		if (strcmp(current->surname, surname) == 0) {
			return current;
		}
		else {
			current = current->next;
		}
	} while (current);

	return NO_PERSON_FOUND;
}

int deletePerson(Position head)
{
	Position current = head;
	char surname[MAX_LENGHT] = { 0 };

	strcpy(surname, enterSurname());
	if (head->next) {
		Position previous = NULL;

		while (current->next&& strcmp(current->surname,surname)) {
			previous = current;
			current = current->next;
		}
		//we have to for "previous" so intellisense
		if (previous && previous->next && strcmp(current->surname, surname)==0) {
			printPerson(current);
			previous->next = current->next;
			free(current);
		}
		else {
			return NO_PERSON_FOUND_INT;
		}
	}
	else {
		return EMPTY_LIST;
	}

	return EXIT_SUCCESS;
}

int insertAfterPerson(Position person) {
	Position newPerson = NULL;

	newPerson = createPerson();






	return EXIT_SUCCESS;
}

int bubbleSort(Position newItem) {
	int swapped = 0;
	Position lastPersonRead = NULL;
	Position start = firstItem;

	//Return if the list is empty or has only one element
	if (!firstItem) {
		printf("Empty list!\n");
		return NO_PERSON_FOUND_INT;
	}
	else if (!firstItem->next) {
		printf("Only single element in list!\n");
		return SINGLE_PERSON;
	}

		do {
		swapped = 0;
		Position current = start;

		while (current->next != lastPersonRead) {
			if (strcmp(current->surname, current->next->surname) > 0) {
				swapItems(current, current->next);
				swapped = 1;
			}
			current = current->next;
		}
		lastPersonRead = current;
	while (swapped);
	}
	return EXIT_SUCCESS;
}

Position findLast(Position head) {
	Position current = head;

	while (current->next) {
		current = current->next
	}

	return current;
}

char* enterSurname() {
	char surname[MAX_LENGHT] = { 0 };
	printf("Enter surname of the wanted person:\n");
	scanf("%s", surname);

	return surname;
}

int printPerson(Position person) {
	printf("\033[0;32mName: %s\t Surname: %s\t Birth year:]");
	return EXIT_SUCCESS;
}

Position findPrevious(Position head) {
	position current = head;
	char surname[MAX_LENGHT] = { 0 };

	if (!head->next) {
		printf("Empty list!\n");
		return NO_PERSON_FOUND;
	}

	strcpy(surname, enterSurname());
	do {
		if (strcmp(current->next->surname, surname) == 0) {
			return current;
		}
		else {
			current = current->next;
		}
	} while (current->next != NULL);

	return NO_PERSON_FOUND;
}

int swapItems(Position first, Position second) {
	char tempName[MAX_LENGHT];
	char tempSurname[MAX_LENGHT];
	int tempBirthYear;

	strcpy(tempName, first->name);
	strcpy(tempSurname, first->surname);
	tempBirthYear = first->birthYear;

	strcpy(first->name, second->name);
	strcpy(first->surname, second->surname);
	first->birthYear = second->birthYear;

	strcpy(second->name, tempName);
	strcpy(second->surname, tempSurname);
	second->birthYear = tempBirthYear;

	return EXIT_SUCCESS;
}
