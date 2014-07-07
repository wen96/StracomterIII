/*
 * Clock.h
 *
 *  Created on: Mar 17, 2012
 *      Author: rellik
 */

#ifndef CLOCK_H_
#define CLOCK_H_

#include <iostream>
using namespace std;
#include <string>
#include <SFML/System.hpp>
#include <cstdio>

/**
 * Clase Clock, implementa un reloj
 */
class Clock{
public:
	Clock();
	Clock(bool paused_);
	~Clock();

	Clock(const Clock &pc);
	Clock & operator=(const Clock &pc);

	/**
	 * Empieza el contador del reloj
	 */
	void Start();

	/**
	 * Resetea el tiempo del reloj
	 * @param paused Determina si al resetear el reloj estara parado o no
	 */
	void Reset(bool paused=false);

	/**
	 * Para el reloj y resetea el contador
	 */
	void Stop();

	/**
	 * Pausa el reloj, pero no resetea el tiempo
	 */
	void Pause();

	/**
	 * Despausa el reloj
	 */
	void Unpause();

	/**
	 * Obtiene el tiempo que el reloj ha estado en marcha
	 * @return Tiempo en milisegundos
	 */
	int getElapsedMiliseconds();

	/**
	 * btiene el tiempo que el reloj ha estado en marcha
	 * @return Tiempo en segundos
	 */
	int getElapsedSeconds();

	/**
	 * Convierte el estado del reloj en un string
	 * @return
	 */
	string toString();

	/**
	 * Determina si el reloj esta pausado o no
	 * @return
	 */
	bool isPaused();
private:
	sf::Clock reloj;
	bool paused;
	int elapsedTime;
};


#endif /* CLOCK_H_ */
