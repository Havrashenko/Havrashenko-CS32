#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <string.h>

union SemaphoreUnion {
    int value;
    struct semid_ds *buffer;
    unsigned short *array;
    struct seminfo *__buffer;
};

void customAcquireSemaphore(int semaphoreId) {
    struct sembuf operation;
    operation.sem_num = 0;
    operation.sem_op = -1;
    operation.sem_flg = SEM_UNDO;
    if (semop(semaphoreId, &operation, 1) == -1) {
        perror("customAcquireSemaphore failed");
        exit(EXIT_FAILURE);
    }
}

void customReleaseSemaphore(int semaphoreId) {
    struct sembuf operation;
    operation.sem_num = 0;
    operation.sem_op = 1;
    operation.sem_flg = SEM_UNDO;
    if (semop(semaphoreId, &operation, 1) == -1) {
        perror("customReleaseSemaphore failed");
        exit(EXIT_FAILURE);
    }
}

int customSharedMemoryId;
void *customSharedMemoryPtr;
int customSemaphoreId;

void customSignalHandler(int signal) {
    printf("Client: Signal received from Signal %d\n", signal);
    if (signal == SIGUSR1) {
        int sum = 0, i = 0, value;

        printf("Client: Calculating sum of data...\n");
        customAcquireSemaphore(customSemaphoreId);

        do {
            memcpy(&value, (int *)customSharedMemoryPtr + i, sizeof(int));
            if (value == 0) break;
            sum += value;
            i++;
        } while (1);

        memcpy(customSharedMemoryPtr, &sum, sizeof(int));

        printf("Client: Sum calculated and written to shared memory...\n");
        customReleaseSemaphore(customSemaphoreId);
        printf("Client: Notifying the server about data processing completion...\n");
        kill(getppid(), SIGUSR1);
    }
}

void customConnectSharedMemoryAndSemaphore(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <shm_id> <sem_id>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    printf("Client: Connecting to the shared memory...\n");
    customSharedMemoryId = atoi(argv[1]);
    customSemaphoreId = atoi(argv[2]);

    customSharedMemoryPtr = shmat(customSharedMemoryId, NULL, 0);
    if (customSharedMemoryPtr == (void *) -1) {
        perror("shmat");
        exit(EXIT_FAILURE);
    }

    printf("Client: Connected to shared memory.\n");
    signal(SIGUSR1, customSignalHandler);
}

void customRunClient() {
    while (1) {
        pause();
    }
}

int main(int argc, char *argv[]) {
    customConnectSharedMemoryAndSemaphore(argc, argv);
    customRunClient();
    shmdt(customSharedMemoryPtr);
    return 0;
}

