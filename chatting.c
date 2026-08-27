#include "chatting.h"
#include "service.h"
#include "formating.h"
#include "calculating.h"

#include<stdio.h>
#include<assert.h>
#include<math.h>




// ГЛАВНОЕ
//----------------------------------------------------------------------------------------------------------------------------------------------------------
void print_topic() //Вывод приветсвия и описания программы
{
	printf("_________________________MEGA QUADRATIC SOLVER_________________________\n"
		   "                                 (v.2.0)                               \n"
		   "\n"
		   "YOU need to input three coeficents of a quadratic_equation, and this   \n"        //Приветсвенное сообщение пользователю
		   "programm will calculate its roots  8) 8) 0_0                           \n"
		   "WE added new mode - quadratic tester!!!!                               \n"
		   "Press ENTER to start . . .                                             \n");
	getchar();
}


//----------------------------------------------------------------------------------------------------------------------------------------------------------






//SOLVER
//----------------------------------------------------------------------------------------------------------------------------------------------------------
void scan_coefs(double* a_ptr, double* b_ptr, double* c_ptr) //Считывание коэфицентов с консоли
{
	assert(a_ptr != NULL);
	assert(c_ptr != NULL);  //Проверка на отсутсвие указателей на переменные
	assert(b_ptr != NULL);


	printf("Enter three cof of quadradic equation ax^2 + bx + c = 0, please\n");

	int num_inputs = 0;

	//Ввод Коэфицентов. В циклах пока пользователь не введет число
	do 
	{
		printf("a: ");   //Коэфицент а при х^2
		num_inputs = scanf("%lf", a_ptr); 
		clear_buffer();
	} while (num_inputs == 0); //Если scanf считал число то прекращаем цикл

	do
	{
		printf("b: ");   //Коэфицент b при х
		num_inputs = scanf("%lf", b_ptr);
		clear_buffer();
	} while (num_inputs == 0);

	do
	{
		printf("c: ");   //Коэфицент c - свободный член
		num_inputs = scanf("%lf", c_ptr);
		clear_buffer();
	} while (num_inputs == 0);
}

void print_answer(int num_roots, double  x1, double  x2) //Вывод ответа - корней или их отсутсвие
{
	switch(num_roots) //Получили кол-во корней и проверяем чему оно равно
	{
		case NO_ROOT:
			printf("You have no roots\n"); 
			break;

		case ONE_ROOT:
			printf("You have one root x = %g\n", crealf(x1));
			break;

		case TWO_ROOTS: 
			printf("You have two roots:\n x1 = %g\n x2 = %g\n", crealf(x1), crealf(x2)); 
			break;

		case TWO_COMPLEX_ROOTS:
			#define real x1
			#define imag x2

			printf("You have two complex roots:\n x1 = %g%+gi\n x2 = %g%+gi\n", real, imag, real, -imag); //Вывод комплексных корней

			#undef real
			#undef imag
			break;


		case INF_ROOTS: 
			printf("Any number can be a root\n");
			break;

		default:
			printf("None information abou roots error!!\n");
			
	}
}
//----------------------------------------------------------------------------------------------------------------------------------------------------------


//TESTER
//----------------------------------------------------------------------------------------------------------------------------------------------------------
void scan_user_roots(double* x1_user, double* x2_user)
{
	printf("Please enter roots of this equation up to the 2 signs after point: \n");

	printf("x1: ");
	scanf("%lf.2", x1_user);

	printf("x2: ");
	scanf("%lf.2", x2_user);

	clear_buffer();

}

void print_result(bool is_wrong, int score, double x1_correct, double x2_correct)
{
	if (is_wrong)
	{
		printf("You are wrong. The correct answer is x1 = %.2lf and x2 = %.2lf\n", 
				x1_correct, x2_correct);
		printf("Your score is %d\n", score);
	}
	else
	{
		score++;
		printf("You are right! Your score now is %d\n\n", score);	
	}

}
//----------------------------------------------------------------------------------------------------------------------------------------------------------