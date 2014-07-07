/*
 * TransformStack.cc
 *
 *  Created on: 24/12/2011
 *      Author: gallardo
 */

#include "TransformStack.h"

TransformStack::TransformStack() {

	//Pila Vacia.

}

TransformStack::~TransformStack() {


	//Vacio la Pila.
	while(!pila.empty())
	{
		pila.pop();
	}

}

void
TransformStack::Apply()  const{

	if(!pila.empty())
	{
		pila.top().exportOpenGL();
	}
}

Transform
TransformStack::Pop() {

	Transform aux;
	if(!pila.empty())
	{
		aux = pila.top();
		pila.pop();
	}

	return aux;
}

void
TransformStack::Push(Transform t) {

	pila.push(t);
}

Transform&
TransformStack::Top() {
	return pila.top();
}

int
TransformStack::Size() const {
	return pila.size();
}

bool
TransformStack::Vacia() const {
	return pila.empty();
}

void
TransformStack::Empty() {
	while(!Vacia())
	{
		pila.pop();
	}
}
