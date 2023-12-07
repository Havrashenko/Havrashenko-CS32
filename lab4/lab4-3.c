#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc == 2) {
        const char *varName = argv[1];
        if (unsetenv(varName) != 0) {
            perror("Error deleting environment variable");
            return 1;
        }
    } else {
        if (clearenv() != 0) {
            perror("Failed to delete all environment variables");
            return 1;
        }
    }

    extern char **environ;
    for (char **env = environ; env != NULL && *env != NULL; env++) {
        printf("%s\n", *env);
    }

    return 0;
}

