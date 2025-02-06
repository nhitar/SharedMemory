#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/ipc.h>

#define PROJECT_ID 16 // Идентификатор для генерации ключа
#define MEMORY_SIZE 1000 // Размер сегмента разделяемой памяти
#define ACCESS_RIGHTS 0666 // Права доступа

int main() {
    // Генерация уникального ключа для разделяемой памяти
    key_t key = ftok(".", PROJECT_ID);
    if (key == -1) {
        printf("Error: Keygen process gone wrong.\n");
        exit(1);
    }

    // Создание идентификатора для сегмента разделяемой памяти
    int identifier = shmget(key, MEMORY_SIZE, ACCESS_RIGHTS | IPC_CREAT);
    if (identifier == -1) {
        printf("Error: Failed to create shared memory id.\n");
        exit(1);
    }
    
    // Получение адреса сегмента разделяемой памяти
    char* sharedMemory = shmat(identifier, 0, 0);
    if (sharedMemory == (char*)(-1)) {
        printf("Error: Failed to attach to shared memory.\n");
        exit(1);
    }

    // Запись "Hello world!" в разделяемую память
    sprintf(sharedMemory, "Hello world!");

    // Вывод ключа
    printf("%d\n", key);

    // Отключение от сегмента разделяемой памяти
    shmdt(sharedMemory);
    return 0;
}