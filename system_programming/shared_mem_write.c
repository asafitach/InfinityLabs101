#include <stdio.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>


int main()
{
	key_t key = ftok("shared_zone",65);
	int shmid = shmget(key,1024,0666|IPC_CREAT);
	char *str = (char*) shmat(shmid,(void*)0,0);

    printf("Write Data : \n");
	strcpy(str, "write in shared zone...\n");

	shmdt(str);

	return 0;
}
