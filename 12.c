#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <pwd.h>
#include <uuid/uuid.h>
#include <grp.h>

int main(int argc, char *argv[])
{
    struct passwd *pwd;
    pwd = getpwuid(getuid());
    struct group *grp = getgrgid(pwd->pw_gid);
    printf("user id: %d\n", pwd->pw_uid);
    printf("user name: %s\n", pwd->pw_name);
    printf("group id: %d\n", pwd->pw_gid);
    printf("group name: %s\n", grp->gr_name);
    printf("Process id: %d\n", getpid());
    printf("Process parent id: %d\n", getppid());
    return 1;
}
