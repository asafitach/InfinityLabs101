#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>


#define BUFF_SIZE 100

int main()
{
	int fd1;
	char * file_path = "/home/asafitach/asaf-itach/system_programming/pip";
	char str1[BUFF_SIZE] = {0}; 
	char str2[BUFF_SIZE] = "program 2 sends Hi!\n"; 

	mkfifo(file_path, 0666);

	while (1)
	{
		fd1 = open(file_path,O_RDONLY);
		read(fd1, str1, BUFF_SIZE);

		printf("User1: %s\n", str1);
		close(fd1);

		fd1 = open(file_path,O_WRONLY);
		write(fd1, str2, 21);
		close(fd1);
        sleep(1);
	}
	return 0;
}
