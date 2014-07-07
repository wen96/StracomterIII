/*
 * Tri.cc
 *
 *  Created on: Nov 27, 2011
 *      Author: rellik
 */

#include "Tri.h"

ostream&
operator<<(ostream &os, const Tri &t) {

	os << "[" << t.getA() << "," << t.getB() << "," << t.getC() << "]";

	return os;
}

Tri::Tri(){
	ab = NULL;
	bc = NULL;
	ca = NULL;
}

Tri::~Tri(){
	a = Point();
	b = Point();
	c = Point();
	ab = NULL;
	bc = NULL;
	ca = NULL;
}

Tri::Tri(const Tri &t){
	a = t.a;
	b = t.b;
	c = t.c;
	ab = NULL;
	bc = NULL;
	ca = NULL;
}

Tri::Tri(Point A, Point B, Point C) {
	a = A;
	b = B;
	c = C;
	ab = NULL;
	bc = NULL;
	ca = NULL;
}

Tri::Tri(Point A, Point B, Point C, Tri *AB, Tri *BC, Tri *CA) {
	a = A;
	b = B;
	c = C;
	ab = AB;
	bc = BC;
	ca = CA;
}

void Tri::setTris(Tri *AB, Tri *BC, Tri *CA) {
	ab = AB;
	bc = BC;
	ca = CA;
}

bool Tri::liesInside(Point i, Point j, Point k, Point l) {
	bool estaDentro = false;

	Tri t(i, j, k);

	t.makeCounterClockwise();

	/*
	 * Calculamos el siguiente determinante
	 *
	 * | (t.a.x - l.x),		(t.a.y - l.y),		(t.a.x*t.a.x - l.x*l.x) + (t.a.y*t.a.y - l.y*l.y) |
	 * | (t.b.x - l.x),		(t.b.y - l.y),		(t.b.x*t.b.x - l.x*l.x) + (t.b.y*t.b.y - l.y*l.y) |
	 * | (t.c.x - l.x),		(t.c.y - l.y),		(t.c.x*t.c.x - l.x*l.x) + (t.c.y*t.c.y - l.y*l.y) |
	 *
	 * Si es > 0 l esta dentro del circulo formado por ijk.
	 */

	Matrix<double> mat(3, 3);

	mat(1, 1) = t.a.getX() - l.getX();
	mat(1, 2) = t.a.getY() - l.getY();
	mat(1, 3) = (t.a.getX() * t.a.getX() - l.getX() * l.getX())
					+ (t.a.getY() * t.a.getY() - l.getY() * l.getY());

	mat(2, 1) = t.b.getX() - l.getX();
	mat(2, 2) = t.b.getY() - l.getY();
	mat(2, 3) = (t.b.getX() * t.b.getX() - l.getX() * l.getX())
					+ (t.b.getY() * t.b.getY() - l.getY() * l.getY());

	mat(3, 1) = t.c.getX() - l.getX();
	mat(3, 2) = t.c.getY() - l.getY();
	mat(3, 3) = (t.c.getX() * t.c.getX() - l.getX() * l.getX())
					+ (t.c.getY() * t.c.getY() - l.getY() * l.getY());

	estaDentro = mat.determinant() > 0.0;

	return estaDentro;
}

void Tri::swapP(Tri *t1, Tri *t2) {
	if (ab != NULL && t1 == ab) {
		ab = t2;
	} else if (bc != NULL && t1 == bc) {
		bc = t2;
	} else if (ca != NULL && t1 == ca) {
		ca = t2;
	}
}

Point Tri::getBaricenter(){

	double newX = a.getX() + b.getX() + c.getX();
	newX /= 3;

	double newY = a.getY() + b.getY() + c.getY();
	newY /= 3;

	Point p(newX, newY);

	return p;
}

Point Tri::getIncenter(){

	double abL = Point::distance(a,b);
	double bcL = Point::distance(b,c);
	double caL = Point::distance(c,a);

	double p = abL + bcL + caL;

	double newX = a.getX()*bcL + b.getX()*caL + c.getX()*abL;
	newX /= p;

	double newY = a.getY()*bcL + b.getY()*caL + c.getY()*abL;
	newY /= p;

	Point incenter(newX, newY);

	return incenter;
}

void Tri::updateEdges(Tri *_ab, Tri *_bc, Tri *_ca) {
	if (ab != NULL)
		ab->swapP(this, _ab);

	if (bc != NULL)
		bc->swapP(this, _bc);

	if (ca != NULL)
		ca->swapP(this, _ca);
}

Point Tri::opositeP(int caso) {

	Point resul;
	Point i, j;
	Tri *opuT;

	switch (caso) {
	case 0:
		opuT = ab;
		i = a;
		j = b;
		break;
	case 1:
		opuT = bc;
		i = b;
		j = c;
		break;
	case 2:
		opuT = ca;
		i = c;
		j = a;
		break;
	}

	if (i == opuT->a) {
		if (j == opuT->b) {
			resul = opuT->c;
		} else {
			resul = opuT->b;
		}
	} else if (i == opuT->b) {
		if (j == opuT->a) {
			resul = opuT->c;
		} else {
			resul = opuT->a;
		}
	} else {
		if (j == opuT->a) {
			resul = opuT->b;
		} else {
			resul = opuT->a;
		}
	}

	return resul;
}

Point Tri::opositeP(Tri *op) {
	Point res;

	if (ab == op)
		res = c;
	else if (bc == op)
		res = a;
	else
		res = b;

	return res;
}

void Tri::makeCounterClockwise() {
	double dx1, dx2, dy1, dy2;
	double o;

	dx1 = b.getX() - a.getX();
	dy1 = b.getY() - a.getY();
	dx2 = c.getX() - a.getX();
	dy2 = c.getY() - a.getY();
	o = (dx1 * dy2) - (dy1 * dx2);

	if (o < 0.0) {
		Point p = b;
		b = c;
		c = p;
	}
}

bool Tri::isCounterClockwise(){
	double dx1, dx2, dy1, dy2;
	double o;

	dx1 = b.getX() - a.getX();
	dy1 = b.getY() - a.getY();
	dx2 = c.getX() - a.getX();
	dy2 = c.getY() - a.getY();
	o = (dx1 * dy2) - (dy1 * dx2);

	return o < 0.0;
}

std::vector<Tri *> Tri::opositeT(Tri *op) {
	std::vector<Tri *> resul;

	if (op == ab) {
		resul.push_back(bc);
		resul.push_back(ca);
	} else if (op == bc) {
		resul.push_back(ca);
		resul.push_back(ab);
	} else {
		resul.push_back(ab);
		resul.push_back(bc);
	}

	return resul;
}

Point Tri::getA() const {
	return a;
}

Tri *Tri::getAb() const {
	return ab;
}

Point Tri::getB() const {
	return b;
}

Tri *Tri::getBc() const {
	return bc;
}

Point Tri::getC() const {
	return c;
}

Tri *Tri::getCa() const {
	return ca;
}

void Tri::setA(Point a) {
	this->a = a;
}

void Tri::setAb(Tri *ab) {
	this->ab = ab;
}

void Tri::setB(Point b) {
	this->b = b;
}

void Tri::setBc(Tri *bc) {
	this->bc = bc;
}

void Tri::setC(Point c) {
	this->c = c;
}

void Tri::setCa(Tri *ca) {
	this->ca = ca;
}

int Tri::isInside(Point p) {
	/*-1 si esta fuera
	 * 1 si esta dentro
	 * 0 si esta en una linea
	 * -2 si ha habido algun error*/
	int isInsideTri = -2;
	int sideVectora = -3, sideVectorb = -3, sideVectorc = -3;

	sideVectora = side(a, b, p);
	sideVectorb = side(b, c, p);
	sideVectorc = side(c, a, p);
	if (sideVectora == 0.0 || sideVectorb == 0.0 || sideVectorc == 0.0) { //en algun vector
		if (sideVectora == 0
				&& ((sideVectorb == 1 && sideVectorc == 1)
						|| (sideVectorb == -1 && sideVectorc == -1))) {
			isInsideTri = 0;
		} else if (sideVectorb == 0
				&& ((sideVectora == 1 && sideVectorc == 1)
						|| (sideVectora == -1 && sideVectorc == -1))) {
			isInsideTri = 0;
		} else if (sideVectorc == 0
				&& ((sideVectora == 1 && sideVectorb == 1)
						|| (sideVectora == -1 && sideVectorb == -1))) {
			isInsideTri = 0;
		} else if ((sideVectora == 0 && sideVectorb == 0)
				|| (sideVectorb == 0 && sideVectorc == 0)
				|| (sideVectorc == 0 && sideVectora == 0)) {
			isInsideTri = 0;
		} else {
			isInsideTri = -1;
		}
	} else if (sideVectora == 1.0 && sideVectorb == 1.0 && sideVectorc == 1.0) { //sentido horario
		isInsideTri = 1;
	} else if (sideVectora == -1.0 && sideVectorb == -1.0
			&& sideVectorc == -1.0) { //sentido antihorario
		isInsideTri = 1;
	} else { //fuera
		isInsideTri = -1;
	}

	return isInsideTri;
}

int Tri::side(Point p1,Point p2, Point ps) {
	double dx1, dx2, dy1, dy2;
	double o;

	dx1 = p2.getX() - p1.getX();
	dy1 = p2.getY() - p1.getY();
	dx2 = ps.getX() - p1.getX();
	dy2 = ps.getY() - p1.getY();
	o = (dx1 * dy2) - (dy1 * dx2);
	if (o > 0.001)
		return (-1); //LEFT SIDE
	if (o < -0.001)
		return (1); //RIGHT SIDE
	return (0); //COLINEAR
}


