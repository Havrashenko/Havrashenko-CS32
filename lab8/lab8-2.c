#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void customHandleTerminate(int signum) {
    printf("Received SIGTERM signal. Processing termination...\n");
}

void customHandleInterrupt(int signum) {
    printf("Received SIGINT signal. Processing termination...\n");
}

void customHandleUserSignal(int signum) {
    printf("Received SIGUSR1 signal. Finalizing operations...\n");
    exit(0);
}

int main() {
    struct sigaction customSignalAction;

    customSignalAction.sa_handler = customHandleInterrupt;
    sigaction(SIGINT, &customSignalAction, NULL);

    customSignalAction.sa_handler = customHandleTerminate;
    sigaction(SIGTERM, &customSignalAction, NULL);

    customSignalAction.sa_handler = customHandleUserSignal;
    sigaction(SIGUSR1, &customSignalAction, NULL);

    signal(SIGPROF, SIG_DFL);
    signal(SIGHUP, SIG_IGN);

    while (1) {
        pause();
    }

    return 0;
}

