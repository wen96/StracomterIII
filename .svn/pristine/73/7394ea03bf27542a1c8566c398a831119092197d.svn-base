/*
 * MotorFisica.h
 *
 *  Created on: 28/10/2011
 *      Author: Chutaos Team
 */

#ifndef BOX_H_
#define BOX_H_

#include <iostream>
#include <cmath>
#include <vector>

#include "Box2D/Box2D.h"
#include "Point.h"
#include "Polygon.h"

using namespace std;

/**\struct PairPoints
 * Estructura que contiene una pareja de puntos b2Vec2*/
typedef struct  {

	/**\brief Punto A*/
	b2Vec2 pA;
	/**\brief Punto B*/
	b2Vec2 pB;

}PairPoints;

/**\class Box
 * Clase que imita el objeto b2Shape de la librería Box2D*/
class Box {

	friend ostream& operator<<(ostream &, const Box &);
public:

	//--------- FORMA CANÓNICA ------------//
	/**\brief Constructor.
	 * \param v Vector de Posiciones.
	 * \param n_vertex: - Número de vértices.*/
	Box(vector<b2Vec2>, int);

	/**\brief Constructor.
	 * \param p Vector de Posiciones.
	 * \param n_vertex: - Número de vértices.*/
	Box(vector<Point>, int);

	/**\brief Constructor
	 * \param pol Polygono con la forma de la caja.
	 */
	Box(const Polygon &);

	/**\brief Constructor sobrecargado para crear círculos.
	 * \param p - Centro del círculo.
	 * \param rad - Radio del círculo.*/
	Box(b2Vec2, float);

	/**\brief Constructor sobrecargado para crear círculos.
	 * \param p - Centro del círculo.
	 * \param rad - Radio del círculo.*/
	Box(Point, float);

	/**\brief Constructor sobrecargado para crear Cadenas
	 * \param n_vertex - Número de vértices.
	 * \param v - Vértices de la cadena.*/
	Box(int, vector<b2Vec2>);

	/**\brief Constructor sobrecargado para crear Cadenas
	 * \param n_vertex - Número de vértices.
	 * \param v - Vértices de la cadena.*/
	Box(int, vector<Point>);

	/**\brief Constructor de Copia.
	 * \param b - Caja a copiar.*/
	Box(const Box &);

	/**\brief Operador de asignación.
	 * \param b - Caja a asignar.
	 * \return Devuelve la caja con la nueva información.*/
	 Box& operator=(const Box &);

	/**\brief Destructor*/
	virtual ~Box();

	//--------- SETTERS/GETTERS ------------//
	/**\brief Asigna el radio del objeto Box.
	 * \param rad - float con el nuevo valor del radio.*/
	void setRadio(float rad) {
		if(rad >= 0)
			box->m_radius = rad;
	}

	/**\brief Devuelve el radio del objeto Box.
	 * \return Devuelve el radio del objeto Box.*/
	float getRadio(void) const {
		return box->m_radius;
	}

	/**\brief Devuelve el Type del objeto.
	 * Círculo:0; Línea:1; Polygono:2; Cadena:3;
	 * \return Devuelve el Type del objeto.*/
	int getType(void) const {
		return box->m_type;
	}
	/**\brief Devuelve el Shape del objeto.
	 * \return Devuelve el Shape del objeto (la caja física).*/
	const b2Shape * getShape() {
		return box;
	}

private:
	/**\brief It's the Box used for collisions*/
	b2Shape *box;
};

/**\brief Convierte un vecto de Points a un vector de b2Vec2
 * \param v Vecto de Points a convertir
 * \return Devuelve el vector de b2Vec2
 */
vector<b2Vec2> Point2b2Vec2(vector<Point>);
/**\brief Convierte objeto Point a un objeto b2Vec2
 * \param p Point a convertir.
 * \return Devuelve el punto b2Vec2.
 */
b2Vec2 Point2b2Vec2(Point);

/**\brief Convierte objeto b2Vec2 a un objeto Point
 * \param p v2Vec2 a convertir.
 * \return Devuelve el punto Point.
 */
Point b2Vec22Point(b2Vec2);
#endif /* Box_H_ */
