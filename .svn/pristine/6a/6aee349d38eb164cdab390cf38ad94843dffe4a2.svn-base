/*
 * Element.cc
 *
 *  Created on: 01/01/2012
 *      Author: Chutaos Team
 */

#include "Element.h"
#include "GraphicTree.h"

Element::Element() {
	element = Core::Element::e_none;

}

Element::~Element() {
	element = Core::Element::e_none;
}

Core::Element::Type
Element::getElementType() const {
	return element;
}

Element&
Element::operator=(const Element &e) {

	if(this != &e)
	{
		this->~Element();
		element = e.element;
	}

	return *this;
}

Element::Element(const Element& e){
	element = e.element;
};

string
Element::getName() const{

	string nombre;

	switch(element) {

	case Core::Element::e_camera:
		nombre = "Camera";
		break;
	case Core::Element::e_entity:
		nombre = "Entity";
		break;
	case Core::Element::e_light:
		nombre = "Light";
		break;
	case Core::Element::e_transform:
		nombre = "Transform";
		break;
	case Core::Element::e_shape:
		nombre = "Shape";
		break;
	case Core::Element::e_model:
		nombre = "Model";
		break;
	case Core::Element::e_texture:
		nombre = "Textura";
		break;
	case Core::Element::e_text:
		nombre = "Text";
		break;
	case Core::Element::e_menu:
		nombre = "Menu";
		break;
	case Core::Element::e_form:
		nombre = "Form";
		break;
	case Core::Element::e_none:
		nombre = "None";
		break;
	default:
		break;
	}
	return nombre;
}

GraphicNode *Element::getNodo() const
{
    return nodo;
}

GraphicNode *Element::getPadre() const
{
    return padre;
}

void Element::setNodo(GraphicNode *nodo_)
{
    this->nodo = nodo_;
}

void Element::setPadre(GraphicNode *padre_)
{
    this->padre = padre_;
}


