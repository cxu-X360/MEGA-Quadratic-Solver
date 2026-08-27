#include<stdio.h>

#define print(...) printf(__VA_ARGS__)


int main(int argc, char *argv[])
{
	printf("argc: %d\n", argc);
	
	for (int i = 0; i < argc; i++)
	{
		printf("argv[%d]: %s\n", i, argv[i]);
	}
}