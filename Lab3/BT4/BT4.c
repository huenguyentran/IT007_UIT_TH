#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <semaphore.h>
#include <wait.h>
#define BUFFER_SIZE 10
#define SHM_NAME "shm_bt4"
int main() {
    int fd;
    char *buffer;
    int *sum_ptr;
    fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
    ftruncate(fd, BUFFER_SIZE);
    buffer = mmap(NULL, BUFFER_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    sum_ptr = (int *)(buffer + BUFFER_SIZE);
    *sum_ptr = 0;
    pid_t pid = fork();
    if (pid > 0) { 
        srand(time(NULL));
        while (*sum_ptr <= 100) {
            int random_num = 10 + rand() % 11;  
            snprintf(buffer, BUFFER_SIZE, "%d", random_num); 
            sleep(1);
        }
        wait(NULL);
        munmap(buffer, BUFFER_SIZE);
        close(fd);
        shm_unlink(SHM_NAME);
        exit(0);
    } 
    else if (pid == 0) { 
        while (*sum_ptr <= 100) {
            int num = atoi(buffer);  
            *sum_ptr += num;
            printf("So nhap vao %d, tong la %d \n", num, *sum_ptr);
            sleep(1);
        }
        munmap(buffer, BUFFER_SIZE);
        close(fd);
        exit(0);
    } 
    exit(1);
}