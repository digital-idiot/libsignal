#ifndef MATRICES_H_   /* Include guard */
#define MATRICES_H_

#include "structures.h"


twodmatrix fillMatrix(size_t r, size_t c, double value);

twodmatrix m_init(size_t r, size_t c);
 
twodmatrix m_transpose(twodmatrix m);

twodmatrix m_inverse(twodmatrix mat);

twodmatrix matrixMul(twodmatrix A, twodmatrix B); //Multiplication of two 2D Matrix

#endif
