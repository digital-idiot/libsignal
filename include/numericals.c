#include<math.h>
#include<stdlib.h>
#include "struct_ops.h"
#include "numericals.h"


vector polyfit(plotdata dat, unsigned short deg) //polyfit: Returns a vector with co-efficients
{
	vector v;
	if((deg>=1)&&(dat.length!=0)&&(dat.y!=NULL)&&(dat.x!=NULL))
	{
		twodmatrix X;
		twodmatrix y;
		/*X.m = dat.length;
		X.n = deg + 1;
		X.matrix = malloc(X.m*sizeof(double*));
		for(size_t i=0;i<X.m;i++)
		{
			X.matrix[i] = malloc(X.n*sizeof(double));
		}*/
		X = m_init(dat.length, deg+1);
		for(size_t i=0;i<X.m;i++)
		{
			for(size_t j=0;j<X.n;j++)
			{
				X.matrix[i][j] = pow(dat.x[i],j);
			}
		}
		/*y.m = dat.length;
		y.n = 1;
		y.matrix = malloc(y.m*sizeof(double*));
		for(size_t i=0;i<y.m;i++)
		{
			y.matrix[i] = malloc(y.n*sizeof(double));
		}*/
		y = m_init(dat.length, 1);
		for(size_t i=0;i<y.m;i++)
		{
			y.matrix[i][0] = dat.y[i];
		}
		v = matrixColCopy(matrixMul(matrixMul(m_inverse(matrixMul(m_transpose(X),X)),m_transpose(X)),y),0,deg,0);
	}
	else
	{
		v.l = 0;
		v.array = NULL;
	}
	return v;
}

vector polyval(vector coeff, vector x)
{
	vector y;
	if((coeff.l>1)&&(coeff.array!=NULL)&&(x.l>0)&&(x.array!=NULL))
	{
		/*y.l = x.l;
		y.array = malloc(y.l*sizeof(double));*/
		y = v_init(x.l);
		for(size_t i=0;i<y.l;i++)
		{
			y.array[i] = 0;
			for(size_t j=0;j<coeff.l;j++)
			{
				y.array[i] = y.array[i] + (coeff.array[j]*pow(x.array[i],j));
				//printf("%Lf\t",coeff.array[j]);
			}
			//printf("\n");
		}
	}
	else
	{
		y.l = 0;
		y.array = NULL;
	}
	return y;
}

double* interpolate(plotdata pd, double x)
{
	double* y;
	y = NULL;
	if((x>pd.x[0])&&(x<pd.x[pd.length-1]))
	{
		y = malloc(sizeof(double));
		*y = 0;
		for(size_t i=0;i<pd.length;i++)
		{
			double temp = 1;
			for(size_t j=0;j<pd.length;j++)
			{
				if(j!=i)
				{
					temp = temp*((x-pd.x[j])/(pd.x[i]-pd.x[j]));
				}
			}
			*y = *y + (temp*pd.y[i]);
		}
	}
	return y;
}

twodpoint* fminbnd(plotdata pd)
{
	twodpoint* pt = NULL;
	if((pd.length!=0)&&(pd.x!=NULL)&&(pd.y!=NULL))
	{
		pt = malloc(sizeof(twodpoint));
		pt->yy = pd.y[0];
		pt->xx = pd.x[0];
		for(size_t i=1;i<pd.length;i++)
		{
			if(pd.y[i]<(pt->yy))
			{
				pt->yy = pd.y[i];
				pt->xx = pd.x[i];
			}
		}
	}
	return pt;
}

double* dsearchn(vector v, double x)
{
	double* vi = malloc(sizeof(double));
	double temp = fabsl(v.array[0] - x);
	for(size_t i=1;i<v.l;i++)
	{
		if(fabsl(v.array[i]-x)<temp)
		{
			temp = fabsl(v.array[i]-x);
			*vi = v.array[i];
		}
	}
	return vi;
}
