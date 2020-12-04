#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/dirent.h>
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
	int dir_fd = open(dir_path, O_RDONLY);
	if (dir_fd == 0)
	{
		perror("Failed to open");
		return 2;
	}
    printf("%-20s%s\n", "type", "name");
    while (1)
    {
        char buf[16 * sizeof(struct dirent)];
        long basep = 0;
        int count_files = __getdirentries64(dir_fd, buf, (int)sizeof(buf), &basep);
        if (count_files == -1)
        {
            perror("Failed: to getdirentfiles");
            return -1;
        }
        if (count_files == 0)
        {
            printf("im so sad");
            break;
        }
        printf("%s", buf);
    }
	close(dir_fd);
	return 1;
}
