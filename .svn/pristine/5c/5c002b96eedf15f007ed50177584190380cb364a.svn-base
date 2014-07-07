/*
 * Shape.cc
 *
 *  Created on: 11/02/2012
 *      Author: gallardo
 */

#include "Shape.h"

Shape::Shape() {

	relleno = true;
	shape = Polygon();
	color = Color<float>();
	element = Core::Element::e_shape;
	tamano = 1;

}

Shape::Shape(Color<float> color_) {

	relleno = true;
	shape = Polygon();
	color = color_;
	element = Core::Element::e_shape;
	tamano = 1;

}

Shape::Shape(Polygon shape_, Color<float> color_) {

	relleno = true;
	shape = shape_;
	color = color_;
	element = Core::Element::e_shape;
	tamano = 1;

}

Shape::Shape(Polygon shape_, Color<float> color_, bool relleno_) {

	relleno = relleno_;
	shape = shape_;
	color = color_;
	element = Core::Element::e_shape;
	tamano = 1;

}
Shape::Shape(Polygon shape_) {

	relleno = true;
	shape = shape_;
	color = Color<float>();
	element = Core::Element::e_shape;
	tamano = 1;

}
Shape::Shape(const Shape &s)
{
	relleno = s.relleno;
	shape = s.shape;
	color = s.color;
	element = s.element;
	tamano = s.tamano;
}

Shape::~Shape() {
	relleno = false;
	shape = Polygon();
	color = Color<float>();
	element = Core::Element::e_none;
	tamano = -1;
}

Shape&
Shape::operator =(const Shape &s) {

	if(this != &s)
	{
		this->~Shape();
		relleno = s.relleno;
		shape = s.shape;
		color = s.color;
		element = s.element;
		tamano = s.tamano;
	}

	return *this;
}

Color<float> Shape::getColor() const
{
    return color;
}

Polygon Shape::getShape() const
{
    return shape;
}

void Shape::setColor(Color<float> color_)
{
    this->color = color_;
}

void Shape::setShape(Polygon shape_)
{
    this->shape = shape_;
}

void Shape::exportOpenGL() {

	if(shape.getNVertices() == 2)
	{
		DrawLine(shape.getPuntos()[0], shape.getPuntos()[1], color, tamano);
	}
	else
	{
		if(relleno)
			DrawSolidPolygon(shape, color);
		else
			DrawPolygon(shape, color);
	}
}

bool Shape::isRelleno() const
{
    return relleno;
}

void Shape::setRelleno(bool relleno_)
{
    this->relleno = relleno_;
}

void Shape::setTamano(int t) {
	tamano = t;
}

int Shape::getTamano() {
	return tamano;
}



