#ifndef SHAREDVARIABLE_H
#define SHAREDVARIABLE_H

#define NAME "OS"
#define NUM 8
#define SIZE 4096
#define BUFFER 2
#define THREAD_NUM 1
#define ITR 5

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <pthread.h>
#include <semaphore.h>
#include <err.h> 
#include <errno.h>
#include <time.h>

struct SharedMData {
	int n; 
    sem_t full;
	sem_t empty;
	pthread_mutex_t mutex;
};

#endif /* SHAREDVARIABLE_H */