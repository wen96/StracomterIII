#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <iostream>
#include <vector>
#include "Simplex.h"
#include "Optimization.h"
#include "EntityManager.h"
#include "ResourceManager.h"
#include "Point.h"
#include "Map.h"
#include "World.h"
#include "EventControl.h"

using namespace std;

/*Ejemplo de Simplex Entero Z = 8 (Encuentra uno con el mejor valor)*/
const string obj = "Max z 2x1 + x2";
const string r1 = "4x1 + 2x2 >= 15";
const string r2 = "12x1 + 7x2 <= 55";
const string r3 = "5x1 + 2x2 <= 18";

int main(int argc,char *argv[]) {

	Optimization* opti = new Optimization();
	World *w = new World();
	EventControl *ec = new EventControl();
	ResourceManager *rm = ResourceManager::getInstance(w,ec);
	EntityManager *em = new EntityManager(rm);
	Map *mapa = new Map();

	mapa->setMap("testFiles/maps/mapRuben.xml");
	mapa->setManager(em);
	mapa->loadData();

	opti->CargarFuncionObjetivo(4773784,8);
	opti->CalcularEnemigos();
	opti->CargarEnemigos(mapa);

	vector<Entity*> enemigos = em->getBadPersons();
	for(int i=0; i<enemigos.size(); i++)
	{
		//cout<<"ENEMIGO "<<i+1<<": "<<enemigos[i]->getCenter()<<endl;
	}
	//cout<<"DESDE: "<<mapa->getSupIzq()<<endl;
	//cout<<"HASTA: "<<mapa->getInfDer()<<endl;

	return 0;
}
