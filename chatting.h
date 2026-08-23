#ifndef CHATTING_H
#define CHATTING_H

#include<complex.h>

//MAIN
void print_topic();

//SOLVER
void scan_coefs(double* a_ptr, double* b_ptr, double* c_ptr);
void print_answer(int num_roots, double  x1, double  x2);

//TESTER
void print_result(bool is_wrong, int score, double x1_correct, double x2_correct);
void scan_user_roots(double* x1_user, double* x2_user);


#endif