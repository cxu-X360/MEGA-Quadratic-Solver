#include "service.h"

#include <stdio.h>
#include <math.h>
#include <float.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <cassert>

#define EPSILON pow(10, -4) //10^-4

bool equal(double a, double b) //сравнивает, равны ли две ddouble переменные. Разница меньше некоторого маленького эпсилон
{
	return fabs(a - b) < EPSILON ?  true : false; 
}

bool isnul(double a)
{
	return fabs(a) < EPSILON ? true : false; // сравнивает переменную double с 0. Равна 0 если отличается на маленькое эпсилон
}

void clear_buffer()  //очищает стандартный буффер ввода до \n включительно вызовами getchar()
{
	char _ = 0;
	while ((_ = (char) getchar()) != '\n' && _ != EOF){}
}

void print_separator() //выводит текстовый разделитель в консоль
{
	printf("-------------------------------------------------------------------\n");
}

void slow_printf(const char* format_string, ...) //посимвольно медленно выводит форматную строку, что ей передается
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

	putchar('\n');

	free(out_string);
}

int randomize(int min, int max)
{ 
	//srand((unsigned int) time(NULL));
	return (min < max) ? ((rand() % (max - min + 1)) + min) : 0;
}

void skip_line(FILE* file)
{
	const int MAX_STRING_LEN = 100; //Максимальная длина заголовка при чтении файла 

	char buff[MAX_STRING_LEN] = {};

	assert(strlen(buff) < MAX_STRING_LEN - 2);

	fgets(buff, MAX_STRING_LEN, file);

	//printf("%s", buff);
}

bool equal_str(const char* str1, const char* str2)
{

	int i = 0;

	//printf("cur_char1: %c\n cur_char2: %c\n", str1[0], str2[0]);

	while ((str1[i] != '\0') && (str2[i] != '\0'))
	{
		//printf("cur_char1: %c\n cur_char2: %c\n", str1[i], str2[i]);

		if ((str1[i] - str2[i]) != 0)
		{
			return false;
		}

		i++;
	}

	//printf("cur_char1: %c\n cur_char2: %c\n", str1[i], str2[i]);

	return str1[i] == str2[i];

}


int delete_all_space(const char* string, char* newstring) //Функция принимает строку и закидывает новую строку с удаленными пробельными символами. 
													//Возвращает кол-во удаленных пробел символов
{
	int lenght = (int) strlen(string);

	int j = 0, count = 0;

	for (int i = 0; i < lenght; i++)
	{
		if (isspace(string[i]))
		{
			count++;

			continue;
		}

		newstring[j] = string[i];

		j++; 
	}
	newstring[j] = '\0';

	return count;
}

int count_symbols(const char* string, char symbol) //Принимает строку и возвращает кол-во указанных симсволов в ней
{
	int count = 0;
	int lenght = (int) strlen(string);

	for (int i = 0; i < lenght; i++)
	{
		if (string[i] == symbol)
		{
			count++;
		}
	}

	return count;
}

int count_alpha(const char* string) //Принимает строку и возвращает кол-во символов, входящих в ASCII как буква алфавита
{
	int count = 0;
	int lenght = (int) strlen(string);

	for (int i = 0; i < lenght; i++)
	{
		if (isalpha(string[i]))
		{
			count++;
		}
	}

	return count;
}

bool issign(int ch) // Проверяет символ, является ли он плюсом или минусом
{
	return (ch == '+' || ch == '-') ? true : false;
}


// void print_arc_arv(int argc, char* argv[])
// {
// 	printf("%d\n", argc);

// 	for (int i = 0; i < argc; i++)
// 	{
// 		printf("%s\n", argv[0]);
// 	}
// }



// int delete_all(char* string, char delete_char, char* newstring)
// {
// 	int lenght = strlen(string);

// 	char newstring[lenght + 1];

// 	int j = 0, count = 0;

// 	for (int i = 0; i < lenght; i++)
// 	{
// 		char current_char = string[i];

// 		if (isspace(current_char))
// 		{
// 			count++;

// 			continue;
// 		}

// 		newstring[j] = string[i]

// 		j++; 
// 	}
// 	return count;
// }

