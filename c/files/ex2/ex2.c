#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"ex2.h"



int comparition(char *file_name,char *str, func *arr)
	{
	int i=0; 
	for(i=0;i<5;i++)
	{			printf("%d", i);
		if(arr[i].cmp(str)==0)
		{

			i=arr[i].operation(file_name, str);/*************5 means succses 6 means exit 7 means eror*/
		}
	}
	return(i);
}




/**********************************************************/

int RemoveFile( char *file_name, char *str)
{
	str = str; 
			
	if(remove(file_name)!=0)
	{
		printf("Eror in removing file");
		return(7);
	}
	
	return(5);
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
		return(7);
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
		return(7);
	}

	ptr=NULL;
	f_ptr=NULL;

	printf("\nCounter stands on %d\n", count-1);
		
	return(5);
}

/**********************************************************/

int Exit (char *file_name, char *str)
{
	str=str;
	printf("\n \n End of session with %s, good-bye \n \n", file_name);
	return(6);
}

/**********************************************************/

int Append(char *name_of_file, char *str)
{
	int check = 0;
	FILE *f_ptr = NULL;

	
	f_ptr = fopen(name_of_file, "a");
	if(f_ptr == NULL)
	{
		printf("Eror found while loading the file");
		return(7);
	}

	check = fprintf(f_ptr, "\n %s", str);
	if(check < 1)
	{
		printf("Could not append string\n");
		return(7);
	}
	
	check = fclose(f_ptr);
	if(check != 0)
	{
		printf("Closing failed");
		return(7);
	}
		printf("hhhh");
	return(5);
}

/**********************************************************/

int AppendInBegining(char *file_name, char *str)
{
	int chr = 0;
	int check = 0;
	FILE *f_ptr = NULL;
	FILE *f_tmp_ptr = NULL;
	

	
	f_tmp_ptr = fopen("temp_file.txt", "w+");

	f_ptr = fopen(file_name, "w+");

	/*f_ptr=CopyFile(f_tmp_ptr, f_ptr);
	*/

	chr = fgetc(f_ptr);
	while(chr > 0)
	{
		chr = fputc( chr, f_tmp_ptr);
		chr = fgetc(f_ptr);
	}
	
	
	rewind(f_tmp_ptr);
	rewind(f_ptr);
	
	check = fprintf(f_ptr, "\n %s", str);
	if(check < 1)
	{
		printf("Could not append string\n");
	}
	
	/*f_ptr=CopyFile(f_ptr, f_tmp_ptr);
	*/
	
	chr = fgetc(f_tmp_ptr);
	while(chr > 0)
	{
		chr = fputc( chr, f_ptr);	
		chr = fgetc(f_tmp_ptr);
	}
	
	
	check = fclose(f_ptr);
	if(check != 0)
	{
		printf("Closing failed");
	}
	fclose(f_tmp_ptr);
	/*RemoveFile("temp_file.txt", str);
*/	return(5);
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
	str=str;
	return(0);
}

/*************************EOF******************************/
