/*
 * Model.cc
 *
 *  Created on: 15/02/2012
 *      Author: Chutaos Team
 */

#include "Model.h"
#include "load3ds.c"

Model::Model() {

	n_vertices = -1;
	puntos = NULL;
	id = -1;
	ruta = "";
	element = Core::Element::e_model;
	textura = NULL;
	material = Material();
	materialActive = false;
	color = Color<float>(0,0,1,1);
}

Model::Model(string ruta_, int id_) {

	ruta = ruta_;
	id = id_;
	puntos = NULL;
	n_vertices = -1;
	element = Core::Element::e_model;
	color = Color<float>(0,0,0,-1);
	textura = NULL;
	material = Material();
	materialActive = false;
}




Model::Model(string ruta_, int id_, Textura textura_)
{
	ruta = ruta_;
	id = id_;
	puntos = NULL;
	n_vertices = -1;
	element = Core::Element::e_model;
	color = Color<float>(0,0,0,-1);
	textura = new Textura(textura_);

	material = Material();
	materialActive = false;
}

Model::Model(const Model &m)
{
	ruta = m.ruta;
	n_vertices = m.n_vertices;
	id = m.id;
	element = m.element;
	color = m.color;
	material = m.material;
	materialActive = m.materialActive;
	if(m.textura != NULL)
	{
		textura = new Textura(*m.textura);
	}
	else
		textura = NULL;

	if(m.puntos != NULL)
	{
		puntos = new float[n_vertices];
		//puntos[n_vertices];
		for(int i = 0; i < n_vertices; i++)
		{
			puntos[i] = m.puntos[i];
		}

	}else
	{
		puntos = NULL;
	}
}
Model&
Model::operator=(const Model &m) {

	if(this != &m)
	{

		Destructor();
		ruta = m.ruta;
		element = m.element;
		n_vertices = m.n_vertices;
		id = m.id;
		color = m.color;
		material = m.material;
		materialActive = m.materialActive;
		if(m.puntos != NULL)
		{
			puntos = new float[n_vertices];
			//puntos[n_vertices];
			for(int i = 0; i < n_vertices; i++)
			{
				puntos[i] = m.puntos[i];
			}

		}else
		{
			puntos = NULL;
		}

		if(textura != NULL)
		{
			delete textura;
			textura = NULL;
		}

		if(m.textura != NULL)
		{
			textura = new Textura(*m.textura);
		}
	}

	return *this;
}
Model::~Model() {

	if(puntos != NULL)
	{
		free(puntos);
		puntos = NULL;
	}

	if(textura != NULL)
	{
		delete textura;
		textura = NULL;
	}
	n_vertices = -1;
	id = -1;
	ruta = "";
	element = Core::Element::e_none;
	color = Color<float>(0,0,0,-1);
	material = Material();
	materialActive = false;
}

float *Model::getPuntos() const
{
    return puntos;
}

int Model::getVertices() const
{
    return n_vertices;
}

Color<float>Model::getColor() const{
	return color;
}

void Model::setPuntos(float *puntos_)
{
    this->puntos = puntos_;
}

void Model::setVertices(int vertices_)
{
    n_vertices = vertices_;
}

void Model::setColor(Color<float> color_) {
	color = color_;
}

void Model::createDisplayList()
{

	if(id == -1)
		id = glGenLists(1000);
	if(puntos != NULL)
	{
		free(puntos);
		puntos = NULL;
	}
	puntos = Load3DS(ruta.c_str(),&n_vertices);
	if(puntos != NULL)
	{
		glNewList(id , GL_COMPILE);

		if(textura != NULL)
		{
			textura->Activar();
		}

		/*if(color.getAlpha() != -1)
		{
			color.exportOpenGL();
		}*/
		glPushMatrix();
		//glScaled(8,8,8);
		//glRotated(90,1,0,0);
		//glRotated(90,0,1,0);

		//glRotated(90,0,0,1);

		if(materialActive)
		{
			material.exportOpenGL();
		}
			glBegin(GL_TRIANGLES);
				for (int i = 0; i < n_vertices; i++)
				{
					glNormal3fv((float*) & puntos[i << 3] + 3);
					glTexCoord2fv((float*) & puntos[i << 3] + 6);
					glVertex3fv((float*) & puntos[i << 3]);
				}
			glEnd();

		if(materialActive)
		{
			material.Desactivar();
			Material::resetMaterial();
		}

		if(textura != NULL)
		{
			textura->Desactivar();
		}
		glPopMatrix();
		glEndList();

	}

}



void Model::createDisplayList(int id_)
{
	if(puntos != NULL)
	{
		free(puntos);
		puntos = NULL;
	}
	puntos = Load3DS(ruta.c_str(),&n_vertices);
	if(puntos != NULL)
	{
		glNewList(id_ , GL_COMPILE);
		if(color.getAlpha() != -1)
		{
			color.exportOpenGL();
		}
		if(textura != NULL)
		{
			textura->Activar();
		}
		glTranslated(0,0,-10);
		glScaled(20,20,20);
		glRotated(-90,1,0,0);
		glRotated(90,0,1,0);
		//glRotated(90,0,0,0);
			glBegin(GL_TRIANGLES);
				for (int i = 0; i < n_vertices; i++)
				{
					glNormal3fv((float*) & puntos[i << 3] + 3);
					glTexCoord2fv((float*) & puntos[i << 3] + 6);
					glVertex3fv((float*) & puntos[i << 3]);
				}
			glEnd();
		if(textura != NULL)
		{
			textura->Desactivar();
		}
		glEndList();
	}
}


void Model::exportOpenGL()
{
	if(color.getAlpha() != -1)
		color.exportOpenGL();

	glCallList(id);
}

void Model::setTexture(Textura textura_)
{
	if(textura != NULL)
	{
		delete textura;
		textura = NULL;
	}

	textura = new Textura(textura_);
}



Textura *Model::getTextura() const
{
	return textura;
}


void Model::Destructor() {
	if(puntos != NULL)
	{
		free(puntos);
		puntos = NULL;
	}

	if(textura != NULL)
	{
		delete textura;
		textura = NULL;
	}
	n_vertices = -1;
	id = -1;
	ruta = "";
	element = Core::Element::e_none;
	color = Color<float>(0,0,0,-1);
}

void Model::setMaterial(Material m) {
	materialActive = true;
	material = m;
}
Material Model::getMaterial() {
	return material;
}

void Model::activeMaterial(bool m)
{
	materialActive = m;
}




