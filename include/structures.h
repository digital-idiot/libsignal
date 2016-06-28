#ifndef STRUCTURES_H_   /* Include guard */
#define STRUCTURES_H_

#include<stdio.h>

typedef struct twomat //double 2D array with its dimensions
{
	size_t m;
	size_t n;
	double **matrix;
}twodmatrix;

typedef struct vect //double 1D array with its length
{
	size_t l;
	double *array;
}vector;

typedef struct plotd //double two 1D array of same size to Store 2D data points **Note: values x of must be strictly increasing**
{
	size_t length;
	double *y;
	double *x;
}plotdata;

typedef struct pt //2D point
{
	double xx;
	double yy;
}twodpoint;

#endif
