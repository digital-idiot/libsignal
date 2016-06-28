#ifndef NUMERICALS_H_   /* Include guard */
#define NUMERICALS_H_

#include "structures.h"
#include "vectors.h"
#include "matrices.h"


vector polyfit(plotdata dat, unsigned short deg); //polyfit: Returns a vector with co-efficients, uses Least Square Fit method

vector polyval(vector coeff, vector x);

double* interpolate(plotdata pd, double x);

twodpoint* fminbnd(plotdata pd); //Use genseries() to generate input set within the given range. Obtain plotdata from f(x) accordingly.

double* dsearchn(vector v, double x);

#endif
