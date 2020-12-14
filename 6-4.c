#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <limits.h>
#include <fcntl.h>
#include <string.h>

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
        int i;
        for (i = 5*lvl; i > 0; i--)
            printf("-");
        printf("%s", dir->d_name);
        if (dir->d_type == DT_UNKNOWN){
            if (fstatat(dir_fd, dir->d_name, &stat_buf, AT_SYMLINK_NOFOLLOW) == -1)
            {
                perror("Failed to fstatat");
                return -1;
            }
            printf("(%s)\n",is_type(stat_buf.st_mode));
            if (S_ISDIR(stat_buf.st_mode) 
                && (strcmp(dir->d_name, ".") != 0) 
                && (strcmp(dir->d_name, "..") != 0))
            {
                char *file_path;
                asprintf(&file_path, "%s/%s", dir_path, dir->d_name);
                dirw(file_path, lvl+1);
            }
        }
        else{
            printf("(%s)\n", dir_type(dir->d_type));
            if (dir->d_type == DT_DIR 
                && (strcmp(dir->d_name, ".") != 0)
                && (strcmp(dir->d_name, "..") != 0))
            {
                char *file_path;
                asprintf(&file_path, "%s/%s", dir_path, dir->d_name);
                dirw(file_path, lvl+1);
            }
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
    const char *dir_path = (argc == 2) ? argv[1] : ".";
    if (dirw(dir_path, 0) == -1)
    {
        printf("Error");
        return 2;
    }

    return 1;
}
