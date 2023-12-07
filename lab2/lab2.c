#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Function to generate a random sequence of given length
void generateSequence(int numbers[], int length) {
    for (int i = 0; i < length; i++) {
        numbers[i] = rand() % 10;
        printf("%d ", numbers[i]);
    }
    printf("\n");
}

// Function to check if 7 is present in the sequence
int containsSeven(int numbers[], int length) {
    for (int i = 0; i < length; i++) {
        if (numbers[i] == 7) {
            return 1; // true
        }
    }
    return 0; // false
}

// Function to count the number of duplicates in the sequence
int countDuplicates(int numbers[], int length) {
    int count = 0;
    for (int i = 0; i < length; i++) {
        for (int j = i + 1; j < length; j++) {
            if (numbers[i] == numbers[j]) {
                count++;
            }
        }
    }
    return count;
}

int main() {
    srand(time(NULL));
    int betAmount;
    int sequenceLength;
    int totalWin = 0;

    printf("Enter your bet amount: ");
    scanf("%d", &betAmount);

    printf("Enter the length of the sequence to generate: ");
    scanf("%d", &sequenceLength);

    int generatedNumbers[sequenceLength];
    
    generateSequence(generatedNumbers, sequenceLength);

    if (containsSeven(generatedNumbers, sequenceLength)) {
        totalWin += betAmount;
    }

    int duplicateCount = countDuplicates(generatedNumbers, sequenceLength);

    if (duplicateCount > 0) {
        totalWin += betAmount;
    }

    if (duplicateCount >= sequenceLength / 3) {
        totalWin += betAmount;
    }

    printf("Total winnings: %d\n", totalWin);

    return 0;
}

