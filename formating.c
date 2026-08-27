#include "formating.h"
#include "service.h"

#include<stdio.h>


void formating_monomial(const char x_string[], double coef, bool is_print_plus) //Форматирует одночлен. Если при нем множитель 1 или -1, то убирает его. 
{                                                                         //Если множитель 0, то убирает весь одночлен.
	if (isnul(coef)) return;                                              //Принимает буквенную часть в виде строки, коэфицент и условие на сохранение '+' перед членом
                                                                          //Возвращает строку - отформатированный одночлен
	if (equal(coef,1.0f))
	{
		printf(is_print_plus ? "+%s" : "%s", x_string);
	}
	else if (equal(coef,-1.0f))
	{
		printf("-%s", x_string);
	}
	else
	{
		printf(is_print_plus ? "+%g%s" : "%g%s", coef, x_string);
	}
}

void formating_equation(double a, double b, double c)//Комбинирует отформартированные одночлены и возвращает полное выражение
{
	if (a<0)
	{
		a = -a;  //Домножение на -1 всего выражения если a < 0
		b = -b;
		c = -c;
	}

	formating_monomial("x^2", a, false); //Форматирование одночлена с x^2
	formating_monomial("x", b, !isnul(a) && b > 0); //Форматирование одночлена с х. Если a=0, то след по старшинству члену не печатать слева '+'
	if (!(isnul(c)))
	{
		printf(isnul(a) && isnul(b) ? "%g" : "%+g", c);     //Форматирование свободного члена с. Если a=0 и b=0, то не печатать '+' перед членом
	}
	else if (isnul(a) && isnul(b)) //печатать ноль в случае обнуления всех трех переменных, иначе с=0 не печатается
	{
		printf("0");
	}

	printf("=0\n");

}