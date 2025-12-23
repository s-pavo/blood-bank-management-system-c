#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Donor {
    char name[50];
    int age;
    char blood_type[10];
    struct Donor *prev;
    struct Donor *next;
};

struct Donor *head = NULL;
struct Donor *tail = NULL;

/* Add Donor */
void addDonor(char name[], int age, char blood_type[]) {
    struct Donor *newDonor = malloc(sizeof(struct Donor));
    if (newDonor == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }

    strcpy(newDonor->name, name);
    newDonor->age = age;
    strcpy(newDonor->blood_type, blood_type);

    newDonor->next = NULL;
    newDonor->prev = tail;

    if (head == NULL)
        head = newDonor;
    else
        tail->next = newDonor;

    tail = newDonor;
    printf("Donor added successfully!\n");
}

/* Print Donors */
void printDonors() {
    if (head == NULL) {
        printf("No donors found.\n");
        return;
    }

    struct Donor *current = head;
    printf("\nDonor List:\n");
    while (current != NULL) {
        printf("Name: %s | Age: %d | Blood Type: %s\n",
               current->name, current->age, current->blood_type);
        current = current->next;
    }
}

/* Search by Blood Type */
void searchByBloodType(char blood_type[]) {
    if (head == NULL) {
        printf("No donors found.\n");
        return;
    }

    struct Donor *current = head;
    int found = 0;

    printf("\nDonors with blood type %s:\n", blood_type);
    while (current != NULL) {
        if (strcmp(current->blood_type, blood_type) == 0) {
            printf("Name: %s | Age: %d\n", current->name, current->age);
            found = 1;
        }
        current = current->next;
    }

    if (!found)
        printf("No matching donors found.\n");
}

/* Delete Donor */
void deleteDonor(char name[]) {
    if (head == NULL) {
        printf("No donors found.\n");
        return;
    }

    struct Donor *current = head;

    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {

            if (current == head && current == tail) {
                head = tail = NULL;
            } else if (current == head) {
                head = current->next;
                head->prev = NULL;
            } else if (current == tail) {
                tail = current->prev;
                tail->next = NULL;
            } else {
                current->prev->next = current->next;
                current->next->prev = current->prev;
            }

            free(current);
            printf("Donor removed successfully!\n");
            return;
        }
        current = current->next;
    }

    printf("Donor not found.\n");
}

/* Save to File */
void saveToFile() {
    if (head == NULL) {
        printf("No donors to save.\n");
        return;
    }

    char filename[50];
    printf("Enter filename: ");
    fgets(filename, sizeof(filename), stdin);
    filename[strcspn(filename, "\n")] = '\0';

    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("File open failed.\n");
        return;
    }

    struct Donor *current = head;
    while (current != NULL) {
        fprintf(fp, "%s %d %s\n",
                current->name, current->age, current->blood_type);
        current = current->next;
    }

    fclose(fp);
    printf("Donor list saved successfully!\n");
}

/* Load from File */
void loadFromFile() {
    char filename[50];
    printf("Enter filename: ");
    fgets(filename, sizeof(filename), stdin);
    filename[strcspn(filename, "\n")] = '\0';

    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("File open failed.\n");
        return;
    }

    while (head != NULL) {
        struct Donor *temp = head;
        head = head->next;
        free(temp);
    }
    tail = NULL;

    char name[50], blood_type[10];
    int age;

    while (fscanf(fp, "%s %d %s", name, &age, blood_type) != EOF) {
        addDonor(name, age, blood_type);
    }

    fclose(fp);
    printf("Donor list loaded successfully!\n");
}

int main() {
    int choice;
    char buffer[50];
    char name[50], blood_type[10];
    int age;

    while (1) {
        printf("\nBlood Bank Management System\n");
        printf("1. Add Donor\n");
        printf("2. Print Donors\n");
        printf("3. Search by Blood Type\n");
        printf("4. Delete Donor\n");
        printf("5. Save to File\n");
        printf("6. Load from File\n");
        printf("7. Exit\n");

        printf("Enter choice: ");
        fgets(buffer, sizeof(buffer), stdin);
        sscanf(buffer, "%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter donor name: ");
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = '\0';

                printf("Enter donor age: ");
                fgets(buffer, sizeof(buffer), stdin);
                sscanf(buffer, "%d", &age);

                printf("Enter blood type: ");
                fgets(blood_type, sizeof(blood_type), stdin);
                blood_type[strcspn(blood_type, "\n")] = '\0';

                addDonor(name, age, blood_type);
                break;

            case 2:
                printDonors();
                break;

            case 3:
                printf("Enter blood type: ");
                fgets(blood_type, sizeof(blood_type), stdin);
                blood_type[strcspn(blood_type, "\n")] = '\0';
                searchByBloodType(blood_type);
                break;

            case 4:
                printf("Enter donor name to delete: ");
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = '\0';
                deleteDonor(name);
                break;

            case 5:
                saveToFile();
                break;

            case 6:
                loadFromFile();
                break;

            case 7:
                printf("Exiting program...\n");
                exit(0);

            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}
