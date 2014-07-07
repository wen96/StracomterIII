/*
 * EventControl.cc
 *
 *  Created on: 28/12/2011
 *      Author: Chutaos Team
 */

#include "EventControl.h"
#include "EntityManager.h"
#include "SceneManager.h"

EventControl::EventControl(EntityManager *ent) {
	entities = ent;
	// TODO Auto-generated constructor stub
	ac = AudioControl::getInstance();
	textura = new Textura("Graphics/Resources/texturas/exploMala.png",1);

}

EventControl::~EventControl() {
	entities = NULL;
	// TODO Auto-generated destructor stub
	ac = NULL;
}

EventControl::EventControl() {
	ac = AudioControl::getInstance();
	textura = new Textura("Graphics/Resources/texturas/exploMala.png",1);
}

bool EventControl::doAttack(Entity* ent){
	bool matado = false;
	if (((Character*)ent)->canShoot()){
		if (ent->getType()==Core::Entities::e_explosive || ent->getType() == Core::Entities::e_miniboss){
			matado = this->Explosion(ent);
		}else{
			matado = this->Shoot(ent);
		}
	}
	return matado;
}

bool EventControl::Shoot(Entity* ent) {
	Character *shooter = (Character*) ent;
	vector<Entity*> en;

	en = entities->getCharacters();
	vector<Entity*>::iterator iter;
	//Para fuego amigo comentar arriba y descomentar bajo
	/*if (shooter->isGoodPerson()){
	 en = entities->getBadPersons();
	 }else{
	 en = entities->getGoodPersons();
	 }*/
	bool matado = false;
	bool intersecta = false;
	if (shooter->canShoot()) {
		//Sonido de disparo
		switch(shooter->getType())
		{
		case Core::Entities::e_especialist:
		case Core::Entities::e_megaboss:
			ac->playSound(Audio::Sound::e_machineGun,ent->getCenter());
			break;
		default:
			ac->playSound(Audio::Sound::e_pistol,ent->getCenter());
			break;
		}
		if (shooter->laser.hit) {
			for (iter = en.begin(); iter != en.end() && !intersecta; iter++) {
				if ((*iter)->getBody()->getBody() == shooter->laser.body) {
					Character* reventado = ((Character*) (*iter));
					bool muerto = reventado->hurt(shooter->shootDamage());

					Point hitPoint(shooter->laser.point);
					Vector2D direction(hitPoint, shooter->getCenter());
					ParticleManager::getInstance()->doBloodBurst(hitPoint, direction);

					if (!reventado->isDead()) {
						matado = this->postDisparo(muerto,shooter,reventado);

					}

					intersecta = true;
				}

			}
		}
		if (!intersecta) {
			shooter->shootDamage();
		}
	}
	return matado;
}

bool EventControl::Slash(Entity* ent) {
	Character *samuray = (Character*) ent;
	vector<Entity*> en;

	en = entities->getCharacters();
	vector<Entity*>::iterator iter;
	//Para fuego amigo comentar arriba y descomentar bajo
	/*if (shooter->isGoodPerson()){
	 en = entities->getBadPersons();
	 }else{
	 en = entities->getGoodPersons();
	 }*/
	bool matado = false;
	bool intersecta = false;
	if (samuray->canSlash()) {
		ac->playSound(Audio::Sound::e_knife,ent->getCenter());
		if (samuray->laser.hit) {
			Point puntaLaser(samuray->laser.point);
			if (Point::distance(puntaLaser, samuray->getCenter())
			< Core::Radius + 50) { //Si esta a una distancia prudente

				for (iter = en.begin(); iter != en.end() && !intersecta;iter++) {
					if ((*iter)->getBody()->getBody() == samuray->laser.body) {

						Character* reventado = ((Character*) (*iter));
						bool muerto = reventado->hurt(samuray->slashDamage());
						matado = this->postDisparo(muerto,samuray,reventado);
						if (!reventado->isDead()) {
							matado = this->postDisparo(muerto,samuray,reventado);
						}

						intersecta = true;
					}

				}
			}
		}
		if (!intersecta) {
			samuray->slashDamage();
		}
	}
	return matado;
}

bool EventControl::postDisparo(bool muerto, Character* atacante, Character *atacado){
	bool matado = false;
	if (muerto) {
		ac->playSound(Audio::Sound::e_dead,atacado->getCenter());
		(atacante)->addScore(atacado->getExpKill());
		(atacado)->setDead(true);
		entities->addDead(atacado->getType(),
				atacado->getId());
		matado = true;
	} else {
		ac->playSound(Audio::Sound::e_ouch,atacado->getCenter());
		//Si al que se ha disparado no es el player (es un bot)
		if (!entities->isPlayer(atacado)) {
			////cout << "No han disparado al player" << endl;
			//Si se disparan entre contrarios
			if ((atacante->isGoodPerson()
					&& !atacado->isGoodPerson())
					|| (!atacante->isGoodPerson()
							&& atacado->isGoodPerson())) {
				////cout << "Se han disparado entre enemigos" << endl;
				//Ponemos el centro desde donde le han disparado en sus atacantes
				((Bot*) atacado)->addAtacker(
						atacante->getCenter());
			}
		}
	}

	return matado;
}

bool EventControl::Explosion(Entity* ent) {
	Character *explosivos = (Character*) ent;
	vector<Entity*> en = entities->getCharacters();
	vector<Entity*>::iterator iter;
	World *mundo = ResourceManager::getInstance()->getWorld();
	bool matado = false;

	if (explosivos->canShoot()){
		if (ent->getType() == Core::Entities::e_explosive || ent->getType() == Core::Entities::e_miniboss) {
			Point puntaLaser(explosivos->laser.point);
			SceneManager *sm = SceneManager::getInstance();
			GraphicNode *escena = sm->getNode(Graphics::DirectNodes::t_escena);
			puntaLaser.setZ(1);
//			Shape *circ = new Shape(Polygon(puntaLaser,Core::explosionRadius),Color<float>(1,0,0));
			Shape *circ = new Shape(puntaLaser, Core::explosionRadius, textura);
			sm->addElement(circ,escena);
			ac->playSound(Audio::Sound::e_explosion,puntaLaser);
			explosiones.push_back(AuxExplosion(circ,Clock(false)));

			ParticleManager::getInstance()->doExplosion(puntaLaser);

			float damage = explosivos->shootDamage();
			for (iter = en.begin(); iter != en.end();iter++) {
				int distance = Point::distance(explosivos->laser.point,(*iter)->getCenter());
				//Si esta en la distancia de explosion
				if (distance <= Core::explosionRadius){
					float porcentDamage = 1-(distance/Core::explosionRadius);
					Character* reventado = ((Character*) (*iter));
					// Si tenemos linea de vision
					if (mundo->RayBody(explosivos->laser.point, reventado->getCenter()).body == reventado->getBody()->getBody()) {
						bool muerto = reventado->hurt(damage*porcentDamage);
						//TODO: Martin la fuerza aplicasela aqui al character reventado

						Vector2D aux = (Vector2D( explosivos->laser.point,reventado->getCenter()))*100;
						reventado->setLinearVelocity(Force(aux.x,aux.y));

						if (!reventado->isDead()){//si no estaba muerto ya
							matado = this->postDisparo(muerto,explosivos,reventado);
						}
					}
				}
			}
		}
	}
	return matado;
}

bool EventControl::Explosion(Point p, int damage) {
	vector<Entity*> en = entities->getCharacters();
	vector<Entity*>::iterator iter;
	World *mundo = ResourceManager::getInstance()->getWorld();
	bool matado = false;

	SceneManager *sm = SceneManager::getInstance();
	GraphicNode *escena = sm->getNode(Graphics::DirectNodes::t_escena);

	ac->playSound(Audio::Sound::e_explosion,p);
	p.setZ(1);

//	Shape *circ = new Shape(Polygon(p,Core::explosionRadius),Color<float>(1,0,0));
	Shape *circ = new Shape(p, Core::explosionRadius, textura);
	sm->addElement(circ,escena);

	explosiones.push_back(AuxExplosion(circ,Clock(false)));

	ParticleManager::getInstance()->doExplosion(p);

	for (iter = en.begin(); iter != en.end();iter++) {
		int distance = Point::distance(p,(*iter)->getCenter());
		if (distance <= Core::explosionRadius){//Si esta dentro del radio de explosion
			float porcentDamage = 1-(distance/Core::explosionRadius);
			Character* reventado = ((Character*) (*iter));
			if (mundo->RayBody(p, reventado->getCenter()).body == reventado->getBody()->getBody()) { // Si tenemos linea de vision
				bool muerto = reventado->hurt(damage*porcentDamage);
				//TODO: Martin la fuerza aplicasela aqui al character reventado (justo arriba)

				Vector2D aux = (Vector2D(p,reventado->getCenter()))*10;
				reventado->setLinearVelocity(Force(aux.x, aux.y));

				if (!reventado->isDead()){//si no estaba muerto ya
					if (muerto){
						reventado->setDead(true);
						entities->addDead(reventado->getType(),
								reventado->getId());
						matado = true;
					}
				}
			}
		}
	}

	return matado; //No se muy bien porque
}

void EventControl::ComeBackCompanions() {
	if (entities != NULL) {
		vector<Entity*> compains = entities->getIACompains();
		vector<Entity*>::iterator iter; //recorremos todos los companyeros
		Point p = (entities->getPlayer())->getCenter();
		Core::Entities::Type playerType = entities->getPlayerType();
		for (iter = compains.begin(); iter != compains.end(); iter++) {
			switch ((*iter)->getType()) {
			case Core::Entities::e_explosive:
				if((*iter)->getType() != playerType)
					((Explosive*) (*iter))->goToComeBack(p);
				break;
			case Core::Entities::e_tecnic:
				if((*iter)->getType() != playerType)
					((Technic*) (*iter))->goToComeBack(p);
				break;
			case Core::Entities::e_especialist:
				if((*iter)->getType() != playerType)
					((Especialist*) (*iter))->goToComeBack(p);
				break;
			case Core::Entities::e_captain:
				if((*iter)->getType() != playerType)
					((Captain*)(*iter))->goToComeBack(p);
				break;
			default:
				break;
			}
			//((Bot*)(*iter))->;//cambiamos el estado a ComeBack
		}
	}
}

EntityManager *EventControl::getEntities() const {
	return entities;
}

void EventControl::setEntities(EntityManager *entities) {
	this->entities = entities;
}

void EventControl::Update() {
	//TODO si estamos seguros de que no va a haber mas de uno de cada tipo esto puede ser mas eficiente
	this->UpdateExplosions();
	this->UpdateMoral();
	this->UpdateAmmunition();
}

void EventControl::UpdateExplosions(){
	vector<AuxExplosion>::iterator iter;
	SceneManager *sm = SceneManager::getInstance();
	iter = explosiones.begin();
	while (iter != explosiones.end()){
		if ((*iter).clock.getElapsedSeconds() > 2){
			Shape *aux = (*iter).explosion;
			//cout << "Borrar elemento" << endl;
			sm->removeElement(aux);//Que mierdas pasa con esto TODO
			//delete aux;
			explosiones.erase(iter);
		}else{
			iter++;
		}
	}

//	vector<ParticleEmiter *>::iterator pIter = particulas.begin();
//	while(pIter != particulas.end()){
//		(*pIter)->Step();
//
//		pIter++;
//	}

}

void EventControl::UpdateMoral() {
	vector<Entity*> subidoras = entities->getEntitiesbyType(
			Core::Entities::e_captain);
	vector<Entity*> receptoras = entities->getGoodPersons();
	vector<Entity*>::iterator iterSub;
	vector<Entity*>::iterator iterRec;
	for (iterSub = subidoras.begin(); iterSub != subidoras.end(); iterSub++) {
		Point posSub = (*iterSub)->getCenter();
		for (iterRec = receptoras.begin(); iterRec != receptoras.end();
				iterRec++) {
			Point posRec = (*iterRec)->getCenter();
			if (Point::distance(posSub, posRec) < 200) {
				((Character*) (*iterRec))->setMoral(3);
			} else {
				((Character*) (*iterRec))->returnMoral();
			}
		}
	}
}
void EventControl::UpdateAmmunition() {
	vector<Entity*> subidoras = entities->getEntitiesbyType(
			Core::Entities::e_especialist);
	vector<Entity*> receptoras = entities->getGoodPersons();
	vector<Entity*>::iterator iterSub;
	vector<Entity*>::iterator iterRec;
	for (iterSub = subidoras.begin(); iterSub != subidoras.end(); iterSub++) {
		Point posSub = (*iterSub)->getCenter();
		for (iterRec = receptoras.begin(); iterRec != receptoras.end();
				iterRec++) {
			Point posRec = (*iterRec)->getCenter();
			if (Point::distance(posSub, posRec) < 200) {
				((Character*) (*iterRec))->updateAmmunition();
			}
		}
	}
}

