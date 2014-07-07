/*
 * Material.cc
 *
 *  Created on: 26/02/2012
 *      Author: Chutaos Team
 */

#include "../include/Material.h"

//FORMA CANONICA
Material::Material() {
    ambiente = Color<float>(0.1,0.1,0.1,1.0);
    difusa = Color<float>(0.7,0.7,0.7,1.0);
    especular = Color<float>(0.9,0.9,0.9,1.0);
    brillo = 100;

}

Material::~Material() {
    ambiente = Color<float>(0,0,0,0);
    difusa = Color<float>(0,0,0,0);
    especular = Color<float>(0,0,0,0);
    brillo = 100;
}


Material::Material(const Material & material)
{
    ambiente = material.ambiente;
    difusa = material.difusa;
    especular = material.especular;
    brillo = material.brillo;
}

Material & Material::operator =(const Material & material)
{
	if(this != &material)
	{
	    ambiente = material.ambiente;
	    difusa = material.difusa;
	    especular = material.especular;
	    brillo = material.brillo;
	}
	return *this;
}


//AMBIENTE

void Material::setAmbiente(Color<float> ambiente)
{
    this->ambiente = ambiente;

}

void Material::setAmbiente(float r, float g, float b, float a)
{
	ambiente.setR(r);
	ambiente.setG(g);
	ambiente.setB(b);
	ambiente.setAlpha(a);
}

//DIFUSA


void Material::setDifusa(Color<float> difusa)
{
    this->difusa = difusa;

}

void Material::setDifusa(float r, float g, float b, float a)
{
    difusa.setR(r);
    difusa.setG(g);
    difusa.setB(b);
    difusa.setAlpha(a);
}

//ESPECULAR

void Material::setEspecular(Color<float> especular)
{
    this->especular = especular;

}

void Material::setEspecular(float r, float g, float b, float a)
{
    especular.setR(r);
    especular.setG(g);
    especular.setB(b);
    especular.setAlpha(a);
}


//BRILLO

void Material::setBrillo(float b)
{
    brillo = b;
}

Color<float> Material::getAmbiente() const
{
    return ambiente;
}

float Material::getBrillo() const
{
    return brillo;
}

Color<float> Material::getDifusa() const
{
    return difusa;
}

Color<float> Material::getEspecular() const
{
    return especular;
}


void Material::exportOpenGL() const
{
	glColorMaterial(GL_FRONT, GL_SPECULAR);
	especular.exportOpenGL();
	glColorMaterial(GL_FRONT, GL_AMBIENT);
	ambiente.exportOpenGL();
	glColorMaterial(GL_FRONT, GL_DIFFUSE);
	difusa.exportOpenGL();
	glMaterialf (GL_FRONT, GL_SHININESS, brillo);
}

void Material::Desactivar() const {
	Color<float> esp(1,1,1,1);
	Color<float> amb(1,1,1,1);
	Color<float> dif(1,1,1,1);
	float br = 100;
	glColorMaterial(GL_FRONT, GL_SPECULAR);
	esp.exportOpenGL();
	glColorMaterial(GL_FRONT, GL_AMBIENT);
	amb.exportOpenGL();
	glColorMaterial(GL_FRONT, GL_DIFFUSE);
	dif.exportOpenGL();
	glMaterialf (GL_FRONT, GL_SHININESS, br);
}

void Material::resetMaterial() {

	Color<float> esp(1,1,1,1);
	Color<float> amb(1,1,1,1);
	Color<float> dif(1,1,1,1);
	float br = 100;
	glColorMaterial(GL_FRONT, GL_SPECULAR);
	esp.exportOpenGL();
	glColorMaterial(GL_FRONT, GL_AMBIENT);
	amb.exportOpenGL();
	glColorMaterial(GL_FRONT, GL_DIFFUSE);
	dif.exportOpenGL();
	glMaterialf (GL_FRONT, GL_SHININESS, br);
}
