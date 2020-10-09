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
	struct stat stat_buf;
	if (lstat(argv[1], &stat_buf) == -1)
	{
		perror("Failed to stat");
		return 3;
	}
	int dst_fd = open(argv[2], O_WRONLY|O_CREAT|O_TRUNC, stat_buf.st_mode);
	if (dst_fd == -1){
		perror("Failed to open target file:");
		return 2;
	}
	if (fchmod(dst_fd, stat_buf.st_mode) == -1)
	{
		perror("Failed to fchmod");
		return 3;
	}
	struct timespec am_time[2] = {{stat_buf.st_atime, 0},{stat_buf.st_mtime, 0}};
		
	while (1){
		uint8_t buf[4096];
		ssize_t buf_size = read(src_fd, buf, sizeof(buf));

		if (buf_size == -1){
			perror("Failed to read a block");
			close(src_fd);
			close(dst_fd);
		}
		if (buf_size == 0){
			break;
		}
		size_t local_buf_size = (size_t)buf_size;
		size_t bytes_written = 0;
		while (bytes_written < local_buf_size){
			ssize_t write_result = write(dst_fd, &buf[bytes_written], local_buf_size - bytes_written);
			fsync(dst_fd);
			if (write_result == -1){
				perror("Failed to write");
				close(src_fd);
				close(dst_fd);
				return 3;
			}
			bytes_written += (size_t)write_result;
		}
			
	}
	if (futimens(dst_fd, am_time) == -1)
	{
		perror("Failed to futimens");
		return 3;
	}
	close(src_fd);
	close(dst_fd);
	return 0;
}
