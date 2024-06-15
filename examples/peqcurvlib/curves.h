#ifndef CURVES_H
#define CURVES_H

typedef struct Curve{
	uint16_t * out;
	uint16_t * in;
	int size_out;
	int size_in;
}Curve;

void fillCurve(Curve *, int , int ,int , int );
Curve createCircle(uint16_t, uint16_t, uint16_t,double);
Curve createEllipse(uint16_t, uint16_t, uint16_t, uint16_t, double);
#endif