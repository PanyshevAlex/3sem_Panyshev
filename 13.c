#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <pwd.h>
#include <uuid/uuid.h>
#include <grp.h>
#include <sys/wait.h>
int printinfo()
{
    struct passwd *pwd;
    if (!(pwd = getpwuid(getuid())))
        return 0;
    struct group *grp;
    if (!(grp = getgrgid(pwd->pw_gid)))
        return 0;
    printf("user id: %d\n", pwd->pw_uid);
    printf("user name: %s\n", pwd->pw_name);
    printf("group id: %d\n", pwd->pw_gid);
    printf("group name: %s\n", grp->gr_name);
    printf("Process id: %d\n", getpid());
    printf("Process parent id: %d\n", getppid());
    return 1;
}

int main(int argc, char *argv[])
{
    pid_t child_id = fork();
    switch (child_id)
    {
        case -1:
            perror("fork");
            return 1;
        case 0:
            printf("child:\n");
            if (!printinfo())
            {
                perror("err");
                return 1;
            }
            return 0;
        default:
            wait(NULL);
            printf("parent:\n");
            if (!printinfo())
            {
                perror("err");
                return 1;
            }
            return 0;
    }
            
    return 0;
}
