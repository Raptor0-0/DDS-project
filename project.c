#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_PATIENTS 50

typedef struct {
    char name[30];
    char priority[7];
    char phoneno[15];
    int bedno;
} Hospital;

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void removeTrailingNewline(char *str) {
    str[strcspn(str, "\n")] = 0;
}

void addpatient(Hospital *hp, int *count) {
    if (*count >= MAX_PATIENTS) {
        printf("Hospital full, cannot add more patients.\n");
        return;
    }
    printf("Enter patient name: ");
    fgets(hp[*count].name, sizeof(hp[*count].name), stdin);
    removeTrailingNewline(hp[*count].name);

    printf("Enter patient phone number: ");
    fgets(hp[*count].phoneno, sizeof(hp[*count].phoneno), stdin);
    removeTrailingNewline(hp[*count].phoneno);

    printf("Enter patient bed number: ");
    scanf("%d", &hp[*count].bedno);
    clearInputBuffer();

    printf("Enter patient priority (High/Med/Low): ");
    fgets(hp[*count].priority, sizeof(hp[*count].priority), stdin);
    removeTrailingNewline(hp[*count].priority);

    (*count)++;
    printf("Patient added successfully.\n");
}

int removepatient(Hospital *hp, int *count) {
    char pname[30];
    printf("Enter patient name to remove: ");
    fgets(pname, sizeof(pname), stdin);
    removeTrailingNewline(pname);

    for (int i = 0; i < *count; i++) {
        if (strcasecmp(hp[i].name, pname) == 0) {
            for (int j = i; j < *count - 1; j++) {
                hp[j] = hp[j + 1];
            }
            (*count)--;
            printf("Patient %s removed.\n", pname);
            return 1;
        }
    }
    printf("Patient %s not found.\n", pname);
    return 0;
}

void getpatientdetails(Hospital *hp, int count) {
    char pname[30];
    printf("Enter patient name to get details: ");
    fgets(pname, sizeof(pname), stdin);
    removeTrailingNewline(pname);

    for (int i = 0; i < count; i++) {
        if (strcasecmp(hp[i].name, pname) == 0) {
            printf("\nPatient Details:\n");
            printf("+----------------+------------------+------------+----------+\n");
            printf("| Name           | Phone Number     | Bed Number | Priority |\n");
            printf("+----------------+------------------+------------+----------+\n");
            printf("| %-14s | %-16s | %-10d | %-8s |\n",
                   hp[i].name, hp[i].phoneno, hp[i].bedno, hp[i].priority);
            printf("+----------------+------------------+------------+----------+\n");
            return;
        }
    }
    printf("Patient %s not found.\n", pname);
}

void getallpatientdetails(Hospital *hp, int count) {
    if (count == 0) {
        printf("No patient records available.\n");
        return;
    }

    printf("\n+--------+----------------+------------------+------------+----------+\n");
    printf("| Sr No. | Name           | Phone Number     | Bed Number | Priority |\n");
    printf("+--------+----------------+------------------+------------+----------+\n");
    for (int i = 0; i < count; i++) {
        printf("| %-6d | %-14s | %-16s | %-10d | %-8s |\n",
               i + 1, hp[i].name, hp[i].phoneno, hp[i].bedno, hp[i].priority);
    }
    printf("+--------+----------------+------------------+------------+----------+\n");
}

int getPriorityRank(const char *priority) {
    if (strcasecmp(priority, "High") == 0) return 3;
    else if (strcasecmp(priority, "Med") == 0) return 2;
    else if (strcasecmp(priority, "Low") == 0) return 1;
    else return 0;
}

void sortPatientsByPriority(Hospital *hp, int count, bool descending) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            int rank1 = getPriorityRank(hp[j].priority);
            int rank2 = getPriorityRank(hp[j + 1].priority);

            if ((descending && rank1 < rank2) || (!descending && rank1 > rank2)) {
                Hospital temp = hp[j];
                hp[j] = hp[j + 1];
                hp[j + 1] = temp;
            }
        }
    }
}

void showMenu() {
    printf("\nHOSPITAL MANAGEMENT SYSTEM\n");
    printf("1. Admit a patient\n");
    printf("2. Discharge a patient\n");
    printf("3. Search for a patient by name\n");
    printf("4. Sort patients by priority\n");
    printf("5. Display all patients\n");
    printf("6. Exit\n");
    printf("Enter your choice: ");
}

int main() {
    Hospital hp[MAX_PATIENTS];
    int length = 0;
    int choice;

    while (true) {
        showMenu();
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input! Please enter a number.\n");
            clearInputBuffer();
            continue;
        }
        clearInputBuffer();

        switch (choice) {
            case 1:
                addpatient(hp, &length);
                break;
            case 2:
                removepatient(hp, &length);
                break;
            case 3:
                getpatientdetails(hp, length);
                break;
            case 4:
                if (length == 0) {
                    printf("No patients to sort.\n");
                } else {
                    int orderChoice;
                    printf("Sort by priority:\n");
                    printf("1. High to Low\n");
                    printf("2. Low to High\n");
                    printf("Enter your choice: ");
                    if (scanf("%d", &orderChoice) != 1) {
                        printf("Invalid input. Returning to main menu.\n");
                        clearInputBuffer();
                        break;
                    }
                    clearInputBuffer();

                    if (orderChoice == 1) {
                        sortPatientsByPriority(hp, length, true);  // High to Low
                        printf("Patients sorted from High to Low priority.\n");
                    } else if (orderChoice == 2) {
                        sortPatientsByPriority(hp, length, false); // Low to High
                        printf("Patients sorted from Low to High priority.\n");
                    } else {
                        printf("Invalid sort choice.\n");
                    }
                }
                break;
            case 5:
                getallpatientdetails(hp, length);
                break;
            case 6:
                printf("Exiting program.\n");
                return 0;
            default:
                printf("Invalid choice! Please enter a number between 1 and 6.\n");
                break;
        }
    }

    return 0;
}
