/*
 * EventControl.h
 *
 *  Created on: 28/12/2011
 *      Author: Chutaos Team
 */

#ifndef EVENTCONTROL_H_
#define EVENTCONTROL_H_

#include <iostream>
#include <list>
#include "Entity.h"
#include "Character.h"
#include "Clock.h"
#include "Shape.h"
#include "AudioControl.h"
#include "ParticleManager.h"

class EntityManager;
class SceneManager;

/**
 * Clase auxiliar para mostrar la explosion en el suelo
 */
class AuxExplosion{
public:
	/**
	 * Constructor con la forma y el reloj para controlar el tiempo de eliminar
	 * @param s con la furma
	 * @param c con el reloj
	 */
	AuxExplosion(Shape *s, Clock c){
		explosion = s;
		clock = c;
	}
	/**
	 * Puntero a Shape para colgar del arbol la forma de la explosion
	 */
	Shape *explosion;
	/**
	 * Reloj para controlar el tiempo para borrarlo
	 */
	Clock clock;
};

/**
 * Clase que controla los eventos que se producen en el juego.
 * Como disparos, explosiones y demas
 */
class EventControl {
public:
	/**
	 * Constructor
	 */
	EventControl();
	/**
	 * Constructor
	 * @param ent
	 */
	EventControl(EntityManager *ent);

	/**
	 * Destructor
	 */
	virtual ~EventControl();

	/**
	 * Evento de disparo, devuelve si se ha muerto o al que disparas
	 * @param ent
	 * @return
	 */
	bool Shoot(Entity* ent);

	/**
	 * Evento cuchillada, devuelve si se ha muerto o al que acuchillas
	 * @param ent
	 * @return
	 */
	bool Slash(Entity* ent);

	/**
	 * Realiza una explison para la entidad pasada por parametro
	 * @param ent
	 * @return
	 */
	bool Explosion(Entity* ent);

	/**
	 * Realiza una explosion en el punto p con el danyo damage
	 * @param p con el punto
	 * @param damage con el danyo
	 * @return
	 */
	bool Explosion(Point p, int damage);


	bool doAttack(Entity* ent);

	/**
	 * Funcion que pone en modo volver a las entidades companyeras para vuelvan a tu lado pase lo que pase
	 */
	void ComeBackCompanions();

	/**
	 * Funcion que lanza la eventos automaticos periodicos
	 */
	void Update();

	/**
	 * Funcion que lanza el evento de la moral
	 */
	void UpdateMoral();

	/**
	 * Funcion que lanza el evento de actualizar la municion
	 */
	void UpdateAmmunition();

	/**
	 * Actualiza el borrado de explosiones
	 */
	void UpdateExplosions();

	/**
	 * Devuelve el punteo al gestor de entidades que maneja
	 * @return
	 */
    EntityManager *getEntities() const;

    /**
     * Cambia el gestor de entidades que maneja
     * @param entities
     */
    void setEntities(EntityManager *entities);

private:

    /**
     * Funcion auxiliar para no repetir codigo
     */
    bool postDisparo(bool muerto, Character* atacante, Character *atacado);

    /**
     * Gestor de entidades sobre las que aplicar los eventos
     */
	EntityManager *entities;

	/**
	 * Vector de explosiones para meter y borrar
	 */
	vector<AuxExplosion> explosiones;

//	vector<ParticleEmiter *> particulas;

	/**
	 * Puntero al control de audio, por comodidad
	 */
	AudioControl *ac;

	/**
	 * Textura, no se ni para que
	 */
	Textura *textura;
};

#endif /* EVENTCONTROL_H_ */
