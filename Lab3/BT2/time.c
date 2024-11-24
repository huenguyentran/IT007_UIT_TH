#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/time.h>
int main(int argc, char* argv[]) 
{ 
    if (argc < 2)  exit(1);
    pid_t pid = fork();
    struct timeval start, end;
    gettimeofday(&start, NULL);
    if (pid == 0) {
        execl("/bin/sh","sh","-c", argv[1], NULL);
    } 
    else if (pid > 0){
        wait(NULL);
        gettimeofday(&end, NULL);
        double elapsed = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec)/1000000.00;
        printf("Thoi gian thuc thi: %.5f seconds\n", elapsed);
    }
    exit(0);
}