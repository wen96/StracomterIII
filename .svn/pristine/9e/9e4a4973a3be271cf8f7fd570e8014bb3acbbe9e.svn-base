/*
 * Especialist.cc
 *
 *  Created on: 15/02/2012
 *      Author: ruben
 */

#include "Especialist.h"
#include "EntityManager.h"

Especialist::Especialist() {
	// TODO Auto-generated constructor stub

}

Especialist::~Especialist() {
	// TODO Auto-generated destructor stub
}

void Especialist::updateAI(EntityManager* manager) {
	if (hp <= 15 && haveHealthobject()){
		applyObjectHealth();
	}else if (ammunition <= 10 && haveArmmorobject()){
		applyobjectArmmor();
	}else{
		string stad = statusMachine.getCurrentS();
		//////////////////////////////// 	UPDATEAI	/////////////////////////////////////////////////
		if (stad == "Debug") {
			this->Debug();
		} else if (stad == "FollowPlayer") {
			this->FollowPlayer(manager);
		} else if (stad == "Attack") {
			this->Attack(manager);
		} else if (stad == "ComeBack") {
			this->ComeBack();
		} else if (stad == "GotoPoint") {
			this->gotoPosition(manager);
		}
	}
}

void Especialist::FollowPlayer(EntityManager* manager) {

	//Si me atacan
	if (meAtacan(manager)) {
		//Me giro hacia donde me atacan
		this->generateVisionRotation(atackers.front());
		this->generateVisionTri();
		atackers.pop(); //saco el punto desde donde me atacan
	}

	if (enemySpotted(manager)) {
		//si vemos a agluien actacamos
		statusMachine.updateStates(2);
	} else {
		Entity* player = manager->getPlayer();
		if (player != NULL) {
			if (!player->getCenter().isInRadius(getCenter(), 200)) {
				this->calculatePath(player->getCenter());
				this->updateState(4);
			} else {
				this->mov->setMode(1);
				this->Move();
			}
		} else {
			this->turnAround(1);
			this->generateVisionTri();
		}
	}
}

//Attack 2
void Especialist::Attack(EntityManager* manager) {
	Point *curarse=NULL;
	Entity *ent = NULL;
	vector <Entity *> l = manager->getEntitiesbyType(Core::Entities::e_captain);
	if (!l.empty()){
		ent = l[0];
		curarse = new Point(ent->getCenter());
	}

	if (hp < 20 && curarse != NULL){
		this->goToComeBack(*curarse);
		//cout << "Entra especia curarse" << endl;
	}else {
		Entity *objetivo = this->selectObjetive(manager);

		if (objetivo != NULL) {
			this->Dispara(objetivo);
		} else {
			this->statusMachine.updateStates(1);
		}
	}

	if (curarse!= NULL){
		delete curarse;
	}
}

//Comback 3
void Especialist::ComeBack() {
	if (Move()) {
		path.clear();
		statusMachine.updateStates(1);
	}
}
//Debug 0
void Especialist::Debug() {
	this->mov->setMode(0);
	this->Move();
}

//Pursues 4
void Especialist::gotoPosition(EntityManager* manager) {
	bool llegado = false;

	this->mov->setMode(0);
	llegado = this->Move();

	//Si me atacan
	if (meAtacan(manager)) {
		//Me giro hacia donde me atacan
		this->generateVisionRotation(atackers.front());
		this->generateVisionTri();
		atackers.pop(); //saco el punto desde donde me atacan
	}

	if (enemySpotted(manager)) {
		this->statusMachine.updateStates(2); //atacar
	} else {
		if (llegado) {
			this->statusMachine.updateStates(1); //followPlayer
		}
	}
}

void Especialist::generateFSM() {
	int deb = statusMachine.addState("Debug");

	// Patrullamos la zona = 1
	int follow = statusMachine.addState("FollowPlayer");

	// Atacamos a un enemigo = 2
	int atack = statusMachine.addState("Attack");

	// Perseguimos a un enemigo = 3
	int comeBack = statusMachine.addState("ComeBack");

	// De momento = 4
	int gotoPoint = statusMachine.addState("GotoPoint");

	statusMachine.addTransition(follow, atack, 2);
	statusMachine.addTransition(follow, comeBack, 3);

	statusMachine.addTransition(atack, follow, 1);
	statusMachine.addTransition(atack, comeBack, 3);

	statusMachine.addTransition(comeBack, follow, 1);

	statusMachine.addTransition(follow, gotoPoint, 4);
	statusMachine.addTransition(gotoPoint, follow, 1);
	statusMachine.addTransition(gotoPoint, atack, 2);

	// Para hacer pruebas
	statusMachine.addTransition(follow, deb, 0);
	statusMachine.addTransition(atack, deb, 0);
	statusMachine.addTransition(comeBack, deb, 0);

	statusMachine.makeCurrent(follow);

}

void Especialist::goToComeBack(Point p) {
	calculatePath(p);
	statusMachine.updateStates(4);
}

Especialist::Especialist(ResourceManager *r, Core::Entities::Type t, Pathfinder *pf_) {
	id = 0;
	visible = true;
	small = false;
	resource = r;
	features = NULL;
	goodPerson = (t == Core::Entities::e_captain || t == Core::Entities::e_especialist || t == Core::Entities::e_tecnic
			|| t == Core::Entities::e_explosive);
	dead = false;
	blind = false;
	currentObj = NULL;
	vision = Tri();
	generateFeatures(t);
	generateCollision();
	generateFSM();
	pf = pf_;
	idDisplay = t*5;

	generateVisionTri();

	mov = new MovementComp();
	mov->setPos(Point());
	mov->setVelocity(Vector2D());
	mov->setHeading(Vector2D(this->angle));
	mov->setMaxSpeed(400);
	mov->setMass(1);
	mov->setMaxForce(4);

}

Especialist::Especialist(const int idG, const Point pos, float angle, ResourceManager *res, Core::Entities::Type t, Pathfinder *pf_) {
	features = NULL;
	id = idG;
	setCenter(pos);
	setAngle(angle);
	visible = true;
	small = false;
	resource = res;
	goodPerson = (t == Core::Entities::e_captain ||
			t == Core::Entities::e_especialist ||
			t == Core::Entities::e_tecnic ||
			t == Core::Entities::e_explosive);
	dead = false;
	blind = false;
	currentObj = NULL;
	vision = Tri();
	generateFeatures(t);
	generateCollision();
	generateFSM();
	pf = pf_;
	idDisplay = t;

	generateVisionTri();

	mov = new MovementComp();
	mov->setPos(pos);
	mov->setVelocity(Vector2D());
	mov->setHeading(Vector2D(this->getAngle()));
	mov->setMaxSpeed(speed);
	mov->setMass(1);
	mov->setMaxForce(force);
}
