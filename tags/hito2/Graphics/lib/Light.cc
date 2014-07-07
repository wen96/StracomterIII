/*
 * Light.cc
 *
 *  Created on: 02/02/2012
 *      Author: Chutaos Team
 */

#include "Light.h"

Light::Light() {
	posicion = Point();
	especular = Color<float>();
	difusa = Color<float>();
	ambiente = Color<float>();
	element = Core::Element::e_light;
	id = 0;
	light = 0;
	active = true;
}

Light::Light(int id_) {
	posicion = Point();
	especular = Color<float>();
	difusa = Color<float>();
	ambiente = Color<float>();
	element = Core::Element::e_light;
	id = id_;
	light = id%8;
	active = true;
}

Light::Light(Color<float> amb, Color<float> dif, Color<float> esp, Point pos)
{
	posicion = pos;
	especular = esp;
	difusa = dif;
	ambiente = amb;
	element = Core::Element::e_light;
	id = 0;
	light = 0;
	active = true;
}

Light::Light(Color<float> amb, Color<float> dif, Color<float> esp, Point pos, int id_)
{
	posicion = pos;
	especular = esp;
	difusa = dif;
	ambiente = amb;
	element = Core::Element::e_light;
	id = id_;
	light = id%8;
	active = true;
}

Light::~Light() {
	posicion = Point();
	especular = Color<float>();
	difusa = Color<float>();
	ambiente = Color<float>();
	element = Core::Element::e_none;
	id = -1;
	light = -1;
	active = false;
}

Light::Light(const Light &light_) {
	Copiar(light_);
}

void
Light::Copiar(const Light &light_) {
	posicion = light_.posicion;
	especular = light_.especular;
	difusa = light_.difusa;
	ambiente = light_.ambiente;
	element = light_.element;
	id = light_.id;
	light = light_.id;
	active = light_.active;
}


Light&
Light::operator=(const Light &light_) {

	if(this != &light_)
	{
		this->~Light();
		Copiar(light_);
	}

	return *this;
}
Color<float>
Light::getAmbiente() const {
    return ambiente;
}

Color<float>
Light::getDifusa() const {
    return difusa;
}

Color<float>
Light::getEspecular() const {
    return especular;
}

Point
Light::getPosicion() const {
    return posicion;
}
int
Light::getId() const {
	return id;
}
void
Light::setAmbiente(Color<float> ambiente_) {
    this->ambiente = ambiente_;
}

void
Light::setDifusa(Color<float> difusa_) {

    this->difusa = difusa_;
}

void
Light::setEspecular(Color<float> especular_) {
    this->especular = especular_;
}

void
Light::setPosicion(Point posicion_) {
    this->posicion = posicion_;
}

void
Light::setId(int id_) {
	id = id_;
}

void
Light::switchOff() {
	active = false;
}

void
Light::switchOn() {
	active = true;
}
void
Light::exportOpenGL() {

	if(id >= 0)
	{
		glEnable(GL_LIGHTING);
		GLfloat dif[4];
		GLfloat esp[4];
		GLfloat amb[4];
		GLfloat pos[4];

		dif[0] = difusa.getR();
		dif[1] = difusa.getG();
		dif[2] = difusa.getB();
		dif[3] = difusa.getAlpha();

		esp[0] = especular.getR();
		esp[1] = especular.getG();
		esp[2] = especular.getB();
		esp[3] = especular.getAlpha();

		amb[0] = ambiente.getR();
		amb[1] = ambiente.getG();
		amb[2] = ambiente.getB();
		amb[3] = ambiente.getAlpha();

		pos[0] = posicion.getX();
		pos[1] = posicion.getY();
		pos[2] = posicion.getZ();
		pos[3] = 1;

		light = id%8;

		if(active){
			glEnable(GL_LIGHT0 + light);
		}else
			glDisable(GL_LIGHT0 + light);

		glLightfv(GL_LIGHT0 + light, GL_DIFFUSE, dif);
		glLightfv(GL_LIGHT0 + light, GL_SPECULAR, esp);
		glLightfv(GL_LIGHT0 + light, GL_AMBIENT, amb);
		glLightfv(GL_LIGHT0 + light, GL_POSITION, pos);

	}
}

void
Light::exportOpenGL(int num_luz) {

	if(id >= 0)
	{
		glEnable(GL_LIGHTING);
		GLfloat dif[4];
		GLfloat esp[4];
		GLfloat amb[4];
		GLfloat pos[4];

		dif[0] = difusa.getR();
		dif[1] = difusa.getG();
		dif[2] = difusa.getB();
		dif[3] = difusa.getAlpha();

		esp[0] = especular.getR();
		esp[1] = especular.getG();
		esp[2] = especular.getB();
		esp[3] = especular.getAlpha();

		amb[0] = ambiente.getR();
		amb[1] = ambiente.getG();
		amb[2] = ambiente.getB();
		amb[3] = ambiente.getAlpha();

		pos[0] = posicion.getX();
		pos[1] = posicion.getY();
		pos[2] = posicion.getZ();
		pos[3] = 0;

		light = num_luz%8;
		glLightfv(GL_LIGHT0 + light, GL_DIFFUSE, dif);
		glLightfv(GL_LIGHT0 + light, GL_SPECULAR, esp);
		glLightfv(GL_LIGHT0 + light, GL_AMBIENT, amb);
		glLightfv(GL_LIGHT0 + light, GL_POSITION, pos);
		if(active)
			glEnable(GL_LIGHT0 + light);
		else
			glDisable(GL_LIGHT0 + light);
	}
}

void Light::setLight(int light_)
{
	if(light_ >= 0 && light_ < 8)
	{
		light = light_;
	}
}

ostream&
operator<<(ostream &os, const Light &l) {

	os << "Luz(" << l.getId() << ") - Pos.: " << l.getPosicion() << " Amb.:" << l.getAmbiente() << " Dif.:" << l.getDifusa() << " Esp.:" << l.getEspecular();
	return os;
}


