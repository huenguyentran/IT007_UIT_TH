#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <sys/types.h>

#define BUFFER_SIZE 100

typedef struct {
    int sequence[BUFFER_SIZE];
    int length;
} CollatzData;

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Sử dụng: ./collatz <số nguyên dương>\n");
        return 1;
    }

    int n = atoi(argv[1]);
    if (n <= 0) {
        printf("Vui lòng nhập số nguyên dương\n");
        return 1;
    }

    int shmid;
    key_t key = ftok("collatz", 65); // Tạo key
    CollatzData *collatzData;

    // Tạo shared memory segment
    if ((shmid = shmget(key, sizeof(CollatzData), IPC_CREAT | 0666)) < 0) {
        perror("shmget");
        exit(1);
    }

    // Gắn kết vùng nhớ shared với vùng nhớ của tiến trình
    if ((collatzData = (CollatzData *)shmat(shmid, NULL, 0)) == (CollatzData *)-1) {
        perror("shmat");
        exit(1);
    }

    // Tiến trình con (Producer) tính toán chuỗi Collatz
    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        exit(1);
    } else if (pid == 0) {
        int length = 0;
        while (n != 1 && length < BUFFER_SIZE) {
            collatzData->sequence[length++] = n;
            if (n % 2 == 0) {
                n /= 2;
            } else {
                n = 3 * n + 1;
            }
        }
        collatzData->sequence[length++] = 1;
        collatzData->length = length;
        exit(0);
    } else {
        // Tiến trình cha (Consumer) in chuỗi kết quả
        wait(NULL);
        printf("Chuỗi Collatz: ");
        for (int i = 0; i < collatzData->length; i++) {
            printf("%d ", collatzData->sequence[i]);
        }
        printf("\n");

        // Xóa shared memory segment
        shmctl(shmid, IPC_RMID, NULL);
    }

    return 0;
}
