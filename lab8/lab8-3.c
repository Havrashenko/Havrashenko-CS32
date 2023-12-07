#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void customHandleAlarm(int signal) {
}

void setupCustomAlarm(int duration, const char *notificationText) {
    signal(SIGALRM, customHandleAlarm);
    alarm(duration);
    pause();
    printf("Scheduled Notification: %s\n", notificationText);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <duration in seconds> <message>\n", argv[0]);
        return 1;
    }

    int notificationDuration = atoi(argv[1]);
    char *notificationMessage = argv[2];

    pid_t childProcessID = fork();

    if (childProcessID < 0) {
        perror("Fork failed");
        exit(1);
    }

    if (childProcessID == 0) {
        setupCustomAlarm(notificationDuration, notificationMessage);
        exit(0);
    } else {
        printf("Notification set for %d seconds. Child process PID: %d\n", notificationDuration, childProcessID);
        exit(0);
    }

    return 0;
}

