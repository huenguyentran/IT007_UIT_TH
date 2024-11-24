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
    fd = shm_open(name, O_RDWR,0666); 
    ptr = mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0); 
    printf("Read shared memory: "); 
    printf("%s\n",(char *)ptr); 
    strcpy(ptr, "Hello Process A"); 
    printf("Shared memory updated: %s\n", ptr); 
    sleep(5); 
    munmap(ptr, SIZE); 
    close(fd);
    shm_unlink(name); 
    return 0; 
}