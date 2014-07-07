/*
 * Force.h
 *
 *  Created on: 18/11/2011
 *      Author: sergio
 */

#ifndef FORCE_H_
#define FORCE_H_

#include "Box2D/Box2D.h"

/**\class Force
 * Clase que simula una fuerza 2D*/
class Force {
public:
	/**\brief Constructor*/
	Force();
	/**\brief Constructor sobrecargado
	 * \param forceX_ Fuerza en el eje X.
	 * \param forceY_ Fuerza en el eje Y.*/
	Force(float, float);
	/**\brief Constructor de copia.
	 * \param force Objeto a copiar.*/
	Force(const Force &);
	/**\brief Sobrecarga del operador de asignación.
	 * \param force Objeto a copiar.
	 * \return Devuelve el objeto copiado.*/
	Force & operator=(const Force &);
	/**\brief Destructor*/
	virtual ~Force();
	/**\brief Devuelve la fuerza.
	 * \return Devuelve la fuerza en forma de b2Vec2*/
	b2Vec2 getForce() const;
	/**\brief Devuelve la fuerza X.
	 * \return Devuelve la fuerza en el eje X*/
	float getForceX() const{
		return forceX;
	};
	/**\brief Devuelve la fuerza Y.
	 * \return Devuelve la fuerza en el eje Y*/
	float getForceY() const{
		return forceY;
	};
	/**\brief Asigna la fuerza X.
	 * \param forceX_ Valor a asignar a la fuerza X*/
	void setForceX(float forceX_){
		forceX = forceX_;
	};
	/**\brief Asigna la fuerza Y.
	 * \param forceY_ Valor a asignar a la fuerza Y*/
	void setForceY(float forceY_){
		forceY = forceY_;
	};
	/**\brief Asigna la fuerza X e Y.
	 * \param forceX_ Valor a asignar a la fuerza X
	 * \param forceY_ Valor a asignar a la fuerza Y*/
	void setForce(float forceX_, float forceY_) {
		forceX = forceX_;
		forceY = forceY_;
	}
	/**\brief Asigna una fuerza.
	 * param force Fuerza en forma de b2Vec2*/
	void setForce(b2Vec2 force) {
		forceX = force.x;
		forceY = force.y;
	}

private:
	/**\brief Fuerza X*/
	float forceX;
	/**\brief Fuerza Y*/
	float forceY;
};

#endif /* FORCE_H_ */
