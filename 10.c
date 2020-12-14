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

    struct kevent event;
            EV_SET(&event, dirfd, EVFILT_VNODE, EV_ADD | EV_ENABLE | EV_CLEAR, NOTE_WRITE, 0, (void *)argv[1]);

  kevent(kq, &event, 1, NULL, 0, NULL); 
  while (1) {
        struct kevent change;
        if (kevent(kq, NULL, 0, &event, 1, NULL) == -1) { exit(1); }
        if (change.udata == NULL) {
            break;
        } else {
        printf ("%s\n", (char*)change.udata);
        }
    }
    close (kq);
    return 0;
}
