#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>

#include "service.h"
#include "calculating.h"
#include "chatting.h"


#define MAX_RAND 10
#define MIN_RAND -10
#define nan NAN

#define int_poison -2


const char std_tests_filename[] = "STD_TESTS.txt";
const char tests_filename[] = "TESTS.txt";
const char log_filename[] = "LOG.txt";


typedef struct 
{
	double a, b, c;

	int num_roots;

	double x1, x2;

} TestData;



void fprint_test(FILE* file, TestData test)
{
	fprintf(file, "%8lg %8lg %8.8lg %8.5lg %8.5lg %9d\n", test.a, test.b, test.c, test.x1, test.x2, test.num_roots);
}

int fscan_test(FILE* file, TestData* test_ptr)
{
	return fscanf(file, "%lg %lg %lg %lg %lg %d\n", &test_ptr->a, &test_ptr->b, &test_ptr->c, &test_ptr->x1, &test_ptr->x2, &test_ptr->num_roots);
}

void linear_generation(TestData* test_ptr)
{		// (*test).b  =>  test->b

	test_ptr->b = (double) randomize(MIN_RAND, MAX_RAND);
	test_ptr->c = (double) randomize(MIN_RAND, MAX_RAND);

	if (isnul(test_ptr->b)) 
	{
		test_ptr->x1 = test_ptr->x2 = NAN;
		test_ptr->num_roots = (isnul(test_ptr->c)) ? INF_ROOTS : NO_ROOT; 
	}

	else
	{
		test_ptr->x1 = test_ptr->x2 = -test_ptr->b / test_ptr->c;
		test_ptr->num_roots = ONE_ROOT;
	}

}

void viete_generation(TestData* test_ptr)
{
	test_ptr->x1 = (double) randomize(MIN_RAND, MAX_RAND);
	test_ptr->x2 = (double) randomize(MIN_RAND, MAX_RAND);

	test_ptr->b = -test_ptr->a * (test_ptr->x1 + test_ptr->x2);
	test_ptr->c = test_ptr->a * (test_ptr->x1 * test_ptr->x2);

	test_ptr->num_roots = TWO_ROOTS;
}

void cmplx_roots_to_coefs(int real, int imag,  double a, double* b_ptr, double* c_ptr)
{
	*b_ptr = (double) (-2 * real);

	int D = -1 * (2 * imag) * (2 * imag);

	*c_ptr = (double) ((*b_ptr * *b_ptr - D) / (4 * a));


}

void complex_generation(TestData* test_ptr)
{
	int real = randomize(MIN_RAND, MAX_RAND);

	int imag = int_poison;

	do
	{
		imag = randomize(MIN_RAND, MAX_RAND);

	}while (imag <= 0);

	test_ptr->x1 = (double) real;
	test_ptr->x2 = (double) imag; 

	cmplx_roots_to_coefs(real, imag, test_ptr->a, &test_ptr->b, &test_ptr->c);
}

void quadratic_generation(TestData* test_ptr)
{
	bool have_roots = randomize(0, 1);
	printf("%d\n", have_roots);

	if (have_roots)
	{
		viete_generation(test_ptr);
	}
	else
	{
		complex_generation(test_ptr);
		//printf("3) b: %lg, c: %lg, x1: %lg, x2: %lg\n", test_ptr->b, test_ptr->c);
	}
}

void generate_tests(FILE* tests_f, int num_tests, bool is_zero_a)
{
	srand(time(NULL));

	tests_f = freopen(tests_filename, "a", tests_f);

	TestData correct_test = {.a = is_zero_a ? 0 : (double) randomize(MIN_RAND, MAX_RAND), .b = 0, .c = 0, .x1 = nan, .x2 = nan, .num_roots = int_poison};

	for(int i = 0; i < num_tests; i++)
	{
		if (is_zero_a)
		{
			linear_generation(&correct_test);
		}
		else
		{
			quadratic_generation(&correct_test);
			//printf("4) b: %lg, c: %lg, x1: %lg, x2: %lg\n", correct_test.b, correct_test.c);
		}
		                                                               
		fprint_test(tests_f, correct_test);
	}
}

void add_std_tests(FILE* std_tests_f, FILE*  tests_f)
{

	tests_f = freopen(tests_filename, "a", tests_f);

	TestData std_test = {.a = 0, .b = 0, .c = 0, .x1 = nan, .x2 = nan, .num_roots = int_poison};


	while (fscan_test(std_tests_f, &std_test) != 0)
	{
		fprint_test(tests_f, std_test);
	}
}

bool check_result(TestData correct_test, TestData user_test)
{
	bool is_correct1 = equal(user_test.x1, correct_test.x1) || equal(user_test.x1, correct_test.x2);
	bool is_correct2 = equal(user_test.x2, correct_test.x1) || equal(user_test.x2, correct_test.x2);

	bool is_num_correct = user_test.num_roots == correct_test.num_roots;

	if (isnan(correct_test.x1) && isnan(correct_test.x2))
	{
		return is_num_correct;
	}
	else
	{
		return is_correct1 && is_correct2;
	}
}

void skip_line(FILE* file, int size)
{
	char buff[size];

	fgets(buff, sizeof(buff), file);

	//printf("%s", buff);
}

void check_tests(FILE* tests_f, FILE* log_f)
{
	tests_f = freopen(tests_filename, "r", tests_f);

	fprintf(log_f, "NUM                       a        b        c      x1       x2  num_roots\n");

	skip_line(tests_f, 100);

	TestData user_test = {.a = 0, .b = 0, .c = 0, .x1 = nan, .x2 = nan, .num_roots = int_poison};
	TestData correct_test = {.a = 0, .b = 0, .c = 0, .x1 = 0, .x2 = 0, .num_roots = int_poison};

	bool result = int_poison;

	int num_scans = 0;

	int count_test = 0;

	while ((num_scans = fscan_test(tests_f, &correct_test)) > 0)
	{
		user_test.a = correct_test.a;
		user_test.b = correct_test.b;
		user_test.c = correct_test.c;

		user_test.num_roots = solve_equation(correct_test.a, correct_test.b, correct_test.c, &user_test.x1, &user_test.x2);

		result = check_result(correct_test, user_test);

		fprintf(log_f, "%d  ", count_test);
		count_test++;

		fprintf(log_f, "\bCorrect values: ");
		fprint_test(log_f, correct_test);
 	
		fprintf(log_f, "   Calc values:    ");
		fprint_test(log_f, user_test);

		fprintf(log_f, "   Result: %s\n\n", result ? "Correct" : "-------FAILED!!!!!------");
	}
}

void make_tests_file(FILE* std_tests_f, FILE* tests_f)
{
	
	fprintf(tests_f, "          a       b        c     x1   x2  num_roots\n");

    add_std_tests(std_tests_f, tests_f);

	generate_tests(tests_f, 30, false);
	generate_tests(tests_f, 10, true);

}

void print_log()
{
	assert(test_fа != NULL)
	assert(std_tests_f != NULL)
	assert(log_f != NULL)

	FILE* tests_f = fopen(tests_filename, "w");
	FILE* std_tests_f = fopen(std_tests_filename, "r");
	FILE* log_f = fopen(log_filename, "w");

	make_tests_file(std_tests_f, tests_f);

	check_tests(tests_f, log_f);

	fclose(tests_f);
	fclose(std_tests_f);
	fclose(log_f);

}