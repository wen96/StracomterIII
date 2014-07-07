/*
 * Enemy.cc
 *
 *  Created on: 15/02/2012
 *      Author: Chutaos Team
 */

#include "Enemy.h"
#include "EventControl.h"
#include "Map.h"

Enemy::Enemy() {
	// TODO Auto-generated constructor stub
}

Enemy::~Enemy() {
	// TODO Auto-generated destructor stub
}

void Enemy::updateAI(EntityManager* manager) {

	string stad = statusMachine.getCurrentS();

	//////////////////////////////// 	PARTRULLAR	/////////////////////////////////////////////////
	if (stad == "Debug") {
		this->Debug();
	}
	if (stad == "Patrol") {
		this->Patrol(manager);
		//////////////////////////////// 	ATACAR		/////////////////////////////////////////////////
	} else if (stad == "Attack") {
		this->Attack(manager);
		//////////////////////////////// 	PERSEGUIR	/////////////////////////////////////////////////
	} else if (stad == "Pursue") {
		this->gotoPosition(manager);
		////////////////////////////////	 ASEGURAR 	/////////////////////////////////////////////////
	} else if (stad == "Ensure") {
		this->ensureZone(manager);
	}

}

//Patrol 10
void Enemy::Patrol(EntityManager* manager) {

	if (!meAtacan(manager)) {
		if (enemySpotted(manager)) {
			this->statusMachine.updateStates(20);
		} else {
			if(patrolPoints[currentPatrolPoint].isInRadius(this->getCenter(), 10)){
				path.clear();
				path.push_back(patrolPoints[currentPatrolPoint]);

				currentPatrolPoint += rand() % 2 + 1;
				currentPatrolPoint = currentPatrolPoint % 3;

				path.push_back(patrolPoints[currentPatrolPoint]);
				if (mov!=NULL){
					mov->setPath(path);
				}
			}else{
				if(path.empty()){
					this->calculatePath(patrolPoints[currentPatrolPoint]);
				}else
					this->Move();
			}
		}
	} else {
		this->calculatePath(atackers.front());
		atackers.pop();
		this->statusMachine.updateStates(30);
	}
}

//Pursue 30
void Enemy::gotoPosition(EntityManager* manager) {
	bool llegado = false;

	llegado = this->Move();

	if (enemySpotted(manager)) {
		this->statusMachine.updateStates(20);
	} else {
		if (llegado) {
			nRotations = 0;
			this->statusMachine.updateStates(40);
		}
	}
}

//Ensure 40
void Enemy::ensureZone(EntityManager* manager) {

	bool terminadoGiro = this->fullRotation();

	if (enemySpotted(manager)) {
		this->statusMachine.updateStates(20);
	} else {
		if (terminadoGiro) {
			this->calculatePath(patrolPoints[currentPatrolPoint]);
			this->statusMachine.updateStates(10);
		}
	}
}

//Attack 20
void Enemy::Attack(EntityManager* manager) {

	Entity *objetivo = this->selectObjetive(manager);

	if (objetivo != NULL) {
		if (this->isInsideFOV(objetivo->getCenter()) == 2) {
			this->calculatePath(objetivo->getCenter());
			this->statusMachine.updateStates(30);
		} else {
			this->Dispara(objetivo);
		}
	} else {
		if (currentObj != NULL) {
			this->calculatePath(*currentObj);
			this->statusMachine.updateStates(30);

			delete currentObj;
			currentObj = NULL;
		} else {
			this->calculatePath(patrolPoints[currentPatrolPoint]);
			this->statusMachine.updateStates(10);
		}
	}
}

void Enemy::Debug() {
	this->Move();
}

void Enemy::partialRotation() {
	double ang = this->getAngle();

	if (((int) ang) % 90 == 0) {
		if (flagPatrullo) {
			timerPatrolRotation.Reset();
			flagPatrullo = false;
		} else {
			if (timerPatrolRotation.getElapsedMiliseconds() > 3000) {
				flagPatrullo = true;
				this->turnAround(1);
				vision = this->generateVisionTri();
			}
		}
	} else {
		flagPatrullo = true;
		this->turnAround(1);
		vision = this->generateVisionTri();
	}

}

bool Enemy::fullRotation() {
	if (nRotations < 360) {
		nRotations++;
		this->turnAround(1);
		vision = this->generateVisionTri();
		return false;
	}

	return true;
}

void Enemy::generateFSM() {
	int deb = statusMachine.addState("Debug");

	// Patrullamos la zona = 1
	int pat = statusMachine.addState("Patrol");

	// Atacamos a un enemigo = 2
	int att = statusMachine.addState("Attack");

	// Perseguimos a un enemigo = 3
	int pur = statusMachine.addState("Pursue");

	// Perseguimos a un enemigo = 4
	int ens = statusMachine.addState("Ensure");

	statusMachine.addTransition(pat, att, 20);
	statusMachine.addTransition(pat, pur, 30);

	statusMachine.addTransition(att, pat, 10);
	statusMachine.addTransition(att, pur, 30);

	statusMachine.addTransition(pur, att, 20);
	statusMachine.addTransition(pur, ens, 40);

	statusMachine.addTransition(ens, pat, 10);
	statusMachine.addTransition(ens, att, 20);

	statusMachine.makeCurrent(pat);

	// Para hacer pruebas
	statusMachine.addTransition(pat, deb, 0);
	statusMachine.addTransition(att, deb, 0);
	statusMachine.addTransition(pur, deb, 0);
	statusMachine.addTransition(ens, deb, 0);

	statusMachine.setDebug(false);
}

Enemy::Enemy(ResourceManager *r, Core::Entities::Type t, Pathfinder *pf_) {
	features = NULL;
	id = 0;
	visible = true;
	small = false;
	resource = r;
	goodPerson =
			(t == Core::Entities::e_captain
					|| t == Core::Entities::e_especialist
					|| t == Core::Entities::e_tecnic
					|| t == Core::Entities::e_explosive);
	dead = false;
	blind = false;
	visible = true;
	vision = Tri();
	generateCollision();
	generateFeatures(t);
	generateFSM();
	pf = pf_;
	currentObj = NULL;
	flagPatrullo = true;

	generateVisionTri();

	mov = new MovementComp();
	mov->setPos(Point());
	mov->setVelocity(Vector2D());
	mov->setHeading(Vector2D(this->angle));
	mov->setMaxSpeed(400);
	mov->setMass(1);
	mov->setMaxForce(4);
	idDisplay = t;
	clkSanar.Reset();
	clkAmmu.Reset();

//	statusMachine.setDebug(true);
}

Enemy::Enemy(const int idG, const Point pos, float angle, ResourceManager *res,
		Core::Entities::Type t, Pathfinder *pf_, vector<Point> patrulla) {
	features = NULL;
	id = idG;
	setCenter(pos);
	setAngle(angle);
	visible = true;
	small = false;
	resource = res;
	goodPerson =
			(t == Core::Entities::e_captain
					|| t == Core::Entities::e_especialist
					|| t == Core::Entities::e_tecnic
					|| t == Core::Entities::e_explosive);
	dead = false;
	blind = false;
	visible = true;
	vision = Tri();
	generateFeatures(t);
	generateCollision();
	generateFSM();
	pf = pf_;
	patrolPosition = pos;
	currentObj = NULL;
	flagPatrullo = true;

	generateVisionTri();

	mov = new MovementComp();
	mov->setPos(Point());
	mov->setVelocity(Vector2D());
	mov->setHeading(Vector2D(this->angle));
	mov->setMaxSpeed(400);
	mov->setMass(1);
	mov->setMaxForce(4);
	idDisplay = t;
	clkSanar.Reset();
	clkAmmu.Reset();

	currentPatrolPoint = rand()%3;
	patrolPoints = patrulla;

//	statusMachine.setDebug(true);
}

