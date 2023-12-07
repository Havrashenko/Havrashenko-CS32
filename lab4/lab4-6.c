#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void displayEnvironment() {
    extern char **environ;
    char **envPtr = environ;
    while (*envPtr) {
        printf("%s\n", *envPtr);
        envPtr++;
    }
}

void displayHelp() {
    printf("Usage: environment [options]\n");
    printf("Options:\n");
    printf("  -h, --help           Display this help message\n");
    printf("  -i, --info <variable> Display the value of the specified variable\n");
    printf("  -s, --set <variable=value> Set the value of the specified variable\n");
    printf("  -d, --del <variable> Delete the specified variable\n");
    printf("  -a, --assign <variable> --value <value> Assign a new value to the specified variable\n");
    printf("  -c, --clear          Clear the environment\n");
}

void displayVariable(const char *variable) {
    char *value = getenv(variable);
    if (value) {
        printf("%s=%s\n", variable, value);
    } else {
        printf("Variable %s is not set.\n", variable);
    }
}

void setVariableValue(const char *variable, const char *value) {
    setenv(variable, value, 1);
    printf("%s=%s\n", variable, value);
}

void deleteVariable(const char *variable) {
    unsetenv(variable);
}

void assignValue(const char *variable, const char *value) {
    if (value) {
        setenv(variable, value, 1);
        printf("%s=%s\n", variable, value);
    } else {
        printf("No value specified for assignment.\n");
    }
}

void clearEnvironment() {
    clearenv();
}

int main(int argc, char *argv[]) {
    if (argc == 1) {
        // Display information about the current environment
        displayEnvironment();
    } else if (argc == 2 && (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0)) {
        // Display help
        displayHelp();
    } else if (argc == 3 && (strcmp(argv[1], "-i") == 0 || strcmp(argv[1], "--info") == 0)) {
        // Display the value of the specified variable
        displayVariable(argv[2]);
    } else if (argc == 4 && (strcmp(argv[1], "-s") == 0 || strcmp(argv[1], "--set") == 0)) {
        // Set the value of the specified variable
        setVariableValue(argv[2], argv[3]);
    } else if (argc == 3 && (strcmp(argv[1], "-d") == 0 || strcmp(argv[1], "--del") == 0)) {
        // Delete the specified variable
        deleteVariable(argv[2]);
    } else if (argc == 5 && strcmp(argv[1], "-a") == 0 && strcmp(argv[3], "-v") == 0) {
        // Assign a new value to the specified variable
        assignValue(argv[2], argv[4]);
    } else if ((argc == 2 && strcmp(argv[1], "-c") == 0) || (strcmp(argv[1], "--clear") == 0)) {
        // Clear the environment
        clearEnvironment();
    } else {
        // Invalid command format, display help
        displayHelp();
    }

    return 0;
}

