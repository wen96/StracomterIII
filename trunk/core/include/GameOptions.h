/*
 * GameOptions.h
 *
 *  Created on: 17/04/2012
 *      Author: Chutaos team
 */

#ifndef GAMEOPTIONS_H_
#define GAMEOPTIONS_H_

#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;

/**
 *\brief Clase para almacenar la configuracion de opciones del juego.
 * Alamacena opciones del estilo: volumen de sonido, resolucion...
 * EN CONSTRUCCION
 */
class GameOptions {
public:
	/**
	 * Para singletton
	 * @return con el puntero a GameOptions
	 */
	static GameOptions * getInstance();

	/**
	 * Destructor
	 */
	virtual ~GameOptions();

	/**
	 * Carga las opciones desde el fichero pasado por parametro
	 * @param fich
	 * @return con si lo ha cargado o no
	 */
	bool loadData(string fich);

	/**
	 * Guarda las opciones en el fichero pasado por parametro
	 * @param fich con el fichero
	 */
	void saveData(string fich);

	/**
	 * Devuelve el valor del volumen de los efectos
	 * @return con el valor
	 */
    float getEffectsVolume() const;

    /**
	 * Devuelve el valor del volumen de la musica
	 * @return con el valor
     */
    float getMusicVolume() const;

    /**
     * Cambia el valor del volumen de los efectos
     * Valor maximo 100
     * Valor minimo 0
     * @param effectsVolume con el nuevo valor
     */
    void setEffectsVolume(float effectsVolume);

    /**
     * Cambia el valor del volumen de la musica
     * Valor maximo 100
     * Valor minimo 0
     * @param musicVolume con el nuevo valor
     */
    void setMusicVolume(float musicVolume);

    /**
     * Devuelve la variable que almacena la dificultad del juego
     * Grado de dificultad:
	 * Min: 1
	 * Medium: 1.3
	 * Max: 1.5
     * @return con el valor
     */
    float getDificultad() const;

    /**
     * Devuelve el ancho de la ventana
     * @return con el ancho
     */
    int getWindowWidth() const;

    /**
     * Devuelve si la ventana debe estar en pantalla completa o no
     * @return
     */
    bool isFullScreen() const;

    /**
     * Devuelve si los shaders estan activos o no
     * @return
     */
    bool isUseShaders() const;

    /**
     * Cambia la variable que almacena la dificultad del juego
     * Solo admite:
	 * Min: 1
	 * Medium: 1.3
	 * Max: 1.5
     * @param dificultad con el nuevo valor
     */
    void setDificultad(float dificultad);

    /**
     * Cambia si la ventana debe estar a pantalla completa o no
     * @param fullScreen con el nuevo valor
     */
    void setFullScreen(bool fullScreen);

    /**
     * Cambia si se deben usar shaders o no
     * @param useShaders con el nuevo valor
     */
    void setUseShaders(bool useShaders);

    /**
     * Cambia el ancho de la ventana
     * @param windowWidth con el nuevo valor
     */
    void setWindowWidth(int windowWidth);

    /**
     * Devuelve el alto de la ventana
     * @return
     */
    int getWindowHeight() const;

    /**
     * Cambia el alto de la ventana
     * @param windowHeight con el nuevo valor
     */
    void setWindowHeight(int windowHeight);

    /**
     * Cambia el ancho y alto de la ventana a los pasado como parametro
     * @param width
     * @param height
     */
    void setResolution(int width, int height);

    /**
     * Sube en 5 el volumen de la musica
     */
    void upMusicVolume();

    /**
     * Baja en 5 el volumen de la musica
     */
    void downMusicVolume();

    /**
     * Sube en 5 el volumen de los efectos
     */
    void upEffectsVolume();

    /**
     * Baja en 5 el volumen de los efectos
     */
    void downEffectsVolume();

    /**
     * Aumenta la dificultad de la partida a la siguiente
	 * Grado de dificultad:
	 * Min: 1
	 * Medium: 1.3
	 * Max: 1.5
     */
    void upDificult();

    /**
     * Baja el nivel de dificultad e la partida
     * Grado de dificultad:
	 * Min: 1
	 * Medium: 1.3
	 * Max: 1.5
     */
    void downDificult();

    /**
     * Pone el contario a la pantalla completa
     * fullScreen = !fullScreen
     */
    void switchFullScreen();

    /**
     * Pone el contrario a el uso de shaders
     * useShaders = !useShaders
     */
    void switchShaders();

    /**
     * Sube la resolucion
     * Valores:
     * 800x600
     * 1024x768
     */
    void upResolution();

    /**
     * Baja la resolucion
     * Valores:
     * 800x600
     * 1024x768
     */
    void downResolution();

    /**
     * Devuelve el dificultad seleccionada en modo texto
     * Facil: 1
	 * Medio: 1.3
	 * Dificil: 1.5
     * @return con el string resultante
     */
    string getStringDificult();

    bool isParticlesOn();

    void setParticles(bool on);

    void switchParticles();

private:
    /**
     * Constructor
     */
    GameOptions();
    /**
     * Variable para singletton
     */
    static GameOptions *_app;

    /**
     * Funcion que se le pasa un string y te devuelve la propiedad y el valor de la misma
     * Divide el string por el caracter :
     * Ejemplo: musicVolume:10 => property=musicVolume, value=10
     * @param ori String que trocear
     * @param property srting para devolver la propiedad
     * @param value string para devolver el valor
     * @return booleano con si todo ha ido bien o la cadena no es un valor valido
     */
    bool parseString(string ori, string & property, string & value);

    /**
     * Aplica una propiedad por medio de string, para hacer mas comoda su aplicacion cuando se lee de fichero
     * @param property con el valor de la propiedad
     * @param value con el valor de la propiedad
     * @return
     */
    bool setProperty(string property, string value);

    /**
     * Valor de volumen de la musica
     * Min: 0
     * Max: 100
     */
    float musicVolume;

    /**
     * Valor de volumen de los efectos
     * Min: 0
     * Max: 100
     */
    float effectsVolume;

    /**
     * Ancho de la ventana
     */
    int windowWidth;

    /**
     * Alto de la ventana
     */
    int windowHeight;

    /**
     * Pantalla completa
     */
    bool fullScreen;

    /**
     * Usar shaders (efectos graficos avanzados, consumen mas recursos)
     */
    bool useShaders;
    /**
	 * Grado de dificultad:
	 * Min: 1
	 * Medium: 1.3
	 * Max: 1.5
	 */
    float dificultad;

    /**
     * Determina si se muestran las particulas o no.
     */
    bool useParticles;

};

#endif /* GAMEOPTIONS_H_ */
