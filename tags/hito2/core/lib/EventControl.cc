/*
 * EventControl.cc
 *
 *  Created on: 28/12/2011
 *      Author: Chutaos Team
 */

#include "EventControl.h"
#include "EntityManager.h"

EventControl::EventControl(EntityManager *ent) {
	entities = ent;
	// TODO Auto-generated constructor stub

}

EventControl::~EventControl() {
	entities = NULL;
	// TODO Auto-generated destructor stub
}

EventControl::EventControl()
{
}

bool EventControl::Shoot(Entity* ent){
	Character *shooter =(Character*)ent;
	vector<Entity*> en;

	en = entities->getCharacters();
	/*if (shooter->isGoodPerson()){
		en = entities->getBadPersons();
	}else{
		en = entities->getGoodPersons();
	}*/
	bool matado = false;
	bool intersecta = false;
	if (shooter->canShoot()){

		if(shooter->laser.hit)
		{
			for(unsigned int i = 0; i < en.size() && !intersecta; i++)
			{
				if(en[i]->getBody()->getBody() == shooter->laser.body)
				{
					Character* reventado = ((Character*)en[i]);
					bool muerto = reventado->hurt(shooter->shootDamage());
					if (!reventado->isDead()){
						if (muerto){
							(shooter)->addScore(reventado->getExpKill());
							reventado->setDead(true);
							entities->addDead(reventado->getType(),
									reventado->getId());
							matado = true;
						}else{
							//Si al que se ha disparado no es el player (es un bot)
							if (!entities->isPlayer(reventado)) {
								////cout << "No han disparado al player" << endl;
								//Si se disparan entre contrarios
								if ((shooter->isGoodPerson()
										&& !reventado->isGoodPerson())
										|| (!shooter->isGoodPerson()
												&& reventado->isGoodPerson())) {
									////cout << "Se han disparado entre enemigos" << endl;
									//Ponemos el centro desde donde le han disparado en sus atacantes
									((Bot*)reventado)->addAtacker(shooter->getCenter());
								}
							}
						}

					}


					intersecta = true;
				}

			}
		}
		if (!intersecta){
			shooter->shootDamage();
		}
	}
	return matado;
}

void EventControl::ComeBackCompanions(){
	if (entities!=NULL){
		vector<Entity*> compains = entities->getIACompains();
		vector<Entity*>::iterator iter;//recorremos todos los companyeros
		Point p = (entities->getPlayer())->getCenter();
		for (iter = compains.begin(); iter != compains.end(); iter++){
			switch ((*iter)->getType()){
			case Core::Entities::e_explosive:
				((Explosive*)(*iter))->goToComeBack(p);
				break;
			case Core::Entities::e_tecnic:
				((Technic*)(*iter))->goToComeBack(p);
				break;
			case Core::Entities::e_especialist:
				((Especialist*)(*iter))->goToComeBack(p);
				break;
			case Core::Entities::e_captain:
				//((Captain*)(*iter))->goToComeBack(p);
				break;
			default:
				break;
			}
			//((Bot*)(*iter))->;//cambiamos el estado a ComeBack
		}
	}
}

EntityManager *EventControl::getEntities() const
{
    return entities;
}



void EventControl::setEntities(EntityManager *entities)
{
    this->entities = entities;
}

void EventControl::Update(){
	//TODO si estamos seguros de que no va a haber mas de uno de cada tipo esto puede ser mas eficiente
	this->UpdateMoral();
	this->UpdateAmmunition();
}

void EventControl::UpdateMoral(){
	vector<Entity*> subidoras = entities->getEntitiesbyType(Core::Entities::e_captain);
	vector<Entity*> receptoras = entities->getGoodPersons();
	vector<Entity*>::iterator iterSub;
	vector<Entity*>::iterator iterRec;
	for (iterSub = subidoras.begin(); iterSub != subidoras.end(); iterSub++){
		Point posSub = (*iterSub)->getCenter();
		for (iterRec = receptoras.begin(); iterRec != receptoras.end(); iterRec++){
			Point posRec = (*iterRec)->getCenter();
			if (Point::distance(posSub, posRec)<200){
				((Character*)(*iterRec))->setMoral(3);
			}else{
				((Character*)(*iterRec))->returnMoral();
			}
		}
	}
}
void EventControl::UpdateAmmunition(){
	vector<Entity*> subidoras = entities->getEntitiesbyType(Core::Entities::e_especialist);
	vector<Entity*> receptoras = entities->getGoodPersons();
	vector<Entity*>::iterator iterSub;
	vector<Entity*>::iterator iterRec;
	for (iterSub = subidoras.begin(); iterSub != subidoras.end(); iterSub++){
		Point posSub = (*iterSub)->getCenter();
		for (iterRec = receptoras.begin(); iterRec != receptoras.end(); iterRec++){
			Point posRec = (*iterRec)->getCenter();
			if (Point::distance(posSub, posRec)<200){
				((Character*)(*iterRec))->updateAmmunition();
			}
		}
	}
}

