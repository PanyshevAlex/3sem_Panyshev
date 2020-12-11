#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define MSGSZ 128

typedef struct msgbuf {
    long    mtype;
    char    mtext[MSGSZ];
} message_buf;

int main(int argc, char *argv[])
{
    int msgid;
    message_buf msg;
    size_t buf_lenght;


    if ((msgid = msgget((key_t)atoi(argv[1]), 0)) < 0)
    {
        perror("msgget");
        return 0;
    }
    msg.mtype = 1;
    strcpy(msg.mtext, argv[2]);
    buf_lenght = strlen(msg.mtext) + 1;
    if (msgsnd(msgid, &msg, buf_lenght, IPC_NOWAIT) < 0)
    {
        perror("msgsnd");
        return 1;
    }
    else
        printf("Message: \"%s\" Sent\n ", msg.mtext);
    return 1;
}
