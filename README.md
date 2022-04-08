# Operating-System-assgnments

The Producer-Consumer problem is a classical problem. The Producer-Consumer problem is used for multi-process synchronization, which means synchronization between more than one processes.
In this problem, we have one producer and one consumer. The producer is the one who produces something, and the consumer is the one who consumes something, produced by the producer. The producer and consumer both share the common memory buffer, and the memory buffer is of fixed-size.

I have created the following four files for this assignment
1. producer.c
2. consumer.c
3. sharedVariable.h
4. cleanup.c

To compile and run the program use the following commands.                                                                                                                              
$ gcc sharedVariable.c -pthread -lrt -o producer

$ gcc consumer.c -pthread -lrt -o consumer

$ gcc cleanup.c -pthread -lrt -o cleanup

$ ./producer & ./consumer &

./cleanup can be used to clean the buffer if the program crashes and is not able to clean the buffer

The output is:

Producer produces item 1

Producer produces item 2

Consumer consumes item 2

Producer produces item 2

Consumer consumes item 2

Consumer consumes item 1


sharedVariable.h contains all my global variables for producer.c and consumer.c. You can adjust the number of threads, the buffer size and iterations in sharedVariable.h at the top of the code. It has a data structure, struct SharedMData which is shared amongs both producer.c and consumer.c

The code for SharedMData() located in sharedVariable.h

One of the main requirements for this assignment is to use a shared memory, I declared it in main method of producer.c
shm_open() is used to create shared memory as followed.

shm_open(NAME, O_CREAT | O_RDWR, 0666); 

consumer.c also has to call shm_open() to access the share memory without passing O_CREAT, meaning that it is accessing the shared memory that producer.c created; it does not have to reserve share memory.

I mapped SharedMData in shared memeory after creating the shared memory object.

