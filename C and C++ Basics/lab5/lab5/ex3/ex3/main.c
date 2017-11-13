#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>


double f(double x)
{
    return 1.5 + x/sqrt(3) - x*x*9.81/(2*30*30*cos(30*3.1415926/180)*cos(30*3.1415926/180));
}

double abss(double v)
{
    return v<0?-v:v;
}

int main()
{
    double t;
    double head = 75,tail = 85,mid;

    mid = (head+tail)/2;
    while (abss(f(mid))>=FLT_EPSILON)
    {
        if ( f(mid) * f(head) > 0 ) head = mid;
        else                        tail = mid;
        mid = (head+tail)/2;
    }
    t = mid/(30*cos(30*3.1415926/180));
    printf("t = %.8lf\n",t);
    return 0;
}
