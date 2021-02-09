
int main()
{
static int s_1=7;
int i =7;
int *ptr =&i;
int *ptr2=(int*)malloc(sizeof(int));
printf ("%p,%p,%p, %p", ptr, ptr2, &ptr, &ptr2);
if(ptr)
{
&ptr;
}
free(ptr2);
