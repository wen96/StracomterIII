#ifndef __Polygon__
#define __Polygon__

#include <iostream>
using namespace std;

#include <cstdlib>
#include "gpc.h"
#include "Point.h"
#include <cmath>
#include <vector>
#include "Vector2D.h"

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

	/**\brief SObrecarga para crear poligonos rellenos
	 * @param center punto vacio
	 * @param vPuntos Puntos del poligono
	 */
	Polygon(Point center, std::vector<Point> vPuntos);

	/**\brief Constructor de lineas
	 * @param Inicio
	 * @param Fin
	 */
	Polygon(Point, Point);

	/**\brief Constructor de poligonos huecos
	 * @param vPuntos Puntos del poligono
	 */
	Polygon(std::vector<Point> vPuntos);

	/**\brief Destructor por defecto
	 */
	virtual ~Polygon();

	/**\brief Constructor de copia
	 *\param poly Poligono a copiar
	 */
	Polygon(const Polygon &poly);

	/**\brief SObrecarga de la asignacion
	 * @param poly Poligono a copiar
	 * @return poligono copiado
	 */
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
	vector<Point> getPuntos() const {
		return puntos;
	}

	/**\brief Obtiene el tipo del poligono
	 * @return tipo
	 */
	int getType() const;

	/**\brief Establece el tipo del poligono
	 * @param type tipo
	 */
	void setType(int type);

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

	/**\brief Determina si el poligono es convexo
	 * @return true si lo es
	 */
	bool isConvex() const;

	/**\brief Determina si el poligono tiene un orden dextrogiro
	 * @return true si lo es
	 */
	bool isClockwise() const;

	/**\brief Le da la vuelta al poligono
	 */
	void Reverse();

	/**\brief Convierte un poligono en su convex hull
	 */
	void makeConvexHull();

	/**\brief Elimina los puntos que formas lineas
	 */
	void removeColinear();

	/**\brief Expande el punto B
	 * Devuelve el resultado de expandir la geometria de estos dos vectores (AB y BC).
	 * @param A Punto anterior al objetivo
	 * @param B Punto a expandir
	 * @param C Punto posterior al objetivo
	 * @param izquierda Indica si lo queremos a la izquierda o a la derecha de las lineas
	 * @return Punto B expandido
	 */
	static Point getNewPoint(Point A, Point B, Point C, bool dextrogiro, double distance);

	/**\brief Guarda el poligono en formato gpc
	 * @param
	 */
	void toGPC(gpc_polygon *);

	/**\brief Obtiene el poligono de un formato gpc
	 * @param
	 */
	void fromGPC(gpc_polygon *);

	/**\brief Obtiene los triStrips que definen el poligono
	 * @return vector de vectores de puntos
	 */
	vector<vector<Point> > getTriStrip();

	/**\brief Une this con pol
	 * @param pol poligono con el que unirse
	 */
	void Join(Polygon pol);

	/**\brief Le resta pol a this
	 * @param pol Objeto a restar
	 */
	void Diff(Polygon pol);

	/**\brief Hace la diferencia y devuelve un tristrip
	 * @param pol poligono a restar
	 * @return vector de vectores de puntos
	 */
	vector<vector<Point> > DiffToTriStrips(Polygon pol);

	/**\brief Intersecta this con pol
	 * @param pol Poligono a intersectar
	 */
	void Inter(Polygon pol);

	/**\brief Getter de los vertices
	 * @return vertices
	 */
    int getVertices() const;

    /**\brief Setter del angulo
     * @param angulo angulo
     */
    void setAngulo(double angulo);

    /**\brief Setter del centro
     * @param centro Centro
     */
    void setCentro(Point centro);

    /**\brief Setter de los puntos
     * @param puntos Puntos
     */
    void setPuntos(vector<Point> puntos);

    /**\brief Setter dle radio
     * Para circulos
     * @param radio Radio
     */
    void setRadio(double radio);

    /**\brief Setter de los vertices
     * @param vertices Vertices
     */
    void setVertices(int vertices);

    /**
     * Calcula el centroide del poligono
     * @return Centro de masas del poligono
     */
    Point getCentroid();

    void Expand(double dist, bool dir = true);
private:
	/**\brief Numero de vertices del poligono
	 */
	int n_vertices;

	/**\brief Centro del poligono
	 */
	Point centro;

	/**\brief Vector de Points que representan el poligono
	 */
	vector<Point> puntos;

	/**\brief Tamaño de los lados del poligono
	 */
	double radio;

	/**\brief Giro del poligono
	 * 0 significa que el 1º punto estará a la derecha del todo, 90 es arriba, 180 izquierda y 270 abajo.
	 * Cambiando el angulo puedes girar el poligono.
	 */
	double angulo;

	/**\brief Tipo dle poligono
	 */
	int type;

	/**\brief Genera los vertices del poligono
	 * Genera todos los vertices a partir del centro, el radio, el numero de lados
	 * y el angulo de desplazamiento
	 */
	void generatePoints();
};

#endif
