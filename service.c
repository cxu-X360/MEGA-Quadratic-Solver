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

void slow_print(char *s) //посимвольно медленно выводит строку, что ей передается со скоростью в 
{
	int i = 0;
	while (s[i] != '\0'){
		printf("%c", s[i]);
		Sleep(20);
		i++;
	}
}

int randomize(int min, int max)
{ 
	srand((unsigned int) time(NULL));
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

bool equal_str(char* str1, char* str2)
{
	char cur_char1 = cur_char2 = '\0';

	int i = 0;

	while (((cur_char1 = str1[i]) != '\0') && ((cur_char2 = str2[i]) != '\0'))
	{
		if ((cur_char1 - cur_char2) != 0)
		{
			return false;
		}

	}
	return true;

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

