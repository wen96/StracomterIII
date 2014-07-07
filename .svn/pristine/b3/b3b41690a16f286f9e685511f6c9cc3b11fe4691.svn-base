#include "Polygon.h"
#include "LineEquation.h"


Polygon::Polygon(int n, Point center, double radius, double ang) {
	if (n >= 3 && radius >= 0) {
		n_vertices = n;

		radio = radius;
		centro = center;
		angulo = ang;
		type = POL_POLYGON;
		generatePoints();
	}
}

Polygon::Polygon(Point center, double radius) {
	if (radius >= 0) {
		centro = center;
		radio = radius;
		n_vertices = 300;
		type = POL_CIRCLE;
		generatePoints();
	}
}

Polygon::Polygon(Point center, std::vector<Point> vPuntos) {
	centro = center;
	n_vertices = vPuntos.size();
	for (int i = 0; i < n_vertices; i++) {
		puntos.push_back(
				Point(vPuntos[i].getX() + center.getX(),
						vPuntos[i].getY() + center.getY()));
	}
	radio = 0;

	if (n_vertices == 2)
		type = POL_EDGE;
	else if (n_vertices >= 3 && n_vertices <= 8)
		type = POL_POLYGON;
	else if (n_vertices > 8)
		type = POL_CIRCLE;
}

Polygon::Polygon(std::vector<Point> vPuntos) {

	n_vertices = vPuntos.size();
	puntos = vPuntos;
	centro = Point(0, 0);
	radio = 0;

	type = POL_CHAIN;
}

Polygon::Polygon(Point a, Point b) {
	centro = a;
	n_vertices = 2;
	puntos.push_back(a);
	puntos.push_back(b);
	radio = 0;
	type = POL_EDGE;
}
Polygon::Polygon(const Polygon &poly) {

	n_vertices = poly.n_vertices;
	centro = poly.centro;
	puntos = poly.puntos;
	radio = poly.radio;
	angulo = poly.angulo;
	type = poly.type;
}

Polygon::~Polygon() {
	puntos.clear();
	n_vertices = 0;
	centro = Point(0, 0);
	angulo = 0;
	radio = 0;
	type = POL_NONE;
}

Polygon &
Polygon::operator =(const Polygon & poly) {
	if (this != &poly) {
		//this->~Polygon();

		n_vertices = poly.n_vertices;
		centro = poly.centro;
		puntos = poly.puntos;
		radio = poly.radio;
		angulo = poly.angulo;
		type = poly.type;
	}
	return *this;
}

void Polygon::setType(int type) {
	this->type = type;
}

void Polygon::generatePoints() {
	/*
	 * desp es el desplazamiento de cada punto con respecto al grado 0. Cada punto sera el angulo
	 * inicial mas i veces el numero de grados entre dos vertices en un poligono con n_vertices lados.
	 *
	 * Las siguietes dos lineas calculan los puntos x e y. Como sin calcula a partir de radianes, no grados,
	 * hay que convertir desp (que esta en grados) a radianes. Esto se hace multiplicando por PI/180.*/

	/*for (int i = 0; i < n_vertices; i++) {
	 double desp = (angulo + ((double) 360 / n_vertices) * i);
	 double x = centro.getX() + radio * (sin(desp * (M_PI / 180)));
	 double y = centro.getY() + radio * (-cos(desp * (M_PI / 180)));


	 puntos[i].setXY(x, y);
	 }*/

	double x, y;
	double x0, y0;
	x0 = centro.getX();
	y0 = centro.getY();
	double angle = (double) 360 / (double) n_vertices;

	for (int i = 0; i < n_vertices; i++) {
		x = x0 + (cos(angle * M_PI / 180 * i) * radio);
		y = y0 + (sin(angle * M_PI / 180 * i) * radio);
		puntos.push_back(Point(x, y));
	}

}

int Polygon::getType() const {
	return type;
}

ostream&
operator<<(ostream &os, const Polygon &poli) {
	if (!poli.puntos.empty()) {
		for (int i = 0; i < poli.n_vertices; i++) {
			os << poli.puntos[i];
		}
	}
	return os;
}

bool Polygon::isConvex() const {
	bool convex = true;

	if (puntos.size() >= 3) {

		vector<Point> pAux = puntos;
		pAux.push_back(puntos[0]);
		pAux.push_back(puntos[1]);

		Vector2D v01(puntos[0], puntos[1]);
		Vector2D v02(puntos[1], puntos[2]);

		v01.Normalize();
		v02.Normalize();

		bool negativo = v01.crossProduct(v02) < 0;

		for (unsigned int i = 1; i < puntos.size(); i++) {
			Vector2D v1(pAux[i], pAux[i + 1]);
			Vector2D v2(pAux[i + 1], pAux[i + 2]);

			v1.Normalize();
			v2.Normalize();

			double dotP = v1.crossProduct(v2);
			if ((dotP < 0) != negativo) {
				convex = false;
			}
		}
	} else {
		convex = false;
	}

	return convex;
}

bool Polygon::isClockwise() const {
	bool clockwise = false;

	if (isConvex()) {
		Vector2D v1(puntos[0], puntos[1]);
		Vector2D v2(puntos[1], puntos[2]);

		clockwise = v1.crossProduct(v2) >= 0;
	}

	return clockwise;
}

void Polygon::Reverse() {
	vector<Point>::iterator iter;
	vector<Point> vAux;

	for (iter = puntos.end() - 1; iter != puntos.begin() - 1; iter--) {
		vAux.push_back(*iter);
	}

	puntos = vAux;
}

void Polygon::makeConvexHull() {

	vector<Point> result;

	if (puntos.size() >= 4) {
		Point leftMostPoint = puntos[0];
		vector<Point>::iterator iter;
		for (iter = puntos.begin() + 1; iter != puntos.end(); iter++) {
			if ((*iter).getX() < leftMostPoint.getX()
					|| ((*iter).getX() == leftMostPoint.getX()
							&& (*iter).getY() < leftMostPoint.getY())) {
				leftMostPoint = *iter;
			}
		}

		Point current = leftMostPoint;
		int leftMostInt;
		do {
			result.insert(result.begin(),current);
			if (current == puntos[0])
				leftMostInt = 1;
			else
				leftMostInt = 0;

			for (unsigned int i = leftMostInt + 1; i < puntos.size(); i++) {
				Vector2D v1(current, puntos[leftMostInt]);
				Vector2D v2(current, puntos[i]);

				if (v1.crossProduct(v2) > 0) {
					leftMostInt = i;
				}
			}
			current = puntos[leftMostInt];
		} while (current != result.back());

		puntos = result;
		n_vertices = puntos.size();
	}
}

void Polygon::removeColinear(){

	if(puntos.size() >= 3){

		vector<Point>::iterator pIter = puntos.begin();
		while(pIter != puntos.end() -2){
			if(pIter == puntos.end() -1){
				if(Point::Colinear(*pIter, puntos[0], puntos[1], 0.001)){
					puntos.erase(puntos.begin());
					n_vertices--;
				}
				break;
			}else if(Point::Colinear(*pIter, *(pIter + 1), *(pIter+2), 0.001)){
				puntos.erase(pIter+1);
				n_vertices--;
			}else{
				pIter++;
			}
		}
	}
}

Point Polygon::getNewPoint(Point A, Point B, Point C, bool dextrogiro,
		double distance) {

	Point p;

	equ f1(A, B);
	equ f2(B, C);

	Vector2D v1(A, B);

	if (dextrogiro)
		v1.perpCCW();
	else
		v1.perpCW();

	v1.Normalize();
	v1 *= distance;
	f1.Move(v1);

	Vector2D v2(B, C);

	if (dextrogiro)
		v2.perpCCW();
	else
		v2.perpCW();

	v2.Normalize();
	v2 *= distance;
	f2.Move(v2);

	p = f1.Intersection(f2);

	return p;
}

////// GPC ////////

void Polygon::toGPC(gpc_polygon *gpcPoly) {

	// Reservamos memoria para el poligono
	gpcPoly->num_contours = 1;
	gpcPoly->hole = (int*) malloc(sizeof(int));
	gpcPoly->contour = (gpc_vertex_list*) malloc(sizeof(gpc_vertex_list));

	gpcPoly->contour[0].num_vertices = this->n_vertices;
	gpcPoly->hole[0] = 0;
	gpcPoly->contour[0].vertex = (gpc_vertex*) malloc(
			this->n_vertices * sizeof(gpc_vertex));
	for (int i = 0; i < this->n_vertices; i++) {
		gpcPoly->contour[0].vertex[i].x = puntos[i].getX();
		gpcPoly->contour[0].vertex[i].y = puntos[i].getY();
	}
}

void Polygon::fromGPC(gpc_polygon *gpcPoly) {

	puntos.clear();
	n_vertices = gpcPoly->contour[0].num_vertices;

	for (int i = 0; i < this->n_vertices; i++) {
		puntos.push_back(
				Point(gpcPoly->contour[0].vertex[i].x,
						gpcPoly->contour[0].vertex[i].y));
	}
}

vector<vector<Point> > Polygon::getTriStrip() {
	vector<vector<Point> > triStrip;

	if (this->n_vertices >= 3) {

		gpc_polygon ori;
		this->toGPC(&ori);

		gpc_tristrip result;
		gpc_polygon_to_tristrip(&ori, &result);

		for (int i = 0; i < result.num_strips; i++) {
			vector<Point> vP;
			for (int j = 0; j < result.strip[i].num_vertices; j++) {
				vP.push_back(
						Point(result.strip[i].vertex[j].x,
								result.strip[i].vertex[j].y));
			}
			if (!vP.empty()) {
				triStrip.push_back(vP);
			}
		}

		gpc_free_polygon(&ori);
		gpc_free_tristrip(&result);
	}

	return triStrip;
}

void Polygon::Join(Polygon pol) {

	gpc_polygon ori1, ori2, destino;

	this->toGPC(&ori1);
	pol.toGPC(&ori2);

	gpc_polygon_clip(GPC_UNION, &ori1, &ori2, &destino);

	this->fromGPC(&destino);

	gpc_free_polygon(&ori1);
	gpc_free_polygon(&ori2);
	gpc_free_polygon(&destino);
}

void Polygon::Diff(Polygon pol) {

	gpc_polygon ori1, ori2, destino;

	this->toGPC(&ori1);
	pol.toGPC(&ori2);

	gpc_polygon_clip(GPC_DIFF, &ori1, &ori2, &destino);

	this->fromGPC(&destino);

	gpc_free_polygon(&ori1);
	gpc_free_polygon(&ori2);
	gpc_free_polygon(&destino);
}

vector<vector<Point> > Polygon::DiffToTriStrips(Polygon pol) {
	vector<vector<Point> > triStrip;

	if (this->n_vertices >= 3) {

		gpc_polygon ori, dif;
		this->toGPC(&ori);
		pol.toGPC(&dif);

		gpc_tristrip result;
		gpc_tristrip_clip(GPC_DIFF, &ori, &dif, &result);

		for (int i = 0; i < result.num_strips; i++) {
			vector<Point> vP;
			for (int j = 0; j < result.strip[i].num_vertices; j++) {
				vP.push_back(Point(result.strip[i].vertex[j].x, result.strip[i].vertex[j].y));
			}
			if (!vP.empty()) {
				triStrip.push_back(vP);
			}
		}

		gpc_free_polygon(&ori);
		gpc_free_polygon(&dif);
		gpc_free_tristrip(&result);
	}

	return triStrip;
}

void Polygon::Inter(Polygon pol) {

	gpc_polygon ori1, ori2, destino;

	this->toGPC(&ori1);
	pol.toGPC(&ori2);

	gpc_polygon_clip(GPC_INT, &ori1, &ori2, &destino);

	this->fromGPC(&destino);

	gpc_free_polygon(&ori1);
	gpc_free_polygon(&ori2);
	gpc_free_polygon(&destino);
}

int Polygon::getVertices() const
{
    return n_vertices;
}

void Polygon::setAngulo(double angulo)
{
    this->angulo = angulo;
}

void Polygon::setCentro(Point centro)
{
    this->centro = centro;
}

void Polygon::setPuntos(vector<Point> puntos)
{
    this->puntos = puntos;
}

void Polygon::setRadio(double radio)
{
    this->radio = radio;
}

void Polygon::setVertices(int vertices)
{
    n_vertices = vertices;
}


