#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void signal_handler(int val)
{
    if (val == 2)
    {
        printf("^C doesn't work buddy\n");
    }
    if (val == 3)
    {
        printf("^\\ doesn't work buddy\n");
    }
    if (val == 15)
    {
        printf("SIGTERM doesn't work buddy\n");
    }
}

int main(){
    if (signal(SIGINT, signal_handler) == SIG_ERR)
    {
        perror("failed to SIGINT");
        return 1;
    }
    if (signal(SIGQUIT, signal_handler) == SIG_ERR)
    {
        perror("failed to SIGQUIT");
        return 1;
    }
    if (signal(SIGTERM, signal_handler) == SIG_ERR)
    {
        perror("failed to SIGTERM");
        return 1;
    }
    while(1)
    {
        printf("im alive\n");
        sleep(1);
    }
    return 1;
}
