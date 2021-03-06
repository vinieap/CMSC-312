#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h> 
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define str_memory_key 7646
#define int_memory_key 7647
#define SSHMSZ 7
#define ISHMSZ 4

int main() {
    int str_memory_id;
    char *str_memory;

    int int_memory_id;
    int *int_memory;

    int pidB, pidC;

    str_memory_id = shmget(str_memory_key, SSHMSZ, IPC_CREAT | 0666);
    int_memory_id = shmget(int_memory_key, ISHMSZ, IPC_CREAT | 0666);

    str_memory = shmat(str_memory_id, NULL, 0);
    int_memory = shmat(int_memory_id, NULL, 0);

    pidB = fork();
    pidC = fork();

    if(!pidB && pidC > 0) {
        str_memory_id = shmget(str_memory_key, SSHMSZ, 0666);
        int_memory_id = shmget(int_memory_key, ISHMSZ, 0666);

        str_memory = shmat(str_memory_id, NULL, 0);
        int_memory = shmat(int_memory_id, NULL, 0);

        while(*int_memory != 1){sleep(1);}

        memcpy(str_memory, "shared", strlen("shared"));
        *int_memory = 2;

        shmdt(str_memory);
        shmdt(int_memory);
    } else if(pidB > 0 && !pidC) {
        str_memory_id = shmget(str_memory_key, SSHMSZ, 0666);
        int_memory_id = shmget(int_memory_key, ISHMSZ, 0666);

        str_memory = shmat(str_memory_id, NULL, 0);
        int_memory = shmat(int_memory_id, NULL, 0);

        while(*int_memory != 2){sleep(1);}

        memcpy(str_memory, "memory", strlen("memory"));
        *int_memory = 3;
        
        shmdt(str_memory);
        shmdt(int_memory);
    } else if(pidB > 0 && pidC >0){
        *int_memory = 1;

        while(*int_memory != 2){}

        printf("%s\n", str_memory);
        fflush(stdout);

        while(*int_memory != 3){}

        printf("%s\n", str_memory);
        fflush(stdout);

        shmdt(str_memory);
        shmdt(int_memory);

        shmctl(str_memory_id, IPC_RMID, 0);
        shmctl(int_memory_id, IPC_RMID, 0);
        wait(NULL);
        printf("Goodbye\n");
    }
    return 0;
}