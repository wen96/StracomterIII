/*
 * TListener.h
 *
 *  Created on: 10/04/2012
 *      Author: Chutaos Team
 */

#ifndef TLISTENER_H_
#define TLISTENER_H_

#include "Point.h"
#include <SFML/Audio.hpp>

/**
 * Clase estatica para almacenar la posicion del escuchante.
 * Los sonidos se atenuaran respecto a la posicion del listener.
 * Tambien se puede cambiar el volumen global.
 */
class TListener {
public:
	/**
	 * Cambia la posicion del escuchante al punto pasado por parametro.
	 * @param p Point donde se desea poner el escuchante
	 */
	static void setPosition(Point p);
	/**
	 * Cambia la posicion del escuchante al punto pasado por parametro.
	 * @param x coordenada x del punto
	 * @param y coordenada y del punto
	 * @param z coordenada z del punto
	 */
	static void setPosition(double x, double y, double z);

	/**
	 * Devuelve un punto con la posicion del listener
	 * @return Point con la posicion
	 */
	static Point getPosition();

	/**
	 * Cambia el valor del volumen global del escuchante.
	 * Valores: max 100.0 min 0.0. Como floats.
	 * @param vol float con el valor del volumen
	 */
	static void setVolumen(float vol);
	/**
	 * Devuelve el valor de volumen actual del listener
	 * Valores: max 100.0 min 0.0. Como floats.
	 * @return float con el valor del volumen
	 */
	static float getVolumen();
};

#endif /* TLISTENER_H_ */
