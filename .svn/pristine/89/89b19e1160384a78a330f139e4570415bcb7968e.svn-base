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
	/**\brief Reescala la pantalla.
	 * \param w Anchura de la pantalla.
	 * \param h Altura de la pantalla.*/
	void Reshape(float, float);
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
};



#endif /* SCENE_H_ */
