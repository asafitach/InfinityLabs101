void CopyArr( int a1[], int a2[], int sze);

int main()
{
int size =7;
int a[]={0,1,2,3,4,5,6};
int b[]={0,0,0,0,0,0,0};
CopyArr(a, b, size);
return (0);
}

void CopyArr( int a1[], int a2[], int sze)
{
	int i=0;
	for (i; i<sze;i++)
	{
	a2[i]=a1[i];
	}
return;
}
