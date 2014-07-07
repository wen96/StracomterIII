/*
 * Enemy.h
 *
 *  Created on: 15/02/2012
 *      Author: Chutaos Team
 */

#ifndef ENEMY_H_
#define ENEMY_H_

#include "Bot.h"
#include "EntityManager.h"

enum State {
	Debug = 0,
	Patrol = 10,
	Attack = 20,
	Pursue = 30,
	Ensure = 40
};

class Enemy: public Bot {
public:
	/**
	 * Constructor
	 */
	Enemy();
	/**
	 * Constructor
	 * @param r
	 * @param t
	 * @param pf_
	 */
	Enemy(ResourceManager *r, Core::Entities::Type t, Pathfinder *pf_);
	/**
	 * Constructor
	 * @param
	 * @param
	 * @param
	 * @param r
	 * @param t
	 * @param pf_
	 */
	Enemy(const int, const Point, float, ResourceManager *r, Core::Entities::Type t, Pathfinder *pf_);
	/**
	 * Constructor de copia
	 * @param
	 */
	Enemy(const  Enemy&);
	/**
	 * Destructor
	 */
	virtual ~Enemy();

	/*////////////////////////////////// IA /////////////////////////////////////*/
	/**Funcion para actualizar el estado el personaje con IA
	 * @param manager puntero al entity manager para la actualizacion
	 */
	void updateAI(EntityManager* manager);
	/**
	 * Genera la maquina de estados para el tipo específico
	 */
	void generateFSM();

	////// ESTADOS ////// Consultar documento en redmine para entender funcionamiento
	/**
	 * Estado de patrulla
	 * @param manager
	 */
	void Patrol(EntityManager* manager);
	/**
	 * Estado de moverse a posicion
	 * @param manager
	 */
	void gotoPosition(EntityManager* manager);
	/**
	 * Estado de asegurar una zona
	 * @param manager
	 */
	void ensureZone(EntityManager* manager);
	/**
	 * Estado de atacar
	 * @param manager
	 */
	void Attack(EntityManager* manager);
	/**
	 * Estado de debug
	 * Solo intenta recorrer su camino
	 */
	void Debug();


	/**
	 * Giro a giros parciales y esprando unos segundos
	 */
	void partialRotation();

	/**
	 * Giro completo sin parar
	 * @return
	 */
	bool fullRotation();

	//dirigirse a
	/*////////////////////////////////// -- /////////////////////////////////////*/

protected:
	/**
	 * Booleano con si ha matado en la utlima iteracion
	 */
	bool killedLastTime;

	/**
	 * Punto de patrulla
	 */
	Point patrolPosition;

	/**
	 * Para el giro parcial
	 */
	sf::Clock timerPatrolRotation;

	/**
	 * No se
	 */
	bool flagPatrullo;

	/**
	 * Para el giro parcial
	 */
	int nRotations;
};

#endif /* ENEMY_H_ */
