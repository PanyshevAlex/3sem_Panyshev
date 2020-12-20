#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char *argv[])
{
    if (argc != 3){ 
        printf("Usage: %s some.file string\n", argv[0]);
        return 1;
    }   
    int fd = open(argv[1], O_WRONLY|O_CREAT|O_APPEND, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);//mode -rw-r--r--
    if (fd == -1){
        perror("Failed to open:");
        return 2;
    }   

    ssize_t string_size = strlen(argv[2]);
    ssize_t bytes_written = 0;
    while (bytes_written < string_size){
        ssize_t write_result = dprintf(fd, "%s", &argv[2][bytes_written]);
        if (write_result == -1){
            perror("Failed to dprintf");
            close(fd);
            return -1; 
        }   
        bytes_written += write_result;
    }   
    if (fsync(fd) == -1) 
    {   
        perror("Failed to fsync");
    }   
    if (close(fd) == -1){
        perror("Failed to close");
        return 3;
    }   
    return 0;
} 
