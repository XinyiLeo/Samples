#include <stdio.h>
#include <math.h>
#include <stdlib.h>


struct Pol{
	double len;
	double ang;
};

struct Num{
	double real;
	double img;
}complex;

int main(){
	struct Num num1, num2;
	struct Pol num3, num4;
	char oper;
	int i;
	int c;
	printf("Please input two complex numbers in form(a+bi):\n");
	scanf("%.2lf+%.2lfi", &num1.real, &num1.img);
	scanf("%.2lf+%.2lfi", &num2.real, &num2.img);
	car2pol(num1);
	car2pol(num2);
}

int* car2pol(struct Num)
{
	double x, y;
	x = sqrt((complex.real)*(complex.real) + (complex.img)*(complex.img));
	y = atan(complex.img / complex.real);

}