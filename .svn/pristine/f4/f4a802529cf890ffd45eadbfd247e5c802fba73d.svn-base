/*
 * SteeringBehavior.h
 *
 *  Created on: Feb 26, 2012
 *      Author: Chutaos Team
 */

#ifndef STEERINGBEHAVIOR_H_
#define STEERINGBEHAVIOR_H_

#include "Vector2D.h"
#include "MovementComp.h"
#include "Path.h"

class MovementComp;

/**
 * Clase SteeringBehavior
 * Representa una forma de moverse
 */
class SteeringBehavior{
public:
	SteeringBehavior();
	SteeringBehavior(MovementComp *mov, MovementComp *lead=NULL);
	~SteeringBehavior();
	SteeringBehavior(const SteeringBehavior &sBeh);
	SteeringBehavior & operator=(const SteeringBehavior &sBeh);

	/**
	 * Calcula la fuerza necesaria para lelgar al objetivo
	 * @return Verctor con la fuerza necesaria
	 */
	Vector2D Calculate();

	void setPath(vector<Point> vp, bool loop = false);
	void setOwner(MovementComp *mov);
	void setMode(int modo);
	void setLeader(MovementComp *mov);
	MovementComp * getLeader();
private:
	/**
	 * Lider al que seguir en caso de estar en modo formacion
	 */
	MovementComp *owner;

	/**
	 * Camino a seguir
	 */
	Path camino;

	/**
	 * Modo de movimiento
	 * 0 -> Seguir camino
	 * 1 -> Seguir lider
	 */
	int mode;

	/**
	 * Lider al que seguir
	 */
	MovementComp *leader;

	/**
	 * Comportamiento Buscar
	 * Intenta llegar a la posicion objetivo
	 * @param TargetPos posicion objetivo
	 * @return Fuerza necesaria para llegar
	 */
	Vector2D Seek(Vector2D TargetPos);

	/**
	 * Comportamiento Llegar
	 * Intenta llegar a la posicion objetivo, frenando cuando se acerca a esta
	 * @param TargetPos posicion objetivo
	 * @param deceleration Nivel de deaceleracion
	 * @return Fuerza necesaria para llegar
	 */
	Vector2D Arrive(Vector2D TargetPos, int deceleration);

	/**
	 * Comportamiento seguir un camino.
	 * Hace Seek al siguiente punto del camino
	 * @return Fuerza necesaria
	 */
	Vector2D FollowPath();

	/**
	 * Comportamiento Persecucion
	 * Intenta ir a la posicion relativa de su lider
	 * @param offset Distancia al lider
	 * @return Fuerza necesaria
	 */
	Vector2D OffsetPursuit(Vector2D offset);
};


#endif /* STEERINGBEHAVIOR_H_ */
