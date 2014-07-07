#ifndef __PATHFINDER__
#define __PATHFINDER__

#include "GraphUD.h"
#include "NavGraph.h"
#include "Triangulation.h"
#include "Map.h"
#include "World.h"
#include "Polygon.h"
#include "BodyData.h"
#include "Body.h"
#include <vector>
#include <cmath>

/**\brief Clase Pathfinder
 * Esta clase se encarga de lo siguiente
 * 		- Crear el grafo de navegacion a partir del grafo del mapa
 *		- Recibir peticiones de calculo de caminos y procesarlas mediante A*
 *		- Realizar A*
 *		- Suavizar los caminos realizados por A*
 */
class Pathfinder {
public:
	/**\brief Constructor vacio
	 */
	Pathfinder();

	/**\brief Destructor
	 */
	~Pathfinder();

	/**\brief Constructor sobrecargado
	 * @param sI Punto superior izquierdo del mapa
	 * @param iD Punto inferior derecho del mapa
	 * @param r Radio de las entidades dinamicas
	 */
	Pathfinder(Point sI, Point iD, double r);

	/**\brief Carga fName como mapa
	 * Carga los datos del archivo fName y a partir de ellos
	 * genera las primitivas de bloqueo y las expande.
	 * @param fName Nombre del mapa a cargar
	 */
	void setMap(string fName);

	/** Funcion A * que devuelve un vector de puntos para una ruta en un mapa desde un punto origen hasta uno fin
	 * Algoritmo A estrella para recorrido del grafo de navegacion del mapa.
	 * @param ori punto origen.
	 * @param des punto destino.
	 * @return vector de puntos con el camino a seguir.
	 */
	std::vector<Point> AStar(Point ori, Point des);

	/**\brief Devuelve la triangualrización actual
	 * @return vectro<Tri *> vectro de triangulos con la triangualrización del mapa
	 */
	std::vector<Tri *> getTriangulation();

	/**\brief Obtiene un vector de vectores de puntos con todos los puntos expandidos del mapa
	 * @return vector<vector<Point> > Vectores con todos los puntos del mapa.
	 */
	std::vector<std::vector<Point> > getExpPoints();

	/**\brief Genera la trianguarización
	 * Hace que se termine la triagularizacion
	 */
	void generateTriangulation();

	/**\brief Aplana la triangularización
	 * Añade puntos nuevos a la triangularizacion de forma que no haya triangulos que cruzen paredes.
	 */
	void flattenTriangulation();

	/**\brief Elimina los triangulos no navigables
	 */
	void removeNonNavigableTris();

	/**\brief Elimina los triangulos no navegables
	 * Elimina todos los triangulos que esten fuera del mapa
	 * Lo comprueba mirando que el tercer punto de cada triangulo este a la izquierda de los otros dos.
	 * @param vPuntos
	 */
	void removeTris(std::vector<Point> vPuntos);

	/**\brief Elimina los triangulos no navegables
	 * Los elimina lanzando un rayo desde sus centros al punto (0,0)
	 */
	void removeTris();

	/**\brief Elimina los triangulos no navegables
	 * Elimina todos los triangulos que estan fuera del perimetro o dentro pero dentro tambien de una primitiva de bloqueo.
	 */
	void removeTris2();

	/**\brief Devuelve el grafo dual correspondiente a la triangularización
	 * @return NavGraph correspondiente a la triangularización actual
	 */
	NavGraph getDualGraph();

	/**getNearestCenter devuelve el InCenter del triangulo al que se esta haciendo click en su interior.
	 * Usada para calcular el punto del nodo mas cercano al punto a buscar.
	 * @param p Punto a buscar
	 * @return punto del incenter del triangulo.
	 */
	Point getNearestCenter(Point p);

	/**\brief Suaviza un camino
	 * Suaviza el camino pasado por parametros de forma que se salte nodos no necesarios del camino
	 * @param camino Camino a suavizar
	 * @return vector<Point> Camino suavizado
	 */
	std::vector<Point> smoothPath(std::vector<Point> camino);

	//PROVISIONALES PARA PRUEBAS
	void setDualGraph(NavGraph nav);

	/**\brief Angulo que forman los vectores A y B
	 * @param A1 Primer punto del vector A
	 * @param A2 Segundo punto del vector A
	 * @param B1 Primer punto dle vector B
	 * @param B2 Segundo punto del vector B
	 * @return double Angulo que forman los vectores, en radianes.
	 */
	static double getAngle(Point A1, Point A2, Point B1, Point B2);

	/**\brief Expande el punto B
	 * Devuelve el resultado de expandir la geometria de estos dos vectores (AB y BC).
	 * @param A Punto anterior al objetivo
	 * @param B Punto a expandir
	 * @param C Punto posterior al objetivo
	 * @return Punto B expandido
	 */
	Point getNewPoint(Point A, Point B, Point C);

	Point getNewPoint2(Point A, Point B, Point C);

	/**\brief Expande la geometria del mapa
	 * Expande todos los puntos que forman el mapa
	 */
	void expandGeometry();
private:

	/**\brief Grafo de navegacion del mapa
	 */
	NavGraph navigationGraph;

	//vector<ASNode> getAdyacence(int parent, vector<ASNode>closeList);
	/** isInList calcula si un nodo esta en un vector de nodos.
	 * Funcioin auxiliar para el algoritmo AStar.
	 * @param node a buscar
	 * @param list con el vector donde buscar
	 * @return booleano con si esta o no
	 */
	bool isInList(ASNode node, vector<ASNode>list);

	/** isInList calcula si un nodo esta en un vector de nodos y lo devuelve en una variable.
	 * Funcioin auxiliar para el algoritmo AStar.
	 * @param node a buscar
	 * @param list con el vector donde buscar
	 * @param getIt nodo pasado por referencia para devolver el nodo encontrado
	 * @return booleano con si esta o no
	 */
	bool isInList(ASNode node, vector<ASNode>list, ASNode &getIt);

	/**getMinCost devuelve el nodo de menor coste en f de un vector pasado por parametro.
	 * Funcioin auxiliar para el algoritmo AStar.
	 * @param lista donde buscar
	 * @return nodo de menor coste f
	 */
	ASNode getMinCost(vector<ASNode> lista);

	/**generatePath funcion para generar el camino a recorrer despues de realizar el algoritmo A*.
	 * Va recorriendo desde el ultimo nodo, todos ellos hacia atras mirando sus padres.
	 * Funcioin auxiliar para el algoritmo AStar.
	 * @param origen nodo de origen
	 * @param destino nodo destino
	 * @param closeList lista cerrada tras el algoritmo A*
	 * @param ori punto de origen
	 * @param des punto de destino
	 * @return vector de puntos con el recorrido
	 */
	vector<Point> generatePath(ASNode origen, ASNode destino, vector<ASNode> closeList,Point ori, Point des);

	/**  getNode devuelve el nodo de un vector cullo id es igual al pasado por parametro
	 * @param id a buscar
	 * @param lista con el vector donde buscar
	 * @return nodo resultante de la busqueda
	 */
	ASNode getNode(int id, vector<ASNode> lista);

	/**\brief Genera el grafo dual del mapa
	 * Crea el grafo de navegacion a partir de la triangularización.
	 */
	void generateDualGraph();

	/**\brief Radio de las entidades dinamicas
	 */
	double charRadius;

	/**\brief Mapa de juego
	 */
	Map map;

	/**\brief Mundo fisico
	 * Usado para detectar colisiones
	 */
	World *mundo;

	/**\brief Punto superior izquierdo que delimita el mapa
	 */
	Point supIzq;

	/**\brief Punto inferior derecho que delimita el mapa
	 */
	Point infDer;

	/**\brief Triangualrización del mapa
	 */
	Triangulation dTris;

	/**\brief Triangulos que forman la triangularización
	 */
	std::vector<Tri *> triangles;

	/**\brief Vector de puntos que forman el perimetro del mapa
	 */
	std::vector<Point> pointList;

	/**\brief Vectores de puntos que forman las primitivas de bloqueo
	 */
	std::vector<std::vector<Point> > objectList;

	/**\brief Vectores con todos los puntos del mapa expandidos
	 */
	std::vector<std::vector<Point> > expObjs;

	/**\brief Determina si p esta dentro de poly
	 * @param poly Posible polygono contenedor
	 * @param p Punto a determinar
	 * @return true si p esta dentro de poly
	 */
	int isInside(Polygon poly, Point p);

	//void flattenGeometry();

	/**\brief Genera los objetos de la fisica
	 * Genera los objetos necesarios para intersectar triangulos con primitivas
	 */
	void createCollision();

	/**\brief Añade un punto p a los vectores de puntos
	 * Añade p en la lista que le corresponde, en su posicion de forma que sigan estando en
	 * sentido horario/antihorario segun corresponda
	 * @param p Punto a insertar
	 */
	void addPoint(Point p);

	/**\brief Añade la lista de puntos a los vectores de puntos
	 * @param Vector de puntos a incluir
	 */
	void addPoints(vector<Point> vPoints);

	/**\brief Elimina los triangulos vecinos de Tri
	 * Elimina los triangulos que sean vecinos de tri y tambien esten fuera del mapa
	 * @param tri Triangulo de origen
	 */
	void removeAdyacent(Tri *);

	/**\brief Añade los puntos de interseccion de las primitivas
	 */
	void flattenGeometry();

};

#endif
