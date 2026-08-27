#include<stdio.h>
#include<math.h>
#include<assert.h>
#include<stdlib.h>
#include<time.h>
#include<ctype.h>
#include<string.h>

#include "service.h"    //Дополнительные функции для облегчения жизни
#include "formating.h"  //Функции для форматирования выражений
#include "chatting.h"   //Функции для взаимодействия с пользователем
#include "calculating.h" //Функции для математических вычислений
#include "unit_test.h"  //Функции связанные с unit tester




const int NUM_PARAMS = 2;

const char MODE_SOLVER[] = "+s";
const char MODE_TESTER[] = "+t";
const char HID_MODE_UNIT_TESTER[] = "h+ut";





void solver();
void tester();
void unit_tester();

void unit_tester()
{
	printf("You can check if solver works correctly. \n"
		   "The result will print into a text file LOG.txt \n"
		   "Press ENTER to start checking....\n");
	getchar();

	print_log();

	char ans_open = '\0';

	do
	{
		printf("Do you wanna open LOG.txt? (y/n)");
		
		ans_open = (char) getchar();
		clear_buffer();

	}while (ans_open != 'y' && ans_open != 'n');

	if (ans_open == 'y')
	{
		#ifdef _WIN32	
			system("LOG.txt");

		#else
			printf("Sorry, we are working only in windows((((((\n");
		#endif
	}
	printf("Press ENTER to continue....\n");
	getchar();
}

void tester()
{
	srand((unsigned int) time(NULL)); //Установка разного сида рандома на каждый запуск программы
	int static score = 0;  //счет пользователя - кол-во верно подряд идущих уравнений

	bool is_wrong = false; //совершил ли пользователь ошибку

	printf("This is tester mode. You will solve quadratic equation until you make a mistake\n");
	

	while (!is_wrong) //Главный цикл генерации очередного квадратного уравнения пока пользователь не ошибется
	{
		int a = 0, b = 0, c = 0; //очередные коэфиценты
		//int* coefs[NUM_COEFS] = { &a, &b, &c }; // массив указателей на переменные где хранятся коэфиценты
		
		double  x1_user = 0,  x2_user = 0;  //Корни, которые введет пользователь
		double  x1_correct = 0, x2_correct = 0;  //Правильные значения корнкй

		coef_generate(&a, &b, &c); //генерация коэфицентов очередного уравнения и рерол если D<0 или а=0, чтобы уравнение имело корни гарантировано

		printf("Your equation is: \n");
		formating_equation((double) a, (double) b, (double) c); //вывод выражения на экран

		solve_equation((double) a, (double) b, (double) c, &x1_correct, &x2_correct); //решение этого уравнения для сверки с пользователем

		scan_user_roots(&x1_user, &x2_user); //Считывание корней, которые вычислил пользователь

		is_wrong = !check_correct_roots(x1_user, x2_user, x1_correct, x2_correct); //Проверка на правильность посчитанных корней

		print_result(is_wrong, score, x1_correct, x2_correct); //Результат очередного круга

	}

	

}

void solver() //Главная функция режима solver.
{
	double a = 0, b = 0, c = 0;   
	double  x1 = NAN,  x2 = NAN;    

	scan_coefs(&a, &b, &c); //Считывание коэфицентов с консоли

	formating_equation(a, b, c); //Вывод отформатированного выражения

	int num_roots = solve_equation(a, b, c, &x1 , &x2); // Решение уравнения

	print_answer(num_roots, x1, x2); //Вывод ответа - корней или их отсутсвие
}

bool correct_param_input(int argc, char* argv[])
{

}


int main(int argc, char* argv[])
{
	if (correct_param_input)
	{
		
	}

	if (argc != NUM_PARAMS) //Если кол-во параметров не совпадает, вернуть ошибку
	{
		correct_param_input = false;
	}

	char* input_param = argv[1];

		case SOLVER:
			print_separator();
			solver();
			print_separator();              //s - solver 
			break; 							//t - tester
											//q - выйти из программы
		case TESTER:
			print_separator();
			tester();
			print_separator();
			break;

		case UNIT_TESTER:
			print_separator();
			unit_tester();
			print_separator();
			break;

		case QUIT:
			is_over = true;
			break;
		default:
			printf("--Wrong answer, try again--\n\n");   	


			s

	print_topic();  //Вывод приветсвия и описания программы

	char mode_string[2] = "";
	bool is_over = false;


	while (!(is_over))          //Главный цикл программы
	{	
		printf("\nWhich mode do u wanna use?\n");
		printf("Solver - s \nTester - t \nUnit Tester - u \nQuit - q \n");  //Выбор режима
		printf("Enter mode: ");

		scanf("%2s", mode_string);

		char mode = (strlen(mode_string) == 1) ? mode_string[0] : '\0';
		
		clear_buffer();


	}

	printf("Good bye!");

	return 0;
}