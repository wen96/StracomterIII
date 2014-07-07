/*
 * BodyData.h
 *
 *  Created on: 18/11/2011
 *      Author: Chutaos Team
 */

#ifndef BODYDATA_H_
#define BODYDATA_H_

#include "Box2D/Box2D.h"
#include "Box.h"
#include "Force.h"

/**\class BodyData
 * Contiene las características del Body*/
class BodyData {
public:
	/**\brief Constructor por defecto.
	 * Necesitará crearse una caja física (Box)*/
	BodyData();
	/**\brief Constructor sobrecargado.
	 * \param pol Polígono con el que crear el Body.
	 * \param type Indica el tipo del objeto, estático, dinámico...
	 * \param masa_ masa del objeto.*/
	BodyData(Polygon pol, b2BodyType type = b2_staticBody, float masa_ = 1.0);
	/**\brief Destructor.*/
	virtual ~BodyData();
	/**\brief Devuelve el BodyDef.
	 * \return Devuelve el Objeto BodyDef de la Box2D.*/
	b2BodyDef* getBodyDef() const{
		return bodyDef;
	}
	/**\brief Devuelve el FictureDef.
	 * \return Devuelve el Objeto FixtureDef de la Box2D.*/
	b2FixtureDef& getFixtureDef(){
		return fixtureDef;
	}
	/**\brief Devuelve el b2Shape.
	* \return Devuelve el Objeto b2Shape de la Box2D.*/
	const b2Shape* getShape() const{
		return box->getShape();
	}
	/**\brief Devuelve la estructura de la masa.
	 * \return Estructura de la calse Box2D que define la masa.*/
	b2MassData* getMass() const{
		return masa;
	}
	/**\brief Constructor de Copia.
	 * \param bd Objeto BodyData a copiar.*/
	BodyData(const BodyData &);
	/**\brief Sobrecarga del operador asignación para BodyData.
	 * \param bd Objeto BodyData a copiar.
	 * \return Devuelve el objeto copiado.*/
	BodyData& operator=(const BodyData&);
	/**\brief Asigna la velocidad Angular.
	 * \param vel Velocidad angular.*/
	void setAngularVelocity(float);
	/**\brief Asigna la velocidad lineal.
	 * \param force velocidad representada mediante un objeto Force.*/
	void setLinearVelocity(Force);
	/**\brief Asigna la copisión del objeto.
	 * \param p_centro Posición a asignar.*/
	void setPosition(Point);
	/**\brief Fija o desfija el objeto ante las rotaciones.
	 * \param fix true si se quiere fijo y false en caso contrario.*/
	void fixedRotation(bool);
	/**\brief Pone el objeto a Despierto o dormido.
	 * \param awake_ true si está despierto, false en caso contrario.*/
	void setAwake(bool);
	/**\brief Asigna el ángulo del objeto.
	 * angle_ Ángulo a asignar*/
	void setAngle(float);
	/**\brief Asigna la densidad al objeto.
	 * \param density_ Densidad a asignar.*/
	void setDensity(float);
	/**\brief Asigna la fricción al objeto.
	* \param friction_ Fricción a asignar.*/
	void setFriction(float);
	/**\brief Asigna la restitución al objeto.
	* \param restitution_ Restitución a asignar.*/
	void setRestitution(float);
	/**\brief Asigna la Box al objeto.
	* \param b Densidad a asignar.*/
	void setBox(const Box&);
	/**\brief Asigna la masa al objeto.
	* \param masa_ Masa a asignar.*/
	void setMasa(float);
	/**\brief Asigna la Amortiguación lineal al objeto.
	* \param damping Amortiguación a asignar.*/
	void setLinearDamping(float);
	/**\brief Asigna la amortiguación angular al objeto.
	* \param damping Amortiguación a asignar.*/
	void setAngularDamping(float);
	/**\brief Indica si el objeto es sensor o no.
	 * Un objeto sensor no generea respuesta física a las colisiones.
	* \param sensor true si es sensor y false en caso contrario.*/
	void setSensor(bool);

	void setGoodPerson();
	void setBadPerson();
	void setNeutral();
	void setObstacle();
    Polygon getPoligon() const;
    void setPoligon(Polygon poligon);

private:
	/**\brief Definición de Body*/
	b2BodyDef *bodyDef;
	/**\brief Definición de la forma*/
	b2FixtureDef fixtureDef;
	/**\brief Definición de la caja física.*/
	Box *box;
	/**\brief Estructura de la masa.*/
	b2MassData *masa;
	Polygon poligon;
};

#endif /* BODYDATA_H_ */
