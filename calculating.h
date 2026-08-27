
#ifndef CALCULATING_H
#define CALCULATING_H

#define NUM_COEFS 3


double calc_discriminant(double a, double b, double c);

// int linear_equation(double a, double b, double c, double  *x1_ptr, double  *x2_ptr);
// int quadratic_equation(double a, double b, double c, double  *x1_ptr, double  *x2_ptr);

int solve_equation(double a, double b, double c, double  *x1_ptr, double  *x2_ptr);

void coef_generate(int *a_ptr, int *b_ptr, int *c);

bool check_correct_roots(double x1_user, double x2_user, double x1_correct, double x2_correct);

#endif