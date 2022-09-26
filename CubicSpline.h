void CubicInterpolation(double (*function)(double), int nestSize, double *nestNode, Poly *OutPolynomial);
double *FindD_(double *distributedDifference, double *nestNode, int nestSize);
void FindC1_(double *functionValue, Poly *OutPolynomial, int nestSize);
void FindC2_(double *ds, Poly *OutPolynomial, int nestSize);
void FindC3_(double *distributedDifference, double *ds, Poly *OutPolynomial, double *nestNode, int nestSize);
void FindC4_(double *distributedDifference, double *ds, Poly *OutPolynomial, double *nestNode, int nestSize);