/*
 * TProgressBar.cc
 *
 *  Created on: Apr 5, 2012
 *      Author: Chutaos Team
 */

#include "TProgressBar.h"

TProgressBar::TProgressBar() {
	percentage = 0.0;

	width = 0;
	height = 0;
	pos = Point();

	background = new Shape(Color<float>(0.13, 0.13, 0.13));
	foreground = new Shape(Color<float>(0.49, 0.99, 0.0));
	border = new Shape(Color<float>(0.0, 0.0, 0.0));
	border->setRelleno(false);
}

TProgressBar::~TProgressBar() {

	percentage = 0.0;

	width = 0;
	height = 0;
	pos = Point();

	if(background != NULL){
		delete background;
		background = NULL;
	}

	if(foreground != NULL){
		delete foreground;
		foreground = NULL;
	}

	if(border != NULL){
		delete border;
		border = NULL;
	}
}

TProgressBar::TProgressBar(const TProgressBar & tpb) {

	this->Copy(tpb);
}

TProgressBar & TProgressBar::operator =(const TProgressBar & tpb) {

	if (this != &tpb) {
		this->Copy(tpb);
	}
	return *this;
}

void TProgressBar::Copy(const TProgressBar & tpb) {
	percentage = tpb.percentage;

	width = tpb.width;
	height = tpb.height;
	pos = tpb.pos;

	background = new Shape(*tpb.background);
	foreground = new Shape(*tpb.foreground);
	border = new Shape(*tpb.border);
}

TProgressBar::TProgressBar(Point p, int w, double h) {
	percentage = 0.0;

	if (w >= 0)
		width = w;
	else
		width = 0;

	if (h >= 0)
		height = h;
	else
		height = 0;

	pos = p;

	background = new Shape(Color<float>(0.13, 0.13, 0.13));
	foreground = new Shape(Color<float>(0.49, 0.99, 0.0));
	border = new Shape(Color<float>(0.0, 0.0, 0.0));
	border->setRelleno(false);

	makeShapes();
}

void TProgressBar::setPercentage(double p) {
	if (p < 0.0)
		p = 0.0;
	else if (p > 1.0)
		p = 1.0;

	percentage = p;

	makeShapes();
}

void TProgressBar::setWidth(double w) {
	if (w >= 0) {
		width = w;
		makeShapes();
	}
}

void TProgressBar::setHeight(double h) {
	if (h >= 0) {
		height = h;
		makeShapes();
	}
}

void TProgressBar::setPos(Point p) {
	pos = p;
}

void TProgressBar::exportOpenGL() {
	if(width > 0 && height > 0){
		background->exportOpenGL();
		foreground->exportOpenGL();
		border->exportOpenGL();
	}
}

void TProgressBar::makeShapes(){

	// Junto con pos, los puntos del rectangulo exterior
	Point p1(pos.getX(), pos.getY() + height);
	Point p2(p1.getX() + width, p1.getY());
	Point p3(p2.getX(), pos.getY());

	// Extremo del rectangulo interior
	Point p4(p1.getX() + width * percentage, p1.getY());
	Point p5(pos.getX() + width * percentage, pos.getY());

	vector<Point> vecP;
	vecP.push_back(pos);
	vecP.push_back(p1);
	vecP.push_back(p2);
	vecP.push_back(p3);

	border->setShape(Polygon(vecP));
	background->setShape(Polygon(Point(), vecP));

	vecP.pop_back();
	vecP.pop_back();
	vecP.push_back(p4);
	vecP.push_back(p5);

	foreground->setShape(Polygon(Point(), vecP));
}
