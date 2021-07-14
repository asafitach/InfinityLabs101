#include <stdio.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define BUFF_SIZE 100

struct mesg_buffer {
	long mesg_type;
	char mesg_text[100];
} message;

int main()
{
	key_t key;
	int msgid;

	key = ftok("msg_queue_key", 65);

	msgid = msgget(key, 0666 | IPC_CREAT);
	message.mesg_type = 1;
    strcpy(message.mesg_text, "Write msg...\n");

	msgsnd(msgid, &message, sizeof(message), 0);
	msgsnd(msgid, &message, sizeof(message), 0);
	msgsnd(msgid, &message, sizeof(message), 0);
	msgsnd(msgid, &message, sizeof(message), 0);

	printf("Data send is : %s \n", message.mesg_text);

	return 0;
}
