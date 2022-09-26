#include <stdlib.h>
#include "interpolation.h"
#include "HermitInterpolation.h"
#include "TestFunctions.h"
#include "Common.h"
#include "CubicSpline.h"
#include <math.h>
#include <stdio.h>

const double (*Functions[7])(double) = {f0, f1, f2, f3, f4, f5, f6};
const double (*Derivatives[7])(double) = {d0, d1, d2, d3, d4, d5, d6};

struct interpolation_ctx_inner {
    int	method;
	int	n;
	double	a, b;
    double f21, f22;
    double (*f)(double);
    
    double *X;
    double *D;
    Poly *P;
};

double EvaluatePolynomial(Poly P, double x, double xi)
{
    return P.c1 + P.c2*(x-xi) + P.c3*(x-xi)*(x-xi) + P.c4*(x-xi)*(x-xi)*(x-xi);
}

interpolation_ctx interpolation_create(int method, int n, int k,
				       double a, double b)
{
    interpolation_ctx res_ctx;
    if ((k < 0 || k>6) || (a >= b) || (method!=1 && method!=2) || (n<5))
	{
        return NULL;
	}
   
    
    res_ctx = malloc(sizeof(*res_ctx));
    res_ctx->X = malloc(n*sizeof(double));
    res_ctx->D = malloc(n*sizeof(double));
    res_ctx->P = malloc((n-1)*sizeof(Poly));
         
    
    res_ctx->method = method;
    res_ctx->n = n;
    res_ctx->a = a;
    res_ctx->b = b;
    switch (k){
        case INTERPOLATION_F_1:
            res_ctx->f = f0;
            res_ctx->f21 = 0;
            res_ctx->f22 = 0;
            break;
        case INTERPOLATION_F_X:
            res_ctx->f = f1;
            res_ctx->f21 = 0;
            res_ctx->f22 = 0;
            break;
        case INTERPOLATION_F_X2:
            res_ctx->f = f2;
            res_ctx->f21 = 2;
            res_ctx->f22 = 2;
            break;
        case INTERPOLATION_F_X3:
            res_ctx->f = f3;
            res_ctx->f21 = 6*a;
            res_ctx->f22 = 6*b;
            break;
        case INTERPOLATION_F_X4:
            res_ctx->f = f4;
            res_ctx->f21 = 12*a*a;
            res_ctx->f22 = 12*b*b;
            break;
        case INTERPOLATION_F_EX:
            res_ctx->f = f5;
            res_ctx->f21 = exp(a);
            res_ctx->f22 = exp(b);
            break;
        case INTERPOLATION_F_1DIVX2:
            res_ctx->f = f6;
            res_ctx->f21 = (5000*a*a)/((25*a*a+1)*(25*a*a+1)*(25*a*a+1))- 50/((25*a*a+1)*(25*a*a+1));
            res_ctx->f22 = (5000*b*b)/((25*b*b+1)*(25*b*b+1)*(25*b*b+1))- 50/((25*b*b+1)*(25*b*b+1));
            break;
    }

    for (int i = 0; i<n; i++)
    {
        res_ctx->X[i] = a + i*(b-a)/(n-1);
    }

    switch (method) {
        case INTERPOLATION_METHOD1:
            HermitInterpolation(Functions[k], Derivatives[k], n, res_ctx->X, res_ctx->P);
            break;
        case INTERPOLATION_METHOD2:
            CubicInterpolation(Functions[k], n, res_ctx->X, res_ctx->P);
            break;
    }

    return res_ctx;
}

double interpolation_calculate(interpolation_ctx ctx, double x)
{
    int n = ctx->n;
    double a = ctx->a;
    double b = ctx->b;
    if (x<a || x>b)
    {
        fprintf(stderr,"Incorrect input\n");
        return -1;
    }

    int k = LowerBound(ctx->X, x, n);
	return EvaluatePolynomial(ctx->P[k], x, ctx->X[k]);
}

void interpolation_destroy(interpolation_ctx ctx)
{
    free(ctx->X);
    free(ctx->D);
    free(ctx->P);
	free(ctx);
}

