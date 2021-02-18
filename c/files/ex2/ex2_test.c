/******************************* reviwed bu Eden *****************************/

#include<stdio.h>/*printf fgets*/
#include<stdlib.h>/*malloc free*/
#include"ex2.h"



int main()
{
	char *fgets_suc = NULL;
	STAT stat = SUCCSESS;
	char *str = NULL;
	/*char *file_name = "rec.txt";*/
	char file_name[300] = "0";


	func arr[4];
	arr[0].name = "-remove";
	arr[0].cmp = RemCmp;
	arr[0].operation = RemoveFile;

	arr[1].name = "-count";
	arr[1].cmp = CountCmp;
	arr[1].operation = CountFile;

	arr[2].name = "-exit";
	arr[2].cmp = ExitCmp;
	arr[2].operation = Exit;

	arr[3].name="<";
	arr[3].cmp=AppFirstCmp;
	arr[3].operation=AppendInBeginning;

	arr[4].name="append";
	arr[4].cmp=AppLastCmp;
	arr[4].operation=Append;

	
	printf("Please enter the file name followed by Enter key:\n");
	scanf("%s", file_name);

	str = (char*)malloc(100 * sizeof(char));
	if(str == NULL)
	{
		printf("malloc");
		return (1);
	}
	
	getchar();
	while(stat == SUCCSESS)
	{
			
		printf("Please enter string to be added to the file\n"	
		" -NOTE- max size of string is 100 chars\n");

		fgets_suc = fgets(str, 100, stdin);
		
		
		if(fgets_suc==NULL)
		{
			printf("Coulden't get input\n");
			return(1);
		}
				
		stat = Comparition(file_name, str, arr);	
		if(ERROR == stat)
		{
			free(str);	
			return(1);
		}
	}

		free(str);	
	
	exit(0); /*only exit works (approved by Erez)*/
}
