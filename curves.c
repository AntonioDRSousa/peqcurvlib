#include<stdio.h>
#include<stdint.h>

#include<stdlib.h>
#include<math.h>

#include "curves.h"

const double PI = 3.14159265358979323851;
const double E  = 2.718281828459045;

/*
	The Curve is a set of points (x,y).
	We can represent in C with as a 'struct',
	but there's a cheap option: represent in only one array.
	That's it, in order: all even numbers are value of x coordinate,
	in next number(odd number) we represent the y value.
	For example, points {(1,5),(9,4),(0,1)} the array is :
	[1,5,9,4,0,1].
	This made work with  this struct more simple and with more performance.

	A simple manner for represent a curve in mathmatic is parametric equation.
	In this equation, we represent a curve in a equation with only 1 variable 
	called 't', in a define interval from 'a' to 'b'. 
	This useful because we can define a curve with a simple for loop.
	
	The precision can draw curve more better, but are reduce performance.
	
	You must declare a pointer of double for represent curve and pass enderece as argument of functions.
	The creation of curve allocate array of points of curve.
	You can use this array in a loop for drawing, using even numbers for x and odd numbers for y.
*/

void flood_fill(char ** mat,int x,int y,char target,char replacement,int * count){
	if((mat[x][y]==replacement)||(mat[x][y]!=target)){
		return;
	}
	(*count)+=2;
    mat[x][y]=replacement;
    flood_fill(mat,x,y-1,target,replacement,count);
    flood_fill(mat,x,y+1,target,replacement,count);
    flood_fill(mat,x-1,y,target,replacement,count);
    flood_fill(mat,x+1,y,target,replacement,count);
}

void fillCurve(Curve * crv, int x, int y, int height, int width) {
	register int i,j,k = 0;
	
	char ** mat = (char **) calloc(height,sizeof(char*));
	for(i=0;i<height;i++){
		mat[i] = (char *) calloc(width,sizeof(char));
		for(j=0;j<width;j++){
			mat[i][j]=' ';
		}
	}

	for(i = 0; i < crv->size_out; i+=2) {
        mat[(crv->out)[i]][(crv->out)[i+1]] = 'x';
    }
	
	flood_fill(mat,x,y,' ','o',&(crv->size_in));
	crv->in = (uint16_t *) calloc(crv->size_in,sizeof(uint16_t));

	for(i=0;i<height;i++){
		for(j=0;j<width;j++){
			if(mat[i][j]=='o'){
				(crv->in)[k] = (uint16_t) i;
				(crv->in)[k+1] = (uint16_t) j;
				k+=2;
			}
		}
	}
}

Curve initCurve(double a, double b, double precision){
	Curve crv;
	crv.in = NULL;
	crv.size_out = (int) 2*ceil((b-a)/precision);
	crv.size_in = 0;
	crv.out = (uint16_t *) calloc(crv.size_out,sizeof(uint16_t));
	return crv;
}

/*
	functions for create curves
*/

Curve createEllipse(uint16_t a, uint16_t b, uint16_t rx, uint16_t ry, double precision) {
	register double tmin = 0;
	register double tmax = 2*PI;

	Curve crv = initCurve(tmin,tmax,precision);
	
	register double t; register int i;
    for(t=tmin, i=0; t <= tmax; t+=precision,i+=2) {
		(crv.out)[i]   = a + rx*cos(t);
		(crv.out)[i+1] = b + ry*sin(t);
    }
	
	return crv;
}

Curve createCircle(uint16_t a, uint16_t b, uint16_t r, double precision) {
	return createEllipse(a, b, r, r, precision);
}
