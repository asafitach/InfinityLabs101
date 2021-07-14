#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define BUFF_SIZE 100

int main()
{
	int fd;
	char *file_path = "/home/asafitach/asaf-itach/system_programming/pip";
	char buf1[BUFF_SIZE] = {0};
	char buf2[BUFF_SIZE] = "program 1 sends Hi!\n";

	mkfifo(file_path, 0666);

	while (1)
	{
		fd = open(file_path, O_WRONLY);


		write(fd, buf2, 21);
		close(fd);

		fd = open(file_path, O_RDONLY);
		read(fd, buf1, BUFF_SIZE);
        printf("User1: %s\n", buf1);


		close(fd);
        sleep(1);
	}
	return 0;
}
