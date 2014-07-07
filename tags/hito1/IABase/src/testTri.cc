#include <iostream>
#include "Triangulation.h"
#include "Point.h"

using namespace std;

int main() {
	/*
	 Point a = Point(1,1);
	 Point b = Point(3,1);
	 Point c = Point(1,3);
	 Tri triangle(a,b,c);
	 cout << "Debe dar 0: ";
	 cout << triangle.isInside(Point(1,2)) << endl;
	 cout << "Debe dar 1: ";
	 cout << triangle.isInside(Point(1.5,1.5)) << endl;
	 cout << "Debe dar -1: ";
	 cout << triangle.isInside(Point(4,4)) << endl;

	 cout << "Debe dar 0: ";
	 cout << triangle.isInside(Point(1,1)) << endl;
	 cout << "Debe dar 1: ";
	 cout << triangle.isInside(Point(1.5,2)) << endl;
	 cout << "Debe dar -1: ";
	 cout << triangle.isInside(Point(1,44)) << endl;
	 */

	std::vector<Point> puntos;

	Point p1(1, 1), p2(1, 2), p3(2, 1);

	puntos.push_back(p3);
	puntos.push_back(p1);
	puntos.push_back(p2);

	/*	int count = 1;
	 double n;

	 cout << "Punto 0: ";
	 cin >> n;
	 Point p;

	 p.setX(n);

	 cin >> n;

	 p.setY(n);

	 while(n != 0.0){
	 puntos.push_back(p);
	 cout << "Punto " << count << ": ";

	 cin >> n;
	 p.setX(n);

	 cin >> n;
	 p.setY(n);

	 count++;
	 }

	 std::vector<Point>::iterator iter;

	 cout << endl << "Los puntos son: " << endl;

	 for(iter = puntos.begin(); iter != puntos.end(); iter++){
	 cout << *iter << endl;
	 }
	 */
	Triangulation triads(p2, p3);
	triads.addPoints(puntos);

	char c;

	cin >> c;
	while (c == 'p') {
		triads.stepDelaunay();
		cin >> c;
	}

	triads.continueDelaunay();

	cout << endl << "--------------" << endl;
	cout << "Resultado:" << endl;

	std::vector<Tri *> tris = triads.finishedDelaunay();
	std::vector<Tri *>::iterator iter;

	for (iter = tris.begin(); iter != tris.end(); iter++) {
		cout << **iter << endl;
	}

	return 0;
}
