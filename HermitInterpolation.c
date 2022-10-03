#include <stdlib.h>
#include "Common.h"
#include "interpolation.h"
#include "HermitInterpolation.h"

void HermitInterpolation(double (*function)(double), double (*derivative)(double), int nestSize, double *nestNode, Poly *OutPolynomial)
{
    double *functionValue = FindFunctionValues(function, nestSize, nestNode);
    double *derivativeValue = FindFunctionValues(derivative, nestSize, nestNode);
    double *distributedDifference = FindDistributedDifference(functionValue, nestSize, nestNode);
   // FindD(derivativeValue, nestSize, distributedDifference[0], distributedDifference[nestSize-2]);
    FindC1(functionValue, OutPolynomial, nestSize);
    FindC2(derivativeValue, OutPolynomial, nestSize);
    FindC3(derivativeValue, distributedDifference, OutPolynomial, nestNode, nestSize);
    FindC4(derivativeValue, distributedDifference, OutPolynomial, nestNode, nestSize);
    free(distributedDifference);
    free(derivativeValue);
    free(functionValue);
}

//change derivative according to natural boundary conditions
void FindD(double *OutDerivativeValue, int nestSize, double firstDistributedDifference, double lastDistributedDifference)
{
    OutDerivativeValue[0] = 0.5 * (3.0 * firstDistributedDifference - OutDerivativeValue[1]);
    OutDerivativeValue[nestSize - 1] = 0.5 * (3.0 * lastDistributedDifference - OutDerivativeValue[nestSize - 2]);
}

void FindC1(double *functionValue, Poly *OutPolynomial, int nestSize)
{
    for (int i = 0; i < nestSize - 1; ++i)
    {
        OutPolynomial[i].c1 = functionValue[i];
    }
}

void FindC2(double *ds, Poly *OutPolynomial, int nestSize)
{
    for (int i = 0; i < nestSize - 1; ++i)
    {
        OutPolynomial[i].c2 = ds[i];
    }
}

void FindC3(double *distributedDifference, double *ds, Poly *OutPolynomial, double *nestNode, int nestSize)
{
    for (int i = 0; i < nestSize - 1; ++i)
    {
        OutPolynomial[i].c3 = (3.0 * ds[i] - 2.0 * distributedDifference[i] - distributedDifference[i + 1]) / (nestNode[i + 1] - nestNode[i]);
    }
}

void FindC4(double *distributedDifference, double *ds, Poly *OutPolynomial, double *nestNode, int nestSize)
{
    for (int i = 0; i < nestSize - 1; ++i)
    {
        double tmp = nestNode[i+1] - nestNode[i];
        tmp *= tmp;
        OutPolynomial[i].c4 = (-2.0 * ds[i] + distributedDifference[i] + distributedDifference[i + 1]) / tmp;
    }
}
