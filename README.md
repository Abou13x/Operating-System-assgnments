# Operating-System-assgnments

#Producer-Consumer Problem is a synchronization problem where the producer produces items and place them in the buffer - the consumer consumes the items from the buffer. In this assignment, the producer and the consumer run under two seperate processes while sharing the stack pointer, semaphore and mutex.
#This project contains four files.
#producer.c
#consumer.c
#sharedVariable.h
#cleanup.c

To compile and run the program use the following commands.

$ gcc producer.c -pthread -lrt -o producer
$ gcc consumer.c -pthread -lrt -o consumer
$ gcc cleanup.c -pthread -lrt -o cleanup
$ ./producer & ./consumer &
