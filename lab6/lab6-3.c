#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

int globalIterations;
int globalMinNum;
int globalMaxNum;
int globalTargetNum;
int globalExitSignal = 0;

struct ThreadInfo {
    char *threadName;
    char *message;
};

void *customThreadFunction(void *arg) {
    struct ThreadInfo *info = (struct ThreadInfo *)arg;
    for (int i = 1; i <= globalIterations; i++) {
        if (globalExitSignal) {
            printf("Thread %s. Exiting due to signal.\n", info->threadName);
            pthread_exit(NULL);
        }
        printf("Thread %s. %s %d\n", info->threadName, info->message, i);
        int random = globalMinNum + rand() % (globalMaxNum - globalMinNum + 1);
        printf("Thread %s. Random Number: %d\n", info->threadName, random);
        if (random == globalTargetNum) {
            printf("Thread %s. Received %d, setting exit signal.\n", info->threadName, globalTargetNum);
            globalExitSignal = 1;
        }
        sleep(1);
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t threadArray[2];
    struct ThreadInfo threadInfoArray[] = {
        {"First", "Message1"},
        {"Second", "Message2"}
    };
    printf("Enter the number of iterations: ");
    scanf("%d", &globalIterations);
    printf("Enter the minimum number: ");
    scanf("%d", &globalMinNum);
    printf("Enter the maximum number: ");
    scanf("%d", &globalMaxNum);
    printf("Enter the target number: ");
    scanf("%d", &globalTargetNum);
    srand(time(NULL));
    for (int i = 0; i < 2; i++) {
        if (pthread_create(&threadArray[i], NULL, customThreadFunction, &threadInfoArray[i]) != 0) {
            perror("pthread_create");
            exit(1);
        }
    }
    for (int i = 0; i < 2; i++) {
        if (pthread_join(threadArray[i], NULL) != 0) {
            perror("pthread_join");
            exit(1);
        }
    }
    printf("Main Thread. All threads have completed.\n");
    return 0;
}

