/*
 * Animation.h
 *
 *  Created on: 27/03/2012
 *      Author: Chutaos Team
 */

#ifndef ANIMATION_H_
#define ANIMATION_H_

#include <iostream>
#include <cmath>
#include "Entity.h"
#include "Clock.h"

/**
 * Clase que con la que se le puede crear una animacion a una entidad o a una transformacion
 * Para crear varios efectos a la vez, se deben crear distintas instancias de esta clase
 * Por el momento si que funcionaria si se aplica una por transformacio y otra por entity
 * Las entity solo funcionan en 2 dimensiones
 */
class Animation {
public:
	/**
	 * Crea una animacion de tipo entidad
	 * Si se quieren varios tipo, utilizar el set
	 *
	 * @param entityAnimated_
	 */
	Animation(Entity *entityAnimated_);
	/**
	 * Crea una animacion de tipo transformacion
	 * Si se quieren varios tipo, utilizar el set
	 * @param transformAnimated_
	 */
	Animation(Transform *transformAnimated_);

	/**
	 * Crea una animacion con los dos tipos
	 *
	 * @param entityAnimated_
	 * @param transformAnimated_
	 */
	Animation(Entity *entityAnimated_,Transform *transformAnimated_);

	/**
	 * Destructor
	 */
	virtual ~Animation();

	/**
	 * Reinicio de variables para constructor y destructor
	 */
	void initializeVars();

	/**
	 * Reinicia la animacion
	 */
	void init();

	/**
	 * Da un paso de ejecucion
	 * Llama a las funciones de step de cada efecto
	 * Devuelve si ha terminado o no
	 * @return true si ha terminado y false si no
	 */
	bool step();

	/**
	 * Lanza la animacion y hace step hasta que termina la animacion
	 */
	void play();

	/**
	 * NOTA IMPORTANTE: Si creas una animacion de un tipo concreto recuerda hacer el create adecuado:
	 * Entity: createTranslation,createRotation,createFade
	 * Transform: createTranslationTransform, createRotationTransform
	 */

	/**
	 * Crear una translacion para la entidad en 3 dimensiones que solo funciona en 2 dimensiones
	 * Las traslaciones son en cantidades, es decir, no va hacia un punto si no que se mueve una cantidad
	 * en un punto. Por ejemplo:
	 * Point(100,100,0) => Point(-100,-100,0)
	 * Esto se movera 100 pixeles positivos en x y 100 en y luego volvera 100 en x y 100 en y volviendo asi
	 * a su poisicion original.
	 * @param points_ Vector de puntos a recorrer
	 */
	void createTranslation(vector<Point> points_);

	/**
	 * Crea una translacion para una transformacion
	 * Las traslaciones son en cantidades, es decir, no va hacia un punto si no que se mueve una cantidad
	 * en un punto. Por ejemplo:
	 * Point(100,100,0) => Point(-100,-100,0)
	 * Esto se movera 100 pixeles positivos en x y 100 en y luego volvera 100 en x y 100 en y volviendo asi
	 * a su poisicion original.
	 * @param points_
	 */
	void createTranslationTransform(vector<Point> points_);

	/**
	 * Crea una animacion de rotacion para una entidad (2 dimensiones)
	 * Girara desde su posicion original hasta los grados pasados por parametro
	 * @param grados_
	 */
	void createRotation(vector<float> grados_);

	/**
	 * Crea una animacion de rotacion para transformacion
	 * Girara desde su posicion original hasta los grados pasados por parametro
	 * @param v
	 */
	void createRotationTransform(vector<vector<float> > v);

	/**
	 * Crea una traslacion de color recorriendo los colores del vector
	 * @param colores_ vector de los colores
	 */
	void createFade(vector<Color<float> > colores_);

	/**
	 * Funcion para dar un paso en traslacion
	 * Usada por la funcion step
	 * @return
	 */
	bool stepTranslation();

	/**
	 * Funcion para dar un paso en rotacion
	 * Usada por la funcio step
	 * @return
	 */
	bool stepRotation();

	/**
	 * Funcion para dar un paso en la transicion de color
	 * Usado por la funcion step
	 * @return
	 */
	bool stepFade();


	/*
	 * GETTERS AND SETTERS PASO DE COMENTARLOS, LUEGO COMENTO LAS VARIABLES
	 */
	/**
	 *
	 * @return
	 */
    vector<Color<float> > getColores() const;
    /**
     *
     * @return
     */
    Entity *getEntity() const;
    /**
     *
     * @return
     */
    vector<Point> getRecorrido() const;
    /**
     *
     * @return
     */
    vector<float> getRotaciones() const;
    /**
     *
     * @return
     */
    Transform *getTranform() const;
    /**
     *
     * @return
     */
    bool isAnimFadeColor() const;
    /**
     *
     * @return
     */
    bool isAnimRotation() const;
    /**
     *
     * @return
     */
    bool isAnimTranlation() const;
    /**
     *
     * @param animFadeColor
     */
    void setAnimFadeColor(bool animFadeColor);
    /**
     *
     * @param animRotation
     */
    void setAnimRotation(bool animRotation);
    /**
     *
     * @param animTranlation
     */
    void setAnimTranlation(bool animTranlation);
    /**
     *
     * @param colores
     */
    void setColores(vector<Color<float> > colores);
    /**
     *
     * @param entity
     */
    void setEntity(Entity *entity);
    /**
     *
     * @param recorrido
     */
    void setRecorrido(vector<Point> recorrido);
    /**
     *
     * @param rotaciones
     */
    void setRotaciones(vector<float> rotaciones);
    /**
     *
     * @param tranform
     */
    void setTranform(Transform *tranform);
    /**
     *
     * @return
     */
    int getTimeAnimation() const;
    /**
     * En milisegundos
     * @param timeAnimation
     */
    void setTimeAnimation(int timeAnimation);


private:
	Entity *entity;
	Transform *transform;
	int timeAnimation;
	Clock clockEntity;
	Clock clockTransform;


	bool animTranlation;
	vector<Point> recorrido;
	int actualTrans;
	Point lastPoint;
	float lastPorcent;
	Point totalTranslated;

	bool animRotation;
	vector<float> rotaciones;
	int actualRot;
	float lastAngle;

	vector<vector<float> > rotTransform;
	vector<float> lastRotTransform;

	bool animFadeColor;
	vector<Color<float> > colores;
	int actualColor;
	Color<float> lastColores;
};

#endif /* ANIMATION_H_ */
