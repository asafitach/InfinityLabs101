#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"ex2.h"



int comparition(char *file_name,char *str, func *arr)
	{
	int i=0; 
	for(i=0;i<5;i++)
	{			
		if(arr[i].cmp(str)==0)
		{
			printf("%d %s\n", i
			i=arr[i].operation(file_name, str);
			return(i);
		}
	}
	return(ERROR);
}




/**********************************************************/

int RemoveFile( char *file_name, char *str)
{
	str = str; 
			
	if(remove(file_name)!=0)
	{
		printf("Eror in removing file");
		return(ERROR);
	}
	
	return(SUCSSES);
}

/**********************************************************/

int CountFile (char *file_name, char *str)
{
	int count = 0;
	char *ptr = str;
	int check = 0;
	FILE *f_ptr = NULL;
	
	f_ptr = fopen(file_name, "r");
	if(f_ptr == NULL)
	{
		printf("Counter:Eror found while loading the file");
		return(ERROR);
	}

	while(ptr != NULL)
	{
		ptr = fgets(str,100, f_ptr);
		count++;
	}
	
	check = fclose(f_ptr);
	if(check != 0)
	{
		printf("Closing failed");
		return(ERROR);
	}

	ptr=NULL;
	f_ptr=NULL;

	printf("\nCounter stands on %d\n", count-1);
		
	return(SUCSSES);
}

/**********************************************************/

int Exit (char *file_name, char *str)
{
	str=str;
	printf("\n \n End of session with %s, good-bye \n \n", file_name);
	return(EXIT_DONE);
}

/**********************************************************/

int Append(char *name_of_file, char *str)
{
	int check = 0;
	FILE *f_ptr = NULL;

	
	f_ptr = fopen(name_of_file, "+a");
	if(f_ptr == NULL)
	{
		printf("Eror found while loading the file");
		return(ERROR);
	}

	check = fprintf(f_ptr, "\n %s", str);
	if(check < 1)
	{
		printf("Could not append string\n");
		return(ERROR);
	}
	
	check = fclose(f_ptr);
	if(check != 0)
	{
		printf("Closing failed");
		return(ERROR);
	}

	return(SUCSSES);
}

/**********************************************************/

int AppendInBegining(char *file_name, char *str)
{
	int chr = 0;
	int check = 0;
	FILE *f_ptr = NULL;
	FILE *f_tmp_ptr = NULL;
	

	
	f_tmp_ptr = fopen("temp_file.txt", "w+");
	if(f_tmp_ptr==NULL)
	{		printf("Eror found while loading the file");
		return(ERROR);
	}


	f_ptr = fopen(file_name, "r+");
	if(f_ptr==NULL)
	{		printf("Eror found while loading the file");
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
	return(SUCSSES);
}



/**********************************************************/

int RemCmp(char *str)
{
		return(strcmp(str,"-remove"));
}

/**********************************************************/

int CountCmp(char *str)
{
	return(strcmp(str,"-count"));
}

/**********************************************************/

int ExitCmp(char *str)
{
	return(strcmp(str,"-exit"));
}

/**********************************************************/

int AppFirstCmp(char *str)
{
	if(*(str)=='<')
	{
		return(0);
	}
	
	return(1);
}

/**********************************************************/

int AppLastCmp(char *str)
{
	str=str;/*patch*/
	return(0);
}



/*************************EOF******************************/
