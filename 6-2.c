#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <limits.h>
#include <fcntl.h>
#include <stdlib.h>

const char *dir_type(uint8_t type)
{
    switch (type){
    case DT_FIFO:   return "FIFO";
    case DT_CHR:    return "CHARACTER SPECIAL";
    case DT_DIR:    return "DIRECTORY";
    case DT_BLK:    return "BLOCK SPECIAL";
    case DT_REG:    return "REGULAR";
    case DT_LNK:    return "SYMBOLIC LINK";
    case DT_SOCK:   return "SOCKET";
    case DT_WHT:    return "WHITEOUT";
    default: return "unknown?";
    }
}

const char *is_type(mode_t file_mode)
{

    switch (file_mode & S_IFMT) {
    case S_IFBLK:  return "BLOCK SPECIAL";
    case S_IFCHR:  return "CHARACTER SPECIAL";
    case S_IFDIR:  return "DIRECTORY";
    case S_IFIFO:  return "FIFO";
    case S_IFLNK:  return "SYMBOLIC LINK";
    case S_IFREG:  return "REGULAR";
    case S_IFSOCK: return "SOCKET";
    default:       return "unkwown?";
    }
}

int main(int argc, char *argv[])
{
	if (argc > 2)
	{
		printf("Usage: %s [dir]", argv[1]);
		return 1;
	}
    const char *dir_path = (argc == 2) ? argv[1] : ".";

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
        if (dir->d_type == DT_UNKNOWN){
		    if (fstatat(dir_fd, dir->d_name, &stat_buf, AT_SYMLINK_NOFOLLOW) == -1)
		    {
			    perror("Failed to stat");
			    return 2;
		    }
            printf("%-20s", is_type(stat_buf.st_mode));
        }
        else{
            printf("%-20s", dir_type(dir->d_type));
        }
		printf("%s\n", dir->d_name);
	}
	close(dir_fd);		
	closedir(dir_str);
	return 1;
}
