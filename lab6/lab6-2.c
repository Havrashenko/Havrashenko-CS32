#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

struct ThreadData {
    char *threadName;
    char *message;
    int count;
};

void *customThreadFunction(void *arg) {
    struct ThreadData *threadData = (struct ThreadData *)arg;
    for (int i = 1; i <= threadData->count; i++) {
        printf("Thread %s. %s %d\n", threadData->threadName, threadData->message, i);
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t threadIds[4];
    struct ThreadData threadArgs[] = {
        {"Alpha", "Message1", 3},
        {"Beta", "Message2", 2},
        {"Gamma", "Message3", 4},
        {"Delta", "Message4", 5}
    };

    for (int i = 0; i < 4; i++) {
        if (pthread_create(&threadIds[i], NULL, customThreadFunction, &threadArgs[i]) != 0) {
            perror("pthread_create");
            exit(1);
        }
    }

    for (int i = 0; i < 4; i++) {
        if (pthread_join(threadIds[i], NULL) != 0) {
            perror("pthread_join");
            exit(1);
        }
    }

    return 0;
}

