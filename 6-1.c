#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <limits.h>

void is_type(mode_t file_mode)
{

    switch (file_mode & S_IFMT) {
    case S_IFBLK:  printf("%-20s", "BLOCK SPECIAL");            break;
    case S_IFCHR:  printf("%-20s", "CHARACTER SPECIAL");        break;
    case S_IFDIR:  printf("%-20s", "DIRECTORY");               break;
    case S_IFIFO:  printf("%-20s", "FIFO");               break;
    case S_IFLNK:  printf("%-20s", "SYMBOLIC LINK");                 break;
    case S_IFREG:  printf("%-20s", "REGULAR");            break;
    case S_IFSOCK: printf("%-20s", "SOCKET");                  break;
    default:       printf("%-20s", "unkwown?");                break;
    }
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
		dir_path = ;
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
 	struct dirent *dir;
	struct stat stat_buf;
	printf("%-20s%s\n", "type", "name");
	while ((dir = readdir(dir_str)) != NULL){
		char file_path[PATH_MAX];
		snprintf(file_path, sizeof file_path, "%s/%s", dir_path, dir->d_name);

		if (lstat(file_path, &stat_buf) == -1)
		{
			perror("Failed to stat");
			return 2;
		}	
		is_type(stat_buf.st_mode);
		printf("%s\n", dir->d_name);
	}
		
	closedir(dir_str);
	return 1;
}
