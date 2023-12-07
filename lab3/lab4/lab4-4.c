#include <stdio.h>
#include <stdlib.h>
#include <pwd.h>
#include <unistd.h>

int main() {
    // Get information about the current user by UID
    uid_t currentUserID = getuid();
    struct passwd *currentUserInfo = getpwuid(currentUserID);

    if (currentUserInfo) {
        printf("Information about the current user by UID:\n");
        printf("Username: %s\n", currentUserInfo->pw_name);
        printf("Full name: %s\n", currentUserInfo->pw_gecos);
    } else {
        perror("Error retrieving user information by UID");
    }

    // Get information about the "root" user by username
    const char *rootUsername = "root";
    struct passwd *rootUserInfo = getpwnam(rootUsername);

    if (rootUserInfo) {
        printf("\nInformation about the 'root' user by username:\n");
        printf("Username: %s\n", rootUserInfo->pw_name);
        printf("Full name: %s\n", rootUserInfo->pw_gecos);
    } else {
        perror("Error retrieving user information for the 'root' user by username");
    }

    return 0;
}

