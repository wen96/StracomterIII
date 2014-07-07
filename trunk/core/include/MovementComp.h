/*
 * MovementComp.h
 *
 *  Created on: Feb 26, 2012
 *      Author: rellik
 */

#ifndef MOVEMENTCOMP_H_
#define MOVEMENTCOMP_H_

#include "Vector2D.h"
#include "Path.h"
#include "Clock.h"
#include "SteeringBehavior.h"


class SteeringBehavior;

/**
 * Clase MovementComp
 * Representa una componente de movimiento
 */
class MovementComp {
public:
	MovementComp();
	MovementComp(SteeringBehavior *steer);
	MovementComp(MovementComp *leader);
	~MovementComp();
	MovementComp(const MovementComp &mov);
	MovementComp & operator=(const MovementComp &mov);

	/**
	 * Actualiza el estado segun el tiempo que ha pasado
	 */
	void Update();

	/**
	 * Establece el camino que ha de seguir
	 * @param vPuntos Camino a seguir
	 * @param loop Si es un bucle o no
	 */
	void setPath(vector<Point> vPuntos, bool loop = false);

	/**
	 * Suma a la velocidad exsitente
	 * @param force Velocidad a sumar
	 */
	void addVelocity(Vector2D force);

	void setPos(Point p);
	Vector2D getPos();
	Point getPosP();
    Vector2D getHeading() const;
    double getMass() const;
    double getMaxForce() const;
    double getMaxSpeed() const;
    Vector2D getSide() const;
    Vector2D getVelocity() const;
    void setHeading(Vector2D heading);
    void setMass(double mass);
    void setMaxForce(double maxForce);
    void setMaxSpeed(double maxSpeed);
    void setVelocity(Vector2D velocity);
    void setOffset(Vector2D offs);
    Vector2D getOffset();
    void setMode(int modo);
    void setLeader(MovementComp *mov);
    Vector2D getAceleration();
    Vector2D getIncrement();

    /**
     * Convierte el desplazamiento de la comp. a una posicion del mundo.
     * @return
     */
    Vector2D getWorldOffset();

    bool getMeEstoyMoviendo();

private:
    /**
     * Posicion en el mundo
     */
    Vector2D pos;

    /**
     * Velocidad
     */
	Vector2D mVelocity;

	/**
	 * Direccion
	 */
	Vector2D mHeading;

	/**
	 * Perpendicular a la direccion
	 */
	Vector2D mSide;

	/**
	 * Aceleracion
	 */
	Vector2D aceleration;

	/**
	 * Incremento de la velocidad
	 */
	Vector2D velIncrement;

	/**
	 * Masa
	 */
	double mMass;

	/**
	 * Velocidad Maxima
	 */
	double mMaxSpeed;

	/**
	 * Fuerza de giro maxima
	 */
	double mMaxForce;

	/**
	 * Contador para el update
	 */
	Clock time;

	/**
	 * Tipo de movimiento
	 */
	SteeringBehavior *steering;

	/**
	 * Deplazamiento
	 */
	Vector2D offset;
};


#endif /* MOVEMENTCOMP_H_ */
