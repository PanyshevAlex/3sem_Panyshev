#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdint.h>

int main(int argc, char *argv[])
{
	if (argc != 3){
		printf("Usage: %s [source file] [target file]\n", argv[0]);
		return 1;
	}
	int src_fd = open(argv[1], O_RDONLY);
	if (src_fd == -1){
		perror("Failed to open source file:");
		return 2;
	}
	int dst_fd = open(argv[2], O_WRONLY|O_CREAT|O_TRUNC, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);
	if (dst_fd == -1){
		perror("Failed to open target file:");
		return 2;
	}
	off_t bytes_read = 0;
    off_t all_bytes_written = 0;
	while (1){
		uint8_t buf[4096];
		ssize_t buf_size = pread(src_fd, buf, sizeof(buf), bytes_read);

		if (buf_size == -1){
			perror("Failed to read a block");
			close(src_fd);
			close(dst_fd);
		}
		if (buf_size == 0){
			break;
		}
        bytes_read += buf_size;
		size_t local_buf_size = (size_t)buf_size;
		size_t bytes_written = 0;
		while (bytes_written < local_buf_size){
			ssize_t write_result = pwrite(dst_fd, &buf[bytes_written], local_buf_size - bytes_written, all_bytes_written);
			fsync(dst_fd);
			if (write_result == -1){
				perror("Failed to write");
				close(src_fd);
				close(dst_fd);
				return 3;
			}
			bytes_written += (size_t)write_result;
            all_bytes_written += (off_t)write_result;
		}
			
	}

	close(src_fd);
	close(dst_fd);
	return 0;
}
