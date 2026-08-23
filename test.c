#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<string.h>
#include"calculating.h"
#include"calculating.h"

#define LEN_X2 3;
#define LEN_X 1;

int delete_all_space(char* string, char* newstring)
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

bool issign(int ch)
{
	return (ch == '+' || ch == '-') ? true : false;
}

bool is_correct(char equation[])
{
	char first_char = equation[0];

	if (!(isdigit(first_char) || issign(first_char)))
	{
		return false;
	}
	return true;
} 

void parser(char equation[], int* a_ptr, int* b_ptr, int* c_ptr)
{
	char* a_str = equation; // Потому что программа разрешает строки, которые начинаются сразу с первого коэфицента => указатель на коэф а равен 0
	char* b_str = NULL; 
	char* c_str = NULL;

	int i = 0;

	char cur_char = '\0';
	while (isdigit(cur_char = equation[i]) || issign(cur_char))
	{
		printf("%c\n", cur_char);

		i++;
	} 

	i += LEN_X2;

	b_str = a_str + i + 1;

	while ((cur_char = equation[i]) != '*')
	{
		printf("%c\n", cur_char);
		
		i++;
	}

	i += LEN_X;

	c_str = a_str + i + 1;

	printf("b_str: %d, c_str: %d\n",(int) (b_str - a_str), (int) (c_str - a_str));

	// sscanf(a_str, "%d", a_ptr);
	// sscanf(b_str, "%d", b_ptr);
	// sscanf(c_str, "%d", c_ptr);

	*a_ptr = atoi(a_str);
	*b_ptr = atoi(b_str);
	*c_str = atoi(c_str);
  

}

int main()
{
	const int size_eq = 500;

	int a = 0, b = 0, c = 0;

	char equation[size_eq] = {};
	char new_equation[size_eq] = {};

	int len_eq = 0, count_spaces = 0;

	do
	{
		printf("Enter an equation (a*x^2 + b*x + c = 0): ");

		fgets(equation, size_eq, stdin);

		len_eq = strlen(equation);

		count_spaces = delete_all_space(equation, new_equation);

	} while (!is_correct(new_equation));

	printf("%s\n", equation);
	printf("%s\n", new_equation);

	parser(new_equation, &a, &b, &c);

	printf("a = %d, b = %d, c = %d\n", a, b, c);


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

