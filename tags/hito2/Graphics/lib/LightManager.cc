/*
 * LightManager.cc
 *
 *  Created on: 02/02/2012
 *      Author: Chutaos Team
 */

#include "LightManager.h"

LightManager::LightManager() {

	vector<Light*>aux;
	luces = aux;
	id = 0;
	error = new Light(-1);
	asignadas = vector<int>(8,-1);
	activas = vector<bool>(8,false);
}

LightManager::~LightManager() {

	Light *aux;


	while(luces.size() > 0)
	{
		aux = luces[0];
		luces.erase(luces.begin());
		if(aux != NULL)
		{
			delete aux;
		}
	}

	if(error != NULL)
	{
		delete error;
		error = NULL;
	}
}

int
LightManager::addLight() {

	int aux;
	Light *tmp = new Light(id);
	luces.push_back(tmp);
	aux = id;
	id++;
	return aux;
}

int
LightManager::addLight(Color<float> amb, Color<float> dif, Color<float> esp, Point pos) {

	int aux;
	Light *tmp = new Light(amb, dif, esp, pos, id);
	luces.push_back(tmp);
	aux = id;
	id++;
	return aux;
}

void
LightManager::deleteLight(int id_) {

	vector<Light*>::iterator it;
	bool encontrado = false;
	for(it = luces.begin(); it != luces.end() && !encontrado; it++)
	{
		if((*it)->getId() == id_)
		{
			luces.erase(it);
			encontrado = true;
		}
	}
	encontrado = false;
	for(unsigned int i = 0; i < asignadas.size() && !encontrado; i++)
	{
		if(asignadas[i] == id_)
		{
			glDisable(GL_LIGHT0 + i);
			asignadas[i] = -1;
			encontrado = true;
		}
	}
}

Light*
LightManager::getLight(int num_luz) {


	bool encontrado = false;
	int num_id;
	for(unsigned int i = 0; i < luces.size() && !encontrado; i++)
	{
		if(num_luz == luces[i]->getId())
		{
			num_id = i;
			encontrado = true;
		}
	}

	if(encontrado)
		return (luces[num_id]);
	else
		return error;
}

void
LightManager::exportOpenGL() {

	vector<int> aux(8,-1);
	int numluces = 0;
	glEnable(GL_LIGHTING);

	for(unsigned int i = 0; i < luces.size() && numluces < 8; i++)
	{
		if(aux[(luces[i]->getId()%8)] == -1)
		{
			aux[(luces[i]->getId()%8)] = luces[i]->getId();
			numluces++;
		}
	}

	exportOpenGL(aux);
}

void
LightManager::exportOpenGL(int luz0, int luz1, int luz2, int luz3, int luz4, int luz5, int luz6, int luz7) {

	glEnable(GL_LIGHTING);
	vector<int> aux;
	aux.push_back(luz0);
	aux.push_back(luz1);
	aux.push_back(luz2);
	aux.push_back(luz3);
	aux.push_back(luz4);
	aux.push_back(luz5);
	aux.push_back(luz6);
	aux.push_back(luz7);

	exportOpenGL(aux);
}

void
LightManager::exportOpenGL(vector<int> luz) {

	glEnable(GL_LIGHTING);
	for(unsigned int i = 0; i < luz.size() && i < 8; i++)
	{
		if(luz[i] >= 0)
		{
			asignadas[i] = luz[i];
			activas[i] = true;
			getLight(luz[i])->exportOpenGL(i);
		}
		else
		{
			asignadas[i] = -1;
			activas[i] = false;
			glDisable(GL_LIGHT0 + i);
		}
	}
}

void
LightManager::switchOff(int luz) {

	if(luz >= 0 && luz < 8)
	{
		getLight(asignadas[luz])->switchOff();
		activas[luz] = false;
		glDisable(GL_LIGHT0 + luz);
	}

}

void
LightManager::switchOn(int luz) {

	if(luz >= 0 && luz < 8)
	{
		if(asignadas[luz] != -1)
		{
			getLight(asignadas[luz])->switchOn();
			activas[luz] = true;
			glEnable(GL_LIGHT0 + luz);
		}
	}
}

void
LightManager::exportOpenGL(int luz) {

	glEnable(GL_LIGHTING);
	Light *p = getLight(luz);

	if(p->getId() != -1)
	{
		activas[luz%8] = true;
		asignadas[luz%8] = luz;
		p->exportOpenGL();
	}
}

void
LightManager::exportOpenGL(int luz, int pos) {

	glEnable(GL_LIGHTING);
	Light *p = getLight(luz);

	if(p->getId() != -1)
	{
		if(pos >= 0 && pos < 8)
		{
			activas[pos] = true;
			asignadas[pos] = luz;
			p->exportOpenGL(pos);
		}
	}
}

bool
LightManager::isActive(int luz) {

	bool active = false;
	if(luz >= 0 && luz < 8)
	{
		active = activas[luz];
	}

	return active;
}
ostream&
operator<<(ostream &os, const LightManager &m) {

	os << "Gestor de luces." << endl;
	os << "----------------------------------------------------------------------------" << endl;
	os << "Número de luces: " << m.luces.size() << endl;
	os << "Asignadas: ";

	for(unsigned int i = 0; i < m.asignadas.size(); i++)
	{
		os << "\t" << m.asignadas[i];
	}
	os << endl;

	os << "Activas: ";
	for(unsigned int i = 0; i < m.activas.size(); i++)
	{
		os << "\t" << m.activas[i];
	}
	os << endl;

	for(unsigned int i = 0; i < m.luces.size(); i++)
	{
		os << *m.luces[i] << endl;
	}
	os << "----------------------------------------------------------------------------";

	return os;
}

void LightManager::selectLight(int id_, int light_)
{
	if(light_ >= 0 && light_ < 8)
	{
		asignadas[light_] = id_;
		getLight(id_)->setLight(light_);

	}
}




