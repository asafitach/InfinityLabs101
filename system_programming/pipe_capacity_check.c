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
	char buf2[BUFF_SIZE] = {'a', 0};
    size_t counter = 0;

	mkfifo(file_path, 0666);


		fd = open(file_path, O_WRONLY);

        while (2 > write(fd, buf2, 2))
        {
            ++counter;
        }

        printf("Pipe capacity is %lu bytes\n", counter);

		close(fd);

		fd = open(file_path, O_RDONLY);
        while (0 != read(fd, buf1, BUFF_SIZE)){};



		close(fd);

	return 0;
}
