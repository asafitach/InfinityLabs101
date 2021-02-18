/******************************* reviwed bu Eden *****************************/

#ifndef __EX2_H__
#define __EX2_H__

typedef struct{
char *name;
int (*cmp)(char *);
int (*operation)(char*, char*);
} func;



typedef enum {
    SUCCSESS   = 0, 
    EXIT_DONE  = 3,
    ERROR      = 2
} STAT;
 

int Comparition(char *file_name,char *str, func *arr);
int RemoveFile( char *file_name,  char *str);
int CountFile (char *file_name, char *str);
int Exit (char *file_name,  char *str);
int AppendInBeginning(char *file_name, char *str);
int Append(char *name_of_file, char *str);


/****COMPARITION FUNCTIONS****/
int RemCmp(char *str);
int CountCmp(char *str);
int ExitCmp(char *str);
int AppLastCmp(char *str);
int AppFirstCmp(char *str);

#endif /* __EX2_H__ */

