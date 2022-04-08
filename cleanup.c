#include "sharedVariable.h"

int main(){
    int sharedM_fd = shm_open(NAME, O_EXCL | O_RDWR, 0666);

    perror("shm_open() is already open closing now.\n");
    close(sharedM_fd);
    shm_unlink(NAME);

    return EXIT_SUCCESS;
}