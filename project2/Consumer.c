#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>

int main() {
    const char *name = "OS"; // Name shared memory 
    const int SIZE = 4096;   // Sizet

    int shm_fd;  // Shared memory r
    void *ptr;   // Pointer to the shared memory

    // Open the shared memory segment
    shm_fd = shm_open(name, O_RDONLY, 0666);
    if (shm_fd == -1) {
        printf("shared memory failed\n");
        exit(-1);
    }

    // Map the shared memory segment 
    ptr = mmap(0, SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);
    if (ptr == MAP_FAILED) {
        printf("Map failed\n");
        exit(-1);
    }

    // Read from the shared memory region
    printf("%s", (char *)ptr);

    // Remove the shared memory
    if (shm_unlink(name) == -1) {
        printf("Error removing %s\n", name);
        exit(-1);
    }

    return 0;
}

