#include<stdio.h>


int minus_of_int(int x)
{
	return -x;
}

int main()
{
	int a = 0;

	scanf("%d", &a);

	printf("%d\n", minus_of_int(a));
	
	return 0;
}