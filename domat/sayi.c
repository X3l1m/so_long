#include <stdio.h>

int fonksiyon(void)
{
	static int i = 1;
	i++;
	return (i);
}

int main()
{
	int a;
	a = fonksiyon();
	a = fonksiyon();
	a = fonksiyon();
	
	printf("%d\n", a);
	a = fonksiyon();
	printf("%d\n", a);
}