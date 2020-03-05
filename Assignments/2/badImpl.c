#include "countingSem.h"

void countSemInit(countSem_t *countSem, int initValue) {
    countSem->val = initValue;
    sem_init(&countSem->waitSem, 0, 0);
    sem_init(&countSem->mutSem, 0, 1);
}

void countSemWait(countSem_t *countSem) {
    sem_wait(&countSem->mutSem);
    countSem->val--;
    if(countSem->val < 0) {
        sem_post(&countSem->mutSem);
        sem_wait(&countSem->waitSem);
    }
    else {
        sem_post(&countSem->mutSem);
    }
}

void countSemPost(countSem_t *countSem) {
    sem_wait(&countSem->mutSem);
    countSem->val++;
    if(countSem->val <= 0) {
        sem_post(&countSem->waitSem);
    }
    sem_post(&countSem->mutSem);
}

void countSemDestroy(countSem_t *countSem) {
    sem_destroy(&countSem->waitSem);
    sem_destroy(&countSem->mutSem);
}