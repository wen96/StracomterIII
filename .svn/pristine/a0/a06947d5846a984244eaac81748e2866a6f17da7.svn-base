/*
 * Map.h
 *
 *  Created on: Nov 27, 2011
 *      Author: rellik
 */

#ifndef MAP_H_
#define MAP_H_

#include <iostream>
#include "GraphUD.h"
#include "Node.h"
#include "Polygon.h"
#include <fstream>
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

	/**\brief Usa fName como mapa
	 * @param fName Nombre del mapa
	 */
	void setMap(string fName);

	/**\brief Obtiene el grafo del mapa
	 * @return Grafo que representa el mapa
	 */
	GraphUD<Node> getGraph();

	/**\brief Obtiene los puntos que representan el mapa
	 * @return Vector de puntos de las esquinas del mapa
	 */
	std::vector<Point> getVertex();

	/**\brief Obtiene los poligonos que representan el mapa
	 * @return Vector de poligonos del mapa
	 */
	std::vector<Polygon> getPolygons();

	/**\brief Obtiene las primitivas de bloqueo del mapa
	 * @return Vector con los vectores de puntos uqe representan los objetos interiores del mapa
	 */
	std::vector<std::vector<Point> > getObjects();

private:

	/**\brief Nombre del archivo donde esta almacenado el mapa
	 */
	string mapFileS;

	/**\brief Grafo del mapa
	 */
	GraphUD<Node> mapGraph;

	/**\brief Puntos del mapa
	 */
	std::vector<Point> puntos;

	/**\brief Vectores de puntos de los objetos del mapa
	 */
	std::vector<std::vector<Point> > objectList;

	/**\brief Genera los vecotres de puntos
	 */
	void generatePointVectors();


	int* getInfo(string);
};



#endif /* MAP_H_ */
