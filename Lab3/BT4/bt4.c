#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <fcntl.h> 
#include <sys/shm.h> 
#include <sys/stat.h>
#include <unistd.h> 
#include <sys/mman.h> 
#include <time.h>

int main()
{
    const int SIZE = 100; 
    const char *name = "OS"; 
    int fd; 
    char *ptr; 
    fd = shm_open(name, O_CREAT | O_RDWR,0666); 
    ftruncate(fd, SIZE); 
    ptr = mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0); 
    strcpy(ptr, "0");
    __pid_t pid = fork();
    if(pid > 0)
    {
        srand(time(NULL));
        int value = 0;
        while(value <= 100)
        {
            int i = 10 + rand() % 11;
            sprintf(ptr, "%d" ,i); 
            sleep(1);
            value = atoi(ptr);
        }
    }else if(pid ==0 ){
        int sum = 0;
        int value = atoi(ptr);
        while(sum <= 100)
        {
            if(sum != value) 
            {
                sum += value;
                sprintf(ptr, "%d", sum);
                printf("%d \n", sum);
            }
            sleep(1);
        }
        printf("%d \n", sum);
    }else{
        strcpy(ptr, "110");
        printf("Fork that bai");
        exit(1);
    }
    exit(0);
}