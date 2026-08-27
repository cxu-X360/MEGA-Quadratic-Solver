#include "calculating.h"
#include "service.h"
#include "formating.h"
#include "chatting.h"

#include<stdio.h>
#include<math.h>
#include<assert.h>
#include<complex.h>


double calc_discriminant(double a, double b, double c)  //Вычисление дискриминанта по коэфицентам квадратного уравнения
{
 	double D = b * b - 4 * a * c;

 	return D;
}

int linear_equation(double b, double c, double  *x1_ptr, double  *x2_ptr)  //Вычисление корней  при сведение к линейному уравнению (а=0)
{
		if (isnul(b)) // Если и коэфицент b равен 0, остается константное уравнение
		{
			if (isnul(c)) //Если с = 0, то уравнение сводится к 0=0 и любой х подходит
			{
				*x1_ptr = NAN;
				*x2_ptr = NAN;
				return INF_ROOTS;
			}

			else
			{
				*x1_ptr = NAN;
				*x2_ptr = NAN;
				return NO_ROOT; //Если с != 0, то уравение не имеет корней
			}
				
		}

		else //b!=0 уравнеие линейное и решением является -b/c - 1 корень
		{ 
			*x2_ptr = *x1_ptr = ((!isnul(c)) ? -b / c : 0); //Если с = 0 то делить нельзя и ур-ние сводится к bx=0 и есть 1 корень = 0
			return ONE_ROOT;
		}
}

int quadratic_equation(double a, double b, double c, double  *x1_ptr, double  *x2_ptr) //Вычисление корней если уравнение осается квадраныём (a!=0)
{
	double D = calc_discriminant(a, b, c);
	printf("D = %g\n", D);

	if (D < 0)//Если дискриминант меньше 0, то имеются только 2 комплексных сопряженых корня. (x + iy) и (x - iy)
	{  
		double real = -b / 2;

		double imag = sqrt(-D) / 2;

		*x1_ptr = real;                      //В качестве 1 корня возвращается действ часть обоих корней х
		*x2_ptr = imag;   					 //В качестве 2 корня возвращается модуль мнимой части y

		return TWO_COMPLEX_ROOTS;
	}
	
	else //D>=0 Имеются только действ корни
	{	
		*x1_ptr = (-b + sqrt(D)) / (2 * a); 
		*x2_ptr = (-b / a) - *x1_ptr;    //Вычисление второго корня по теореме Виета

		if ( equal(*x1_ptr, *x2_ptr) )   //Если корни совпадают, то имеется только одно решение
		{
			return ONE_ROOT;
		}

		else //Если корни не совпадают, то имеется 2 решения
		{
			return TWO_ROOTS;
		}
	}
}

int solve_equation(double a, double b, double c, double  *x1_ptr, double  *x2_ptr) //Комбинирует линейный и квадратичный случай. Возращает кол-во корней
{
	assert(x1_ptr != NULL);
	assert(x2_ptr != NULL);
	assert(x2_ptr != x1_ptr);

	if (isnul(a)) //Если а=0, то линейный случай
	{
		return linear_equation(b, c, x1_ptr, x2_ptr);
	}

	else //Если a!=0 обычный квадратичный случай
	{
		return quadratic_equation(a, b, c, x1_ptr, x2_ptr);
	}
}

void randomize_coefs(int min, int max, /*int count, */ int* a_ptr, int* b_ptr, int* c_ptr) //принимает максимальное и минимальное значение рандома, 
														  //кол-во переменных и массив из указателей на переменные, куда кладется рандомное значение 
{
	for (int i = 0; i < 3; i++)
	{
		*a_ptr = randomize(min, max);
		*b_ptr = randomize(min, max);
		*c_ptr = randomize(min, max);
	}
}

void coef_generate(int *a_ptr, int *b_ptr, int *c_ptr)
{
	// int a = *(numbers[0]);
	// int b = *(numbers[1]);
	// int c = *(numbers[2]);

	#define MAX_RAND 10
	#define MIN_RAND -10


	double D = 0;

	do //Рерол сгенерированных коэфицентов, 
	{	
		randomize_coefs(MIN_RAND, MAX_RAND, a_ptr, b_ptr, c_ptr); //Генеритрует рандомные коэфиценты

		D = calc_discriminant((double) *a_ptr, (double) *b_ptr, (double) *c_ptr);
		//printf("%d %d %d %g", a_ptr, b_ptr, c_ptr, D);

	} while ((D < 0) || (*a_ptr == 0)); 

	#undef MAX_RAND
	#undef MIN_RAND
}

bool check_correct_roots(double x1_user, double x2_user, double x1_correct, double x2_correct)
{
	bool is_cor1 = (fabs(x1_user - x1_correct) < 0.02) || (fabs(x1_user - x2_correct) < 0.02) ;
	bool is_cor2 = (fabs(x2_user - x2_correct) < 0.02) || (fabs(x2_user - x1_correct) < 0.02);

	// printf("user1: %g, user2: %g, cor1: %g, cor2: %g", x1_user, x2_user, x1_correct, x2_correct);

	// printf("%lg - %lg", fabs(x1_user - x1_correct), fabs(x1_user - x2_correct));

	return (is_cor1 && is_cor2) ? true : false;
}




