/*
 * HIDControl.h
 *
 *  Created on: 17/11/2011
 *      Author: Chutaos Team
 */

#ifndef HIDCONTROL_H_
#define HIDCONTROL_H_

#include <iostream>
#include <SFML/Graphics.hpp>
#include "EntityManager.h"
#include "IOControl.h"
#include "MotorGrafico.h"
#include <time.h>
#include "EventControl.h"
#include "TForm.h"

using namespace std;

class HIDControl {
public:
	/** Constructor por defecto
	 * @param events_ IOControl, puntero para detectar los eventos de teclado y raton
	 */
	HIDControl(IOControl *events_);

	 /** Destructor vacio en este caso
	  */
	virtual ~HIDControl();

	/** Control de eventos para el juego en modo accion.
	 * @param entities PUntero con las entidades a controlar
	 * @return booleano con si el juego se ha pausado o no
	 */
	int actionControl(EntityManager *entities,EventControl *event_);

	bool pauseControl(EntityManager *entities,TForm *menu);

	/**
	 * Funcion que controla los clicks sobre los forms.
	 * Devuelve en un entero el evento asociado al boton pulsado.
	 * Esc devuelve 0 y cuando no se pulsa nada devuelve -1
	 * @param menu form del que capturar los eventos
	 * @return entero asociado al widget pulsado
	 */
	int formMenuControl(TForm *menu);

	/** IsPressUp funcion que deveuelve si se esta presionando la tecla arriba.
	 * @return booleano con si se pulsa o no
	 */
	bool IsPressUp();

	/** IsPressDown funcion que deveuelve si se esta presionando la tecla abajo.
	 * @return booleano con si se pulsa o no
	 */
	bool IsPressDown();

	/** IsPressLeft funcion que deveuelve si se esta presionando la tecla izquierda.
	 * @return booleano con si se pulsa o no
	 */
	bool IsPressLeft();

	/** IsPressRight funcion que deveuelve si se esta presionando la tecla derecha.
	 * @return booleano con si se pulsa o no
	 */
	bool IsPressRight();

	/** IsPressAction funcion que deveuelve si se esta presionando la tecla de accion.
	 * @return booleano con si se pulsa o no
	 */
	bool IsPressAction();

	/** IsPressPause funcion que deveuelve si se esta presionando la tecla de pausado.
	 * @return booleano con si se pulsa o no la tecla de pausado
	 */
	bool IsPressPause();

	bool IsPressSpace(sf::Event event);

	bool IsPressUp(sf::Event event);

	bool IsPressDown(sf::Event event);

	bool IsPressLeft(sf::Event event);

	bool IsPressRight(sf::Event event);

	bool IsPressEscape(sf::Event event);

	bool IsPressPause(sf::Event event);

	bool IsPressClose(sf::Event event);
private:
	/** Varible events, puntero para controlar los eventos de teclado y raton que se producen en tiempo real
	 */
	IOControl *events;

	/** Variable para crear eventos del tipo disparo, explosion...
	 */
	EventControl *event;

	/**
	 * Para saber donde pintar el pause en caso de que muera el player (y por tanto dejed e existir su centro)
	 */
	Point lastPositionPlayer;


};

#endif /* HIDCONTROL_H_ */
