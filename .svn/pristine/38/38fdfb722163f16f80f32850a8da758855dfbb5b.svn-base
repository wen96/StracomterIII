/*
 * Map.h
 *
 *  Created on: Nov 27, 2011
 *      Author: Chutaos team
 */

#ifndef MAP_H_
#define MAP_H_

#include <iostream>
#include "tinyxml.h"
#include <fstream>
#include <vector>
#include "CoreNamespace.h"
#include "EntityManager.h"
#include "Triangulation.h"

using namespace std;

struct obsCont{
	obsCont(){}
	obsCont(Core::Obstacles::Type t, Point pos, double ang){
		tipo = t;
		p = pos;
		a = ang;
	}
	Core::Obstacles::Type tipo;
	Point p;
	double a;
};

struct objCont{
	Core::Objects::Class tipo;
	Point p;
	double a;
};

/**\class Map
 * \brief Clase que controla los mapas del juego
 */
class Map{
public:
	/**\brief Constructor vacio
	 */
	Map();

	/**\brief Constructo de copia
	 * @param map objeto a copiar
	 */
	Map(const Map &);

	/**\brief Destructor
	 */
	~Map();

	/**\brief Sobrecarga de la asignacion
	 * @param map objeto a copiar
	 * @return objeto copiado
	 */
	Map & operator=(const Map &);

	/**\brief Constructor sobrecargado
	 * @param fName Nombre dle archivo que contiene el mapa
	 */
	Map(string fName);

	void setManager(EntityManager *mngr);

	/**\brief Cambia el mapa a usar
	 * @param fName Nuevo mapa a utilizar
	 */
	void setMap(string fName);

	/**\brief Carga los datos desde el archivo
	 * @return True si no ha habido ningun error
	 */
	int loadData();

	/**\brief Obtiene los puntos que representan el mapa
	 * @return Vector de puntos de las esquinas del mapa
	 */
	vector<Point> getPerimeter();

	/**\brief Obtiene las primitivas de bloqueo del mapa
	 * @return Vector con los vectores de puntos uqe representan los objetos interiores del mapa
	 */
	vector<vector<Point> > getObjects();

	/**\brief Obtiene los  del mapa
	 * @return Vector con los vectores de puntos que representan los muros interiores del mapa
	 */
	vector<vector<Point> > getWalls();

	vector<vector<Point> > getDoors();

	/**\brief Define el perimetro del mapa
	 *
	 * @param periVP Nuevo perimetro
	 * @return bool el perimetro apsado es correcto
	 */
	bool setPerimeter(vector<Point> periVP);

	/**\brief Añade un objeto al mapa
	 *
	 * @param p Posicion del objeto
	 * @param tipo Forma que lo define
	 * @return true si es un objeto correcto
	 */
	bool addObstacle(Core::Obstacles::Type tipo, Point p, double ang);

	bool addObject(Core::Objects::Class tipo, Point p, double ang);

	/**\brief Añade una pared al juego
	 *
	 * @param vP Puntos de la pared
	 * @return true si es una pared correcta
	 */
	bool addWall(vector<Point> vP);

	void addDoor(vector<Point> vP);

	/**\brief Guarda el mapa actual
	 * @param fName NOmbre del archivo donde se guardará el mapa
	 * @return true si se ha podido guardar
	 */
	bool writeFile(string fName);

	/**\brief Esquina superior izquierda del mapa
	 * @return el punto que corresponde a la esquina superior izquierda del mapa
	 */
	Point getSupIzq();

	/**\brief Esquina inferior derecha del mapa
	 * @return el punto que corresponde a la esquina inferior derecha del mapa
	 */
	Point getInfDer();

	/**\brief Puntero al entity manager
	 * @return Puntero al entity manager
	 */
	EntityManager *getManager() const;

	/**\brief Posicion del player
	 * @return Point de la posicion del player
	 */
	Point getPlayerPos();

	void setPlayerPos(Point p);

	//// TRIANGULARIZACION

	/**\brief Genera la trianguarización
	 * Hace que se termine la triagularizacion
	 */
	void generateTriangulation();

	vector<Tri *> getTriangulation();

	double getArea();

	bool hasVision(Point a, Point b);

	Tri getTri(Point p);

	void setWorld(World *world);

	/**\
	 * Determina si un punto es parte de la navegacion del mapa (si s epuede llegar hasta él).
	 * @param p Punto a comprobar
	 * @return True si p es navegable
	 */
	bool isNavegable(Point p);
    string getMapFileS() const;

	vector<Point> getTriCenters(int minArea = 0);

	Point miniBoss;
	Point megaBoss;

private:

	/**\brief Copia los contenidos de mapa en this
	 *
	 * @param mapa Objeto a copiar
	 */
	void copia(const Map &mapa);

	/**\brief Entity manager para colocar las entidades
	 */
	EntityManager *manager;

	/**\brief Nombre del archivo donde esta almacenado el mapa
	 */
	string mapFileS;

	/**\brief Puntos del mapa
	 */
	vector<Point> perimetroV;

	/**\brief Vector de paredes
	 */
	vector<vector<Point> > murosV;

	/**\brief Vector de paredes
	 */
	vector<vector<Point> > doorsV;

	vector<obsCont> obstaclesV;

	vector<objCont> objectsV;

	/**\brief Esquina del mapa
	 */
	Point supIzq;

	/**\brief Esquina del mapa
	 */
	Point infDer;

	/**\brief Posicion del player
	 */
	Point playerPos;

	/**\brief Obtiene el enumerado correspondiente a name
	 * @param name Nombre a comvertir
	 * @return enumerado que le corresponde
	 */
	static int getType(const char * name);

	// Para la triangularizacion
	vector<Point> pointList;
	vector<vector<Point> > objectList;
	vector<vector<Point> > expObjs;
	Triangulation dTris;
	double charRadius;

	// Mundo provisional para la fisica del mapa
	World *mapWorld;

	World *gameWorld;

	/**\brief Triangulos que forman la triangularización
	 */
	std::vector<Tri *> triangles;

	/**\brief Aplana la triangularización
	 * Añade puntos nuevos a la triangularizacion de forma que no haya triangulos que cruzen paredes.
	 */
	void flattenTriangulation();

	/**\brief Elimina los triangulos no navegables
	 * Elimina todos los triangulos que esten fuera del mapa
	 * Lo comprueba mirando que el tercer punto de cada triangulo este a la izquierda de los otros dos.
	 * @param vPuntos
	 */
	void removeTris();

	/**\brief Expande la geometria del mapa
	 * Expande todos los puntos que forman el mapa
	 */
	void expandGeometry();

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
	void removeAdyacent(Tri * tri);

	/**\brief Añade los puntos de interseccion de las primitivas
	 */
	void flattenGeometry();

	int isInside(Polygon poly, Point p);

	/**
	 * Añade las puertas al mundo fisico
	 */
	void generateDoorColisions();

	void addExtraCollision();

};



#endif /* MAP_H_ */
