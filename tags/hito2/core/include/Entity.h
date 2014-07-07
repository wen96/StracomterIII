/*
 * Element.h
 *
 *  Created on: 04/11/2011
 *      Author: Chutaos Team
 */

#ifndef ENTITY_H_
#define ENTITY_H_

#include "Point.h"
#include "ResourceManager.h"
#include "CoreNamespace.h"
#include "Color.h"
#include "Body.h"
#include "BodyData.h"
#include "World.h"
#include "Element.h"
#include "Transformacion.h"

class GraphicNode;

/**\brief Class Entity
 * Clase Entity, es una clase abstracta que se encargara de actuar de interfaz de todos los elementos que existan en el mapa
 */
class Entity : public Element {
public:
	/**\brief Constructor por defecto
	 * Inutil, es una clase abstracta.
	 */
	Entity();

	/**
	 * Constructor de copi
	 * @param ent entidad a copiar
	 */
	Entity(const Entity &ent);

	/**
	 * Sobrecarga del operador igual
	 * @param ent entidad a copiar
	 * @return entidad copiada
	 */
	Entity& operator=(const Entity &ent);

	/**\brief Destructor por defecto
	 * Declarado inline, tan solo pondra la propiedad visible a true.
	 */
	virtual ~Entity();

	/** getCenter, devuelve el centro de la entidad calculado por el motor de fisica
	 * @return Point con las cordenadas de la posicion
	 */
	Point getCenter() const;

	/** getAngle, devuelve el angulo calculado por el motor de fisica
	 * @return float cone l valor en grados del angulo
	 */
	float getAngle() const;

	/**
	 * Devuelve el id del personaje
	 * @return id
	 */
	int getId() const;

	/**
	 * Devuelve si el enemigo se puede mover o no
	 * @return
	 */
	bool getMovable() const;

	/**
	 * Devuelve si el objeto es pequenyo o no
	 * Si es pequenyo no se puede pasar por encima de el pero si que se puede disparar por encima de el
	 * @return booleano con si es pequenyo o no
	 */
	bool getSmall() const;

	/**
	 * Booleano para saber si la entidad es visible o no
	 * Sirve para se detectado por la IA o para ser dibujado o no por el motor grafico
	 * @return
	 */
	bool getVisible() const;

	/**
	 * Devuelve el tipo de entidad
	 * @return
	 */
	Core::Entities::Type getType() const;

	/**
	 * Devuelve un puntero al gestor de recursos
	 * Se utiliza para saber la forma del personaje al ser creada su entidad fisica
	 * @return
	 */
	ResourceManager *getResource() const;

	/**
	 * Devuelve el color por defecto del personaje
	 * @return
	 */
	Color<float> getColor() const;

	/**
	 * Devuelve una fuerza del tipo force TODO
	 * Siendo sincero, la verdad es que no tengo ni punyetera idea de donde ha salido esto ni para que sirve
	 * Creo que es totalmente inutil
	 * @return
	 */
	Force getForce() const;

	/**
	 * Devuelve el centro fisico si existe y si no el de la varibale center
	 * @param cen
	 */
	void setCenter(Point cen);

	/**
	 * Aplica un angulo a una entidad
	 * @param angle_
	 */
	void setAngle(float angle_);

	/**
	 * Cambia el id de una entidad
	 * @param ide
	 */
	void setId(unsigned int ide);

	/**
	 * Cambia la movilidad de un personaje
	 * NO USAR: Se decide por el tipo no por la variable
	 * @param m
	 */
	void setMovable(bool m);

	/**
	 * Cambia si es pequenyo o no
	 * @param s
	 */
	void setSmall(bool s);

	/**
	 * Cambia si es visible
	 * @param v
	 */
	void setVisible(bool v);

	/**
	 * Cambia la variable de tipo
	 * Cuidado: NO RECARGA LAS CARACTERISTICAS
	 * @param type_
	 */
	void setType(Core::Entities::Type type_);

	/**
	 * Para guardar el puntero al gestor de recursos
	 * @param resource
	 */
	void setResource(ResourceManager *resource);

	/**
	 * Cambia el color base
	 * @param color
	 */
	void setColor(Color<float> color);

	/**
	 * Aplica la fuerza que usa la entidad
	 * @param f
	 */
	void setForce(Force f);

	/**
	 * Aplica la fuerza para moverse
	 * Llama a la funcion setLinearVelocity con la fuerza
	 */
	void applyForce();

	/**
	 * Le aplica la fuerza pasada por parametro
	 * @param f
	 */
	void applyForce(Force f);

	/**
	 * Da velocidad al personaje en x e y
	 * @param f
	 */
	void addLinearVelocity(Force f);

	/**
	 * cambia la velocidad al personaje en x e y
	 * @param f
	 */
	void setLinearVelocity(Force f);

	/**
	 * Anayade un angulo al ya existente
	 * engleActual + newAngle
	 * @param a
	 */
	void addAngle(float a);

	/**
	 * Devuelve el cuerpo fisico de la entidad
	 * @return
	 */
	Body* getBody();

	/**
	 * Devuelve el id de su display list para dibujar con Opengl
	 * @return
	 */
	int getIdDisplay();

	/**
	 * Funcion para generar la colision de la entidad
	 * Puro para obligar a implementarlo en todas las entidades
	 */
	virtual void generateCollision()=0;

	/**
	 * No usado
	 * @return
	 */
    bool isDirtyBit() const;

    /**
     * Devuelve si se puede mover o no la entidad
     * @return
     */
    bool isMovable() const;

    /**
     * Devuelve si la entidad es un obstaculo del cual se puede disparar a traves
     * @return
     */
    bool isSmall() const;

    /**
     * Devuelve si la entidad es visible o no
     * NO SE PORQUE NO FUNCIONA TODO
     * @return
     */
    bool isVisible() const;

    /**
     * Cambia el body del personaje al pasado por parametro
     * @param body
     */
    void setBody(Body *body);

    /**
     * Cambia el ditibyt
     * @param dirtyBit
     */
    void setDirtyBit(bool dirtyBit);

    /**
     * Funcion porque no funciona la de isVisible
     * @return
     */
    bool soyVisible(){return visible;}

    void set2DNode(GraphicNode* nodo2d_) {
    	nodo2d = nodo2d_;
    }

    GraphicNode * get2DNode() {
    	return nodo2d;
    }

protected:
    /**
     * Cuerpo fisico
     */
	Body *body;

	/**
	 * Tipo de la entidad
	 */
	Core::Entities::Type type;

	/**
	 * Id de la entidad
	 */
    int id;

    /**
     * Punto en el que se encuentra la entidad
     */
    Point center;

    /**
     * Angulo de la entidad
     */
    float angle;
    /**
     * Puntero al gestor de recursos para saber crea su forma fisica
     */
    ResourceManager *resource;

    /**
     * Color base
     */
    Color<float> color;

    /**
     * Fuerza de la entidad
     */
    Force force;

    /**
     * Es visible o no
     */
    bool visible;

    /**
     * Se puede mover o no
     */
    bool movable;

    /**
     * Es pequenya o no
     */
    bool small;

    /**
     * En desuso
     */
    bool dirtyBit;

    /**
     * id Para la display list de opengl
     */
    int idDisplay;

    GraphicNode* nodo2d;

};





#endif /* ENTITY_H_ */
