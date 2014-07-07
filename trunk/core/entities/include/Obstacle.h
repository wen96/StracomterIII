/*
 * Obstacle.h
 *
 *  Created on: 12/11/2011
 *      Author: Chutaos Team
 */

#ifndef Obstacle_H_
#define Obstacle_H_

#include "Entity.h"
#include "Textura.h"
/**\brief Clase Obstacle.
 * Se precisa un enumerado indicando que tipo de obstaculo.
 * */

class Obstacle: public Entity {
	/**\brief Operador de salida.
	 *\param os - salida del operador
	 *\param obj - obstaculo a mostrar
	 *\return os - salida del operador*/
	friend ostream& operator<<(ostream &os, const Obstacle& obj);
public:
	/**\brief Constructor por defecto.*/
	Obstacle();
	/**\brief Constructor.
	 *\param _type - tipo de obstaculo
	 *\param r - puntero a resource manager */
	Obstacle(Core::Obstacles::Type,ResourceManager *r, Point, float);
	Obstacle(Core::Obstacles::Type,ResourceManager *r, Point, float, string, int, int, int);
	/**\brief Constructor.
	 *\param _type - tipo de obstaculo
	 *\param idG - id
	 *\param pos - posicion
	 *\param angles - angulo
	 *\param r - puntero a resource manager
	 *\param _color - color del poligono
	 *\param vP - vector de puntos. */
	Obstacle(Core::Entities::Type,const unsigned int idG, const Point, float, ResourceManager *r, Color<float> color_, vector<Point> vP);
	/**\brief Constructor de copia
	 *\param pare - objeto a copiar.*/
	Obstacle(const Obstacle&);
	/**\brief Destructor.*/
	virtual ~Obstacle();
	/**\brief Operador de igualdad.
	 *\param pare - objeto a copiar.*/
	Obstacle& operator=(const Obstacle&);


	void generateObstacleCollision(Core::Obstacles::Type, Point);
    Core::Obstacles::Type getObstacle() const;
    void setObstacle(Core::Obstacles::Type obstacle);
    vector<Point> getPuntos() const {
    	return puntos;
    }

    bool isInside(Point p);
protected:
	/*\bief Vector de puntos.*/
	vector<Point> puntos;
	Core::Obstacles::Type obstacle;
};

#endif /* Obstacle_H_ */
