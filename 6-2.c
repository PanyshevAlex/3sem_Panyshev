#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <limits.h>
#include <fcntl.h>

void is_type(file_mode)
{
	if (S_ISREG(file_mode))
		printf("%-20s", "REGULAR");
	if (S_ISDIR(file_mode))
		printf("%-20s", "DIRECTORY");
	if (S_ISCHR(file_mode))
		printf("%-20s", "CHARACTER SPECIAL");
	if (S_ISBLK(file_mode))
		printf("%-20s", "BLOCK SPECIAL");
	if (S_ISFIFO(file_mode))
		printf("%-20s", "FIFO");
	if (S_ISLNK(file_mode))
		printf("%-20s", "SYMBOLIC LINK");
	if (S_ISSOCK(file_mode))
		printf("%-20s", "SOCKET");
	if (S_ISWHT(file_mode))
		printf("%-20s", "WHITEOUT");
}

int main(int argc, char *argv[])
{
	if (argc > 2)
	{
		printf("Usage: %s [dir]", argv[1]);
		return 1;
	}
	char *dir_path = NULL;
	if (argc == 1)
	{
		char current_dir_path[PATH_MAX];
		if (getcwd(current_dir_path,sizeof(current_dir_path)) == NULL)
		{
			perror("Failed to getcwd");
			return 2;
		}
		dir_path = current_dir_path;
	}	
	if (argc == 2)
	{	
		dir_path = argv[1];
	}

	DIR *dir_str = opendir(dir_path);
	if (dir_str == NULL)
	{
		perror("Failed to opendir");
		return 2;
	}
	
	int dir_fd;
	if ((dir_fd = dirfd(dir_str)) == -1)
	{
		perror("Failed to dirfd: ");
		return 2;
	}
 	struct dirent *dir;
	struct stat stat_buf;
	printf("%-20s%s\n", "type", "name");
	while ((dir = readdir(dir_str)) != NULL){
		if (fstatat(dir_fd, dir->d_name, &stat_buf, AT_SYMLINK_NOFOLLOW) == -1)
		{
			perror("Failed to stat");
			return 2;
		}	
		is_type(stat_buf.st_mode);
		printf("%s\n", dir->d_name);
	}
	close(dir_fd);		
	closedir(dir_str);
	return 1;
}
