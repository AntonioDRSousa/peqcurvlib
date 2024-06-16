#ifndef CURVES_H
#define CURVES_H

typedef struct Curve{
	int16_t * out;
	int16_t * in;
	int size_out;
	int size_in;
}Curve;

void fillCurve(Curve *, int , int ,int , int );
void moveCurve(Curve *, int, int);
Curve createCircle(int16_t, int16_t, int16_t,double);
Curve createEllipse(int16_t, int16_t, int16_t, int16_t, double);
#endif