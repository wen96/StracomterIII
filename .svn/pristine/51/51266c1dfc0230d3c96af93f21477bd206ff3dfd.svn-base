/*
 * ParticleManager.cc
 *
 *  Created on: May 18, 2012
 *      Author: Chutaos Team
 */

#include "ParticleManager.h"
#include "SceneManager.h"

ParticleManager * ParticleManager::_inst = NULL;

ParticleManager *ParticleManager::getInstance() {
	if (_inst == NULL)
		_inst = new ParticleManager();
	return _inst;
}

ParticleManager::~ParticleManager() {
}

void ParticleManager::doExplosion(Point p) {
	if (GameOptions::getInstance()->isParticlesOn()) {
		AuxPart *aP = new AuxPart(p, Graphics::Particle::explosion);
		emisores.push_back(aP);
	}
}

void ParticleManager::doBloodBurst(Point p, Vector2D v) {
	if (GameOptions::getInstance()->isParticlesOn()) {
		AuxPart *aP = new AuxPart(p, v, Graphics::Particle::bloodBurst);
		emisores.push_back(aP);
	}
}

void ParticleManager::Update() {

	if (timer.isPaused()) {
		timer.Start();
	} else {

		// Actualizo las particulas existentes
		float timeDiff = timer.getElapsedMiliseconds() / 1000.0;
		timer.Reset();

		vector<ParticleNode *>::iterator pIter = particles.begin();
		;
		while (pIter != particles.end()) {
			CompositeParticle * p = (*pIter)->getParticle();

			p->step(timeDiff);

			if (p->isDead()) {
				delete p;
				sm->removeElement(*pIter);
				delete *pIter;
				particles.erase(pIter);
			} else {
				pIter++;
			}
		}

		// Creo las nuevas particulas
		vector<AuxPart *>::iterator eIter = emisores.begin();
		while (eIter != emisores.end()) {
			switch ((*eIter)->tipo) {
			case Graphics::Particle::explosion:
				if ((*eIter)->life.getElapsedMiliseconds() >= 100) {
					delete *eIter;
					emisores.erase(eIter);
				} else {
					CompositeParticle *p = NULL;
					ParticleNode *pn = NULL;

					debris.setMinMaxValues("positionX", (*eIter)->pos.getX(), (*eIter)->pos.getX());
					debris.setMinMaxValues("positionY", (*eIter)->pos.getY(), (*eIter)->pos.getY());

					int i = 0;
					while (i < 100) {
						p = debris.getParticle();
						pn = new ParticleNode(p);
						particles.push_back(pn);
						sm->addElement(pn, sm->getNode(Graphics::DirectNodes::t_escena));
						i++;
					}

					eIter++;
				}
				break;

			case Graphics::Particle::bloodBurst:
				if ((*eIter)->life.getElapsedMiliseconds() >= 100) {
					delete *eIter;
					emisores.erase(eIter);
				} else {
					CompositeParticle *p = NULL;
					ParticleNode *pn = NULL;

					bloodT.setMinMaxValues("positionX", (*eIter)->pos.getX(), (*eIter)->pos.getX());
					bloodT.setMinMaxValues("positionY", (*eIter)->pos.getY(), (*eIter)->pos.getY());
					bloodT.setMinMaxValues("speedX", (*eIter)->dir.x / 2 - 10, (*eIter)->dir.x / 2 + 10);
					bloodT.setMinMaxValues("speedY", (*eIter)->dir.y / 2 - 10, (*eIter)->dir.y / 2 + 10);

					bloodQ.setMinMaxValues("positionX", (*eIter)->pos.getX(), (*eIter)->pos.getX());
					bloodQ.setMinMaxValues("positionY", (*eIter)->pos.getY(), (*eIter)->pos.getY());
					bloodQ.setMinMaxValues("speedX", (*eIter)->dir.x / 2 - 10, (*eIter)->dir.x / 2 + 10);
					bloodQ.setMinMaxValues("speedY", (*eIter)->dir.y / 2 - 10, (*eIter)->dir.y / 2 + 10);

					int i = 0;
					while (i < 10) {
						p = bloodT.getParticle();
						pn = new ParticleNode(p);
						particles.push_back(pn);
						sm->addElement(pn, sm->getNode(Graphics::DirectNodes::t_escena));

						p = bloodQ.getParticle();
						pn = new ParticleNode(p);
						particles.push_back(pn);
						sm->addElement(pn, sm->getNode(Graphics::DirectNodes::t_escena));

						i++;
					}

					eIter++;
				}
				break;

			default:
				eIter++;
				break;
			}
		}
	}
}

ParticleManager::ParticleManager() {

	sm = SceneManager::getInstance();
	loadData();
}

ParticleManager::ParticleManager(const ParticleManager & pm) {
	debris = pm.debris;
	bloodT = pm.bloodT;
	bloodQ = pm.bloodQ;
}

ParticleManager & ParticleManager::operator =(const ParticleManager & pm) {
	if (this != &pm) {
		debris = pm.debris;
		bloodT = pm.bloodT;
		bloodQ = pm.bloodQ;
	}
	return *this;

}

void ParticleManager::loadData() {

	debris.setMinMaxValues("lifeTime", 0.5, 0.75);
	debris.setMinMaxValues("positionX", 0, 0);
	debris.setMinMaxValues("positionY", 0, 0);
	debris.setMinMaxValues("positionZ", 5, 5);
	debris.setMinMaxValues("speedX", -250, 250);
	debris.setMinMaxValues("speedY", -250, 250);
	debris.setMinMaxValues("speedZ", 0, 50);
	debris.setMinMaxValues("accelX", -150, 150);
	debris.setMinMaxValues("accelY", -150, 150);
	debris.setMinMaxValues("accelZ", 0, 50);
	debris.setMinMaxValues("colorR", 0.72, 0.72);
	debris.setMinMaxValues("colorG", 0.69, 0.69);
	debris.setMinMaxValues("colorB", 0.64, 0.64);
	debris.setMinMaxValues("colorA", 1, 1);
	debris.setMinMaxValues("fade", 1, 1);
	debris.setMinMaxValues("amplitude", 0, 0.25);
	debris.setMinMaxValues("round", 1, 1);
	debris.setMinMaxValues("textureNum", 0, 2);

	bloodT.setMinMaxValues("lifeTime", 0.5, 0.75);
	bloodT.setMinMaxValues("positionX", 0, 0);
	bloodT.setMinMaxValues("positionY", 0, 0);
	bloodT.setMinMaxValues("positionZ", 50, 50);
	bloodT.setMinMaxValues("speedX", 0, 0);
	bloodT.setMinMaxValues("speedY", 0, 0);
	bloodT.setMinMaxValues("speedZ", -10, 0);
	bloodT.setMinMaxValues("accelX", -100, 100);
	bloodT.setMinMaxValues("accelY", -100, 100);
	bloodT.setMinMaxValues("accelZ", 0, 50);
	bloodT.setMinMaxValues("colorR", 1, 1);
	bloodT.setMinMaxValues("colorG", 0, 0);
	bloodT.setMinMaxValues("colorB", 0, 0);
	bloodT.setMinMaxValues("colorA", 1, 1);
	bloodT.setMinMaxValues("fade", 1, 1);
	bloodT.setMinMaxValues("amplitude", 0, 0.25);
	bloodT.setMinMaxValues("round", 1, 1);

	bloodQ.setMinMaxValues("lifeTime", 0.5, 0.75);
	bloodQ.setMinMaxValues("positionX", 0, 0);
	bloodQ.setMinMaxValues("positionY", 0, 0);
	bloodQ.setMinMaxValues("positionZ", 50, 50);
	bloodQ.setMinMaxValues("speedX", 0, 0);
	bloodQ.setMinMaxValues("speedY", 0, 0);
	bloodQ.setMinMaxValues("speedZ", -10, 0);
	bloodQ.setMinMaxValues("accelX", -20, 20);
	bloodQ.setMinMaxValues("accelY", -20, 20);
	bloodQ.setMinMaxValues("accelZ", 0, 50);
	bloodQ.setMinMaxValues("colorR", 1, 1);
	bloodQ.setMinMaxValues("colorG", 0, 0);
	bloodQ.setMinMaxValues("colorB", 0, 0);
	bloodQ.setMinMaxValues("colorA", 1, 1);
	bloodQ.setMinMaxValues("fade", 1, 1);
	bloodQ.setMinMaxValues("amplitude", 0, 0.25);
	bloodQ.setMinMaxValues("round", 1, 1);

	//string rroot = RESOURCESROOT;
//	ParticleRendererTextureFading::addTexture(new TextureImage("3rdParty/WankelParticles/fuego1.jpg"));
//	ParticleRendererTextureFading::addTexture(new TextureImage("3rdParty/WankelParticles/fuego2.jpg"));
//	ParticleRendererTextureFading::addTexture(new TextureImage("3rdParty/WankelParticles/fuego3.jpg"));
//	ParticleRendererTextureFading::addTexture(new TextureImage(rroot + "texturas/blood.png"));
}

