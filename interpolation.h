#ifndef __INTERPOLATION_H
#define __INTERPOLATION_H

typedef struct Poly{
	double	c1,c2,c3,c4;
}Poly;

struct interpolation_ctx_inner;
typedef struct interpolation_ctx_inner *interpolation_ctx;

#define INTERPOLATION_METHOD1	1
#define INTERPOLATION_METHOD2	2

#define INTERPOLATION_F_1	0
#define INTERPOLATION_F_X	1
#define INTERPOLATION_F_X2	2
#define INTERPOLATION_F_X3	3
#define INTERPOLATION_F_X4	4
#define INTERPOLATION_F_EX	5
#define INTERPOLATION_F_1DIVX2	6

interpolation_ctx interpolation_create(int method, int n, int k,
				       double a, double b);

double interpolation_calculate(interpolation_ctx ctx, double x);
double EvaluatePolynomial(Poly P, double x, double xi);

void interpolation_destroy(interpolation_ctx ctx);

#endif
