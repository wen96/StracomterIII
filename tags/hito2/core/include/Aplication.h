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
#include <SFML/Graphics.hpp>

using namespace std;

class Aplication {
public:
	/**\brief Crea la unica instancia de Aplication
	 *	Comprueba que no exista ninguna instancia de Aplicacion, si la hay devuelve un puntero,
	 *	 si no la crea y devuelve el puntero.
	 *\return Un puntero a la instancia de Aplicacion
	 */
	static Aplication * getInstance();

	static Aplication * getInstance(string nombreMapa);

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
    float getZoomAction() const;
    bool isMode3D() const;
    void setMode3D(bool mode3D);
    void setZoomAction(float zoomAction);
    float getAngleAction() const;
    void setAngleAction(float);
    float getAngleCamera();
    void setAngleCamera(float);
    GameAction *getActionGame() const;
    GameMenu *getMenuGame() const;
    void setActionGame(GameAction *actionGame);
    void setMenuGame(GameMenu *menuGame);
    float getFps() const;
    void setFps(float fps);

    void setMap(string map_);

private:
	/**
	 * Contructor privado (Es singgletton o como se escriba)
	 */
	Aplication();

	Aplication(string nombreMapa);

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
	 * Cadena con la ruta del mapa actual cargado como xml
	 */
	string defaultMap;

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

	bool mode3D;
	float zoomAction;
	float angleAction;
	float angleCamera;

	SceneManager *sm;

	float fps;
};

#endif /* APLICATION_H_ */
