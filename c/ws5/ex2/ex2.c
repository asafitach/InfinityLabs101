#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"ex2.h"


/*
struct func arr[4];
arr[0].name="-remove";
arr[0].cmp=RemCmp;
arr[0].ptr=RemoveFile;

arr[1].name="-count";
arr[1].cmp=CountCmp;
arr[1].ptr=CountFile;

arr[2].name="-exit";
arr[2].cmp=ExitCmp;
arr[2].ptr=Exit;

arr[3].name="<";
arr[3].cmp=AppFirstCmp;
arr[3].ptr=AppendInBegining;

arr[4].name="append";
arr[4].cmp=AppLastCmp;
arr[4].ptr=Append;
*/ 

/**********************************************************/

int Append(char *name_of_file, char *str)
{
	int check=0;
	FILE *f_ptr=NULL;
	
	f_ptr=fopen(name_of_file, "a");
	if(f_ptr==0)
	{
		printf("Eror found while loading the file");
		return(0);
	}

	check=fprintf(f_ptr, "\n %s", str);
	if(check<1)
	{
		printf("Could not append string\n");
		return(0);
	}
	
	check=fclose(f_ptr);
	if(check!=0)
	{
		printf("Closing failed");
		return(0);
	}

	return(4);
}

/**********************************************************/

int RemoveFile( char *file_name, char *str)
{
	int i=0;
	
	i=remove(file_name);
	
	if(i==-1)
	{
		printf("Eror in removing file");
		return(0);
	}
	return(1);
}

/**********************************************************/

int CountFile (char *file_name, char *str)
{
	int count=0;
	char *ptr=str;
	int check=0;
	FILE *f_ptr=NULL;
	
	f_ptr=fopen(file_name, "r");
	if(f_ptr==0)
	{
		printf("Counter:Eror found while loading the file");
		return(0);
	}

	while(ptr!=0)
	{
		ptr= fgets(str,100, f_ptr);
		count++;
	}
	
	check=fclose(f_ptr);
	if(check!=0)
	{
		printf("Closing failed");
		return(0);
	}

	ptr=NULL;
	f_ptr=NULL;

	printf("\nCounter stands on %d\n", count-1);
		
	return(2);
}

/**********************************************************/

int Exit (char *file_name, char *str)
{
	printf("\n \n End of session with %s, good-bye \n \n", file_name);
	exit(0);
	return(4);
}

/**********************************************************/

int AppendInBegining(char *file_name, char *str)
{
	int chr=0;
	int check=0;
	char copy[100]="0";
	FILE *f_ptr=NULL;
	FILE *f_tmp_ptr=NULL;
	
	
	f_tmp_ptr=fopen("temp_file.txt", "w+");

	f_ptr=fopen(file_name, "w+");

	/*f_ptr=CopyFile(f_tmp_ptr, f_ptr);
	*/

	chr=fgetc(f_ptr);
	while(chr>0)
	{
		chr=fputc( chr, f_tmp_ptr);
		chr=fgetc(f_ptr);
	}
	
	
	rewind(f_tmp_ptr);
	rewind(f_ptr);
	
	check=fprintf(f_ptr, "\n %s", str);
	if(check<1)
	{
		printf("Could not append string\n");
	}
	
	/*f_ptr=CopyFile(f_ptr, f_tmp_ptr);
	*/
	
	chr=fgetc(f_tmp_ptr);
	while(chr>0)
	{
		chr=fputc( chr, f_ptr);	
		chr=fgetc(f_tmp_ptr);
	}
	
	
	check=fclose(f_ptr);
	if(check!=0)
	{
		printf("Closing failed");
	}
	fclose(f_tmp_ptr);
	/*RemoveFile("temp_file.txt", str);
*/	return(0);
}

/**********************************************************/

int RemCmp(char *str)
{
	if(strcmp(str,"-remove"))
	{
		return(REMOVE);
	}
	
	return(FAILED);
}

/**********************************************************/

int CountCmp(char *str)
{
	if(strcmp(str,"-count"))
	{
		return(COUNT);
	}
	
	return(FAILED);
}

/**********************************************************/

int AppLastCmp(char *str)
{
	if(*str=='<')
	{
		return(APPINBEG);
	}
	
	return(FAILED);
}

/**********************************************************/

int AppFirstCmp(char *str)
{
	str=str;
	return(APPINEND);
}

/**********************************************************/

int ExitCmp(char *str)
{
	if(strcmp(str,"-exit"))
	{
		return(EXIT);
	}
	
	return(FAILED);
}

/*************************EOF******************************/

