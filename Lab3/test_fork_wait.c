#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
    pid_t pid;
    pid = fork();
    if(pid == 0)
        printf("Child Process, pid = %d\n", pid);
    else 
    {
        wait(NULL);
        printf("Parent Process, pid = %d\n", pid);
    }
    exit(0);
}
