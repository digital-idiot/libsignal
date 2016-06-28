#include "vectors.h"
#include<stdlib.h>
#include<math.h>

vector v_init(size_t len)
{
	vector v;
	v.l = 0;
	v.array = NULL;
	if(len>0)
	{
		v.l = len;
		v.array = malloc(v.l*sizeof(double));
		for(size_t i=0;i<v.l;i++)
		{
			v.array[i] = 0.0;
		}
	}
	return v;
}

vector v_decrease(vector v, double x)
{
	vector vect;
	vect.l = 0;
	vect.array = NULL;
	if((v.l!=0)&&(v.array!=NULL))
	{
		vect = v_init(v.l);
		for(size_t i=0;i<vect.l;i++)
		{
			vect.array[i] = v.array[i] - x;
		}
	}
	return vect;
}

vector v_increase(vector v, double x)
{
	vector vect;
	vect.l = 0;
	vect.array = NULL;
	if((v.l!=0)&&(v.array!=NULL))
	{
		vect = v_init(v.l);
		for(size_t i=0;i<vect.l;i++)
		{
			vect.array[i] = v.array[i] + x;
		}
	}
	return vect;
}

vector v_div(vector X, vector Y)
{
	vector v;
	v.l = 0;
	v.array = NULL;
	if((X.l!=0)&&(Y.l!=0)&&(X.array!=NULL)&&(Y.array!=NULL)&&(X.l==Y.l))
	{
		v = v_init(X.l);
		for(size_t i=0;i<v.l;i++)
		{
			v.array[i] = X.array[i] / Y.array[i];
		}
	}
	return v;
}

vector v_flipr(vector v)
{
	vector vect;
	if(v.l==0||v.array==NULL)
	{
		vect.l = 0;
		vect.array = NULL;
	}
	else
	{
		vect = v_init(v.l);
		size_t j = v.l;
		for(size_t i=0;i<vect.l;i++)
		{
			j--;
			vect.array[i] = v.array[j];
		}
	}
	return vect;
}

vector v_dotdiv(double n, vector v)
{
	vector vect;
	if((v.l!=0)&&(v.array!=NULL))
	{
		/*vect.l = v.l;
		vect.array = malloc(v.l*sizeof(double));*/
		vect = v_init(v.l);
		for(size_t i=0;i<v.l;i++)
		{
			vect.array[i] = n/v.array[i];
		}
	}
	else
	{
		vect.l = 0;
		vect.array = NULL;
	}
	return vect;
}

vector v_dotmul(double n, vector v)
{
	vector vect;
	if((v.l!=0)&&(v.array!=NULL))
	{
		/*vect.l = v.l;
		vect.array = malloc(v.l*sizeof(double));*/
		vect = v_init(v.l);
		for(size_t i=0;i<v.l;i++)
		{
			vect.array[i] = n * v.array[i];
		}
	}
	else
	{
		vect.l = 0;
		vect.array = NULL;
	}
	return vect;
}

vector v_dotsub(double n, vector v)
{
	vector vect;
	if((v.l!=0)&&(v.array!=NULL))
	{
		/*vect.l = v.l;
		vect.array = malloc(v.l*sizeof(double));*/
		vect = v_init(v.l);
		for(size_t i=0;i<v.l;i++)
		{
			vect.array[i] = n - v.array[i];
		}
	}
	else
	{
		vect.l = 0;
		vect.array = NULL;
	}
	return vect;
}

vector v_dotadd(double n, vector v)
{
	vector vect;
	if((v.l!=0)&&(v.array!=NULL))
	{
		/*vect.l = v.l;
		vect.array = malloc(v.l*sizeof(double));*/
		vect = v_init(v.l);
		for(size_t i=0;i<v.l;i++)
		{
			vect.array[i] = n + v.array[i];
		}
	}
	else
	{
		vect.l = 0;
		vect.array = NULL;
	}
	return vect;
}

vector v_dotpow(double n, vector v)
{
	vector vect;
	if((v.l!=0)&&(v.array!=NULL))
	{
		/*vect.l = v.l;
		vect.array = malloc(v.l*sizeof(double));*/
		vect = v_init(v.l);
		for(size_t i=0;i<v.l;i++)
		{
			vect.array[i] = pow(n, v.array[i]);
		}
	}
	else
	{
		vect.l = 0;
		vect.array = NULL;
	}
	return vect;
}

vector v_pow(vector v, double n)
{
	vector vect;
	if((v.l!=0)&&(v.array!=NULL))
	{
		/*vect.l = v.l;
		vect.array = malloc(v.l*sizeof(double));*/
		vect = v_init(v.l);
		for(size_t i=0;i<v.l;i++)
		{
			vect.array[i] = pow(v.array[i], n);
		}
	}
	else
	{
		vect.l = 0;
		vect.array = NULL;
	}
	return vect;
}

vector v_dot(vector a, vector b)
{
	vector c;
	if((a.l>0)&&(b.l>0)&&(a.array!=NULL)&&(b.array!=NULL)&&(a.l==b.l))
	{
		/*c.l = a.l;
		c.array = malloc(c.l*sizeof(double));*/
		c = v_init(a.l);
		for(size_t i=0;i<c.l;i++)
		{
			c.array[i] = a.array[i] * b.array[i];
		}
	}
	else
	{
		c.l = 0;
		c.array = NULL;
	}
	return c;
}

vector v_add(vector a, vector b)
{
	vector c;
	if((a.l>0)&&(b.l>0)&&(a.array!=NULL)&&(b.array!=NULL)&&(a.l==b.l))
	{
		/*c.l = a.l;
		c.array = malloc(c.l*sizeof(double));*/
		c = v_init(a.l);
		for(size_t i=0;i<c.l;i++)
		{
			c.array[i] = a.array[i] * b.array[i];
		}
	}
	else
	{
		c.l = 0;
		c.array = NULL;
	}
	return c;
}

double* v_min(vector v)
{
	double *min = NULL;
	if((v.l>0)&&(v.array!=NULL))
	{
		min = malloc(sizeof(double));
		*min = v.array[0];
		for(size_t i=1;i<v.l;i++)
		{
			if(v.array[i]<*min)
			{
				*min = v.array[i];
			}
		}
	}
	return min;
}

vector v_exp(vector v)
{
	vector vect;
	if((v.l>0)&&(v.array!=NULL))
	{
		/*vect.l = v.l;
		vect.array = malloc(vect.l*sizeof(double));*/
		vect = v_init(v.l);
		for(size_t i=0;i<vect.l;i++)
		{
			vect.array[i] = expl(v.array[i]);
		}
	}
	else
	{
		vect.l = 0;
		vect.array = NULL;
	}
	return vect;
}

vector genseries(double lo, double up, double delta)
{
	vector vect;
	vect.array = NULL;
	vect.l = 0;
	if((lo<up)&&(delta<=(up-lo)))
	{
		double temp = lo;
		while(temp<=up)
		{
			vect.array = realloc(vect.array,(vect.l+1)*sizeof(double));
			vect.array[vect.l] = temp;
			temp = temp + delta;
			vect.l++;
		}
	}
	return vect;
}
