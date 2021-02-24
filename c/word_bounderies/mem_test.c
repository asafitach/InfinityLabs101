/*****************        Reviewed by Fei       **************************/
#include <stdio.h>
#include <string.h>
#include "mem.h"

int main()
{
	char src1[] = "welcome!! way more space just dont say :SIGABRT";
	char src2[] = "welcome!! way more space just dont say :SIGABRT";
	char *ptr = src1;

	printf("This is before, after MemSet:\n %s\n",ptr);		
	ptr = (char*)MemSet(ptr, 's', 5 * WORD);
	printf("%s\n\n\n",ptr);
	
	ptr = (char*)MemCpy(ptr, src2, 20);
	printf("Try to bring it back-> ->\n%s\n\n\n",ptr);

	
	strcpy(src1, src2);
	printf("(left overloop)\n"
	"This is before, MemCpy,memcpy, MemMove, memmove:\n%s\n",src1);		
	ptr = (char*)MemCpy(src1 ,src1 + WORD, 15);
	printf("%s\n", ptr);
	strcpy(src1, src2);		
	printf("%s\n",(char*)memcpy(src1, src1 +WORD, 15)) ;
	strcpy(src1, src2);		
	ptr = (char*)MemMove(src1, src1 +WORD, 15);
	printf("%s\n", ptr);
	strcpy(src1, src2);
	ptr = (char*)memmove(src1, src1 +WORD, 15);
	printf("%s\n\n", ptr);


	strcpy(src1, src2);
	printf("(right overloop)\n"
	"This is before, MemCpy, memcpy, MemMove, memmove:\n%s\n",src1);		
	ptr = (char*)MemCpy(src1 + WORD, src1, 15);
	printf("%s\n", ptr);
	strcpy(src1, src2);		
	printf("%s\n",(char*)memcpy(src1 +WORD, src1, 15));
	strcpy(src1, src2);		
	ptr = (char*)MemMove(src1 +WORD, src1, 15);
	printf("%s\n", ptr);
	strcpy(src1, src2);
	ptr = (char*)memmove(src1 +WORD, src1, 15);
	printf("%s\n\n", ptr);

	return 0;
}
	


