#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>


#define BUFF_SIZE 100

int main()
{
	int reader;
	int writer;
	char *file_path_read = "/home/asafitach/asaf-itach/system_programming/pipping";
	char *file_path_write = "/home/asafitach/asaf-itach/system_programming/pippong";
	char buf1[BUFF_SIZE] = {0};
	char buf2[BUFF_SIZE] = "program 1 sends Hi!\n";
	int counter = 30;



	while (counter)
	{
	reader = open(file_path_read, O_RDONLY);
		read(reader, buf1, BUFF_SIZE);
        printf("ping: %s\n", buf1);
	close(reader);

	writer = open(file_path_write, O_WRONLY);
		if (-1 == write(writer, buf2, 21))
		{
			perror("failed to write\n");
			exit(1);
		}
	close(writer);

        sleep(1);
		--counter;
	}
	
	
	return 0;
}
