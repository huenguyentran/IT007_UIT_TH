#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h>
#include <signal.h>
#include <wait.h>

void sigint_handler(int signum) {
    printf("count.sh has stopped\n");
    kill(getpid(), SIGTERM);
}
int main(int argc, char* argv[]) 
{ 
    printf("Welcome to IT007, I am 23521063\n");
    struct sigaction act;
    act.sa_handler = sigint_handler;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    sigaction(SIGINT, &act, NULL);
    __pid_t pid = fork();
    if (pid == 0) {
        execl("./count.sh", "./count.sh", "120", NULL);  
    } 
    else if (pid > 0)
    {
        wait(NULL);
    }
    exit(0);
}
