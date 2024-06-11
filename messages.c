#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define LAST_MESSAGE 255

int main() {
	int msqid;
	char pathname[] = "forftok.ipc";
	key_t key;
	int i, len;
	struct mymsgbuf {
		long mtype;
		char mtext[81];
	} mybuf;
	if((key = ftok(pathname, 0)) < 0) {
		printf("Не удалось сгенерировать ipc-ключ\n");
		exit(-1);
	}
	if((msqid = msgget(key, 0666|IPC_CREAT)) < 0) {
		printf("Не удалось получить дескриптор очереди сообщений\n");
		exit(-1);
	}
	for (i = 1; i <= 5; i++) {
		mybuf.mtype = 1;
		strcpy(mybuf.mtext, "This is message");
		len = strlen(mybuf.mtext) + 1;
		if (msgsnd(msqid, (struct msgbuf *) &mybuf, len, 0) < 0) {
			printf("Не удалось отправить сообщение в очередь\n");
			msgctl(msqid, IPC_RMID, (struct msqid_ds *) NULL);
			exit(-1);
		}
	}
	mybuf.mtype = LAST_MESSAGE;
	len = 0;
	if (msgsnd(msqid, (struct msgbuf *) &mybuf, len, 0) < 0) {
		printf("Не удаётся отправить сообщение в очередь\n");
		msgctl(msqid, IPC_RMID, (struct msqid_ds *) NULL);
		exit(-1);
	}
	return 0;
}
