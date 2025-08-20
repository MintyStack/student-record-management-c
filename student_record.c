#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student {
    int roll;
    char name[50];
    float marks;
};

void addStudent(FILE *fp) {
    struct Student s;
    printf("\nEnter Roll Number: ");
    scanf("%d", &s.roll);
    printf("Enter Name: ");
    scanf(" %[^\n]", s.name); // read string with spaces
    printf("Enter Marks: ");
    scanf("%f", &s.marks);

    fwrite(&s, sizeof(s), 1, fp);
    printf("\n✅ Student Record Added Successfully!\n");
}

void displayStudents(FILE *fp) {
    struct Student s;
    rewind(fp);
    printf("\n--- Student Records ---\n");
    while (fread(&s, sizeof(s), 1, fp)) {
        printf("Roll: %d | Name: %s | Marks: %.2f\n", s.roll, s.name, s.marks);
    }
}

void searchStudent(FILE *fp) {
    int roll;
    struct Student s;
    int found = 0;
    printf("\nEnter Roll Number to search: ");
    scanf("%d", &roll);

    rewind(fp);
    while (fread(&s, sizeof(s), 1, fp)) {
        if (s.roll == roll) {
            printf("\n✅ Record Found:\nRoll: %d | Name: %s | Marks: %.2f\n", s.roll, s.name, s.marks);
            found = 1;
            break;
        }
    }
    if (!found) printf("\n❌ Record Not Found.\n");
}

int main() {
    FILE *fp;
    int choice;

    fp = fopen("students.dat", "ab+");
    if (!fp) {
        printf("Error opening file!\n");
        return 1;
    }

    do {
        printf("\n--- Student Record System ---\n");
        printf("1. Add Student\n");
        printf("2. Display All Students\n");
        printf("3. Search Student\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addStudent(fp); break;
            case 2: displayStudents(fp); break;
            case 3: searchStudent(fp); break;
            case 4: printf("\nExiting...\n"); break;
            default: printf("\nInvalid choice!\n");
        }
    } while (choice != 4);

    fclose(fp);
    return 0;
}
