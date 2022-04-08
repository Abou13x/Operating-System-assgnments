#include "sharedVariable.h"
  
void* consumer(struct SharedMData *sharedMData) {
    
    for(int i = 0 ; i < (ITR+3); i++) {

        sleep(2); 
        sem_wait(&sharedMData->full);
        pthread_mutex_lock(&sharedMData->mutex);
        printf("Consumer consumes item %d\n", sharedMData->n);  
        sharedMData->n = (sharedMData->n) - 1;
        pthread_mutex_unlock(&sharedMData->mutex);
        sem_post(&sharedMData->empty);
        
    }
}

int main()
{   

    sleep(1); 

    int sharedM_fd = shm_open(NAME, O_EXCL | O_RDWR, 0666); 

    ftruncate(sharedM_fd, SIZE); 

    struct SharedMData *sharedMData = mmap(0, sizeof(*sharedMData), PROT_READ | PROT_WRITE, MAP_SHARED, sharedM_fd, 0); 


    pthread_t th[THREAD_NUM];

    for (int i = 0; i < THREAD_NUM; i++) {
        if (pthread_create(&th[i], NULL, consumer(sharedMData), sharedMData) != 0) {
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