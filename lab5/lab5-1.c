#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int executeCommands(char *commandSequence) {
    char *tokenizedCommand = strtok(commandSequence, ";");

    while (tokenizedCommand != NULL) {
        int exitStatus = system(tokenizedCommand);

        if (WIFEXITED(exitStatus)) {
            int exitCode = WEXITSTATUS(exitStatus);
            printf("Command '%s' exited with status %d\n", tokenizedCommand, exitCode);
        } else {
            printf("Failed to execute command '%s'\n", tokenizedCommand);
        }

        tokenizedCommand = strtok(NULL, ";");
    }

    return 0;
}

int main(int argumentCount, char *arguments[]) {
    if (argumentCount != 2) {
        printf("Usage: %s \"command(s)\"\n", arguments[0]);
        return 1;
    }

    char *commandSequence = arguments[1];
    int result = executeCommands(commandSequence);

    return result;
}

