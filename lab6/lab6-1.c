#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void *childFunction(void *arg) {
    int childIteration;
    for (childIteration = 1; childIteration <= 10; childIteration++) {
        printf("Child Thread. Iteration: %d\n\n", childIteration);
        sleep(2);
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t childThread;
    int mainIteration;
    if (pthread_create(&childThread, NULL, childFunction, NULL) != 0) {
        perror("pthread_create");
        exit(1);
    }
    for (mainIteration = 1; mainIteration <= 10; mainIteration++) {
        printf("Main Thread. Iteration: %d\n\n", mainIteration);
        sleep(2);
    }
    if (pthread_join(childThread, NULL) != 0) {
        perror("pthread_join");
        exit(1);
    }
    return 0;
}

