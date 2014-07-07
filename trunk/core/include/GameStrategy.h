/*
 * GameStrategy.h
 *
 *  Created on: 26/12/2011
 *      Author: Chutaos Team
 */

#ifndef GAMESTRATEGY_H_
#define GAMESTRATEGY_H_

#include "TForm.h"
#include "HIDControl.h"

/**
 *\brief Inutilizado por el momento
 */
class GameStrategy {
public:
	/**
	 * Constructor
	 * @param hid_
	 * @param menu_
	 */
	GameStrategy(HIDControl *hid_,TForm* menu_);
	/**
	 * Destructor
	 */
	virtual ~GameStrategy();

	/**
	 * Actualizacion para llamar en el bucle principal
	 * @return
	 */
	int Update();

	/**
	 * Renderizado para llamar en el buble principal
	 */
	void Render();

	/**
	 * Inicializador
	 * @return
	 */
	int Start();
private:
	/**
	 * Puntero al menu de estrategia
	 */
	TForm *menu;
    /**
     * HID para control de eventos de menu
     */
    HIDControl *hid;
};

#endif /* GAMESTRATEGY_H_ */
