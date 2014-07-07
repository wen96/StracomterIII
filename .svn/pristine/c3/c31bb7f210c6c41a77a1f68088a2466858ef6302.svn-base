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
	 */
	void actionControl(EntityManager *entities);

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
private:
	/** Varible events, puntero para controlar los eventos de teclado y raton que se producen en tiempo real
	 */
	IOControl *events;
};

#endif /* HIDCONTROL_H_ */
