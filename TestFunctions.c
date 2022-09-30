#include <math.h>
#include "TestFunctions.h"

double f6(double x)
{
    x += 0;
    return 1/(25*x*x+1);
}
double f5(double x)
{
    x += 0;
    return exp(x);
}
double f4(double x)
{
    x += 0;
    return x*x*x*x;
}
double f3(double x)
{
    x += 0;
    return x*x*x;
}
double f2(double x)
{
    return x*x;
}
double f1(double x)
{
    x += 0;
    return x;
}
double f0(double x)
{
    x += 0;
    return 1;
}

double d6(double x)
{
    double tmp;
    tmp = (25*x*x+1);
    tmp *= tmp;
    return -50.0*x/tmp;
}
double d5(double x)
{
    return exp(x);
}
double d4(double x)
{
    return 4.0*x*x*x;
}
double d3(double x)
{
    return 3.0*x*x;
}
double d2(double x)
{
    return 2.0*x;
}
double d1(double x)
{
    x += 0;
    return 1;
}
double d0(double x)
{
    x += 0;
    return 0;
}
