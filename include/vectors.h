#ifndef VECTORS_H_   /* Include guard */
#define VECTORS_H_

#include "structures.h"


vector v_init(size_t len);

vector v_decrease(vector v, double x);

vector v_increase(vector v, double x);

vector v_div(vector X, vector Y);

vector v_flipr(vector v);

double* v_min(vector v);

vector v_exp(vector v);

vector v_dotdiv(double n, vector v);

vector v_dotmul(double n, vector v);

vector v_dotsub(double n, vector v);

vector v_dotadd(double n, vector v);

vector v_dotpow(double n, vector v);

vector v_pow(vector v, double n);

vector v_dot(vector a, vector b);

vector v_add(vector a, vector b);

vector genseries(double lo, double up, double delta);

#endif
