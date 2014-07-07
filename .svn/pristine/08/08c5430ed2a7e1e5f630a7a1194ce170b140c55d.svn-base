/*
 * IOControl.h
 *
 *  Created on: 19/11/2011
 *      Author: Chutaos Team
 */

#ifndef IOCONTROL_H_
#define IOCONTROL_H_
#include <iostream>
#include <SFML/Graphics.hpp>
#include "CoreNamespace.h"
#include "TWindow.h"

using namespace std;

/**\brief Class IOControl
 * Capa de abstraccion de SFML para el control de eventos de ventana
 */
class IOControl {
public:
	/**\brief Constructor por defecto
	 */
	IOControl(TWindow *w);

	/**\brief Destructor
	 */
	virtual ~IOControl();

	/** Funcion IsKeyDown que detecta si esta pulsada una tecla
	 * @param key_ con la tecla que se desea comprobar si esta pulsada
	 * @return bool con true si esta pulsada y false si no
	 */
	bool IsKeyDown(Core::Key::Code key_);

	/** GetMouseX() que devuelve la posicion X del raton en la ventana
	 * Devuelve un entero coincidiendo con el pixel de la barra X como si la pantalla fuera una matriz
	 * @return valor de la x
	 */
	int GetMouseX();

	/** GetMouseY() que devuelve la posicion Y del raton en la ventana
	 * Devuelve un entero coincidiendo con el pixel de la barra Y como si la pantalla fuera una matriz
	 * @return valor de la Y
	 */
	int GetMouseY();

	/** isMouseButtonDown funcion que devuelve si se esta pulsando algun boton del raton
	 * @param b boton que se desea comprobar
	 * @return booleano con si se esta pulsando o no
	 */
	bool isMouseButtonDown(Core::Mouse::Button b);

	/**
	 * Devuelve si el evento pasado por parametro corresponde con presionar la tecla pasado por paramtro
	 * @param event evento de la sfml para comprobar
	 * @param key_ con el codigo de la tecla a comprobar
	 * @return booleano con si se ha pulsado o no
	 */
	bool isKeyPressed(sf::Event event,Core::Key::Code key_);

	/**
	 * Comprueba si el vento corresponde al evento de cerrar la ventana
	 * @param event con el evento
	 * @return con si se ha pulsado o no
	 */
	bool isPressClose(sf::Event event);

	/**
	 * Variable auxiliar para guardar la ventana
	 */
	TWindow *window;
private:


};

#endif /* IOCONTROL_H_ */
