#include "matrices.h"
#include<stdlib.h>
#include<math.h>

twodmatrix fillMatrix(size_t r, size_t c, double value)
{
	twodmatrix z;
	z.m = 0;
	z.n = 0;
	z.matrix = NULL;
	if((r>0)&&(c>0))
	{
		z.m = r;
		z.n = c;
		z.matrix = malloc(z.m*sizeof(double*));
		for(size_t i=0;i<z.m;i++)
		{
			z.matrix[i] = malloc(z.n*sizeof(double));
		}
		for(size_t i=0;i<z.m;i++)
		{
			for(size_t j=0;j<z.n;j++)
			{
				z.matrix[i][j] = value;
			}
		}
	}
	return z;
}

twodmatrix m_init(size_t r, size_t c)
{
	twodmatrix m = fillMatrix(r,c,0);
	return m;
} 

twodmatrix matrixMul(twodmatrix A, twodmatrix B) //Multiplication of two 2D Matrix
{
	twodmatrix C;
	if((A.n==B.m)&&(A.m!=0)&&(A.n!=0)&&(B.m!=0)&&(B.n!=0)&&(A.matrix!=NULL)&&(B.matrix!=NULL))
	{
		/*C.m = A.m;
		C.n = B.n;
		C.matrix = malloc(C.m*sizeof(double*));
		for(size_t h=0;h<C.m;h++)
		{
			C.matrix[h] = malloc(C.n*sizeof(double));
		}*/
		C = m_init(A.m,B.n);
		for(size_t i=0;i<A.m;i++)
		{
			for(size_t j=0;j<B.n;j++)
			{
				C.matrix[i][j] = 0;
				for(size_t k=0;k<B.m;k++)
				{
					C.matrix[i][j] = C.matrix[i][j] + A.matrix[i][k]*B.matrix[k][j];
				}
			}
		}
	}
	else
	{
		C.m=0;
		C.n=0;
		C.matrix = NULL;
	}
	return C;
}

twodmatrix m_transpose(twodmatrix m)
{
	twodmatrix tmat;
	if(m.m==0||m.n==0||m.matrix==NULL)
	{
		tmat.m = 0;
		tmat.n = 0;
		tmat.matrix = NULL;
	}
	else
	{
		/*tmat.m = m.n;
		tmat.n = m.m;
		tmat.matrix = malloc(tmat.m*sizeof(double*));
		for(size_t i=0;i<tmat.m;i++)
		{
			tmat.matrix[i] = malloc(tmat.n*sizeof(double));
		}*/
		tmat = m_init(m.n,m.m);
		for(size_t i=0;i<tmat.m;i++)
		{
			for(size_t j=0;j<tmat.n;j++)
			{
				tmat.matrix[i][j] = m.matrix[j][i];
			}
		}
	}
	return tmat;
}

twodmatrix m_inverse(twodmatrix mat) //2D Matrix Inverse
{
	twodmatrix m = mat;
	twodmatrix im;
	if((m.m==m.n)&&(m.m!=0)&&(m.n!=0)&&(m.matrix!=NULL))
	{
		size_t c;
		/*im.m = m.m;
		im.n = m.n;
		im.matrix = malloc(im.m*sizeof(double*));
		for(size_t i=0;i<im.n;i++)
		{
			im.matrix[i] = malloc(im.n*sizeof(double));
		}*/
		im = m_init(m.m,m.n);
		for(size_t i=0;i<im.m;i++)
		{
			for(size_t j=0;j<im.n;j++)
			{
				if(i==j)
					im.matrix[i][j] = 1;
				else
					im.matrix[i][j] = 0;
			}
		}
		for(size_t i=0;i<im.m;i++)
		{
			double temp = m.matrix[i][i];
			for(size_t j=0;j<im.n;j++)
			{
				m.matrix[i][j] = m.matrix[i][j]/temp;
				im.matrix[i][j] = im.matrix[i][j]/temp;
				if(m.matrix[i][j]==1)
					c = j;
			}
			for(size_t k=0;k<im.m;k++)
			{
				if(k!=i)
				{
					double t = m.matrix[k][c];
					for(size_t l=0;l<im.n;l++)
					{
						m.matrix[k][l] = m.matrix[k][l] - (m.matrix[i][l]*t);
						im.matrix[k][l] = im.matrix[k][l] - (im.matrix[i][l]*t);
					}
				}
			}
		}
		for(size_t i=0;i<m.m;i++) //If singular Return Matrix will be of dimension 1x1 and it's matrix will be NULL
		{
			if(m.matrix[i][i]==0)
			{
				im.m = 1;
				im.n = 1;
				im.matrix = NULL;
				break;
			}
		}
	}
	else
	{
		im.m = 0;
		im.n = 0;
		im.matrix = NULL;
	}
	return im;
}
