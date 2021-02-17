#ifndef __EX1_H__
#define __EX1_H__

struct print_me
{
	int var;
	void(*ptr)(int);
}print_me;



void Init(struct print_me *array,int size);
void Print(int num);


#endif /* __EX1_H__ */
