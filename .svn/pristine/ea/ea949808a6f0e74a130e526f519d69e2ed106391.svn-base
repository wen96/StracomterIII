/*
 * ActionEvents.h
 *
 *  Created on: 04/11/2011
 *      Author: Chutaos Team
 */

#ifndef ACTIONEVENTS_H_
#define ACTIONEVENTS_H_
#include <ctime>
#include <cstdlib>
#include <cmath>
#include "EntityManager.h"
#include "TWindow.h"
#include "ResourceManager.h"
#include "HIDControl.h"
#include "IOControl.h"
#include "World.h"
#include "Body.h"
#include "Scene.h"
#include "EventControl.h"
#include "Map.h"
#include "AI.h"
#include "unistd.h"
#include "TConsole.h"
#include "SceneManager.h"
#include "GameMenu.h"
#include "CharacterFeature.h"
#include "Camera.h"
#include "Light.h"
#include "Transformacion.h"
#include "Text.h"
#include "Shape.h"
#include "Point.h"
#include "Optimization.h"
#include "Clock.h"
#include "TListener.h"
#include "Object.h"

class Aplication;

const int ESCENARIO = 1;

/**
 *\brief Controlador del juego en modo accion, para no llenar la clase aplication de cosas
 */
class GameAction {
public:
	/**
	 * Constructor por defecto.
	 * Se le debe pasar una ventana, un controlador de ventos y una consola para que funcione
	 * @param w puntero a TWindow (ventana)
	 * @param hid_ puntero a HIDControl (controlador de ventos)
	 * @param cons puntero a TConsole (console)
	 * @param map_ mapa a ejecutar
	 */
	GameAction(TWindow *w, HIDControl *hid_, TConsole *cons, Map *map_);

	/**
	 * Destructor por defecto
	 */
	virtual ~GameAction();

	/** Bucle que lanza el bucle principal del juego
	 * Inutilizado
	 * @return entero con el estado en que ha terminado
	 */
	int Start();

	/**
	 * Inicializador de componentes.
	 * Necesario ejecutar antes de hacer update y render
	 */
	void StartUp();

	/**
	 * Funcion de actualizacion del juego en modo accion
	 */
	int Update();

	/**
	 * Funcion de dibujado del juego en modo accion
	 */
	void Render();

	/**
	 * Get de si el juego se debe pausar en modo accion
	 * Inutilizado
	 * @return booleano con el juego esta pausado o no
	 */
	bool getPaused();

	/**
	 * Set del pause
	 * Inutilizado
	 * @param pause_ booleano con el estado del juego
	 */
	void setPaused(bool pause_);

	/**
	 * Funcion que devuelve la consola...no se muy bien para que
	 * @return
	 */
	TConsole getConsole();

	/**
	 * Funcion que parse un comando en modo accion capturado por la consola
	 * Si se ejecute un comando del estilo "add enemy1 100 100" llegara un vector con los elementos {add, enemy1, 100, 100}
	 * @param input vector de string con el comando enviado
	 * @return
	 */
	int parseCommand(vector<string>);

	/**
	 * Funcion que borra todo lo necesario para relanzar el gameAction
	 */
	void Clear();

	/**
	 * Actualiza los elementos graficos correspondientes, como la vida restante, los puntos, el tiempo
	 */
	void UpdateGraphics();

private:
	/**
	 * Puntero al gestor de entidades
	 */
	EntityManager *manager;

	/**
	 * Puntero al gestor de recusrsos
	 */
	ResourceManager *resources;

	/**
	 * PUntero a ventana pasada en el contructor
	 */
	TWindow *window;

	/**
	 * Puntero a control de ventos pasado por parametro
	 */
	HIDControl *hid;

	/**
	 * Mundo fisico para el modo accion
	 */
	World *world;

	/**
	 * No lo se TODO
	 */
	Scene *scene;

	/**
	 * Control de ventos para el modo accion (disparo, explosion y...no se cosas)
	 */
	EventControl *event;

	/**
	 * Puntero para almacenar el mapa pasado por parametro
	 */
	Map *mapa;

	/**
	 * Puntero para crear los enemigos usando Optimizacion
	 */
	Optimization *opti;


	/**
	 * Control de la IA del juego
	 */
	AI *ia;

	/**
	 * Inutilizado
	 */
	bool gameOver;

	/**
	 * Puntero a controlador de caracteristicas de personajes
	 * Esta clase es capaz de leer caracteristicas de un xml y almacenarlas
	 */
	CharacterFeature *features;

	/**
	 * No lo se TODO
	 */
	SceneManager* sManager;

	/**\brief Estado en que esta el juego
	 */
	Core::GameActionStatus::Mode status;

	/**
	 * Puntero a la consola pasada por parametro
	 */
	TConsole *consola;

	/**
	 * Funcion que transforma un string en un emun.
	 * Tipos aceptados: captain,tecnic,especialist,explosives,enemy1,enemy2,enemy3,miniboss,megaboss
	 * @param nombre string a buscar
	 * @return entero con el enum adecuado al CoreNamespace
	 */
	int getEnum(string nombre);

	/**
	 * En desuso
	 */
	int loadMap;

	/**
	 * Puntero auxiliar al controlador de menus, por comodidad
	 */
	GameMenu *gMenu;

	/**
	 * Puntero a Aplication para la comunicacion, por comodidad
	 */
	Aplication *ap;

	/**
	 * Funcion para liberar la memoria que reserva
	 */
	void resetAction();

	/**
	 * Reloj para controlar los refrescos que sufren algunos elementos de HUD
	 */
	Clock clkUpdateFPS;

	/**
	 * Tiempo del juego
	 */
	Clock gameTime;

	// Para la presentacion
	/**
	 * Booleano para controlar si el juego funciona correctamente, acabondose la partida cuando has matado
	 * a todos los enemigos o pase lo que pase, excepto si mueres, el juego continua.
	 * Se puede cambiar mediante la consola de comandos inGame
	 */
	bool debugMode;

	/**
	 * Para coger la opciones de configuracion
	 */
	GameOptions *gameOptions;

	string selectionMap();
};




#endif /* ACTIONEVENTS_H_ */
