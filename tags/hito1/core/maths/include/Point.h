#ifndef __Point__
#define __Point__

#include <iostream>
using namespace std;
#include <cmath>

/**\brief Representa un punto en el espacio
 */
class Point {
	/**\brief Sobrecarga de la salida
	 * La salida sera la siguiente:
	 * 		(x,y)
	 * Siendo x e y las componentes del punto.
	 */
	friend ostream& operator<<(ostream &, const Point &);
public:

	/**\brief Contructor vacio
	 */
	Point() {
		x=0;
		y=0;
		z=0;
	}

	/**\brief Constructor para dos puntos
	 */
	Point(double X, double Y) {
		if(X < 0.000001 && X > -0.000001)
			x = 0.0;
		else
			x = X;
		if(Y < 0.000001 && Y > -0.000001)
			y = 0.0;
		else
			y = Y;
		z = 0;
	}

	/**\brief Constructor para tres puntos
	 */
	Point(double X, double Y, double Z) {
		x = X;
		y = Y;
		z = Z;
	}

	/**\brief Destructor por defecto
	 */
	virtual ~Point() {
		x = 0;
		y = 0;
		z = 0;
	}

	/**\brief Constructor de copia
	 */
	Point(const Point &p) {
		x = p.x;
		y = p.y;
		z = p.z;
	}

	/**\brief Sobrecarga del operador igualdad
	 */
	Point & operator=(const Point &p) {
		if (this != &p) {
			this->~Point();
			x = p.x;
			y = p.y;
			z = p.z;
		}
		return *this;
	}

	static Point interP(const Point &p1, const Point &p2);

	bool isInRadius(const Point &p, double radius);

	bool operator==(const Point &p);

	bool operator!=(const Point &p);

	/**\brief Obtiene la componente X
	 */
	double getX() {
		return x;
	}

	/**\brief Obtiene la componente Y
	 */
	double getY() {
		return y;
	}

	/**\brief Obtiene la componente Z
	 */
	double getZ() {
		return z;
	}

	/**\brief Modifica la componente X
	 */
	void setX(double X) {
		x = X;
	}

	/**\brief Modifica la componente Y
	 */
	void setY(double Y) {
		y = Y;
	}

	/**\brief Modifica la componente Z
	 */
	void setZ(double Z) {
		z = Z;
	}

	/**\brief Modifica las componentes X e Y
	 */
	void setXY(double X, double Y) {
		if(X < 0.001 && X > -0.001)
			x = 0.0;
		else
			x = X;
		if(Y < 0.001 && Y > -0.001)
			y = 0.0;
		else
			y = Y;
	}

	/**\brief Modifica las componentes X e Y
	 *
	 * @param X Valor X
	 * @param Y Valor Y
	 * @param Z Valor Z
	 */
	void setXYZ(double X, double Y, double Z) {
		x = X;
		y = Y;
		z = Z;
	}

	/**\brief Calcula la distancia entre los puntos p1 y p2
	 *
	 * @param p1 El primer punto
	 * @param p2 El segundo punto
	 * @return double Distancia entre esos dos puntos
	 */
	static double distance(Point p1, Point p2);

private:
	/**\brief Coordenada x del punto
	 */
	double x;

	/**\brief Coordenada y del punto
	 */
	double y;

	/**\brief Coordenada z del punto
	 */
	double z;
};

#endif
