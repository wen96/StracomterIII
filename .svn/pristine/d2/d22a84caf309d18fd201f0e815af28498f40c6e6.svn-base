/*
 * TSoundBuffer.h
 *
 *  Created on: 10/04/2012
 *      Author: Chutaos Team
 */

#ifndef TSOUNDBUFFER_H_
#define TSOUNDBUFFER_H_

#include <SFML/Audio.hpp>
#include <iostream>
using namespace std;

/**
 * Buffer de sonido. Carga un archivo de sonido en memoria para poder ser usado cuando se quiera.
 * Se usa en la clase TSoound, para cargar los sonidos tan solo una vez y luego reproducirlo tantas veces
 * como se desee desde con distintos TSound
 */
class TSoundBuffer {
public:
	/**
	 * Constructor por defecto
	 */
	TSoundBuffer();
	/**
	 * Constructor con la ruta de un sonido
	 * @param ruta string con la ruta del sonido
	 */
	TSoundBuffer(string ruta);
	/**
	 * Constructor de copia
	 * @param buf
	 */
	TSoundBuffer(const TSoundBuffer &buf);

	/**
	 * Sobrecarga del operador igual
	 * @param p
	 * @return
	 */
	TSoundBuffer & operator=(const TSoundBuffer &p);

	/**
	 * Destructor
	 */
	virtual ~TSoundBuffer();

	/**
	 * Carga un archivo de sonido mediante una ruta
	 * @param ruta string con la ruta del archivo
	 * @return booleano con si se ha podido cargar o no
	 */
	bool LoadFile(string ruta);

	/**
	 * Devuelve el puntero real de buffer de sonido de la SFML
	 * No ser recomienda usar esta funcion
	 * @return
	 */
    sf::SoundBuffer* getBuffer() const;

    /**
     * Cambia el puntero de sonido de la SFML
     * Utilizarla causa perdidas de memoria.
     * @param buffer
     */
    void setBuffer(sf::SoundBuffer *buffer);
private:
    /**
     * Puntero a Buffer de sonido de la SFML para la capa de abstraccion
     */
    sf::SoundBuffer *Buffer;
};

#endif /* TSOUNDBUFFER_H_ */
