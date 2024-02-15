#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

#define BUFFER_SIZE 25
#define READ_END    0
#define WRITE_END   1

int main(void) {
    char write_msg[BUFFER_SIZE] = "Greetings from Parent";
    char read_msg[BUFFER_SIZE];
    pid_t pid;
    int fd1[2]; // Pipe for parent to child communication
    int fd2[2]; // Pipe for child to parent communication

    // Create the pipes
    if (pipe(fd1) == -1 || pipe(fd2) == -1) {
        fprintf(stderr, "Pipe failed");
        return 1;
    }

    // Fork a child process
    pid = fork();

    if (pid < 0) {
        fprintf(stderr, "Fork failed");
        return 1;
    }

    if (pid > 0) { // Parent process
        // Close the unused ends of the pipes
        close(fd1[READ_END]);
        close(fd2[WRITE_END]);

        // Write to the child
        write(fd1[WRITE_END], write_msg, strlen(write_msg) + 1);

        // Close the write end of the first pipe
        close(fd1[WRITE_END]);

        // Read from child
        read(fd2[READ_END], read_msg, BUFFER_SIZE);
        printf("Parent read: %s\n", read_msg);

        // Close the read end of the second pipe
        close(fd2[READ_END]);
    } else { // Child process
        // Close the unused ends of the pipes
        close(fd1[WRITE_END]);
        close(fd2[READ_END]);

        // Read from parent
        read(fd1[READ_END], read_msg, BUFFER_SIZE);
        printf("Child read: %s\n", read_msg);

        // Close the read end of the first pipe
        close(fd1[READ_END]);

        // Write back to parent
        char child_msg[BUFFER_SIZE] = "Hello from Child";
        write(fd2[WRITE_END], child_msg, strlen(child_msg) + 1);

        // Close the write end of the second pipe
        close(fd2[WRITE_END]);
    }

    return 0;
}

