
typedef struct{
char *name;
int (*cmp)(char *);
int (*operation)(char*, char*);
} func;



typedef enum {
    SUCSSES   = 0, 
    EXIT_DONE = 1,
    ERROR     = 2
} STAT;
 

int comparition(char *file_name,char *str, func *arr);
int RemoveFile( char *file_name,  char *str);
int CountFile (char *file_name, char *str);
int Exit (char *file_name,  char *str);
int AppendInBegining(char *file_name, char *str);
int Append(char *name_of_file, char *str);


/****COMPARITION FUNCTIONS****/
int RemCmp(char *str);
int CountCmp(char *str);
int ExitCmp(char *str);
int AppLastCmp(char *str);
int AppFirstCmp(char *str);



/*FILE *CopyFile(FILE *f_tmp_ptr, FILE *f_ptr);
FILE *OpenFile (char *file_name, char* opt);*/
