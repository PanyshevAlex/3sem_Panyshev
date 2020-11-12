#include <errno.h>    
#include <fcntl.h>     
#include <stdio.h>      
#include <stdlib.h>   
#include <string.h>    
#include <sys/event.h>  
#include <unistd.h>      

int main (int argc, const char *argv[])
{
    int kq = kqueue ();
    if (kq == -1)
    {
        perror("Failed to kqueue");
        return -1;
    }
    int dirfd = open (argv[1], O_RDONLY);
    if (dirfd == -1)
    {
        perror("Failed to open");
        return -1;
    }
    struct kevent direvent;
    EV_SET (&direvent, dirfd, EVFILT_VNODE, EV_ADD | EV_CLEAR | EV_ENABLE,
            NOTE_WRITE, 0, (void *)argv[1]);

    kevent(kq, &direvent, 1, NULL, 0, NULL);

    struct kevent sigevent;
    EV_SET (&sigevent, SIGINT, EVFILT_SIGNAL, EV_ADD | EV_ENABLE, 0, 0, NULL);
    signal (SIGINT, SIG_IGN);

    kevent(kq, &sigevent, 1, NULL, 0, NULL);

    while (1) {
        struct kevent change;
        if (kevent(kq, NULL, 0, &change, 1, NULL) == -1) { exit(1); }
        if (change.udata == NULL) {
            break;
        } else {
        printf ("%s\n", (char*)change.udata);
        }
    }
    close (kq);
    return 0;
}
