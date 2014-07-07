#include "Polygon.h"

Polygon::Polygon(int n, Point center, double radius, double ang) {
	if (n >= 3 && radius >= 0) {
		n_vertices = n;
		puntos = new Point[n_vertices];

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
		puntos = new Point[n_vertices];
		type = POL_CIRCLE;
		generatePoints();
	}
}

Polygon::Polygon(Point center, std::vector<Point> vPuntos){
	centro = center;
	n_vertices = vPuntos.size();
	puntos = new Point[n_vertices];
	for(int i = 0; i < n_vertices; i++){
		puntos[i].setXY(vPuntos[i].getX() + center.getX(), vPuntos[i].getY() + center.getY());
	}
	radio = 0;

	if(n_vertices == 2)
		type = POL_EDGE;
	else if(n_vertices >= 3 && n_vertices <= 8)
		type = POL_POLYGON;
	else if(n_vertices > 8)
		type = POL_CIRCLE;
}


Polygon::Polygon(std::vector<Point> vPuntos){

	n_vertices = vPuntos.size();
	puntos = new Point[n_vertices];
	/*if(n_vertices > 0)
		centro = vPuntos[0];*/ //Aqui estaba todo el fallo. Culpa mia, lo siento...
	centro = Point(0,0);
	for(int i = 0; i < n_vertices; i++){
		puntos[i].setXY(vPuntos[i].getX() + centro.getX(), vPuntos[i].getY() + centro.getY());
	}
	radio = 0;

	type= POL_CHAIN;
}

Polygon::Polygon(Point a, Point b) {
	centro = a;
	n_vertices = 2;
	puntos = new Point[n_vertices];
	puntos[0] = a;
	puntos[1] = b;
	radio = 0;
	type = POL_EDGE;
}
Polygon::Polygon(const Polygon &poly) {

	n_vertices = poly.n_vertices;
	centro = poly.centro;
	puntos = new Point[n_vertices];

	for (int i = 0; i < n_vertices; i++) {
		puntos[i].setXY(poly.puntos[i].getX(), poly.puntos[i].getY());
	}

	radio = poly.radio;
	angulo = poly.angulo;
	type = poly.type;
}

Polygon &
Polygon::operator =(const Polygon & poly) {
	if (this != &poly) {
		this->~Polygon();

		n_vertices = poly.n_vertices;
		centro = poly.centro;
		puntos = new Point[n_vertices];

		for (int i = 0; i < n_vertices; i++) {
			puntos[i] = poly.puntos[i];
		}

		radio = poly.radio;
		angulo = poly.angulo;
		type = poly.type;
	}
	return *this;
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

	double x,y;
	double x0,y0;
	x0 = centro.getX();
	y0 = centro.getY();
	double angle = (double) 360/ (double) n_vertices;

	for (int i = 0; i < n_vertices; i++) {
		x = x0 + (cos(angle*M_PI/180*i) * radio);
		y = y0 + (sin(angle*M_PI/180*i) * radio);
		puntos[i].setXY(x, y);
	}


}

int
Polygon::getType() const{
	return type;
}

ostream&
operator<<(ostream &os, const Polygon &poli) {
	if (poli.puntos != NULL) {
		for (int i = 0; i < poli.n_vertices; i++) {
			os << poli.puntos[i];
		}
	}
	return os;
}
