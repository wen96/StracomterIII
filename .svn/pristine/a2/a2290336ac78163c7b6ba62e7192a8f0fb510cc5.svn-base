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
#include "cmath"

using namespace std;

/**
 *\brief Clase para controlar los eventos de teclado y raton para un modo de juego y con alguna accion especifica
 */
class HIDControl {
public:
	/** Constructor por defecto
	 * @param events_ IOControl, puntero para detectar los eventos de teclado y raton
	 */
	HIDControl(IOControl *events_);

	 /** Destructor vacio en este caso
	  */
	virtual ~HIDControl();

	/**
	 * Control de eventos para el juego en modo accion.
	 * Controla todos los eventos de teclado y raton que puede producir el jugador
	 * @param entities entities PUntero con las entidades a controlar
	 * @param event_ evento a comprobar
	 * @return booleano con si el juego se ha pausado o no
	 */
	int actionControl(EntityManager *entities,EventControl *event_);

	/**
	 * Control cuando se esta en pause en el modo accion
	 * En desuso
	 * @param entities entity manager
	 * @param menu para detectar los clics en los botones
	 * @return devuelve si sigue pausado o no
	 */
	bool pauseControl(EntityManager *entities,TForm *menu);

	/**
	 * Funcion que controla los clicks sobre los forms.
	 * Devuelve en un entero el evento asociado al boton pulsado.
	 * Esc devuelve 0 y cuando no se pulsa nada devuelve -1
	 * @param menu form del que capturar los eventos
	 * @return entero asociado al widget pulsado
	 */
	int formMenuControl(TForm *menu);

	/**
	 * Para comprobar un solo evento en lugar de hacer el bloque y coger todos los eventos de la ventana
	 * Se utiliza para el editor basicamente
	 * @param menu
	 * @param ev
	 * @return devuelve -1 si no se ha pulsado nada y otro numero con el evento asociado al boton pulsado
	 */
	int formMenuControlEditor(TForm *menu,sf::Event ev);

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

	/**
	 * Funcion para simplificar el action control
	 * @param event
	 * @return
	 */
	bool IsPressSpace(sf::Event event);

	/**
	 * Funcion para simplificar el action control
	 * Dice si se ha pulsado la tecla "arriba" en modo accion
	 * @param event
	 * @return
	 */
	bool IsPressUp(sf::Event event);

	/**
	 * Funcion para simplificar el action control
	 * Dice si se ha pulsado la tecla "abajo" en modo accion
	 * @param event
	 * @return
	 */
	bool IsPressDown(sf::Event event);

	/**
	 * Funcion para simplificar el action control
	 * Dice si se ha pulsado la tecla "izquierda" en modo accion
	 * @param event
	 * @return
	 */
	bool IsPressLeft(sf::Event event);

	/**
	 * Funcion para simplificar el action control
	 * Dice si se ha pulsado la tecla "derecha" en modo accion
	 * @param event
	 * @return
	 */
	bool IsPressRight(sf::Event event);

	/**
	 * Funcion para simplificar el action control
	 * @param event
	 * @return
	 */
	bool IsPressEscape(sf::Event event);

	/**
	 * Funcion para simplificar el action control
	 * Dice si se ha pulsado la tecla "Pause" en modo accion
	 * @param event
	 * @return
	 */
	bool IsPressPause(sf::Event event);

	/**
	 * Funcion para simplificar el action control
	 * Dice si se ha pulsado la tecla "Cerrar" en modo accion
	 * @param event
	 * @return
	 */
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
