#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/ipc.h>

#define BUFFER_SIZE 1024 // Размер буфера
#define MEMORY_SIZE 1000 // Размер сегмента разделяемой памяти
#define ACCESS_RIGHTS 0666 // Права доступа

int main() {
    key_t key;
    char buffer[BUFFER_SIZE];

    // Считывание и сохранение ключа
    fgets(buffer, sizeof(buffer), stdin);
    sscanf(buffer, "%d", &key);

    // Проверка ключа
    if (key == -1) {
        printf("Error: Invalid key.\n");
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

    // Вывод информации из разделяемой памяти
    printf("%s\n", sharedMemory);

    // Отключение от сегмента разделяемой памяти
    shmdt(sharedMemory);

    // Удаление сегмента разделяемой памяти
    shmctl(identifier, IPC_RMID, NULL);
    return 0;
}