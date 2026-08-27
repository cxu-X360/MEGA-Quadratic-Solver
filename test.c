#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#include"calculating.h"
#include"calculating.h"

#define LEN_SQUARE_X 3
#define LEN_LINIAR_X 1
#define MAX_LEN_COEF 100

const int POISON = -1;

int delete_all_space(char* string, char* newstring) //Функция принимает строку и закидывает новую строку с удаленными пробельными символами. 
													//Возвращает кол-во удаленных пробел символов
{
	int lenght = strlen(string);

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

int count_symbols(char* string, char symbol) //Принимает строку и возвращает кол-во указанных симсволов в ней
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

int count_alpha(char* string) //Принимает строку и возвращает кол-во символов, входящих в ASCII как буква алфавита
{
	int count = 0;
	int lenght = strlen(string);

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


bool is_correct(char equation[])// Проверяет выражение на корректность (если первым символом является + , - или цифра)
{
	char first_char = equation[0];

	if (!(isdigit(first_char) || issign(first_char)))
	{
		return false;
	}
	return true;
} 

double coef_to_double(char* coef_str, bool have_begin_sign) //Переводит коэфицент из строкового вида в числовой. Если невозможно, возвращает nan
{
	assert(strlen(coef_str) < MAX_LEN_COEF);

	int sign = 0;

	int lenght = strlen(coef_str);
	//printf("len = %d\n", lenght);

	bool is_star_in_end = (coef_str[lenght - 1] == '*');

	if (have_begin_sign)  
	{
		if (!issign(coef_str[0])) //Если первый символ не знак, то ошибка
		{
			return NAN;	
		}                           
	}
	//printf("coef: %s\n", coef_str);
	
	for (int i = have_begin_sign ? 1 : 0; i < ((is_star_in_end) ? (lenght - 1) : lenght); i++) //Проверка всех символов в строке коэфицента кроме первого (для знака и последнего для возможного знака *)
	{

		//printf("		char_%d: %c,   is_dig = %d\n", i, coef_str[i], isdigit(coef_str[i]));
		if (!isdigit(coef_str[i]) && coef_str[i] != '.')
		{
			//printf("		char_%d: %c\n", i, coef_str[i]);	
			return NAN;
		}
	}

	return strtod(coef_str, NULL);
}


bool parser_v2(char equation[], double* a_ptr, double* b_ptr, double* c_ptr) // --//--//--
{
	char cur_char = '\0';

	int i = 0;

	char* start_ptr = equation; //указатель на начало строки
	char* square_x_ptr = NULL;  //указатель переменной, что входит со степенью 2
	char* lin_x_ptr = NULL;     //указатель переменной, что входит со степенью 1

	if (count_symbols(equation, '.') >  3)
	{
		return false;
	}

	if (count_alpha(equation) != 2) //проверка на кол-во букв, иначе стопаем парсер
	{
		return false;
	}

	while (!isalpha(cur_char = equation[i])) //Ищем первое вхождение буквы(то бишь перменной) и отделяем квадратичный коэф
	{	
		printf("%c\n", cur_char);

		i ++;
	}

	char variable = cur_char;  //хранит имя переменной используемой в выражении

	square_x_ptr = &equation[i];

	if (equation[square_x_ptr - start_ptr + 1] != '^' || equation[square_x_ptr - start_ptr + 2] != '2') //Проверка на корректное введение степени "x^2"
	{
		return false;
	}

	i += LEN_SQUARE_X;  //длина выражение "x^2"

	while ((cur_char = equation[i]) != variable) //Ищем след вхождение переменной и отделяем линейный коэф
	{
		printf("%c\n", cur_char);

		i++;
	}

	lin_x_ptr = &equation[i];

	i+=LEN_LINIAR_X;
	
 	char a_str[MAX_LEN_COEF] = {};
 	char b_str[MAX_LEN_COEF] = {}; //Инициилизация строк, в которых хранятся коэфиценты
 	char c_str[MAX_LEN_COEF] = {};

 	strncpy(a_str, start_ptr, square_x_ptr - start_ptr);
 	strncpy(b_str, square_x_ptr + LEN_SQUARE_X, lin_x_ptr - square_x_ptr - LEN_SQUARE_X); //Копирование значения коэфицентов в соотв строки с помощью указателей на переменную в выражении в степенях 1 и 2
 	strncpy(c_str, lin_x_ptr + LEN_LINIAR_X, strlen(equation) - (lin_x_ptr - start_ptr) - 3);

 	//printf("a_str: %s, b-Str: %s, c_str: %s\n", a_str, b_str, c_str);

 	*a_ptr = coef_to_double(a_str, equation[0] == '-');
 	*b_ptr = coef_to_double(b_str, true); //Перевод строк в вещественные числа
 	*c_ptr = coef_to_double(c_str, true);

 	printf("a: %lg, b: %lg, c: %lg\n", *a_ptr, *b_ptr, *c_ptr);

 	return true;

}

int main()
{
	const int size_eq = 500; //Максимальный размер выражения

	double a = 0, b = 0, c = 0;

	char equation[size_eq] = {};
	char new_equation[size_eq] = {};

	int len_eq = 0, count_spaces = 0;

	do //Ввод выражения и удаления в нем пробелов, пока он не окажется правильным
	{
		printf("Enter an equation (a*x^2 + b*x + c = 0 ): ");

		fgets(equation, size_eq, stdin);

		len_eq = strlen(equation);  

		count_spaces = delete_all_space(equation, new_equation);

	} while (!is_correct(new_equation));

	printf("%s\n", equation);
	printf("%s\n", new_equation);

	if (!parser_v2(new_equation, &a, &b, &c)) //Зафейлить подсчет если если неверно спарсился ввод	
	{
			printf("FAIL");
	}
	else
	{
		printf("a = %lg, b = %lg, c = %lg\n", a, b, c);	
	}
	

}

// if (mode == HARD)
// 		{
			
// 			double real1 = 0, real2 = 0, imag1 = 0, imag2 = 0;
// 			char sign, i_char;

// 			printf("x1: ");
// 			int num_inputs1 = scanf("%f.2 %c %f.2 %c", &real1, &sign, &imag1, &i_char);

// 			if (num_inputs1 == 4 && (sign == '+' || sign == '-') && i_char == 'i')
// 			{
// 				if (sign == '-')
// 				{
// 					imag1 *= -1;
// 				}
// 				x1_user = cmplx(real1,imag1);
// 			}

// 			printf("x2: ");
// 			int num_inputs2 = scanf("%f.2 %c %f.2 %c", &real2, &sign, &imag2, &i_char);

// 			if (num_inputs2 == 4 && (sign == '+' || sign == '-') && i_char == 'i')
// 			{
// 				if (sign == '-')
// 				{
// 					imag1 *= -1;
// 				}
// 				x2_user = cmplx(real2, imag2);
// 			}
// 		}

