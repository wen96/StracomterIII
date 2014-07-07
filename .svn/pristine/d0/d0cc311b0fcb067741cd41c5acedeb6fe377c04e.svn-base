/*
 * Scene.h
 *
 *  Created on: 04/11/2011
 *      Author: Chutaos team
 */
#include "EntityManager.h"
#include "MotorGrafico.h"
#include "Entity.h"
#include "ResourceManager.h"
#include "Polygon.h"
#include "Transformacion.h"

#ifndef SCENE_H_
#define SCENE_H_
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>
#include<iostream>
#include<string.h>
#include<stdlib.h>
#include<cstring>
#include<stdio.h>
#include <sstream>
#include "Camera.h"
#include "TransformStack.h"
//#include "TControlMenu.h"
#include "TForm.h"
#include "TWidget.h"
#include "TButton.h"
#include "TLabel.h"
#include "Text.h"
#include "GraphicsNamespace.h"
#include "Tri.h"
#include "NavGraph.h"
#include "AI.h"

using namespace std;

/**\class Scene
 * Escena que contiene elementos.*/
class Scene {
public:
	/**\brief Constructor.
	 * \param entities_ Puntero al EntitiyManager.
	 * \param resources_ Puntero al ResourceManager.
	 * \param w Anchura de la pantalla.
	 * \param h Altura de la pantalla.*/
	Scene(EntityManager *entities_, ResourceManager *resources_, float, float);
	/**\brief Destructor.*/
	virtual ~Scene();
	/**\brief Función que dibuja la escena.*/
	void Draw();

	/** Funcion que pinta un menu del tipo TForm por pantalla
	 * Llama a la funcion Draw() del menu y pinta bien posicionado el raton
	 * @param menu puntero a TFrom con el menu a dibujar
	 */
	void DrawMenu(TForm *menu);

	/** Funcion para dibujar la escena en modo editor
	 * Simplemente una visualizacion diferente, sin hud ni nada parecido para los editores de mapas
	 */
	void DrawModeEditor();

	/**\brief Reescala la pantalla.
	 * \param w Anchura de la pantalla.
	 * \param h Altura de la pantalla.*/
	void Reshape(Point, int);

	void Init(AI *ia);

	void setMode(bool modo);
    bool isDebugOn() const;
    void setDebugOn(bool debugOn);

private:
	/**\brief EntityManager.*/
	EntityManager *entities;
	/**\brief ResourceManager.*/
	ResourceManager *resources;
	/**\brief Anchura de pantalla.*/
	float widht;
	/**\brief Altura de pantalla.*/
	float height;
	/**\Transformación para el escalado*/
	Transform escalado;
	Camera hud;
	Camera game;
	Camera mapa;
	TransformStack pila;

	// Para debug
	AI *ia;
	bool debugOn;

	/** Punto para cuando el player desaparezca, tener la ultima posicion como referencia
	 */
	Point lastPositionPlayer;
};



#endif /* SCENE_H_ */
