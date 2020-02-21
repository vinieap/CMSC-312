#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h> 
#include <unistd.h>

#define str_memory_key 7646
#define int_memory_key 7647
#define SSHMSZ 7
#define ISHMSZ 4

int main() {

    int str_memory_id;
    char *str_memory;

    int int_memory_id;
    int *int_memory;

    str_memory_id = shmget(str_memory_key, SSHMSZ, IPC_CREAT | 0666);
    str_memory = shmat(str_memory_id, NULL, 0);

    int_memory_id = shmget(int_memory_key, ISHMSZ, IPC_CREAT | 0666);
    int_memory = shmat(int_memory_id, NULL, 0);

    *int_memory = 1;

    while(*int_memory != 2)
        sleep(1);

    printf("%s\n", str_memory);

    while(*int_memory != 3)
        sleep(1);

   printf("%s\n", str_memory);

    shmdt(&str_memory);
    shmdt(&int_memory);

    shmctl(str_memory_id, IPC_RMID, NULL);
    shmctl(int_memory_id, IPC_RMID, NULL);

    printf("Process A done\n");

    printf("Goodbye\n");

    return 0;
}