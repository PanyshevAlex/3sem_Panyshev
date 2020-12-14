#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <limits.h>
#include <fcntl.h>

const char *dir_type(__uint8_t type)
{
    switch (type){
    case DT_FIFO:   return "FIFO";                  break;
    case DT_CHR:    return "CHARACTER SPECIAL";     break;
    case DT_DIR:    return "DIRECTORY";             break;
    case DT_BLK:    return "BLOCK SPECIAL";         break;
    case DT_REG:    return "REGULAR";               break;
    case DT_LNK:    return "SYMBOLIC LINK";         break;
    case DT_SOCK:   return "SOCKET";                break;
    case DT_WHT:    return "WHITEOUT";              break;
    default: return "unknown?";                     break;
    }   
}

const char *is_type(mode_t file_mode)
{

    switch (file_mode & S_IFMT) {
    case S_IFBLK:  return "BLOCK SPECIAL";          break;
    case S_IFCHR:  return "CHARACTER SPECIAL";      break;
    case S_IFDIR:  return "DIRECTORY";              break;
    case S_IFIFO:  return "FIFO";                   break;
    case S_IFLNK:  return "SYMBOLIC LINK";          break;
    case S_IFREG:  return "REGULAR";                break;
    case S_IFSOCK: return "SOCKET";                 break;
    default:       return "unkwown?";               break;
    }   
}

int main(int argc, char *argv[])
{
	if (argc > 2)
	{
		printf("Usage: %s [dir]", argv[1]);
		return 1;
	}
    int offset = 0;
    const char *dir_path = (argc == 2) ? argv[1] : ".";
    struct dirent *dir;
    struct stat stat_buf;
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
        int count_files = __getdirentries64(dir_fd, (char *)buf, (int)sizeof(buf), &basep);
        if (count_files == -1)
        {
            perror("Failed: to getdirentfiles");
            return -1;
        }
        if (count_files == 0)
           break;
        while (offset < count_files)
        {
            dir = (struct dirent *)(buf + offset);
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
            offset += dir->d_reclen;
        }
        offset = 0;
    }
	close(dir_fd);
	return 1;
}
