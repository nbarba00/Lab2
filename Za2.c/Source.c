#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGHT (50)

struct _Person;
typedef struct _Person* Position;
typedef struct _Person {
    char name[MAX_LENGHT];
    char surname[MAX_LENGHT];
    int birthYear;
    Position next;
} Person;

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
int menu(Position head); // Forward declaration of menu function

int main() {
    Person head = { .name = {0}, .surname = {0}, .birthYear = 0, .next = NULL };

    menu(&head);

    return EXIT_SUCCESS;
}

int menu(Position head) {
    char choice = '\0';
    Position person = NULL;
    Position previous = NULL;
    while (1) {
        printf("Enter: A(Add to the front of the list), E(Add to the end of the list), "
            "P(Print list items), S(search item in list by surname), D(delete an item from the list), "
            "F(add an item to the list after some specified item), B(add an item to the list before some specified item), "
            "O(sort items in the list by surname), W(write items in the list to the file), "
            "R(Read items in the list from the file), X(exit program)\n");
        scanf(" %c", &choice);
        switch (choice) {
            // add item to the front of the list
        case 'A':
        case 'a':
            insertAtFrontOfTheList(head);
            continue;
            // add item to the end of the list
        case 'E':
        case 'e':
            insertAtEndOfTheList(head);
            continue;
            // print list items...
        case 'P':
        case 'p':
            printList(head->next);
            continue;
            // search item in the list by surname
        case 'S':
        case 's':
            person = findPerson(head->next);
            person ? printPerson(person) : printf("Can't find a person with that surname!\n");
            continue;
            // delete an item from the list
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
                printf("Can't find a person with that surname!\n");
                break;
            default:
                break;
            }
            continue;
            // add an item to the list after some specified item
        case 'F':
        case 'f':
            person = findPerson(head->next);
            person ? insertAfterPerson(person) : printf("Can't...!\n");
            continue;
            // add an item to the list before some specified item
        case 'B':
        case 'b':
            previous = findPrevious(head->next);
            previous ? insertAfterPerson(previous) : printf("Can't find a person with that surname!\n");
            continue;
            // sort items in the list by surname
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
                printf("Single person in the list!\n");
                break;
            default:
                break;
            }
            continue;
            // write items in the list to the file
        case 'W':
        case 'w':
            /* person = findPerson(head->next);
            person ? printPerson(person) : printf("Can't find a person with that surname!\n"); */
            continue;
            // read items in the list from the file
        case 'R':
        case 'r':
            /* person = findPerson(head->next);
            person ? printPerson(person) : printf("Can't find a person with that surname!\n"); */
            continue;
            // exit program
        case 'X':
        case 'x':
            break;
        default:
            printf("Wrong letter! Please try again.\n");
            continue;
        }
        break;
    }
    return EXIT_SUCCESS;
}

// The rest of your code remains unchanged from your initial code.
