#include "sharedVariable.h"


void* producer(struct SharedMData *sharedMData) {
    
    for(int i = 0 ; i < ITR; i++) {

        sleep(1);
        sem_wait(&sharedMData->empty);
        pthread_mutex_lock(&sharedMData->mutex);
        sharedMData->n = (sharedMData->n) + 1; 
        printf("Producer produces item %d\n", sharedMData->n); 
        pthread_mutex_unlock(&sharedMData->mutex);
        sem_post(&sharedMData->full);
        
    }

}

int main()
{
    int sharedM_fd = shm_open(NAME, O_CREAT | O_RDWR, 0666); 
    ftruncate(sharedM_fd, SIZE); 
    struct SharedMData *sharedMData = mmap(0, sizeof(*sharedMData), PROT_WRITE, MAP_SHARED, sharedM_fd, 0); 

    sharedMData->n    = 0;
    pthread_mutex_init(&sharedMData->mutex, NULL);
    sem_init(&sharedMData->empty, 0, BUFFER);
    sem_init(&sharedMData->full, 0, 0);

    pthread_t th[THREAD_NUM];

    for (int i = 0; i < THREAD_NUM; i++) {
        if (pthread_create(&th[i], NULL, producer(sharedMData), sharedMData) != 0) {
            perror("Failed to create thread\n");
        }
    }

    for (int i = 0; i < THREAD_NUM; i++) {
        if (pthread_join(th[i], NULL) != 0) {
            perror("Failed to join thread\n");
        }
    }

    sem_destroy(&sharedMData->empty);
    sem_destroy(&sharedMData->full);
    pthread_mutex_destroy(&sharedMData->mutex);

    munmap(sharedMData, SIZE); 
    close(sharedM_fd); 
    shm_unlink(NAME); 
    return EXIT_SUCCESS; 
}