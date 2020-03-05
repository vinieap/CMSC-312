#ifndef COUNTING_SEM_H
#define COUNTING_SEM_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define min(a, b) (a > b ? b : a)

typedef struct {
    int val;
    sem_t waitSem;
    sem_t mutSem;
} countSem_t;

void countSemWait(countSem_t *countSem);
void countSemPost(countSem_t *countSem);
void countSemInit(countSem_t *countSem, int initValue);
void countSemDestroy(countSem_t *countSem);

#endif