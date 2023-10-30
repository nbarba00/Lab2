#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 50
#define NO_PERSON_FOUND NULL
#define EMPTY_LIST -1
#define NO_PERSON_FOUND_INT -2
#define SINGLE_PERSON -3


struct Person;
typedef struct Person* Position;
typedef struct Person {
    char name[MAX_LENGTH];
    char surname[MAX_LENGTH];
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
int insertAfterPerson(Position person, Position newPerson); // Added function
int insertBeforePerson(Position head, Position person, Position newPerson); // Added function
int bubbleSort(Position head); // Added function
int writeListToFile(Position head, const char* filename); // Added function
int readListFromFile(Position head, const char* filename); // Added function
int menu(Position head);

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
            "P(Print list items), S(Search item in list by surname), D(Delete an item from the list), "
            "F(Add an item to the list after a specified item), B(Add an item to the list before a specified item), "
            "O(Sort items in the list by surname), W(Write items to a file), R(Read items from a file), X(Exit)\n");
        scanf(" %c", &choice);
        switch (choice) {
        case 'A':
        case 'a':
            insertAtFrontOfTheList(head);
            continue;
        case 'E':
        case 'e':
            insertAtEndOfTheList(head);
            continue;
        case 'P':
        case 'p':
            printList(head->next);
            continue;
        case 'S':
        case 's':
            person = findPerson(head->next);
            person ? printPerson(person) : printf("Can't find a person with that surname!\n");
            continue;
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
        case 'F':
        case 'f':
            person = findPerson(head->next);
            if (person) {
                Position newPerson = createPerson();
                if (newPerson) {
                    insertAfterPerson(person, newPerson);
                }
                else {
                    printf("Unable to create a new person.\n");
                }
            }
            else {
                printf("Can't find a person to insert after!\n");
            }
            continue;
        case 'B':
        case 'b':
            previous = findPrevious(head->next);
            if (previous) {
                Position newPerson = createPerson();
                if (newPerson) {
                    insertBeforePerson(head, previous, newPerson);
                }
                else {
                    printf("Unable to create a new person.\n");
                }
            }
            else {
                printf("Can't find a person to insert before!\n");
            }
            continue;
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
        case 'W':
        case 'w':
            if (writeListToFile(head->next, "persons.txt") == EXIT_SUCCESS) {
                printf("List written to file.\n");
            }
            else {
                printf("Failed to write the list to a file.\n");
            }
            continue;
        case 'R':
        case 'r':
            if (readListFromFile(head, "persons.txt") == EXIT_SUCCESS) {
                printf("List read from file.\n");
            }
            else {
                printf("Failed to read the list from a file.\n");
            }
            continue;
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

int insertAfterPerson(Position person, Position newPerson) {
    if (person && newPerson) {
        newPerson->next = person->next;
        person->next = newPerson;
        return EXIT_SUCCESS;
    }
    else {
        return -1; 
    }
}

int insertBeforePerson(Position head, Position person, Position newPerson) {
    if (head && person && newPerson) {
        Position current = head->next;
        Position previous = head;

        while (current) {
            if (current == person) {
                previous->next = newPerson;
                newPerson->next = current;
                return EXIT_SUCCESS;
            }
            previous = current;
            current = current->next;
        }
    }
    return -1; 
}

int bubbleSort(Position head) {
    int swapped;
    Position lastPersonRead = NULL;
    Position start = head;

    if (!head) {
        printf("Empty list!\n");
        return -1;
    }
    else if (!head->next) {
        printf("Only a single element in the list!\n");
        return -1;
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
    } while (swapped);

    return EXIT_SUCCESS;
}

int writeListToFile(Position head, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        return -1; // Handle error
    }

    Position current = head;
    while (current) {
        fprintf(file, "%s %s %d\n", current->name, current->surname, current->birthYear);
        current = current->next;
    }

    fclose(file);
    return EXIT_SUCCESS;
}

int readListFromFile(Position head, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        return -1; 
    }

    // Clear the current list
    Position current = head->next;
    while (current) {
        Position temp = current;
        current = current->next;
        free(temp);
    }
    head->next = NULL;

    while (!feof(file)) {
        Position newPerson = createPerson();
        if (newPerson) {
            if (fscanf(file, "%s %s %d", newPerson->name, newPerson->surname, &newPerson->birthYear) == 3) {
                insertAtEndOfTheList(head);
            }
            else {
                free(newPerson);
            }
        }
    }

    fclose(file);
    return EXIT_SUCCESS;
}

// Ostatak koda isti