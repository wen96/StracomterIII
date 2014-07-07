/*
 * EventControl.h
 *
 *  Created on: 28/12/2011
 *      Author: Chutaos Team
 */

#ifndef EVENTCONTROL_H_
#define EVENTCONTROL_H_

#include <iostream>
#include "Entity.h"

class EntityManager;

class EventControl {
public:
	EventControl();
	EventControl(EntityManager *ent);
	virtual ~EventControl();

	/**
	 * Evento de disparo, devuelve si se ha muerto o al que disparas
	 * @param ent
	 * @return
	 */
	bool Shoot(Entity* ent);

	/**
	 * Funcion que pone en modo volver a las entidades companyeras para vuelvan a tu lado pase lo que pase
	 */
	void ComeBackCompanions();

	void Update();

	void UpdateMoral();
	void UpdateAmmunition();


    EntityManager *getEntities() const;
    void setEntities(EntityManager *entities);
private:
	EntityManager *entities;
};

#endif /* EVENTCONTROL_H_ */
