#ifndef SERVICE_H
#define SERVICE_H

#include <math.h>
#include <stdio.h>
#define inf INFINITY

#define SOLVER 's'
#define TESTER 't'
#define QUIT 'q'
#define UNIT_TESTER 'u'

enum NUM_ROOTS
{
	INF_ROOTS = -1,
	NO_ROOT = 0,
	ONE_ROOT = 1,
	TWO_ROOTS = 2,
	TWO_COMPLEX_ROOTS = 4

};

bool equal(double a, double b);

bool isnul(double a);

void clear_buffer();

void print_separator();

void slow_print(char *s);

int randomize(int min, int max);

void skip_line(FILE* file);

//void print_arc_arv(int argc, char argv[]);

#endif