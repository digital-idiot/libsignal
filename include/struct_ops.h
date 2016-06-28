#ifndef STRUCTOPS_H_   /* Include guard */
#define STRUCTOPS_H_

#include "structures.h"


twodmatrix matrixCopy(twodmatrix matrx, size_t ri, size_t rl, size_t ci, size_t cl); //get a portion of a 2D matrix

vector matrixColCopy(twodmatrix matrx, size_t ri, size_t rl, size_t c); //get any Coloumn from 2D matrix

vector matrixRowCopy(twodmatrix matrx, size_t ci, size_t cl, size_t r); //get any Row from 2D matrix

vector vectorCopy(vector v, size_t x, size_t y); //get a portion of a vector

vector v_concat(vector A, vector B);

twodmatrix plot2mat(plotdata pd);

#endif
