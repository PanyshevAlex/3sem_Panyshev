#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <limits.h>
#include <fcntl.h>
#include <string.h>

void is_type(file_mode)
{       
        if (S_ISREG(file_mode)) 
                printf("(%s)\n", "REGULAR");
        if (S_ISDIR(file_mode)) 
                printf("(%s)\n", "DIRECTORY");
        if (S_ISCHR(file_mode)) 
                printf("(%s)\n", "CHARACTER SPECIAL");
        if (S_ISBLK(file_mode)) 
                printf("(%s)\n", "BLOCK SPECIAL");
        if (S_ISFIFO(file_mode))
                printf("(%s)\n", "FIFO");
        if (S_ISLNK(file_mode)) 
                printf("(%s)\n", "SYMBOLIC LINK");
        if (S_ISSOCK(file_mode))
                printf("(%s)\n", "SOCKET");
        if (S_ISWHT(file_mode)) 
                printf("(%s)\n", "WHITEOUT");
}

int dirw(char *dir_path, int lvl)
{
	DIR *dir_str = opendir(dir_path);
	if (dir_str == NULL)
	{
		perror("Failed to opendir");
		return -1;
	}

	int dir_fd;
	if ((dir_fd = dirfd(dir_str)) == -1)
	{
		perror("Failed to dirfd");
		return -1;
	}
	struct dirent *dir;
	struct stat stat_buf;
	while ((dir = readdir(dir_str)) != NULL)
	{
		if (fstatat(dir_fd, dir->d_name, &stat_buf, AT_SYMLINK_NOFOLLOW) == -1)
		{
			perror("Failed to fstatat");
			return -1;
		}
		int i;
		for (i = 5*lvl; i > 0; i--)
			printf("-");
		printf("%s", dir->d_name);
		is_type(stat_buf.st_mode);
		if (S_ISDIR(stat_buf.st_mode) && (strcmp(dir->d_name, ".") != 0) && (strcmp(dir->d_name, "..") != 0))
		{
			char file_path[PATH_MAX];
			snprintf(file_path, sizeof file_path, "%s/%s", dir_path, dir->d_name);
			dirw(file_path, lvl+1);
		}
	}
	close(dir_fd);
	closedir(dir_str);
	return 1;
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
	if (dirw(dir_path, 0) == -1)
	{
		printf("Error");
		return 2;
	}

	return 1;
}
