#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void customHandleUserSignal(int signum) {
    printf("Received SIGUSR1 signal. Performing cleanup...\n");
    exit(0);
}

void customHandleInterrupt(int signum) {
    printf("Received SIGINT signal. Processing termination...\n");
}

void customHandleTermination(int signum) {
    printf("Received SIGTERM signal. Processing termination...\n");
}

int main() {
    signal(SIGINT, customHandleInterrupt);
    signal(SIGTERM, customHandleTermination);
    signal(SIGUSR1, customHandleUserSignal);

    signal(SIGPROF, SIG_DFL);
    signal(SIGHUP, SIG_IGN);

    while (1) {
        pause();
    }

    return 0;
}

