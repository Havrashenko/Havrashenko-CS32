#include <stdio.h>
#include <stdlib.h>

int displayEnvironmentVariable(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <variable_name>\n", argv[0]);
        return 1;
    }

    const char *requestedVariable = argv[1];
    char *variableValue = getenv(requestedVariable);

    if (variableValue) {
        printf("%s=%s\n", requestedVariable, variableValue);
    } else {
        printf("Environment variable with name %s not found.\n", requestedVariable);
    }

    return 0;
}

int main(int argc, char *argv[]) {
    return displayEnvironmentVariable(argc, argv);
}

