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
	MaxEnemies=0;
}

Optimization::Optimization(int _E1, int _E2, int _E3) {
	simplex = new Simplex();
	E1 = _E1;
	E2 = _E2;
	E3 = _E3;
	MaxEnemies=0;
}

Optimization::Optimization(const Optimization & opti)
{
	if(opti.simplex != NULL)
	{
		simplex = new Simplex(*opti.simplex);
	}
	E1 = opti.E1;
	E2 = opti.E2;
	E3 = opti.E3;
	MaxEnemies=opti.MaxEnemies;
}

Optimization & Optimization::operator =(const Optimization & opti)
{
	if(this != &opti)
	{
		opti.~Optimization();

		if(opti.simplex != NULL)
		{
			simplex = new Simplex(*opti.simplex);
		}
		E1 = opti.E1;
		E2 = opti.E2;
		E3 = opti.E3;
		MaxEnemies=opti.MaxEnemies;
	}
	return *this;
}

Optimization::~Optimization() {
	if(simplex != NULL)
	{
		delete simplex;
		simplex = NULL;
	}
}

int Optimization::getE1() const
{
    return E1;
}

int Optimization::getE2() const
{
    return E2;
}

int Optimization::getE3() const
{
    return E3;
}

Simplex *Optimization::getSimplex() const
{
    return simplex;
}

void Optimization::setE1(int e1)
{
    E1 = e1;
}

void Optimization::setE2(int e2)
{
    E2 = e2;
}

void Optimization::setE3(int e3)
{
    E3 = e3;
}

void Optimization::setSimplex(Simplex *simplex)
{
    this->simplex = simplex;
}

void Optimization::CargarFuncionObjetivo(int tam, int dif)
{
	MaxEnemies= (log(((float)(tam/1000000.0))*dif)*15); //1000000: cambio de unidad (El area da Millones) - 15: Constante de multiplicacion
	float maxDa=(280/3)*MaxEnemies;
	float maxHp=(155/3)*MaxEnemies;
	float maxVe=(140/3)*MaxEnemies;
	char aux[50];
	string obj = "Max z x1 + x2 + x3";
	sprintf(aux,"60x1 + 100x2 + 120x3 <= %f3",maxDa);
	string r1 = aux;//5133.333
	sprintf(aux,"45x1 + 50x2+ 65x3 <=  %f3",maxHp);//2841.666
	string r2 = aux;
	sprintf(aux,"60x1 + 45x2 + 35x3 <=  %f3",maxVe);//2566.666
	string r3 = aux;

	simplex->addRestriccion(r1);
	simplex->addRestriccion(r2);
	simplex->addRestriccion(r3);
	simplex->setObjetivo(obj);
}



void Optimization::CalcularEnemigos()
{
	if(MaxEnemies>0)
	{
		int status = simplex->SimplexInt();
		if (status == 0)
		{
			simplex->getSoluciones();
			E1=simplex->getXi(1).getValorInt();
			E2=simplex->getXi(2).getValorInt();
			E3=simplex->getXi(3).getValorInt();

		}
		if(status == 0 && (E1+E2+E3>0))
		{
			//cout<<"El algoritmo simplex asigno la siguiente distribucion de enemigos:"<<endl;
			//cout<<"Enemigos de tipo 1: "<<E1<<" - Enemigos de tipo 2: "<<E2<<" - Enemigos de tipo 3: "<<E3<<endl;
		}else
		{
			E1=MaxEnemies/3;
			E2=MaxEnemies/3;
			E3=MaxEnemies/3;
			//cout<<"No se consiguio resolver simplex y se asigno una distribucion por defecto:"<<endl;
			//cout<<"Enemigos de tipo 1: "<<E1<<" - Enemigos de tipo 2: "<<E2<<" - Enemigos de tipo 3: "<<E3<<endl;
		}
	}
}



int Optimization::CargarEnemigos(Map *map)
{
		int insertados=0;
		int max=E1+E2+E3;
		EntityManager *em = map->getManager();
		vector<Entity*> paredes=em->getEntitiesbyType(Core::Entities::e_wall);
		Point punto,pFueraS,pSI=map->getSupIzq(),pID=map->getInfDer();
		int tamX= pID.getX()-pSI.getX();
		int tamY= pID.getY()-pSI.getY();
		pFueraS.setXY(pSI.getX()-1000,pSI.getY()-1200);
		vector<Point> enemigos;
		Point pPlayer = em->getPlayer()->getCenter();

		//CREACION DE MUNDO PARA DETECTAR LAS COLISIONES.
		World *w = new World();
		Polygon perimetro(((Floor*)em->getFloor())->getPerimetro());
		BodyData datosC(perimetro);
		datosC.setSensor(true);
		Body *cuerpo = new Body(*w, datosC);
		cuerpo->getPosition();
		vector<Point> vectCol;

		//CALCULA LA POSICION DE TODOS LOS ENEMIGOS
		for(int Iter = 0;max>insertados && Iter<1000000;Iter++)//tras un millon de intentos salimos
		{
			int nX=(rand()%tamX)+pSI.getX();
			int nY=(rand()%tamY)+pSI.getY();
			//CALCULAR RANDOM DE UN PUNTO ENTRE EL SUPIZQ Y INFDER
			punto= Point(nX,nY,1);
			vectCol = w->CutOffPoints(pFueraS,punto);
			if(((vectCol.size()) % 2) != 0)
			{
				int nuevos=2+(rand()%3);
				int anadidos = 0;
				for(int j=0;j<100 && anadidos <= nuevos;j++)
				{
					int dX = random()%90+60;//90 Corresponde con la maxima dispersion desde el punto
					int dY = random()%90+60;//60 Corresponde con la suma de radios(25) mas la minima dispersion (10)
					if((dX+dY)%2==0)
					{
						dX=-dX;
						dY=-dY;
					}
					Point pDispar = Point(punto.getX()+dX,punto.getY()+dY,1);
					vectCol.clear();
					vectCol = w->CutOffPoints(pFueraS,pDispar);
					if(((vectCol.size()) % 2) != 0)
					{
						if(Point::distance(pDispar,pPlayer) > 500)// PARA QUE APAREZCAN A MAS DE 100 PIXELS DEL PLAYER
						{
							bool correcto=true;
							for(unsigned c=0; c<paredes.size();c++)
							{
								if(paredes[c]->getBody()->TestPoint(pDispar))
									correcto=false;
							}
							if(correcto)
							{
								for(unsigned int i = 0; i<vectCol.size(); i++)
								{
									//cout<<vectCol[i]<<endl;
								}
								enemigos.push_back(pDispar);
								anadidos++;
							}
						}
					}
				}

				insertados=insertados+anadidos;
			}
		}

		//CREA LA DISTRIBUCION DE ENTIDADES DE FORMA ALEATORIA
		int pos;
		int ang;
		for(int i=0; i<E1;i++)
		{
			ang = rand()%360;
			pos=(rand()%enemigos.size());
			em->addSmartEntity(enemigos[pos],ang,Core::Entities::e_enemy1,NULL);
			enemigos.erase(enemigos.begin()+pos);
		}
		for(int i=0; i<E2;i++)
		{
			ang = rand()%360;
			pos=(rand()%enemigos.size());
			em->addSmartEntity(enemigos[pos],ang,Core::Entities::e_enemy2,NULL);
			enemigos.erase(enemigos.begin()+pos);
		}
		for(int i=0; i<E3;i++)
		{
			ang = rand()%360;
			pos=(rand()%enemigos.size());
			em->addSmartEntity(enemigos[pos],ang,Core::Entities::e_enemy3,NULL);
			enemigos.erase(enemigos.begin()+pos);
		}

		return insertados;
}





