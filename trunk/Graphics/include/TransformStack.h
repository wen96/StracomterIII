/*
 * TransformStack.h
 *
 *  Created on: 24/12/2011
 *      Author: gallardo
 */

#ifndef TRANSFORMSTACK_H_
#define TRANSFORMSTACK_H_

#include "Transformacion.h"
#include "GL/gl.h"
#include <stack>


/**\class TransformStack
 * Clase que contiene la pila de transformaciones.*/
class TransformStack {

public:
	/**\brief Constructor por defecto*/
	TransformStack();
	/**\brief Destructor por defecto*/
	virtual ~TransformStack();
	/**\brief Inserta una Transformación en la pila.
	 * \param t Transformación a insertar.*/
	void Push(Transform);
	/**\brief Elimina el tope de la pila, y aplica la siguiente transformación.
	 * \return Devuelve la Transformación*/
	Transform Pop();
	/**\brief Aplica la transformación que se encuentra en el tope de la pila.*/
	void Apply() const;
	/**\brief Devuelve el primer elemento.
	 * Devuelve el tope de la pila pero sin eliminar el elemento.
	 * \return El tope de la pila.*/
	 Transform& Top();
	 /**\brief Devuelve el tamaño de la Pila.
	  * \return Tamaño de la Pila.*/
	 int Size() const;
	 /**\brief Indica si la pila está vacia o no.
	  * \return true si está vacia y false en caso contrario.*/
	 bool Vacia() const;
	 /**\brief Vacia la pila.*/
	 void Empty();


private:
	/**\brief pila
	 * Contiene la estructura de Pila con objetos de tipo Transformacion*/
	 stack<Transform> pila;
};

#endif /* TRANSFORMSTACK_H_ */
