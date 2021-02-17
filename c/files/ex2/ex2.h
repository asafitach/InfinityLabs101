
typedef struct{
char *name;
int (*cmp)(char *);
int (*operation)(char*, char*);
} func;


/*
typedef enum {
    REMOVE    = 0,
    COUNT     = 1,
    EXIT      = 2,
    APPINBEG  = 3,
    APPEND    = 4,
    SUCSSES   = 5, 
    EXIT_DONE = 6,
    ERROR     = 7
} STAT;
 */

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
