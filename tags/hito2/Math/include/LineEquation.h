/*
 * LineEquation.h
 *
 *  Created on: Mar 5, 2012
 *      Author: rellik
 */

#ifndef LINEEQUATION_H_
#define LINEEQUATION_H_

#include "Point.h"
#include "Vector2D.h"

struct equ{
	double m;
	double b;
	bool vertical;

	equ(Point a, Point b);
	equ(const equ& e);
	equ & operator=(const equ &e);
	~equ();

	double operator()(const double x);

	void Move(const Vector2D vec);
	Point Intersection(equ &e) const;
	bool Horizontal();
	bool Vertical();
};

#endif /* LINEEQUATION_H_ */
