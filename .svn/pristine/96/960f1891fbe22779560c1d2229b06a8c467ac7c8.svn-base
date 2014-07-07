/*
 * AudioControl.h
 *
 *  Created on: 10/04/2012
 *      Author: Chutaos Team
 */

#ifndef AUDIOCONTROL_H_
#define AUDIOCONTROL_H_
#include "SoundNamespace.h"
#include "TListener.h"
#include "TSound.h"
#include "TSoundBuffer.h"
#include "TMusic.h"
#include "GameOptions.h"
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>

using namespace std;

/**
 * Clase para el control de audio de Stracomter
 * Contiene un vector con todos los sonidos que contendra el Stracomter
 */

class AudioControl {
public:

	/**
	 * Para singletton
	 * @return
	 */
	static AudioControl * getInstance();

	/**
	 * Destructor
	 */
	virtual ~AudioControl();

	/**
	 * Cambia la cancion que se esta escuchando como musica de fondo a otra.
	 * @param song con la nueva cancion a escuchar
	 */
	void switchSong(Audio::Music::Song song);

	/**
	 * Reproduce la musica.
	 * Llama la funcion Play() del objeto de tipo TMusic
	 */
	void playMusic();

	/**
	 * Pausa la musica.
	 * Llama la funcion Pause() del objeto de tipo TMusic
	 */
	void pauseMusic();

	/**
	 * Para la musica.
	 * Llama la funcion Stop() del objeto de tipo TMusic
	 */
	void stopMusic();

	/**
	 * Reproduce un efecto de sonido sin tener en cuenta la posicion del listener
	 * @param ef con el efecto a reproducir
	 */
	void playSound(Audio::Sound::Effect ef);
	/**
	 * Reproduce un sonido pasado como una ruta
	 * Poco eficiente
	 * @param fich
	 */
	void playSound(string fich);
	/**
	 * Reproduce un sonido siendo este relativo al listener, es decir, se atenua segun las caracteristicas del listener
	 * @param ef con el efecto a reproducir
	 * @param pos con la posicion donde se produce el sonido, para el calculo con listener
	 */
	void playSound(Audio::Sound::Effect ef,Point pos);

	/**
	 * Lee de la clase GameOptions los parametros que se aplican a esta clase y los aplica donde pertenece
	 */
	void loadData();

	/**
	 * Reproduce un sonido de tipo pasos en una posicion
	 * Esta funcion utiliza el buffer de sonidos de pasos, que es diferente al resto de sonidos
	 * Existen los 2 buffers para no cortar sonidos con tantos pasos
	 * @param pos con la posicion de los pasos
	 */
	void playSoundStep(Point pos);

private:
	/**
	 * Privado por singletton
	 */
	AudioControl();
	/**
	 * Para singletton
	 */
	static AudioControl *_app;

	/**
	 * Puntero a TMusic para controlar la musica de fonto
	 */
	TMusic *music;

	/**
	 * Buffers de sonido para cargarlos en memoria y no cargarlos desde el disco cada vez
	 */
	vector<TSoundBuffer*> buffers;

	/**
	 * Variable auxiliar
	 */
	TSound sound;
	/**
	 * Iterador del buffer de sonidos sounds. Guarda la posicion de donde se debe reproducir el siguiente sonido
	 */
	int iter_sounds;
	/**
	 * Alamacena un vector de TSound para la repdocciond de sonidos.
	 * Se utiliza un vector, porque si se llama al destructor de la calse TSound se para el sonido, es decir,
	 * si se llega al final de la funcion se llama al destructor y el sonido para antes de que haya terminado
	 */
	TSound sounds[Audio::MAX_SOUNDS];

	/**
	 * Buffer de sonidos de pasos. Esta separado del de sonidos para no chafarlos ya que se producen muchos mas
	 * pasos que sonidos.
	 * Se utiliza un vector, porque si se llama al destructor de la calse TSound se para el sonido, es decir,
	 * si se llega al final de la funcion se llama al destructor y el sonido para antes de que haya terminado
	 */
	TSound steps[Audio::MAX_SOUNDS_STEPS];

	/**
	 * Iterador para sabe en que sonido se va a reproducir el siguietne paso
	 */
	int iter_steps;

	/**
	 * Variable con el volumen que se va a aplicar a los efectos
	 */
	float effectsVolume;
};

#endif /* AUDIOCONTROL_H_ */
