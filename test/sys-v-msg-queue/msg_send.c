#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MSGSZ 128

// Declare the message structure

typedef struct msgbuf {
	long mtype;
	char mtext[MSGSZ];
} message_buf;

int main()
{
	int msqid;
	int msgflg = IPC_CREAT | 0666;
	key_t key;
	message_buf sbuf;
	size_t buf_length;

	key = 2234;

	fprintf(stderr, "\nmsgget: Calling msgget(%#1x,\%#o)\n", key, msgflg);
	if ((msqid = msgget(key, msgflg)) < 0) {
		perror("msgget\n");
		exit(1);
	} else
		fprintf(stderr, "msgget: msgget succeeded: msgqid = %d\n", msqid);

	// We'll send message type 1
	sbuf.mtype = 1;
	strcpy(sbuf.mtext, "Did you get this?");

	buf_length = strlen(sbuf.mtext) + 1;

	// Send a message.
	if((msgsnd(msqid, &sbuf, buf_length, IPC_NOWAIT)) < 0){
		printf("%d, %d, %s, %d\n", msqid, (int)sbuf.mtype, sbuf.mtext, (int)buf_length);
		perror("msgsnd\n");
		exit(1);
	} else
		printf("Message: \"%s\" Sent\n", sbuf.mtext);

	return 0;
}
