/*
 * Aplication.h
 *
 *  Created on: 04/11/2011
 *      Author: Chutaos team
 */

#ifndef APLICATION_H_
#define APLICATION_H_

#include <iostream>
#include "GameAction.h"
#include "TWindow.h"
#include <SFML/Graphics.hpp>

using namespace std;

class Aplication {
public:
	/**\brief Crea la unica instancia de Aplication
	 *	Comprueba que no exista ninguna instancia de Aplicacion, si la hay devuelve un puntero,
	 *	 si no la crea y devuelve el puntero.
	 *\return Un puntero a la instancia de Aplicacion
	 */
	Aplication();
	virtual ~Aplication();

	void Launch();
	void StartUp();

private:


	static Aplication *_app;
	GameAction *actionGame;
	TWindow *window;
	HIDControl *hid;
	IOControl *ioEvents;
};

#endif /* APLICATION_H_ */
