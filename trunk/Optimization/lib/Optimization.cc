/*
 * Optimization.cpp
 *
 *  Created on: 24/02/2012
 *      Author: Chutaos Team
 */

#include "Optimization.h"

Optimization::Optimization() {
	simplex = new Simplex();
	E1 = 0;
	E2 = 0;
	E3 = 0;
	MaxEnemies = 0;
}

Optimization::Optimization(int _E1, int _E2, int _E3) {
	simplex = new Simplex();
	E1 = _E1;
	E2 = _E2;
	E3 = _E3;
	MaxEnemies = 0;
}

Optimization::Optimization(const Optimization & opti) {
	if (opti.simplex != NULL) {
		simplex = new Simplex(*opti.simplex);
	}
	E1 = opti.E1;
	E2 = opti.E2;
	E3 = opti.E3;
	MaxEnemies = opti.MaxEnemies;
}

Optimization & Optimization::operator =(const Optimization & opti) {
	if (this != &opti) {
		opti.~Optimization();

		if (opti.simplex != NULL) {
			simplex = new Simplex(*opti.simplex);
		}
		E1 = opti.E1;
		E2 = opti.E2;
		E3 = opti.E3;
		MaxEnemies = opti.MaxEnemies;
	}
	return *this;
}

Optimization::~Optimization() {
	if (simplex != NULL) {
		delete simplex;
		simplex = NULL;
	}
}

int Optimization::getE1() const {
	return E1;
}

int Optimization::getE2() const {
	return E2;
}

int Optimization::getE3() const {
	return E3;
}

Simplex *Optimization::getSimplex() const {
	return simplex;
}

void Optimization::setE1(int e1) {
	E1 = e1;
}

void Optimization::setE2(int e2) {
	E2 = e2;
}

void Optimization::setE3(int e3) {
	E3 = e3;
}

void Optimization::setSimplex(Simplex *simplex) {
	this->simplex = simplex;
}

void Optimization::CargarFuncionObjetivo(double tam, float dif) {
	MaxEnemies = (log(((tam / 250.0)) * dif) * 10); //1000000: cambio de unidad (El area da Millones) - 15: Constante de multiplicacion
	////cout<<"El numero maximo de enemigos: "<<MaxEnemies<<endl;
	float maxDa = (280 / 3) * MaxEnemies;
	float maxHp = (155 / 3) * MaxEnemies;
	float maxVe = (140 / 3) * MaxEnemies;
	char aux[50];
	string obj = "Max z x1 + x2 + x3";
	sprintf(aux, "60x1 + 100x2 + 120x3 <= %f3", maxDa);
	string r1 = aux; //5133.333
	sprintf(aux, "45x1 + 50x2+ 65x3 <=  %f3", maxHp); //2841.666
	string r2 = aux;
	sprintf(aux, "60x1 + 45x2 + 35x3 <=  %f3", maxVe); //2566.666
	string r3 = aux;

	simplex->addRestriccion(r1);
	simplex->addRestriccion(r2);
	simplex->addRestriccion(r3);
	simplex->setObjetivo(obj);
}

void Optimization::CalcularEnemigos() {
	//cout << "aasdasd" << endl;
	if (MaxEnemies > 0) {
		int status = simplex->SimplexInt();
		if (status == 0) {
			simplex->getSoluciones();
			E1 = simplex->getXi(1).getValorInt();
			E2 = simplex->getXi(2).getValorInt();
			E3 = simplex->getXi(3).getValorInt();

		}
		if (status == 0 && (E1 + E2 + E3 > 0)) {
			////cout<<"El algoritmo simplex asigno la siguiente distribucion de enemigos:"<<endl;
			////cout<<"Enemigos de tipo 1: "<<E1<<" - Enemigos de tipo 2: "<<E2<<" - Enemigos de tipo 3: "<<E3<<endl;
		} else {
			E1 = MaxEnemies / 3;
			E2 = MaxEnemies / 3;
			E3 = MaxEnemies / 3;
			////cout<<"No se consiguio resolver simplex y se asigno una distribucion por defecto:"<<endl;
			////cout<<"Enemigos de tipo 1: "<<E1<<" - Enemigos de tipo 2: "<<E2<<" - Enemigos de tipo 3: "<<E3<<endl;
		}
	}
}

int Optimization::CargarEnemigos(Map *map, Pathfinder *pf) {
	//cout << "entra" << endl;
	int insertados = 0;
	int max = E1 + E2 + E3;
	int e1 = E1, e2 = E2;
	EntityManager *em = map->getManager();
	vector<Point> enemigos;
	Point pPlayer = em->getPlayer()->getCenter();

	vector<Point> puntos = map->getTriCenters(2000);

	//cout << puntos.size() << endl;

	int puntosTam = puntos.size();
	if (puntosTam > 0) {
		for (int i = 0; i < max; i++) {
			int index = rand() % puntosTam;
			if (Point::distance(puntos[index], pPlayer) > 200) {
				if(e1 > 0){
					em->addSmartEntity(puntos[index], 0, Core::Entities::e_enemy1, pf);
					e1--;
				}else if(e2 > 0){
					em->addSmartEntity(puntos[index], 0, Core::Entities::e_enemy2, pf);
					e2--;
				}else{
					em->addSmartEntity(puntos[index], 0, Core::Entities::e_enemy3, pf);
				}
				insertados++;
			} else {
				puntos.erase(puntos.begin() + index);
				puntosTam--;
				if(puntosTam == 0)
					break;
			}
		}
	}
	return insertados;
}

