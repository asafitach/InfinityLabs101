#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"ex2.h"



int main()
{
char str[100]="0";
char file_name[30]="0";




printf("Please enter the file name followed by Enter key:\n");
scanf("%s", file_name);


printf("Please enter string to be added to the file\n"
" -NOTE- max size of string is 100 chars\n");
scanf("%s", str);


	OpenAppendClose(file_name, str);
	
	CountFile(file_name, str);

	AppendInBegining(file_name, str);

	RemoveFile(file_name, str);

	Exit(file_name, str);

	return (0);

}


