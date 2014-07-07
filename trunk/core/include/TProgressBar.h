/*
 * TProgressBar.h
 *
 *  Created on: Apr 5, 2012
 *      Author: Chutaos Team
 */

#ifndef TPROGRESSBAR_H_
#define TPROGRESSBAR_H_

#include "Point.h"
#include "Shape.h"

/**\class TProgressBar
 * Simula una barra de progreso
 */
class TProgressBar{
public:
	TProgressBar();
	~TProgressBar();
	TProgressBar(const TProgressBar &tpb);
	TProgressBar & operator=(const TProgressBar &tpb);

	TProgressBar(Point p, int w, double h);

	void setPercentage(double p);
	void setWidth(double w);
	void setHeight(double h);
	void setPos(Point p);

	void exportOpenGL();

private:
	void Copy(const TProgressBar &tpb);
	void makeShapes();

	double percentage;

	double width;
	double height;
	Point pos;

	Shape *background;
	Shape *foreground;
	Shape *border;
};


#endif /* TPROGRESSBAR_H_ */
