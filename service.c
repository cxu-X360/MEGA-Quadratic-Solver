#include "service.h"

#include<stdio.h>
#include<math.h>
#include<float.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>

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
	while ((_ = getchar()) != '\n' && _ != EOF){}
}

void print_separator() //выводит текстовый разделитель в консоль
{
	printf("-------------------------------------------------------------------\n");
}

void slow_print(char *s) //посимвольно медленно выводит строку, что ей передается
{
	int i = 0;
	while (s[i] != '\0'){
		printf("%c", s[i]);
		Sleep(20);
		i++;
	}
}

int randomize(int min, int max)
{ // __TIME__  randseed(__TIME__)
	return (min < max) ? ((rand() % (max - min + 1)) + min) : 0;
}

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

