#ifndef __Polygon__
#define __Polygon__

#include <iostream>
using namespace std;

#include <cstdlib>

#include "Point.h"
#include <cmath>
#include <vector>

const int POL_NONE = -1;
const int POL_POLYGON = 0;
const int POL_CIRCLE = 1;
const int POL_EDGE = 2;
const int POL_CHAIN = 3;

/**\name Clase Polygon
 *\brief Representa un poligono.
 */
class Polygon{
	/**\brief Sobrecarga de la salida
	 * La salida será la siguiente:
	 * 		p1p2p3p4
	 * Siendo p1, p2, p3 y p4 los puntos del poligono.
	 */
	friend ostream& operator<<(ostream &, const Polygon &);
public:

	/**\brief Constructor vacio
	 */
	Polygon(){
		n_vertices = 0;
		puntos = NULL;
		centro = Point(0,0);
		radio = 0;
		angulo = 0;
		type = POL_NONE;
	}

	/**\brief Constructor por defecto
	 *\param n Numero de lados
	 *\param center punto central del poligono
	 *\param radius radio dle poligono
	 *\param ang angulo de desplazamiento
	 */
	Polygon(int n, Point center, double radius, double ang);

	/**\brief Sobrecarga del constructor para crear circulos
	 *\param center centro del circulo
	 *\param radius radio del circulo
	 */
	Polygon(Point center, double radius);

	Polygon(Point center, std::vector<Point> vPuntos);
	Polygon(Point, Point);

	Polygon(std::vector<Point> vPuntos);

	/**\brief Destructor por defecto
	 */
	virtual ~Polygon(){
		if(puntos != NULL){
			delete [] puntos;
			puntos = NULL;
		}
		n_vertices = 0;
		centro = Point(0,0);
		angulo = 0;
		radio = 0;
		type = POL_NONE;
	}

	/**\brief Constructor de copia
	 *\param poly Poligono a copiar
	 */
	Polygon(const Polygon &poly);

	Polygon & operator=(const Polygon &poly);

	/**\brief Obtiene el numero de vertices
	 */
	int getNVertices() const{
		return n_vertices;
	}

	/**\brief Obtiene el centro del poligono
	 */
	Point getCentro() const{
		return centro;
	}

	/**\brief Obtiene el vector de puntos
	 */
	/*Point* getPuntos() const{
		return puntos;
	}*/
	vector<Point> getPuntos() const {
		vector<Point> p;
		for(int i = 0; i < n_vertices; i++)
		{
			p.push_back(puntos[i]);
		}

		return p;
	}

	int getType() const;

	/**\brief Obtiene el radio
	 */
	double getRadio() const{
		return radio;
	}

	/**\brief Obtiene el angulo del desplazamiento
	 */
	double getAngulo() const{
		return angulo;
	}

private:
	/**\brief Numero de vertices del poligono
	 */
	int n_vertices;

	/**\brief Centro del poligono
	 */
	Point centro;

	/**\brief Vector de Points que representan el poligono
	 */
	Point *puntos;

	/**\brief Tamaño de los lados del poligono
	 */
	double radio;

	/**\brief Giro del poligono
	 * 0 significa que el 1º punto estará a la derecha del todo, 90 es arriba, 180 izquierda y 270 abajo.
	 * Cambiando el angulo puedes girar el poligono.
	 */
	double angulo;

	int type;

	/**\brief Genera los vertices del poligono
	 * Genera todos los vertices a partir del centro, el radio, el numero de lados
	 * y el angulo de desplazamiento
	 */
	void generatePoints();
};

#endif
