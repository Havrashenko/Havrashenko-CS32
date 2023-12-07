#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define DEFAULT_BUFFER_SIZE 127

void displayHelp() {
    printf("Simple Command Processor\n");
    printf("Usage: cmd_processor [-h|--help] [-b|--buffer <buffer_size>]\n");
    printf("Options:\n");
    printf("  -h, --help            Show this help message\n");
    printf("  -b, --buffer <size>   Set the command buffer size (default: %d)\n", DEFAULT_BUFFER_SIZE);
}

int main(int argc, char *argv[]) {
    int bufferSize = DEFAULT_BUFFER_SIZE;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
            displayHelp();
            return 0;
        } else if (strcmp(argv[i], "-b") == 0 || strcmp(argv[i], "--buffer") == 0) {
            if (i + 1 < argc) {
                bufferSize = atoi(argv[i + 1]);
                if (bufferSize <= 0) {
                    printf("Invalid buffer size. Using default size (%d).\n", DEFAULT_BUFFER_SIZE);
                    bufferSize = DEFAULT_BUFFER_SIZE;
                }
            }
        }
    }

    char *userName = getenv("USER");
    if (userName == NULL) {
        printf("Unknown user\n");
        return 1;
    }

    printf("Welcome, %s!\n", userName);
    printf("[%s]$", userName);

    char userInput[bufferSize];
    while (1) {
        if (fgets(userInput, bufferSize, stdin) == NULL) {
            break;
        }

        if (strcmp(userInput, "stop\n") == 0) {
            printf("Wait 3 seconds...\n");
            sleep(3);
            printf("\033[H\033[J");
            break;
        }

        int executionResult = system(userInput);
        if (executionResult == -1) {
            printf("Error executing the command.\n");
        }
    }

    return 0;
}

