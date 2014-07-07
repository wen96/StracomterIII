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
#include "GameMenu.h"
#include "GameStrategy.h"
#include "TWindow.h"
#include "TConsole.h"
#include "Map.h"
#include "TPicture.h"
#include "ResourceManager.h"
#include "AnimationControl.h"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "GameStatus.h"
#include "AudioControl.h"
#include "GameOptions.h"

using namespace std;

/**\brief Clase principal del juego
 * Singleton. Lo lanza todo y lo controla todo
 */
class Aplication {
public:
	/**\brief Crea la unica instancia de Aplication
	 *	Comprueba que no exista ninguna instancia de Aplicacion, si la hay devuelve un puntero,
	 *	 si no la crea y devuelve el puntero.
	 *\return Un puntero a la instancia de Aplicacion
	 */
	static Aplication * getInstance();


	/**
	 * Destructor por defecto
	 */
	virtual ~Aplication();

	/**
	 * Funcion que lanza la aplicacion.
	 * Se debe llamar en un main para que la aplicacion se ejecute
	 */
	void Launch();

	/**
	 * Funcion que inicializaliza los elementos de la aplicacion
	 * En estos momentos inicizliza los atributos de la propia clase y llama a los startup necesarios
	 */
	void StartUp();

	/**
	 * Bucle principal del juego
	 */
	void GameLoop();

	/**
	 * Funcion para llamar a la actualizacion en cada iteracion
	 */
	void Update();

	/**
	 * Funcion que llama a los render necesarios en cada iteracion
	 */
	void Render();

	/**
	 * Devuelve el zoom del modo accion actual
	 * Se debe reducir para estar mas lejos
	 * Por defecto -680
	 * @return float con el zoom del modo accion
	 */
    float getZoomAction() const;

    /**
     * Booleano con si el juego se debe mostrar en 3D o en 2D modo depuracion
     * @return booleano con true esta en modo 3D
     */
    bool isMode3D() const;

    /**
     * Cambia si esta el juego en modo 3D o 2D
     * @param mode3D
     */
    void setMode3D(bool mode3D);

    /**
     * Cambia el zoom del modo accion
	 * Se debe reducir para estar mas lejos
	 * Por defecto -680
     * @param zoomAction
     */
    void setZoomAction(float zoomAction);

    /**
     * Devuelve el valor del angulo de la camara en modo accion.
     * Angulo de arriba a abajo respecto el suelo del escenario
     * Valor por defecto -30
     * @return float con el valor del angulo
     */
    float getAngleAction() const;

    /**
     * Cambia el angulo de la camara en modo accion
     * Angulo de arriba a abajo respecto el suelo del escenario
     * Valor por defecto -30
     * @param angleAction con el nuevo valor
     */
    void setAngleAction(float);

    /**
     * Devuelve al angulo de la camara de izquierda a derecha respecto el suelo del escenario
     * Valor por defecto 0
     * @return float con el angulo
     */
    float getAngleCamera();

    /**
     * Cambia al angulo de la camara de izquierda a derecha respecto el suelo del escenario
     * Valor por defecto 0
     * @param angle_ con el nuevo angulo
     */
    void setAngleCamera(float);

    /**
     * Devuelve el puntero del juego en modo accion
     * EN DESUSO
     * @return puntero con el juego en modo accion
     */
    GameAction *getActionGame() const;

    /**
     * Dvuelve el puntero del controlador de menus
     * EN DESUSO
     * @return puntero con el controlador
     */
    GameMenu *getMenuGame() const;

    /**
     * Cambia el puntero del juego en modo accion
     * EN DESUSO
     * @param actionGame
     */
    void setActionGame(GameAction *actionGame);

    /**
     * Cambia el puntero del controlador de menus
     * EN DESUSO
     * @param menuGame
     */
    void setMenuGame(GameMenu *menuGame);

    /**
     * Devuelve los frames por segundo a los que esta funcionando el videojuego
     * @return float con el numero de imagenes del la ultima iteracion
     */
    float getFps() const;

    /**
     * Absurda funcion sin ningun sentido
     * @param fps
     */
    void setFps(float fps);

    /**
     * Cambia el mapa por defecto que va a cargar el juego.
     * Cuando al juego se le pasa un mapa por parametro de almacena aqui
     * @param map_ string con al ruta del mapa
     */
    void setMap(string map_);

    /**
     * Funcion para modular y mejorar el aspecto del codigo
     * @param event
     */
    void controlOption(int event);

    /**
     * Devuelve un puntero al estado del juego.
     * Funcion innecesaria y peligrosa ya que GameStatus es una clase singletton
     * @return puntero al estado
     */
    GameStatus *getGameSelections() const;

    /**
     * Esta funcion es todavia mas absurda que la de arriba
     * @param gameSelections
     */
    void setGameSelections(GameStatus *gameSelections);

	/**
	 * Cadena con la ruta del mapa actual cargado como xml
	 */
	string defaultMap;

private:
	/**
	 * Contructor privado (Es singgletton o como se escriba)
	 */
	Aplication();

	/**
	 * Puntero para el singletton ese
	 */
	static Aplication *_app;

	/**
	 * Mapa a cargar
	 */
	Map *mapa;

	/**
	 * Control del juego en modo accion
	 */
	GameAction *actionGame;

	/**
	 * Control del juego en modo menu
	 */
	GameMenu *menuGame;

	/**
	 * Control del juego en modo estrategia
	 */
	GameStrategy *strategyGame;

	/**
	 *Controlador de ventana
	 * En estos momentos capa de abstraccion de sfml
	 */
	TWindow *window;

	/**
	 * Interfaz humana
	 * Captura de ventos de teclado y raton
	 */
	HIDControl *hid;

	/**
	 * Capa de abstraccion de sfml para la captura de eventos en tiempo real
	 */
	IOControl *ioEvents;

	/**
	 * Consola de comandos
	 */
	TConsole *consola;

	/**
	 * Gestor de recursos
	 */
	ResourceManager *resManager;

	/**
	 * Enumerado para controlar que controlador ejecutar
	 */
	Core::GameMode::Mode currentMode;	// modo en el que estamos (action, menu o strategy

	/**
	 * Enumerado que controla el menu a mostrar
	 */
	Graphics::Menus::Index currentMenu;

	/**
	 * Disty bit para cambiar de modo
	 */
	bool startNewMode;	// dirty bit para cambiar de modo

	/**
	 * Booleano con si el juego en modo accion debe mostrar en 2D o 3D
	 * Esto para el proximo Stracomter estara en GameOptions
	 */
	bool mode3D;

	/**
	 * Zoom del juego en modo accion.
	 * Por defecto -680, cuanto mas se decrementa mas lejos se esta
	 * Esto para el proximo Stracomter estara en GameOptions
	 */
	float zoomAction;

	/**
	 * Angulo de arriba a  bajo respecto el suelo del escenario
	 * Valor por defecto -30
	 * Esto para el proximo Stracomter estara en GameOptions
	 */
	float angleAction;

	/**
	 * Angula de la camara de izquierda a derecha respecto el suelo del escenario
	 * Valor por defecto 0
	 * Esto para el proximo Stracomter estara en GameOptions
	 */
	float angleCamera;

	/**
	 * Puntero al controlador de la escena del arbol grafico
	 */
	SceneManager *sm;

	/**
	 * Variable auxiliar para almacenar el frames por segundo a los que esta corriendo el juego
	 */
	float fps;

	/**
	 * Controlador de animaciones, para hacer animaciones de forma mas facil
	 */
	AnimationControl *animationMenu;

	/**
	 * Guarda el estado del juego (vida de personajes, personaje seleccionado, etc)
	 */
	GameStatus *gameSelections;

	/**
	 * Puntero para el control del audio
	 */
	AudioControl *ac;

	/**
	 * Puntero para el control de las opciones de juego
	 */
	GameOptions *gameOptions;

};

#endif /* APLICATION_H_ */
