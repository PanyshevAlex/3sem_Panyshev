#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MSGSZ 128

int messageid;

typedef struct msgbuf {
    long    mtype;
    char    mtext[MSGSZ];
} message_buf;

void signal_handler(int val)
{
    if (msgctl (messageid, IPC_RMID, (struct msqid_ds *) 0) < 0)
        perror("msg queue remove err");
    else
        printf("The message queue was successfully deleted. Finishing work.\n");
    exit(0);
}

int main(int argc, char *argv[])
{
    int msgid;
    int msgflg = IPC_CREAT | IPC_EXCL | 0666;
    key_t key = 10;
    message_buf rbuf;
    
    if (signal(SIGINT, signal_handler) == SIG_ERR)
    {   
        perror("failed to SIGINT");
        return 1;
    }
    if (signal(SIGTERM, signal_handler) == SIG_ERR)
    {
        perror("failed to SIGTERM");
        return 1;
    }

    if ((msgid = msgget(key, msgflg )) < 0) {
        perror("msgget");
        return 1;
    }
    else
        printf("msgget succeeded: msqid = %d\nkey: %d\n", msgid, key);
    messageid = msgid;
    while (1)
    {
        if (msgrcv(msgid, &rbuf, MSGSZ, 0, 0) < 0)
            perror("msgrcv");
         printf("%s\n", rbuf.mtext);
    }

    return 1;
}
