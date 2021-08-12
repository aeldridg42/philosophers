#include <stdio.h>
#include <unistd.h>
#include <semaphore.h>
#include <stdlib.h>
#include <sys/time.h>

sem_t *sem;

void check(void)
{
    usleep(100);
    sem_wait(sem);
    printf("hi\n");
    sleep(1);
    sem_post(sem);
}

int main(int argc, char **argv)
{
    int i;
    pid_t p;

    i = 0;
    sem = sem_open("checkname", O_CREAT, 0666, 10);
    p = fork();
    if (p == 0)
    {
        p = fork();
        if (p == 0)
        {
            fork();
        }
    }
    check();
    wait(NULL);
    return(1);
}