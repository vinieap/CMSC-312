#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define str_memory_key 7646
#define int_memory_key 7647
#define SSHMSZ 7
#define ISHMSZ 4

int main() {
    int str_memory_id;
    char *str_memory;

    int int_memory_id;
    int *int_memory;

    str_memory_id = shmget(str_memory_key, SSHMSZ,  0666);
    str_memory = shmat(str_memory_id, NULL, 0);

    int_memory_id = shmget(int_memory_key, ISHMSZ, 0666);
    int_memory = shmat(int_memory_id, NULL, 0);

    while(*int_memory != 2) {
        sleep(1);
    }

    memcpy(str_memory, "memory", strlen("memory") + 1);

    *int_memory = 3;

    printf("Process C done\n");

    return 0;
}
