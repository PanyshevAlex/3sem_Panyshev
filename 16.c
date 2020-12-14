#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main(void)
{
    struct msqid_ds qstatus;
    int qid = msgget(IPC_PRIVATE,IPC_CREAT | 0600);

    if (qid == -1)
    {
        perror("msgget failed");
        return 1;
    }
    if (msgctl(qid,IPC_STAT,&qstatus) < 0)
    {
        perror("msgctl failed");
        return 1;
    }
    printf("Real uid: %d\n",qstatus.msg_perm.cuid);
    printf("Real gid: %d\n",qstatus.msg_perm.cgid);
    printf("Effective uid: %d\n",qstatus.msg_perm.uid);
    printf("Effective gid: %d\n",qstatus.msg_perm.gid);
    printf("Permissions: %d\n",qstatus.msg_perm.mode);
    printf("Message queue id: %d\n",qid);
    printf("%lu message(s) on queue\n",qstatus.msg_qnum);
    printf("Last message sent:%3d at %s \n",qstatus.msg_lspid,ctime(& (qstatus.msg_stime)));
    printf("Last message recieved: %3d at %s \n",qstatus.msg_lrpid,ctime(& (qstatus.msg_rtime)));
    printf("Current bytes on queue %lu\n",qstatus.msg_cbytes);
    printf("Maximum bytes allowed on the queue %lu\n",qstatus.msg_qbytes);
    if (msgctl (qid, IPC_RMID, (struct msqid_ds *) 0) < 0)
        perror("msg queue remove err");
    return 1;
}
