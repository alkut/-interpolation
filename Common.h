#ifndef INTER_COMMON_H
#define INTER_COMMON_H

double *FindFunctionValues(double (*function)(double),  int nestSize, double *nestNode);
double *FindDistributedDifference(double *functionValue,  int nestSize, double *nestNode);

int LowerBound(double *arr, double x, int n);

typedef struct matrix3
{
    double *main, *up, *down;
    int n;
} matrix3;

matrix3 create(int n);
void gauss(matrix3 m, double *OutColumn);
void destroy(matrix3 m);

#endif //INTER_COMMON_H
