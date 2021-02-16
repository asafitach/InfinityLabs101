#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int CountFile (char *file_name, char *str);
void OpenAppendClose(char *name_of_file, char *str);
int RemoveFile( char *file_name,  char *str);
int Exit (char *file_name,  char *str);
/*FILE *CopyFile(FILE *f_tmp_ptr, FILE *f_ptr);
FILE *OpenFile (char *file_name, char* opt);*/
int AppendInBegining(char *file_name, char *str);

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

/*
	RemoveFile(file_name, str);
	*/Exit(file_name, str);
	return 0;
}




void OpenAppendClose(char *name_of_file, char *str)
{
	int check=0;
	FILE *f_ptr=NULL;
	
	f_ptr=fopen(name_of_file, "a");


	check=fprintf(f_ptr, "\n %s", str);
	if(check<1)
	{
		printf("Could not append string\n");
	}
	
	check=fclose(f_ptr);
	if(check!=0)
	{
		printf("Closing failed");
	}
	return;
}



int RemoveFile( char *file_name, char *str)
{
	int i=0;
	
	i=remove(file_name);
	
	
	if(i==-1)
	{
		printf("Eror in removing file");
		return(1);
	}
	return (0);
}

int CountFile (char *file_name, char *str)
{
	int count=0;
	char *ptr=str;
	int check=0;
	FILE *f_ptr=NULL;
	
	f_ptr=fopen(file_name, "r");


while(ptr!=0)
{
ptr= fgets(str,100, f_ptr);
count++;
}
	check=fclose(f_ptr);
	if(check!=0)
	{
		printf("Closing failed");
	}
ptr=NULL;
f_ptr=NULL;

printf("\nCounter stands on %d\n", count-1);


return(count-1);
}


int Exit (char *file_name, char *str)
{
printf("\n \n End of session with %s, good-bye \n \n", file_name);
exit(0);
return(1);
}

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
/*
FILE *OpenFile (char *file_name, char* opt)
{
FILE *f_ptr=NULL;
	f_ptr=fopen(file_name, opt);
	if(f_ptr==0)
	{
		printf("Eror found while loading the file");
		exit(1);
	}
return(f_ptr);
}


FILE *CopyFile(FILE *f_tmp_ptr, FILE *f_ptr)
{
int chr=0;


chr=fgetc(f_ptr);
while(chr>0)
{
chr=fputc( chr, f_tmp_ptr);
chr=fgetc(f_ptr);
}
return(f_tmp_ptr);
}
*/




