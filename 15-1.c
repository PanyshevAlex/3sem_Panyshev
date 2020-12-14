#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int g_last_signal;

void signal_handler(int val)
{
    g_last_signal = val;
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
        pause();
        switch (g_last_signal)
        {
            case SIGINT:
                printf("^C doesnt't work\n");
                break;
            case SIGQUIT:
                printf("^\\ doesn't work\n");
                break;
            case SIGTERM:
                printf("SIGTERM doesn't work\n");
                break;
            default:
                printf("unknown signal");
                break;
        }
    }
    return 1;
}
