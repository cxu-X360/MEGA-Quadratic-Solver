#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <windows.h>
#include <string.h>

#define print(...) printf(__VA_ARGS__)

int count_symbols(const char* string, char symbol) //Принимает строку и возвращает кол-во указанных симсволов в ней
{
	int count = 0;
	int lenght = strlen(string);

	for (int i = 0; i < lenght; i++)
	{
		if (string[i] == symbol)
		{
			count++;
		}
	}

	return count;
}

const int MAX_OUT_STRING_LEN = 500;

void slow_printf(const char* format_string, ...) //посимвольно медленно выводит строку, что ей передается со скоростью в 
{
	va_list  arg_ptr;
	va_start(arg_ptr, format_string);

	char* out_string = (char* ) calloc(strlen(format_string) + count_symbols(format_string, '%') * 100, sizeof(char));

	vsprintf(out_string, format_string, arg_ptr);

	int i = 0;

	while (out_string[i] != '\0')
	{
		printf("%c", out_string[i]);

		Sleep(50);

		i++;
	}

	free(out_string);
}

int main(int argc, char *argv[])
{
	slow_printf("HELLO WORLD, MENYA ZOVUT INUK %d %f %d", 100, 1.0, 1);
}