#include<stdlib.h>
#include "vectors.h"
#include "matrices.h"
#include "struct_ops.h"


twodmatrix matrixCopy(twodmatrix matrx, size_t ri, size_t rl, size_t ci, size_t cl) //get a portion of a 2D matrix
{
	size_t h = matrx.m;
	size_t w = matrx.n;
	twodmatrix cmatrix;
	if(ri>=rl||ci>=cl||ri>=h||rl>=h||ci>=w||cl>=w)
	{
		cmatrix.m = 0;
		cmatrix.n = 0;
		cmatrix.matrix = NULL;
	}
	else 
	{
		size_t i,j;
		size_t rows = rl - ri + 1;
		size_t cols = cl - ci + 1;
		cmatrix = m_init(rows,cols);
		for(i=0;i<rows;i++)
		{
			for(j=0;j<cols;j++)
			{
				cmatrix.matrix[i][j] = matrx.matrix[ri + i][ci + j];
			}
		}
	}
	return cmatrix;
}

vector matrixColCopy(twodmatrix matrx, size_t ri, size_t rl, size_t c) //get any Coloumn from 2D matrix
{
	vector vect;
	if(ri>=rl||ri>=matrx.m||rl>=matrx.m||c>=matrx.n)
	{
		vect.l = 0;
		vect.array = NULL;
	}
	else
	{
		vect = v_init(rl-ri+1);
		for(size_t i=0;i<vect.l;i++)
		{
			vect.array[i] = matrx.matrix[ri + i][c];
		}
	}
	return vect;
}

vector matrixRowCopy(twodmatrix matrx, size_t ci, size_t cl, size_t r) //get any Row from 2D matrix
{
	vector vect;
	if((ci>=cl)||(r>=matrx.m)||(ci>= matrx.n)||(cl>= matrx.n))
	{
		vect.l = 0;
		vect.array = NULL;
	}
	else
	{
		vect = v_init(cl-ci+1);
		for(size_t i=0;i<vect.l;i++)
		{
			vect.array[i] = matrx.matrix[r][ci + i];
		}
	}
	return vect;
}

vector vectorCopy(vector v, size_t x, size_t y) //get a portion of a vector
{
	vector vect;
	if(x>=y||x>=v.l||y>=v.l)
	{
		vect.l = 0;
		vect.array = NULL;
	}
	else
	{
		vect = v_init(y-x+1);
		for(size_t i=0;i<vect.l;i++)
		{
			vect.array[i] = v.array[x + i];
		}
	}
	return vect;
}

vector v_concat(vector A, vector B)
{
	vector C;
	C.l = 0;
	C.array = NULL;
	if((A.l==0)||(A.array==NULL))
	{
		C = B;
	}
	else if((B.l==0)||(B.array==NULL))
	{
		C = A;
	}
	else
	{
		C = v_init(A.l+B.l);
		size_t i = 0;
			for(size_t j=0;(j<A.l)&&(i<C.l);j++)
			{
				C.array[i] = A.array[j];
				i++;
			}
			for(size_t j=0;(j<B.l)&&(i<C.l);j++)
			{
				C.array[i] = B.array[j];
				i++;
			}
	}
	return C;
}

twodmatrix plot2mat(plotdata pd)
{
	twodmatrix mat;
	if((pd.length!=0)&&(pd.x!=NULL)&&(pd.y!=NULL))
	{
		/*mat.m = pd.length;
		mat.n = 2;
		mat.matrix = malloc(mat.m*sizeof(double));
		for(size_t i=0;i<mat.m;i++)
		{
			mat.matrix = malloc(mat.n*sizeof(double));
		}*/
		mat = m_init(pd.length,2);
		for(size_t i=0;i<mat.m;i++)
		{
			mat.matrix[i][0] = pd.x[i];
			mat.matrix[i][1] = pd.y[i];
		}
	}
	else
	{
		mat.m = 0;
		mat.n = 0;
		mat.matrix = NULL;
	}
	return mat;
}
