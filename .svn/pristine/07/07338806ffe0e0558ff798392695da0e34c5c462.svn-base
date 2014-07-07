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
using namespace std;

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
	bool addObject(Point p, Core::Entities::Type tipo);

	/**\brief Añade una pared al juego
	 *
	 * @param vP Puntos de la pared
	 * @return true si es una pared correcta
	 */
	bool addWall(vector<Point> vP);

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

	/**\brief Vectores de puntos de los objetos del mapa
	 */
	vector<Point > mesasV;

	/**\brief Vector de objetos
	 */
	vector<Point > columnasV;

	/**\brief Vector de paredes
	 */
	vector<vector<Point> > murosV;

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
};



#endif /* MAP_H_ */
