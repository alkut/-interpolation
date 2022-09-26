#include <stdlib.h>
#include <stdio.h>
#include "interpolation.h"
#include "Common.h"
#include "CubicSpline.h"

void CubicInterpolation(double (*function)(double), int nestSize, double *nestNode, Poly *OutPolynomial)
{
    double *functionValue = FindFunctionValues(function, nestSize, nestNode);
    double *distributedDifference = FindDistributedDifference(functionValue, nestSize, nestNode);
    double *ds = FindD_(distributedDifference, nestNode, nestSize);

    FindC1_(functionValue, OutPolynomial, nestSize);
    FindC2_(ds, OutPolynomial, nestSize);
    FindC3_(distributedDifference, ds, OutPolynomial, nestNode, nestSize);
    FindC4_(distributedDifference, ds, OutPolynomial, nestNode, nestSize);

    free(ds);
    free(distributedDifference);
    free(functionValue);
}

double *FindD_(double *distributedDifference, double *nestNode, int nestSize)
{
    /*double *res = (double *) malloc(nestSize * sizeof(double ));
    double SumOdd = 0.0, SumEven = 0.0;

    for (int i = 0; i < nestSize - 1; ++i)
    {
        if (i & 1)
            SumOdd += distributedDifference[i];
        else
            SumEven += distributedDifference[i];
    }

    double OddTmp = 0.0, EvenTmp = 0.0;

    res[0] = 3.0 * (SumEven - SumOdd) / (double )(nestSize + 1);

    for (int i = 1; i < nestSize; ++i)
    {
        if (i & 1)
        {
            EvenTmp += distributedDifference[i - 1];
            res[i] = 3.0 * (EvenTmp - OddTmp) * (nestSize - i);
            res[i] -= 3.0 * (i +1) * (SumEven - EvenTmp - SumOdd + OddTmp);
        }
        else
        {
            OddTmp += distributedDifference[i - 1];
            res[i] = -3.0 * (EvenTmp - OddTmp) * (nestSize - i);
            res[i] += 3.0 * (i + 1) * (SumEven - EvenTmp - SumOdd + OddTmp);
        }
        res[i] /= nestSize + 1;
    }

    return res;*/
    double *res = (double *) malloc(nestSize * sizeof(double ));
    res[0] = 3.0 * distributedDifference[0];
    for (int i = 1; i < nestSize - 1; ++i)
        res[i] = 3.0 * ((nestNode[i+1] - nestNode[i]) * distributedDifference[i-1] +
                (nestNode[i] - nestNode[i-1]) * distributedDifference[i]);
    res[nestSize - 1] = 3.0 * distributedDifference[nestSize - 2];
    matrix3 matrix = create(nestSize);

    matrix.main[0] = 2.0;
    for (int i = 1; i < nestSize - 1; ++i)
        matrix.main[i] = 2.0 * (nestNode[i+1] - nestNode[i-1]);
    matrix.main[nestSize-1] = 1.0;

    matrix.up[0] = 1.0;
    for (int i = 1; i < nestSize - 1; ++i)
        matrix.up[i] = (nestNode[i] - nestNode[i-1]);
    matrix.up[nestSize-1] = 0.0;

    matrix.down[0] = 0.0;
    for (int i = 1; i < nestSize - 1; ++i)
        matrix.down[i] = (nestNode[i+1] - nestNode[i]);
    matrix.down[nestSize-1] = 2.0;

    gauss(matrix, res);
    destroy(matrix);
    return res;
}

void FindC1_(double *functionValue, Poly *OutPolynomial, int nestSize)
{
    for (int i = 0; i < nestSize - 1; ++i)
    {
        OutPolynomial[i].c1 = functionValue[i];
    }
}

void FindC2_(double *ds, Poly *OutPolynomial, int nestSize)
{
    for (int i = 0; i < nestSize - 1; ++i)
    {
        OutPolynomial[i].c2 = ds[i];
    }
}

void FindC3_(double *distributedDifference, double *ds, Poly *OutPolynomial, double *nestNode, int nestSize)
{
    for (int i = 0; i < nestSize - 1; ++i)
    {
        OutPolynomial[i].c3 = (3.0 * distributedDifference[i] - 2.0 * ds[i] - ds[i+1]) / (nestNode[i+1] - nestNode[i]);
    }
}
void FindC4_(double *distributedDifference, double *ds, Poly *OutPolynomial, double *nestNode, int nestSize)
{
    for (int i = 0; i < nestSize - 1; ++i)
    {
        double tmp = nestNode[i+1] - nestNode[i];
        tmp *= tmp;
        OutPolynomial[i].c4 = (-2.0 * distributedDifference[i] + ds[i] + ds[i+1]) / tmp;
    }
}

