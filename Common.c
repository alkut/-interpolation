#include <malloc.h>
#include "Common.h"

double *FindFunctionValues(double (*function)(double),  int nestSize, double *nestNode)
{
    double *res = (double *) malloc(nestSize * sizeof(double));
    for (int i = 0; i < nestSize; ++i)
    {
        res[i] = function(nestNode[i]);
    }
    return res;
}

double *FindDistributedDifference(double *functionValue,  int nestSize, double *nestNode)
{
    double *res = (double *) malloc((nestSize - 1) * sizeof(double));
    for (int i = 0; i < nestSize-1; ++i)
    {
        res[i] = (functionValue[i+1] - functionValue[i]) / (nestNode[i+1] - nestNode[i]);
    }
    return res;
}

matrix3 create(int n)
{
    matrix3 res;
    res.n = n;
    res.main = (double *) malloc(n * sizeof (double ));
    res.down = (double *) malloc(n * sizeof (double ));
    res.up = (double *) malloc(n * sizeof (double ));
    return res;
}

void gauss(matrix3 m, double *OutColumn)
{
    for (int i = 0; i < m.n; ++i)
    {
        double x = m.main[i];
        m.main[i] /= x;
        m.up[i] /= x;
        OutColumn[i] /= x;
        if (i != m.n - 1) {
            double y = m.down[i + 1];
            m.down[i + 1] -= y;
            m.main[i + 1] -= y * m.up[i];
            OutColumn[i + 1] -= y * OutColumn[i];
        }
    }
    for (int i = m.n - 1; i > 0; --i)
    {
        double x = m.up[i-1];
        m.up[i-1] -= x;
        OutColumn[i-1] -= x * OutColumn[i];
    }
}

void destroy(matrix3 m)
{
    free(m.main);
    free(m.down);
    free(m.up);
}
