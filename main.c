#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "interpolation.h"


double f5(double x);
double g(double x);

double g(double x)
{
    return x * x;
}

double f5(double x)
{
    return exp(x);
}


void Show_error(interpolation_ctx ctx, double start_point, double end_point, int count, double (*function)(double));

void Show_error(interpolation_ctx ctx, double start_point, double end_point, int count, double (*function)(double))
{
    double ans, step, tmp, tmpX;
    ans = 0.0;
    step = (end_point - start_point) / (count - 1);
    
    for (int i = 0; i < count - 1; ++i)
    {
        tmpX = start_point + i * step;
        tmp = fabs(function(tmpX) - interpolation_calculate(ctx, tmpX));
        if (ans < tmp)
            ans = tmp;
    }
    
    printf("C0 Norm of error: %10.15e\n", ans);
    
}

int main(void)
{
	interpolation_ctx ctx;
    int n;
    
    n = 5;

	ctx = interpolation_create(1,
				   n, 2, 0, 1);

	Show_error(ctx, 0, 1, 1000, g);

	interpolation_destroy(ctx);

	return 0;
}
