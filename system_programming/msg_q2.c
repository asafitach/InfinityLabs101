#include <stdio.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define BUFF_SIZE 100

struct mesg_buffer {
	long mesg_type;
	char mesg_text[BUFF_SIZE];
} message;

int main()
{
	key_t key;
	int msgid;


    fork();
    fork();

	key = ftok("msg_queue_key", 65);

	msgid = msgget(key, 0666 | IPC_CREAT);

	msgrcv(msgid, &message, sizeof(message), 1, 0);

	printf("%s",message.mesg_text);

/* 	msgctl(msgid, IPC_RMID, NULL);
 */
	return 0;
}
