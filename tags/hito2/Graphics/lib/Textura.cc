/*
 * Textura.cc
 *
 *  Created on: 05/03/2012
 *      Author: Chutaos Team
 */

#include "Textura.h"
#include "SFML/Graphics.hpp"

void Textura::ActivarTextura(unsigned int textura_)
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textura_);
}

void Textura::DesactivarTextura() {
	glDisable(GL_TEXTURE_2D);
}
Textura::Textura() {
	width = 0;
	height = 0;
	ruta = "";
	texture = 0;
}

Textura::~Textura() {

	width = 0;
	height = 0;
	ruta = "";
	texture = 0;
}


Textura::Textura(string ruta_, int name_)
{
	ruta = ruta_;
	texture = name_;
	width = 0;
	height = 0;
	generateTexture();
}

int Textura::getHeight() const
{
    return height;
}

string Textura::getRuta() const
{
    return ruta;
}

int Textura::getWidth() const
{
    return width;
}

void Textura::setHeight(int height)
{
    this->height = height;
}

void Textura::setRuta(string ruta)
{
    this->ruta = ruta;
}

void Textura::setWidth(int width)
{
    this->width = width;
}

void Textura::generateTexture()
{
	//unsigned char *textura=LoadJPEG(ruta.c_str(),&width,&height);
	sf::Image tex;
	tex.LoadFromFile(ruta.c_str());
	unsigned char *textura = (unsigned char *) tex.GetPixelsPtr();
	width = tex.GetWidth();
	height = tex.GetHeight();

	glGenTextures(1, &texture);

	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);

	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);

	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, width , height, GL_RGBA, GL_UNSIGNED_BYTE, textura);

	//free(textura);

}

unsigned int Textura::getTexture() const
{
    return texture;
}

void Textura::setTexture(unsigned int id)
{
    this->texture = texture;
}

void Textura::Activar()
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture);
}

void Textura::Activar(unsigned int textura_)
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textura_);
}

Textura::Textura(const Textura & t)
{
	this->Copiar(t);
}

Textura & Textura::operator =(const Textura & t)
{
	if(this != &t)
	{
		Destructor();
		Copiar(t);
	}

	return *this;
}

void Textura::Desactivar()
{
	glDisable(GL_TEXTURE_2D);
}

void Textura::Destructor()
{
	width = 0;
	height = 0;
	ruta = "";
	texture = -1;
}



void Textura::Copiar(const Textura &t)
{
	height = t.height;
	width = t.width;
	ruta = t.ruta;
	texture = t.texture;
}










