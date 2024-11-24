#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <fcntl.h> 
#include <sys/shm.h> 
#include <sys/stat.h> 
#include <unistd.h> 
#include <sys/mman.h> 
int main() 
{ 
    const int SIZE = 4096; 
    const char *name = "OS"; 
    int fd; 
    char *ptr; 
    fd = shm_open(name, O_CREAT | O_RDWR,0666); 
    ftruncate(fd, SIZE); 
    ptr = mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0); 
    strcpy(ptr, "Hello Process B");
    while (strncmp(ptr, "Hello Process B", 15) == 0) 
    { 
        printf("Waiting Process B update shared memory\n"); 
        sleep(1); 
    } 
    printf("Memory updated: %s\n", (char *)ptr); 
    munmap(ptr, SIZE); 
    close(fd); 
    return 0; 
}