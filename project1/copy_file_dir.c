#include <fcntl.h> // for file operations
#include <unistd.h> // for file operations 
#include <dirent.h> // for directory traversing
#include <sys/stat.h> // for file statistic
#include <stdio.h> // I/O operations
#include <string.h> // string operations

void copy_file(const char *src, const char *dest); // This is the copy function copys the content from souce file to destination file
void copy_directory(const char *src, const char *dest); // Copy funcion for directory 

void copy_file(const char *src, const char *dest) {
    int fd_src, fd_dest; // used to file store descriptors keeps track of file 
    ssize_t nread; // read the size of of blocks that can be read of written in a single operation
    char buffer[1024]; // buffer a byte array with size to hold temp data 

    fd_src = open(src, O_RDONLY);// attempt to open src file 
    if (fd_src < 0) {
        perror("Error opening source file");
        return;
    }

    fd_dest = creat(dest, 0644); // create a destination file 
    if (fd_dest < 0) {
        perror("Error creating destination file"); // error checking
        close(fd_src); // close file 
        return;
    }

    while ((nread = read(fd_src, buffer, sizeof(buffer))) > 0) {  // Loop that reads up to 1024 bytes, from fd_src, into buffer, nread stores the numbers 
        if (write(fd_dest, buffer, nread) < nread) {
            perror("Error writing to destination file");
            break;
        }
    }

    close(fd_src); // close 
    close(fd_dest); // close 
}

void copy_directory(const char *src, const char *dest) {
    DIR *dir;
    struct dirent *entry;
    char src_path[1024];
    char dest_path[1024];

    if (mkdir(dest, 0755) < 0) {
        perror("Error creating destination directory");
        return;
    }

    dir = opendir(src);
    if (!dir) {
        perror("Error opening source directory");
        return;
    }

    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        snprintf(src_path, sizeof(src_path), "%s/%s", src, entry->d_name);
        snprintf(dest_path, sizeof(dest_path), "%s/%s", dest, entry->d_name);

        if (entry->d_type == DT_DIR) {
            copy_directory(src_path, dest_path);
        } else {
            copy_file(src_path, dest_path);
        }
    }

    closedir(dir);
}

int main(int argc, char *argv[]) { // 
    if (argc != 3) { // checks if arguements is 3, must be program name, source path, destination path
        fprintf(stderr, "Usage: %s <source> <destination>\n", argv[0]); // print statment 
        return 1;
    }

    struct stat stat_buf;
    if (stat(argv[1], &stat_buf) != 0) {
        perror("Error getting source information"); // error catching 
        return 1;
    }

    if (S_ISDIR(stat_buf.st_mode)) { // checks if source is a directory
        copy_directory(argv[1], argv[2]);
    } else {
        copy_file(argv[1], argv[2]);
    }

    return 0;
}
