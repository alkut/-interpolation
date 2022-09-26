#include "interpolation.h"

void HermitInterpolation(double (*function)(double), double (*derivative)(double), int nestSize, double *nestNode, Poly *OutPolynomial);
void FindD(double *OutDerivativeValue, int nestSize, double firstDistributedDifference, double lastDistributedDifference);
void FindC1(double *functionValue, Poly *OutPolynomial, int nestSize);
void FindC2(double *ds, Poly *OutPolynomial, int nestSize);
void FindC3(double *distributedDifference, double *ds, Poly *OutPolynomial, double *nestNode, int nestSize);
void FindC4(double *distributedDifference, double *ds, Poly *OutPolynomial, double *nestNode, int nestSize);
