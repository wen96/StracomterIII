/*
 * Wall.h
 *
 *  Created on: 12/11/2011
 *      Author: Chutaos Team
 */

#ifndef WALL_H_
#define WALL_H_

#include "StaticEntity.h"

/**\class Wall
 * Representa una pared del juego
 */
class Wall: public StaticEntity {
	/**\brief SObrecarga de la salida
	 * @param os stream de salida
	 * @param obj objeto a mostrar
	 * @return stream modificado
	 */
	friend ostream& operator<<(ostream &os, const Wall& obj);
public:
	/**\brief COnstructor vacio
	 */
	Wall();

	/**\brief Constructor con el gestor de recursos
	 * @param r Gestor de recursos
	 */
	Wall(ResourceManager *r);

	/**\brief Constructor sobrecargado
	 * @param idG identificador de la entidad
	 * @param p Posicion de la pared
	 * @param ang angulo de la pared
	 * @param r gestor de recursos
	 * @param color_ Color de la parec
	 * @param vP Puntos de la pared
	 */
	Wall(const unsigned int idG, const Point p, float ang, ResourceManager *r, Color<float> color_, vector<Point> vP);

	/**\brief Constructor de copia
	 * @param Objeto a copiar
	 */
	Wall(const Wall&);

	/**\brief Destructor
	 */
	virtual ~Wall();

	/**\brief SObrecarga de la asignacion
	 * @param Objeto a copiar
	 * @return Objeto copiado
	 */
	Wall& operator=(const Wall&);

	/**\brief establee los puntos de la pared
	 * @param vP Puntos
	 */
	void setPoints(vector<Point> vP);

	/**\brief Obtiene los puntos de la pared
	 * @return Puntos de la pared
	 */
	vector<Point> getPoints();

	/**\brief Genera la fisica de la pared
	 */
	void generateCollision();

	/**\brief Devuelve el id del displayList
	 * @return id
	 */
	int getIdDisplay() const;

	/**\brief Establece el id del displayList
	 * @param idDisplay id
	 */
    void setIdDisplay(int idDisplay);

    /** Funcion de estandarizado de puntos
     * Funcion para calcular los 8 puntos en el orden correcto para dibujarlos
     */
    void calculate8Points();
protected:
    /**\brief Puntos de la pared
     */
	vector<Point> puntos;
};
/*Atributos que Hereda en la parte privada:
 * 	Type type;
 *	int id;
 *	Box colision;
 *	Point center;
 *	bool visible;
 *	bool muvible = false;
 *	bool small;
 */
#endif /* WALL_H_ */
