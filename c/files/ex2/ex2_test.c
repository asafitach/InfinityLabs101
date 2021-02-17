#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"ex2.h"



int main()
{
	int stat=0;
	char str[100]="0";
	char file_name[300]="0";


	func arr[4];
	arr[0].name="-remove";
	arr[0].cmp=RemCmp;
	arr[0].operation=RemoveFile;

	arr[1].name="-count";
	arr[1].cmp=CountCmp;
	arr[1].operation=CountFile;

	arr[2].name="-exit";
	arr[2].cmp=ExitCmp;
	arr[2].operation=Exit;

	arr[3].name="<";
	arr[3].cmp=AppFirstCmp;
	arr[3].operation=AppendInBegining;

	arr[4].name="append";
	arr[4].cmp=AppLastCmp;
	arr[4].operation=Append;
	 



	printf("Please enter the file name followed by Enter key:\n");
	scanf("%s", file_name);

	stat=5;
	while(5==stat)
	{
		printf("Please enter string to be added to the file\n"
		" -NOTE- max size of string is 100 chars\n");
		scanf("%s", str);

		stat=comparition(file_name, str, arr);
	}

	if(7==stat)
	{
		exit(1);
	}

		return (0);

}

