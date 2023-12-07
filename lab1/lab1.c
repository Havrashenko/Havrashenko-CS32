#include <stdio.h>
#include <stdlib.h>
#define MAX_STUDENTS 100

struct Student {
    char firstName[50];
    char lastName[50];
    int age;
};

void clearBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main() {
    struct Student students[MAX_STUDENTS];
    int numStudents;

    printf("How many students are in your group -> ");
    scanf("%d", &numStudents);

    if (numStudents <= 0 || numStudents > MAX_STUDENTS) {
        printf("Error: Please enter a valid number of students (1-%d)\n", MAX_STUDENTS);
        return 1;
    }

    clearBuffer();

    for (int i = 0; i < numStudents; i++) {
        printf("\nStudent %d\n", i + 1);

        printf("Enter first name: ");
        fgets(students[i].firstName, sizeof(students[i].firstName), stdin);

        printf("Enter last name: ");
        fgets(students[i].lastName, sizeof(students[i].lastName), stdin);

        printf("Enter age: ");
        scanf("%d", &students[i].age);
        clearBuffer();
    }

    printf("\nPress Enter to check all students...\n");
    clearBuffer();

    printf("\nList of students:\n");
    for (int i = 0; i < numStudents; i++) {
        printf("\nStudent %d\n", i + 1);

        printf("First Name: %s", students[i].firstName);
        printf("Last Name: %s", students[i].lastName);
        printf("Age: %d\n", students[i].age);
    }

    return 0;
}

