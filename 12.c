#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <pwd.h>
#include <uuid/uuid.h>
#include <grp.h>

int main(int argc, char *argv[])
{
    printf("Process id: %d\n", getpid());
    printf("Process parent id: %d\n", getppid());
    struct passwd *pwd;
    if (!(pwd = getpwuid(getuid())))
    {
        perror("Error");
        return 0;
    }
    printf("user id: %d\n", pwd->pw_uid);
    printf("user name: %s\n", pwd->pw_name);
    printf("group id: %d\n", pwd->pw_gid);
    struct group *grp;
    if (!(grp = getgrgid(pwd->pw_gid)))
    {
        perror("Error");
        return 0;
    }    
    printf("group name: %s\n", grp->gr_name);
    gid_t *group;
    int ngroups;
    long ngroups_max;

    ngroups_max = sysconf(_SC_NGROUPS_MAX) + 1;
    group = (gid_t *)malloc(ngroups_max *sizeof(gid_t));

    ngroups = getgroups(ngroups_max, group);
    printf("groups:");
    struct group *grps;
    for (int i = 0; i < ngroups; i++)
    {
        printf("%d", group[i]);
        if (!(grps = getgrgid(group[i])))
            printf("(err)");
        printf("(%s);", grps->gr_name);
    }
    printf("\n");
    return 1;
}
