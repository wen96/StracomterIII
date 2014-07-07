/*
 * Shape.cc
 *
 *  Created on: 11/02/2012
 *      Author: gallardo
 */

#include "Shape.h"
#include "SceneManager.h"

Shape::Shape() {

	relleno = true;
	shape = Polygon();
	color = Color<float>();
	element = Core::Element::e_shape;
	tamano = 1;
	cadena = false;
	conTextura = false;
}

Shape::Shape(Color<float> color_) {

	relleno = true;
	shape = Polygon();
	color = color_;
	element = Core::Element::e_shape;
	tamano = 1;
	cadena = false;
	conTextura = false;
}

Shape::Shape(Polygon shape_, Color<float> color_) {

	relleno = true;
	shape = shape_;
	color = color_;
	element = Core::Element::e_shape;
	tamano = 1;
	cadena = false;
	conTextura = false;
}

Shape::Shape(Polygon shape_, Color<float> color_, bool relleno_) {

	relleno = relleno_;
	shape = shape_;
	color = color_;
	element = Core::Element::e_shape;
	tamano = 1;
	cadena = false;
	conTextura = false;
}
Shape::Shape(Polygon shape_) {

	relleno = true;
	shape = shape_;
	color = Color<float>();
	element = Core::Element::e_shape;
	tamano = 1;
	cadena = false;
	conTextura = false;
}

Shape::Shape(Point c, float r , Textura *t){

	vector<Point> vPuntos;
	Point aux;
	element = Core::Element::e_shape;

	aux.setZ(5);
	aux.setX(c.getX() - r/2.0);
	aux.setY(c.getY() - r/2.0);

	vPuntos.push_back(aux);

	aux.setX(c.getX() + r/2.0);
	aux.setY(c.getY() - r/2.0);

	vPuntos.push_back(aux);

	aux.setX(c.getX() + r/2.0);
	aux.setY(c.getY() + r/2.0);

	vPuntos.push_back(aux);

	aux.setX(c.getX() - r/2.0);
	aux.setY(c.getY() + r/2.0);

	vPuntos.push_back(aux);

	shape = Polygon(Point(), vPuntos);
	textura = t;
	conTextura = true;
	cadena = false;

}

Shape::Shape(vector<Point> vPoint){
	relleno = false;
	shape = Polygon(vPoint);
	color = Color<float>();
	element = Core::Element::e_shape;
	tamano = vPoint.size();
	cadena = true;
	conTextura = false;
}

Shape::Shape(const Shape &s) {
	relleno = s.relleno;
	shape = s.shape;
	color = s.color;
	element = s.element;
	tamano = s.tamano;
	cadena = s.cadena;
	conTextura = s.conTextura;
	textura = s.textura;
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

	if (this != &s) {
		this->~Shape();
		relleno = s.relleno;
		shape = s.shape;
		color = s.color;
		element = s.element;
		tamano = s.tamano;
		cadena = s.cadena;
		conTextura = s.conTextura;
		textura = s.textura;
	}

	return *this;
}

Color<float> Shape::getColor() const {
	return color;
}

Polygon Shape::getShape() const {
	return shape;
}

void Shape::setColor(Color<float> color_) {
	this->color = color_;
}

void Shape::setShape(Polygon shape_) {
	this->shape = shape_;
	cadena = false;
}

void Shape::setShape(vector<Point> vPoint){
	this->shape = Polygon(vPoint);
	cadena = true;
}

void Shape::exportOpenGL() {

	if(cadena){
		vector<Point> puntos = shape.getPuntos();
		vector<Point>::iterator iter;
		for(iter = puntos.begin(); iter != puntos.end() - 1; iter++){
			DrawLine(*iter, *(iter+1), color, tamano);
		}
	}else if(conTextura) {
		//glEnable(GL_BLEND);
		//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		vector<Point> vPuntos = shape.getPuntos();
		vPuntos[0].setZ(2);
		if (SceneManager::getInstance()->isShaderActive())
						ResourceManager::getInstance()->activateShader(Graphics::Shader::Phong);
		int idTextura = ResourceManager::getInstance()->getTexturas()[Graphics::Texturas::t_explosion];

		Textura::ActivarTextura(idTextura);

		glBegin(GL_QUADS);

		glNormal3d(0,0,1);
		glColor4d(1,1,1,0.8);

		glTexCoord2d(0,0);
		glVertex3d(vPuntos[0].getX(), vPuntos[0].getY(), vPuntos[0].getZ());
		//glVertex3d(0,0,3);

		glTexCoord2d(1,0);
		glVertex3d(vPuntos[1].getX(), vPuntos[1].getY(), vPuntos[0].getZ());
		//glVertex3d(100,0,3);

		glTexCoord2d(1,1);
		glVertex3d(vPuntos[2].getX(), vPuntos[2].getY(), vPuntos[0].getZ());
		//glVertex3d(100,100,3);

		glTexCoord2d(0,1);
		glVertex3d(vPuntos[3].getX(), vPuntos[3].getY(), vPuntos[0].getZ());
		//glVertex3d(0,100,3);

		glEnd();
		Textura::DesactivarTextura();
		//glEnable(GL_DEPTH_TEST);
		if (SceneManager::getInstance()->isShaderActive())
					ResourceManager::getInstance()->deactivateShader(Graphics::Shader::Phong);

		/*Textura::ActivarTextura(textura.getTexture());
		glBegin(GL_QUADS);
			glColor3d(1,1,1);

			glTexCoord2d(0,0);
			glVertex3d(0,0,1);
			glTexCoord2d(0,1);
			glVertex3d(0,100,1);
			glTexCoord2d(1,1);
			glVertex3d(100,100,1);
			glTexCoord2d(1,0);
			glVertex3d(100,0,1);
		glEnd();

		Textura::DesactivarTextura();*/
		//glDisable(GL_BLEND);
	}
	else if (shape.getNVertices() == 2) {
		DrawLine(shape.getPuntos()[0], shape.getPuntos()[1], color, tamano);
	} else {
		if (relleno)
			DrawSolidPolygon(shape, color);
		else
			DrawPolygon(shape, color);
	}
}

bool Shape::isRelleno() const {
	return relleno;
}

void Shape::setRelleno(bool relleno_) {
	this->relleno = relleno_;
}

void Shape::setTamano(int t) {
	tamano = t;
}

int Shape::getTamano() {
	return tamano;
}

