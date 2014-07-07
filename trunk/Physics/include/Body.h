/*
 * Body.h
 *
 *  Created on: 16/11/2011
 *      Author: Chutaos Team
 */

#ifndef BODY_H_
#define BODY_H_

#include <iostream>
using namespace std;

#include "Box2D/Box2D.h"
#include "BodyData.h"
#include "World.h"
#include "Box.h"
#include "Force.h"

/**\class Body
 * Crea los objetos físicos que interactúan con el mundo.*/
class Body {
public:
	/**\brief Constructor
	 * Es el único constructor de la clase. Obligatoriamente un Body necesita de un World y un BodyData.
	 * \param world_ Mundo en el que se crea el objeto.
	 * \param bodyData_ Características del objeto físico.*/
	Body(World &, BodyData );
	/**\brief Destructor*/
	virtual ~Body();
	/**\brief Constructor de copia.
	 * \param body_ Objeto a copiar.*/
	Body(const Body&);
	/**\brief Operador de asignación.
	 * Sobrecarga del operador asignación para el objeto Body.
	 * \param body_ Objeto a copiar.
	 * \return Devuelve el objeto copiado.*/
	Body& operator=(const Body&);
	/**\brief Aplica velocidad lineal al Body.
	 * \param vel Fuerza que representa la velocidad que se le aplica al Body.*/
	void setLinearVelocity(Force);
	/**\brief Devuelve la velocidad Lineal que tiene el Body.
	 * \return Devuelve un objeto Force con la velocidad lineal del Body.*/
	Force getLinearVelocity() const;
	/**\brief Devuelve la posición del objeto Body.
	 * \return Devuelve la posición de objeto Body en un objeto Point.*/
	Point getPosition() const;
	/**\brief Cambia la posición del Body.
	 * \param p Objeto Point con la nueva posición.*/
	void setPosition(Point);
	/**\brief Añade velocidad lineal al Body.
	 * vel Velocidad que se añade.*/
	void addLinearVelocity(Force);
	/**\brief Cambia el año del Body.
	 * angle Ángulo a aplicar al cuerpo.*/
	void setAngle(float);
	/**\brief Devuelve el ángulo del Body.
	 * \return Devuelve el ángulo del cuerpo.*/
	float getAngle() const;
	/**\brief Fijamos o desfijamos el cuerpo ante las rotaciones.
	 * \param fijo true si fijmos el cuerpo y false si lo desfijamos.*/
	void setFixedRotation(bool);
	/**\brief Añadimos un ángulo al Body.
	 * angle_ Valor añadir al ángulo del cuerpo.*/
	void addAngle(float);
	/**\brief Indica si un punto pertenece al Body.
	 * \param p Punto a probar.
	 * \return true si pertenece y false si no*/
	bool TestPoint(Point) const;
	/**\brief Devuelve un puntero a mundo.
	 * \return Devuelve un puntero a Mundo.*/
	World *getWorld() const {
		return world;
	}
	/**\brief Devuelve un vector de puntos de contacto de objetos sólidos.
	 * \return El vector de puntos de contacto.*/
	vector<Point> solidContacts() const;
	/**\brief Devuelve un vector con los puntos de corte entre dos cadenas.
	 * \param b Cuerpo con el que intersectar.
	 * \return Vector de puntos de corte.*/
	vector<Point> contact(const Body &) const;
    void setWorld(World *world);
	/**\brief Devuelve un puntero al objeto b2Body del Body.
	 * \return Devuelve el puntero a un objeto de Box2D*/
	b2Body* getBody() const {
		return body;
	}
	void Active(bool activo){
		body->SetActive(activo);
	}

	void applyImpulse(Vector2D f, Point p);
    BodyData *getBodydata() const;
    void setBodydata(BodyData *bodydata);
private:
	/**brief Objeto de Box2D Body*/
	b2Body *body;
	/**brief Contiene las características del cuerpo*/
	BodyData *bodydata;
	/**brief Mundo en el que se ha creado el Body.*/
	World *world;
};

#endif /* BODY_H_ */
