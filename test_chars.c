#include<stdio.h>

typedef struct 
{
	int a, b, c;

} Type;

void f(Type* strct_ptr)
{
	strct_ptr->a *= 2;
}

int main()
{
	Type strct1 = {.a = 1, .b = 2, .c = 3};

	f(&strct1);

	printf("a = %d b = %d c = %d\n", strct1.a, strct1.b, strct1.c);

}