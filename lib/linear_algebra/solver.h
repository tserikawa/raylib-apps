#ifndef ___solver
#define ___solver

#include "vector.h"
#include "sqmatrix.h"

void solver_gaussian_elimination(sqmatrix *a, vector *b, vector *x);

#endif