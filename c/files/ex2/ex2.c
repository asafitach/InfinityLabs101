/******************************* reviwed bu Eden *****************************/

#include<stdio.h>/*printf*/
#include<string.h>/*strcmp*/
#include<stdlib.h>/*remove*/
#include"ex2.h"



int Comparition(char *file_name,char *str, func *arr)
{
	int i=0;
	STAT status = SUCCSESS; 
	for(i = 0; i < 5; i++)
	{			
		if(arr[i].cmp(str) == 0)
		{
			status = arr[i].operation(file_name, str);
			return(status);
		}
	}
	return(ERROR);
}




/**********************************************************/

int RemoveFile(char *file_name, char *str)
{
	str = str; 
			
	if(remove(file_name) != 0)
	{
		printf("Eror in removing file");
		return(ERROR);
	}
	
	return(SUCCSESS);
}

/**********************************************************/

int CountFile (char *file_name, char *str)
{
	int count = 0;
	char str_count[100];
	char *return_value = NULL;
	int check = 0;
	FILE *f_ptr = NULL;
	
	str = str;
	
	f_ptr = fopen(file_name, "r");
	if(f_ptr == NULL)
	{
		printf("Counter:Eror found while loading the file");
		return(ERROR);
	}

	do
	{
		return_value = fgets(str_count,100, f_ptr);
		count++;
	}
	while(return_value != NULL);
		
	check = fclose(f_ptr);
	if(check != 0)
	{
		printf("Closing failed");
		return(ERROR);
	}


	f_ptr=NULL;

	printf("\nCounter stands on %d\n", count-1);
		
	return(SUCCSESS);
}

/**********************************************************/

int Exit (char *file_name, char *str)
{
	str = str;
	printf("\n \n End of session with %s, good-bye \n \n", file_name);
	return(EXIT_DONE);
}

/**********************************************************/

int Append(char *name_of_file, char *str)
{
	int check = 0;
	FILE *f_ptr = NULL;

	
	f_ptr = fopen(name_of_file, "a+");
	if(f_ptr == NULL)
	{
		printf("Eror found while loading the file. function: Append\n");
		return(ERROR);
	}

	check = fprintf(f_ptr, " %s", str);
	if(check < 1)
	{
		printf("Could not append string\n");
		return(ERROR);
	}
	check = 0;
	check = fclose(f_ptr);
	if(check != 0)
	{
		printf("Closing failed");
		return(ERROR);
	}

	return(SUCCSESS);
}

/**********************************************************/

int AppendInBeginning(char *file_name, char *str)
{
	int chr = 0;
	int check = 0;
	FILE *f_ptr = NULL;
	FILE *f_tmp_ptr = NULL;
	

	
	f_tmp_ptr = fopen("temp_file.txt", "w+");
	if(f_tmp_ptr == NULL)
	{		
		printf("Eror found while loading the file");
		return(ERROR);
	}


	f_ptr = fopen(file_name, "r+");
	if(f_ptr == NULL)
	{		
		printf("Eror found while loading the file");
		return(ERROR);
	}

	fputs((str+1), f_tmp_ptr);

	chr = fgetc(f_ptr);
	while(chr != EOF)
	{
		fputc( chr, f_tmp_ptr);
		chr = fgetc(f_ptr);
	}
	
	fseek(f_ptr, 0, SEEK_SET);
	fseek(f_tmp_ptr, 0, SEEK_SET);
	

	chr = fgetc(f_tmp_ptr);
	while(chr != EOF)
	{
		fputc( chr, f_ptr);	
		chr = fgetc(f_tmp_ptr);
	}
	
	
	check = fclose(f_ptr);
	if(check != 0)
	{
		printf("Closing failed");
	}
	fclose(f_tmp_ptr);
	RemoveFile("temp_file.txt", str);
	
	return(SUCCSESS);
}



/**********************************************************/

int RemCmp(char *str)
{
		return(strcmp(str,"-remove\n"));
}

/**********************************************************/

int CountCmp(char *str)
{
	return(strcmp(str,"-count\n"));
}

/**********************************************************/

int ExitCmp(char *str)
{
	int res = 0;
	res=strcmp(str,"-exit\n");
	return(res);
}

/**********************************************************/

int AppFirstCmp(char *str)
{
	if(*(str) == '<')
	{
		return(0);
	}
	
	return(1);
}

/**********************************************************/

int AppLastCmp(char *str)
{
	str = str;                /*patch*/
	return(0);
}



/*************************EOF******************************/
