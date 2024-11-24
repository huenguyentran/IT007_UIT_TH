#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <wait.h>
#define BUFFER_SIZE 20
#define SHM_NAME "collatz_shm"
int main(int argc, char* argv[]) {
    if (argc != 2) exit(1);
    int num = atoi(argv[1]);
    if (num <= 0) exit(1);
    int fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
    ftruncate(fd, BUFFER_SIZE);
    char *buffer = mmap(NULL, BUFFER_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (buffer == MAP_FAILED) {
        perror("mmap that bai");
        exit(1);
    }
    snprintf(buffer, BUFFER_SIZE, "%d", num);
    pid_t pid = fork();
    if (pid > 0) { 
        int value;
        do {
            value = atoi(buffer);
            printf("%d, ", value); 
            sleep(1);
        } while (value > 1);
        printf("\n");
        wait(NULL); 
        munmap(buffer, BUFFER_SIZE);
        close(fd);
        shm_unlink(SHM_NAME);
    } 
    else if (pid == 0) { 
        sleep(1);
        int value = atoi(buffer);
        while (value > 1) {
            if (value % 2 == 0) value /= 2; 
            else value = 3 * value + 1;
            snprintf(buffer, BUFFER_SIZE, "%d", value); 
            sleep(1); 
        }
        munmap(buffer, BUFFER_SIZE);
        close(fd);
        exit(0);
    } 
    exit(1);
}