
/*
struct func
{
char name[10];
int *(ptr_cmp)(char *);
int *(ptr)(FILE*, char*);
} func;
*/


enum STAT {
    FAILED   = 0,
    REMOVE   = 1,
    COUNT    = 2,
    APPINBEG = 3,
    EXIT     = 4,
    APPINEND = 5
};

int CountFile (char *file_name, char *str);
int Append(char *name_of_file, char *str);
int RemoveFile( char *file_name,  char *str);
int Exit (char *file_name,  char *str);
int AppendInBegining(char *file_name, char *str);

/****COMPARITION FUNCTIONS****/
int RemCmp(char *str);
int CountCmp(char *str);
int ExitCmp(char *str);
int AppLastCmp(char *str);
int AppFirstCmp(char *str);



/*FILE *CopyFile(FILE *f_tmp_ptr, FILE *f_ptr);
FILE *OpenFile (char *file_name, char* opt);*/
