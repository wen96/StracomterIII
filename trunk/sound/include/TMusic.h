/*
 * Musica.h
 *
 *  Created on: 01/04/2012
 *      Author: Chutaos Team
 */

#ifndef MUSICA_H_
#define MUSICA_H_

#include <iostream>
#include <SFML/Audio.hpp>
#include "SoundNamespace.h"
using namespace std;

/**
 * Clase para reproducir un sonido via streaming (desde un fichero en disco).
 * Esta pensaba para reproducir una pista en segundo plano (otro thread) leyendo desde un fichero en disco.
 * Es más eficiente porque no carga el sonido en memoria.
 */
class TMusic {
public:
	/**
	 * Constructor por defecto
	 */
	TMusic();
	/**
	 * Constructor
	 * @param bucle con un booleano indicando si la cancion debe repertirse en bucle o no
	 */
	TMusic(bool bucle);
	/**
	 * Destructor
	 */
	virtual ~TMusic();

	/**
	 * Abre un archivo para reproducir
	 * @param ruta string con la ruta del archivo a reproducir
	 * @return booleano con si se ha podido abrir el archivo o no
	 */
	bool OpenFile(string ruta);

	/**
	 * Cambia el volumen de la musica
	 * Por defecto: 100
	 * Max: 100
	 * Min: 0
	 * @param volumen float con el nuevo volumen
	 */
	void setVolume(float volumen);

	/**
	 * Cambiar el estado e repeticion continua
	 * @param bucle con el nuevo estado
	 */
	void setLoop(bool bucle);

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
	Audio::Music::Status GetStatus();
private:
	/**
	 * Elemento music de SFML para la capa de abstraccion
	 */
    sf::Music music;
};

#endif /* MUSICA_H_ */
