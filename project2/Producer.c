#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/types.h>

int main() {
    const int SIZE = 4096;       // shared memory
    const char *name = "OS";     //Name of the shared memory
    const char *message0 = "Studying ";      
    const char *message1 = "Operating Systems ";
    const char *message2 = "Is a blast!";

    int shm_fd;  // Shared memory descriptor
    void *ptr;   // Pointer to the shared memory

    // Create the shared memory
    shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);

   
    ftruncate(shm_fd, SIZE);

    // Map the shared memory 
    ptr = mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (ptr == MAP_FAILED) { //error check
        printf("Map failed\n");
        return -1;
    }

    // Write to the shared memory
    sprintf(ptr, "%s", message0);
    ptr += strlen(message0);
    sprintf(ptr, "%s", message1);
    ptr += strlen(message1);
    sprintf(ptr, "%s", message2);
    ptr += strlen(message2);

    return 0;
}

