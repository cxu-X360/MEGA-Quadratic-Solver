#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <assert.h>


#include "service.h"
#include "calculating.h"
#include "chatting.h"


#define nan NAN



const int int_poison = -2;
 
const int NUM_TESTS = 100; //Кол-во тестов - приходится использовать #define

const int MAX_RAND = 10; //Максимальное значение генерации чисел
const int MIN_RAND = -10; //Максимальное значение генерации чисел


const char std_tests_filename[] = "STD_TESTS.txt";
const char tests_filename[] = "TESTS.txt";       //Имена файлов
const char log_filename[] = "LOG.txt";




typedef struct  // Структура, являющаяся тестом.
{
	double a, b, c; //Хранит коэфиценты квадратного уравнения

	double x1, x2; //И сами корни (В случае D<0 Дейст и Мним часть пары сопряженных корней)

	int num_roots; // Кол-во корней


} TestData;

void copy_test(TestData test_src, TestData *test_dest_ptr) //Функция копирования данных их одной структуры(src) TestData в другую (dest)
{
	test_dest_ptr->a = test_src.a;
	test_dest_ptr->b = test_src.b;
	test_dest_ptr->c = test_src.c;

	test_dest_ptr->x1 = test_src.x1;
	test_dest_ptr->x2 = test_src.x2;

	test_dest_ptr->num_roots = test_src.num_roots;

}

void fprint_test(FILE* file, TestData test) //выводит в поток file структуру TestData
{
	fprintf(file, "%8lg %8lg %8.8lg %8.5lg %8.5lg %9d\n", test.a, test.b, test.c, test.x1, test.x2, test.num_roots);
}

int fscan_test(FILE* file, TestData* test_ptr) //считывает из потока file структуру TestData
{
	return fscanf(file, "%lg %lg %lg %lg %lg %d\n", &test_ptr->a, &test_ptr->b, &test_ptr->c, &test_ptr->x1, &test_ptr->x2, &test_ptr->num_roots);
}

void linear_generation(TestData* test_ptr) // генерация тестов в линейном случае (когда а = 0)
{		// (*test).b  =>  test->b

	test_ptr->b = (double) randomize(MIN_RAND, MAX_RAND); //Генерация коэф B и С
	test_ptr->c = (double) randomize(MIN_RAND, MAX_RAND);

	if (isnul(test_ptr->b)) //Если B = 0, то корней или нет или беск, в зависмости от С
	{
		test_ptr->x1 = test_ptr->x2 = NAN;
		
		test_ptr->num_roots = (isnul(test_ptr->c)) ? INF_ROOTS : NO_ROOT; 
	}

	else
	{
		test_ptr->x1 = test_ptr->x2 = isnul(test_ptr->c) ? 0 : -test_ptr->b / test_ptr->c; //Если В != 0, то корень 1 (0 если С = 0 или -B/c иначе)

		test_ptr->num_roots = ONE_ROOT;	
	}

}

void viete_generation(TestData* test_ptr) //генерация тестов в квадратичном случае (когда а != 0) и D >= 0, с помощью теоремы Виета
{
	test_ptr->x1 = (double) randomize(MIN_RAND, MAX_RAND); //Генерация корней
	test_ptr->x2 = (double) randomize(MIN_RAND, MAX_RAND); 

	test_ptr->b = -test_ptr->a * (test_ptr->x1 + test_ptr->x2); //минус Сумма корней * а это коэф B
	test_ptr->c = test_ptr->a * (test_ptr->x1 * test_ptr->x2); //Произведение корней * а это коэф С

	test_ptr->num_roots = TWO_ROOTS;
}

void cmplx_roots_to_coefs(int real, int imag,  double a, double* b_ptr, double* c_ptr) // преобразование комплесных корней в коэфиценты квадратного уравнения
{
	*b_ptr = (double) (-2 * real);

	int D = -1 * (2 * imag) * (2 * imag);

	*c_ptr = (double) ((*b_ptr * *b_ptr - D) / (4 * a));


}

void complex_generation(TestData* test_ptr) //генерация тестов в квадратичном случае (когда а != 0) и D < 0, c помощью комплексных чисел
{
	int real = randomize(MIN_RAND, MAX_RAND);

	int imag = int_poison;

	do 
	{
		imag = randomize(MIN_RAND, MAX_RAND); 

	}while (imag <= 0); //Мы хотим комплексные корни, поэтому мнимая часть != 0

	test_ptr->x1 = (double) real;
	test_ptr->x2 = (double) imag; 

	cmplx_roots_to_coefs(real, imag, test_ptr->a, &test_ptr->b, &test_ptr->c); //Вычисление коэфицентов по комплексным корням
}

void quadratic_generation(TestData* test_ptr) // генерация тестов в квадратичном случае 
{
	bool have_roots = randomize(0, 1); //Решаем, будут ли  у теста действ корни
	printf("%d\n", have_roots);

	if (have_roots)
	{
		viete_generation(test_ptr); //Если есть, то генерируем с коэф b and c и считаем корни с помощью теоремы Виета
	}
	else
	{
		complex_generation(test_ptr); //Если нет, то генериуем действ и мним часть корней и по ним считаем коэф
		//printf("3) b: %lg, c: %lg, x1: %lg, x2: %lg\n", test_ptr->b, test_ptr->c);
	}
}

void generate_tests(FILE* tests_f, int num_tests, bool is_zero_a) // генерирует указанное кол-во тестов и записывает их в файл tests_f, можно указать генерить ли коэф а = 0
{
	srand((unsigned int) time(NULL)); //Установка рандомного сида

	tests_f = freopen(tests_filename, "a", tests_f);

	TestData correct_test = {.a = is_zero_a ? 0 : (double) randomize(MIN_RAND, MAX_RAND), .b = 0, .c = 0, .x1 = nan, .x2 = nan, .num_roots = int_poison};

	for(int i = 0; i < num_tests; i++) //Генерация рандомных тестов в цикле
	{
		if (is_zero_a)
		{
			linear_generation(&correct_test); //Генерация тестов в случае линейного уравнения
		}
		else
		{
			quadratic_generation(&correct_test); //Генерация тестов в случае линейного уравнения
		} 
		                                                               
		fprint_test(tests_f, correct_test); //Вывод тестов в файл
	}
}

void add_std_tests(FILE* std_tests_f, FILE*  tests_f) // записывает стандартные (частные случаи, указываемые от руки) тесты из файла std_tests_f в tests_f
{

	tests_f = freopen(tests_filename, "a", tests_f);

	TestData std_test = {.a = 0, .b = 0, .c = 0, .x1 = nan, .x2 = nan, .num_roots = int_poison};


	while (fscan_test(std_tests_f, &std_test) != 0) //Считывание стандартных тестов из файла
	{
		fprint_test(tests_f, std_test);
	}
}

bool check_result(TestData correct_test, TestData user_test) //Проверяет, совпадает ли тест, вычисленный функцией solve_eq() с эталонным тестом
{
	bool is_correct1 = equal(user_test.x1, correct_test.x1) || equal(user_test.x1, correct_test.x2); //Сравнение первого сгенирированного корня с двумя эталонными
	bool is_correct2 = equal(user_test.x2, correct_test.x1) || equal(user_test.x2, correct_test.x2); //Сравнение первого сгенирированного корня с двумя эталонными

	bool is_num_correct = user_test.num_roots == correct_test.num_roots; //сравнение кол-ва корней

	if (isnan(correct_test.x1) && isnan(correct_test.x2)) //При отсутсвии корней или при их беск. кол-ве сами корни - nan. Проверяем кол-во корней
	{
		return is_num_correct;
	}
	else //Иначе сами корни
	{
		return is_correct1 && is_correct2;
	}
}



void check_tests(TestData* tests_correct_array, TestData* tests_user_array, bool* results_array) // Вычисляет по коэфицентам из эталонных тестов (находящихся в массиве), 
{				// Корни с помощью функции solve_eq() и заносит их в массив

	TestData user_test = {.a = 0, .b = 0, .c = 0, .x1 = nan, .x2 = nan, .num_roots = int_poison};
	TestData correct_test = {.a = 0, .b = 0, .c = 0, .x1 = 0, .x2 = 0, .num_roots = int_poison};

	for (int i = 0; i < NUM_TESTS; i++)
	{
		assert(i < 2*NUM_TESTS);

		copy_test(tests_correct_array[i], &correct_test);

		user_test.a = correct_test.a;
		user_test.b = correct_test.b;
		user_test.c = correct_test.c;

		user_test.num_roots = solve_equation(correct_test.a, correct_test.b, correct_test.c, &user_test.x1, &user_test.x2); //Вычисление собственных корней


		results_array[i] = check_result(correct_test, user_test); //Занесение в массив информации о результате тестирования

		copy_test(user_test, &(tests_user_array[i]) ); //Копирование посчитанного теста в массив
	}
}

void make_tests_file(FILE* std_tests_f, FILE* tests_f) //Создает файл, в котором хранятся эталонные тесты
{
	
	fprintf(tests_f, "          a       b        c     x1   x2  num_roots\n");

    add_std_tests(std_tests_f, tests_f);

	generate_tests(tests_f, NUM_TESTS / 2, false); //Генерация NUM_TESTS/2 = 100/2 = 50 тестов с a != 0
	generate_tests(tests_f, NUM_TESTS / 2, true); //Генерация NUM_TESTS/2 = 100/2 = 50 тестов с a = 0

}

void make_log_file(TestData* tests_correct_array, TestData* tests_user_array, bool* results_array, FILE* log_f) //создает файл, информирующий о верности выполнения функции solve_eq()
{																												//хранятся эталонные тесты, вычисленные тесты и результат(совпадает или нет)
	fprintf(log_f, "NUM                       a        b        c      x1       x2  num_roots\n");

	for (int i = 0; i < NUM_TESTS; i++)
	{
		assert(i < NUM_TESTS);

		printf("i = %d\n", i);
		fprintf(log_f, "%02d  ", i);

		fprintf(log_f, "Correct values: ");
		fprint_test(log_f, tests_correct_array[i]);
 	
		fprintf(log_f, "   Calc values:    ");
		fprint_test(log_f, tests_user_array[i]);

		fprintf(log_f, "   Result: %s\n\n", results_array[i] ? "Correct" : "-------FAILED!!!!!------");

		//assert(!results_array[i]);
	}
}

void init_tests(FILE* tests_f, TestData* tests_correct_array) //Записывает из файла tests_f эталонные тесты в массив
{
	tests_f = freopen(tests_filename, "r", tests_f);//Переоткртие файла с использованием режима r

	int num_scans = 0;

	TestData test = {.a = 0, .b = 0, .c = 0, .x1 = 0, .x2 = 0, .num_roots = int_poison};

	skip_line(tests_f); // Пропуск строки при считывании

	int i = 0;
	//printf("Condition to while in init: %d\n", (num_scans = fscan_test(tests_f, &test)) > 0);

	while ((num_scans = fscan_test(tests_f, &test)) > 0) //Считывание структуры из файла
	{
		assert(i < 2*NUM_TESTS);

		printf("cor_test in init_tests: ");
		fprint_test(stdout, test);
		copy_test(test, &(tests_correct_array[i])); //Копирование сочтенный из файла структуры в массив

		i++;
	}
}

void print_log() //Главная функция unit_tester(). Открыввет и закрывает все файлы, инициилизирует массивы с тестами
{
	TestData tests_correct_array[2 * NUM_TESTS] = {}; 
	TestData tests_user_array[2 * NUM_TESTS] = {};    //Инициилизация массивов данных
	bool results_array[2 * NUM_TESTS] = {};

	FILE* tests_f = fopen(tests_filename, "w");
	FILE* std_tests_f = fopen(std_tests_filename, "r");  //Открытие всех нужных файлов
	FILE* log_f = fopen(log_filename, "w");

	make_tests_file(std_tests_f, tests_f);   //Создание файла с эталонными тестами

	init_tests(tests_f, tests_correct_array);  //Копирование эталонных тестов из файла в массив

	check_tests(tests_correct_array, tests_user_array, results_array); //Проверка функции решение уравнений на эталонных тестах

		fprint_test(stdout, tests_correct_array[2]);
		fprint_test(stdout, tests_user_array[2]);

	make_log_file(tests_correct_array, tests_user_array, results_array, log_f); //СОздание файла с инфой о результатах тестирования

	fclose(tests_f);
	fclose(std_tests_f); //Закрытие файлов
	fclose(log_f);

}