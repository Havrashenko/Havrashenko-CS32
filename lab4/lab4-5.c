#include <stdio.h>
#include <unistd.h>
#include <sys/utsname.h>

int main() {
    char computerName[256];
    struct utsname systemData;

    // Get the hostname
    if (gethostname(computerName, sizeof(computerName)) == 0) {
        printf("Hostname: %s\n", computerName);
    } else {
        perror("Error getting hostname");
    }

    // Get system information
    if (uname(&systemData) == 0) {
        printf("System information:\n");
        printf("OS: %s\n", systemData.sysname);
        printf("Kernel version: %s\n", systemData.release);
        printf("OS version: %s\n", systemData.version);
        printf("Machine type: %s\n", systemData.machine);
    } else {
        perror("Error getting system information");
    }

    return 0;
}

