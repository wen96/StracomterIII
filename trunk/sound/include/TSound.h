/*
 * TSound.h
 *
 *  Created on: 10/04/2012
 *      Author: Chutaos Team
 */

#ifndef TSOUND_H_
#define TSOUND_H_

#include "Point.h"
#include "SoundNamespace.h"
#include "TSoundBuffer.h"
#include <SFML/Audio.hpp>

/**
 * Clase sonido. Sirve para cargar un sonido y reproducirlo.
 * Los sonidos se ejecutan en segundo plano (otro thread) y la ejecution sigue.
 * PRECAUCION: Si se destruye el objeto o se sobreescribe se parara el sonido que se reproduce. Para que esto no
 * ocurra no destruya el objeto antes de que el estado de la reproduccion se "Stop" (parada)
 * Esta pasanda para cargar sonidos cortos que se cargaran en memoria y posteriormente se reproduciran.
 * Si se desea reproducir un archivo muy largo, es altamente recomendable (debido a la implementacion)
 * que se use la clase TMusic.
 * @see TMusic
 */
class TSound {
public:
	/**
	 * Constructor por defecto.
	 */
	TSound();
	/**
	 * Constructor pasandole un buffer de audio con un sonido cargado.
	 * @param buf puntero al buffer de sonido
	 */
	TSound(TSoundBuffer *buf);

	/**
	 * Constructor de copia
	 * @param s TSound a copiar
	 */
	TSound(const TSound &s);

	/**
	 * Sobrecarga del operador igual
	 * @param p TSound a copiar
	 * @return
	 */
	TSound & operator=(const TSound &p);

	/**
	 * Destructor
	 */
	virtual ~TSound();

	/**
	 * Cambia el valor del volumen del sonido.
	 * Valores: max 100.0 min 0.0. Como floats.
	 * El valor por defecto es 100.
	 * @param vol float con el volumen
	 */
	void setVolume(float vol);
	/**
	 * Devuelve el valor del volumen del sonido.
	 * Valores: max 100.0 min 0.0. Como floats.
	 * El valor por defecto es 100.
	 * @return float con el volumen
	 */
	float getVolume();
	/**
	 * Cambia la posicion del sonido, para cuando es relativo al listener
	 * @param p punto con la posicion
	 */
	void setPosition(Point p);
	/**
	 * Devuelve la posicion del sonido
	 * @return Point con la posicion
	 */
	Point getPosition();

	/**
	 * Marca el factor de atenuacion del sonido.
	 * El factor de atenuacion es un factor multiplicador que hace el sonido mas o menos intenso arreglo a la distancia con el listener.
	 * El valor por defecto es 1.
	 * @param ate float con el valor del factor de atenuaion
	 * @see TListener
	 */
	void setAttenuation(float ate);
	/**
	 * Devuelve el facto de atenuacion del sonido
	 * @return
	 */
	float getAttenuation();

	/**
	 * Cambia si el sonido debe atenuarse arreglo a la poscion del player.
	 * True=> NO DEBE ATENUARSE
	 * FALSE=> SI DEBE ATENUARSE
	 * @param rel con el nuevo valor
	 */
	void setRelativeToListener(bool rel);

	/**
	 * Devuelve si el sonido es relativo al usuario o no
	 * True=> NO SE ATENUA
	 * FALSE=> SI SE ATENUA
	 * @return booleano con el resultado
	 */
	bool isRelativeToListener();
	/**
	 * Cambia a reproduccion en bucle o no
	 * @param l con el nuevo valor
	 */
	void setLoop(bool l);

	/**
	 * Devuelve si el sonido esta en modo bucle o no
	 * @return con el valor
	 */
	bool isLoop();
	/**
	 * El la distancia a partir de la cual empiza a atenuarse el sonido, es decir, la distancia a partir de las que
	 * deja de oirse el sonido al 100%.
	 * El valor por defecto es 1.
	 * @param dist
	 */
	void setMinDistance(float dist);
	/**
	 * Devuelve la distancia minima a partir de la cual se atenua el sonido
	 * @return
	 */
	float getMinDistance();

	/**
	 * Reproducir
	 */
	void Play();

	/**
	 * Pausar
	 */
	void Pause();

	/**
	 * Parar
	 */
	void Stop();

	/**
	 * Devuelve el estado de la pista:
	 * En reproduccion, en pause o parada
	 * @return
	 */
	Audio::Sound::Status getStatus();

	/**
	 * Cambia el buffer de sonido cargado en memoria del cual el sonido reproduce su sonido
	 * @param buf cone l buffer de sonido nuevo
	 */
	void setBuffer(TSoundBuffer buf);
private:
	/**
	 * Elemento Sound de la SFML para su capa de abstraccion
	 */
	sf::Sound sound;
};

#endif /* TSOUND_H_ */
