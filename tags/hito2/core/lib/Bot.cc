/*
 * Bot.cc
 *
 *  Created on: 12/11/2011
 *      Author: Chutaos Team
 */

#include "Bot.h"
#include "EntityManager.h"
#include "EventControl.h"
#include "Pathfinder.h"

Bot::Bot() {
	pf = NULL;
}

void Bot::updateState(int input){
	statusMachine.updateStates(input);
}

void Bot::addAtacker(Point p){
	atackers.push(p);
}

void Bot::Dispara(Entity *objetivo){
	this->generateVisionRotation(objetivo->getCenter());
	this->generateRay(objetivo->getCenter());
	this->generateVisionTri();

	ResourceManager::getInstance()->getEvents()->Shoot(this);
}

Bot::Bot(ResourceManager *r, Core::Entities::Type t) {
	setId(0);
	setVisible(true);
	setSmall(false);
	setResource(r);
	goodPerson =
			(t == Core::Entities::e_captain
					|| t == Core::Entities::e_especialist
					|| t == Core::Entities::e_tecnic
					|| t == Core::Entities::e_explosive);
	dead = false;

	blind = false;
	vision = Tri();
	generateFeatures(t);
	generateCollision();
	pf = NULL;

	mov = new MovementComp();
	mov->setPos(Point());
	mov->setVelocity(Vector2D());
	mov->setHeading(Vector2D(this->angle));
	mov->setMaxSpeed(this->getSpeed());
	idDisplay = t;
}

Bot::Bot(const int idG, const Point pos, float angle, ResourceManager *res,
		Core::Entities::Type t) {

	id = idG;
	setVisible(true);
	setSmall(true);
	goodPerson =
			(t == Core::Entities::e_captain
					|| t == Core::Entities::e_especialist
					|| t == Core::Entities::e_tecnic
					|| t == Core::Entities::e_explosive);
	setCenter(pos);
	setResource(res);
	dead = false;
	blind = false;
	vision = Tri();
	generateFeatures(t);
	generateCollision();
	pf = NULL;
	idDisplay = t;

	mov = new MovementComp();
	mov->setPos(pos);
	mov->setVelocity(Vector2D());
	mov->setHeading(Vector2D(this->angle));
	mov->setMaxSpeed(this->getSpeed());
}

bool Bot::meAtacan(EntityManager* manager){
	return !atackers.empty();
}

Bot::Bot(const Bot &ene) {
	setId(ene.getId());
	setVisible(ene.getVisible());
	setSmall(ene.getSmall());
	setCenter(ene.getCenter());
	setResource(ene.getResource());
	setColor(ene.getColor());
	generateFeatures(ene.getType());
	generateCollision();
	blind = ene.blind;
	vision = ene.vision;
	goodPerson = ene.goodPerson;
	pf = ene.pf;

	mov = new MovementComp(*ene.mov);
}

Bot::~Bot() {
	pf = NULL;
	if(mov != NULL){
		delete mov;
		mov = NULL;
	}

}

Bot&
Bot::operator =(const Bot & ene) {
	if (&ene != this) {
		//this->~Bot();
		setId(ene.getId());
		setType(ene.getType());
		setVisible(ene.getVisible());
		setSmall(ene.getSmall());
		setCenter(ene.getCenter());
		setResource(ene.getResource());
		blind = ene.blind;
		vision = ene.vision;
		pf = ene.pf;

		if(mov != NULL)
			delete mov;

		mov = new MovementComp(*ene.mov);
	}
	return *this;
}

ostream& operator<<(ostream &os, const Bot& obj) {
	os << "Entity";
	switch (obj.type) {
	case 1:
		os << "(e_captain)";
		break;
	case 2:
		os << "(e_tecnic)";
		break;
	case 3:
		os << "(e_especialist)";
		break;
	case 4:
		os << "(e_explosive)";
		break;
	case 5:
		os << "(e_enemy1)";
		break;
	case 6:
		os << "(e_enemy2)";
		break;
	case 7:
		os << "(e_enemy3)";
		break;
	case 8:
		os << "(e_miniboss)";
		break;
	case 9:
		os << "(e_megaboss)";
		break;
	default:
		os << "(e_none)";
		break;
	}

	return os;
}

Tri Bot::generateVisionTri() {
	Point a = getCenter();
	double ang = getAngle() * -1;

	double cosAng = cos((ang - 20) * M_PI / 180);
	double sinAng = sin((ang - 20) * M_PI / 180);

	int x = a.getX() + 500 * cosAng;
	int y = a.getY() - 500 * sinAng;
	Point b1(x, y);

	x = a.getX() + 700 * cosAng;
	y = a.getY() - 700 * sinAng;
	Point b2(x, y);

	cosAng = cos((ang + 20) * M_PI / 180);
	sinAng = sin((ang + 20) * M_PI / 180);

	x = a.getX() + 500 * cosAng;
	y = a.getY() - 500 * sinAng;
	Point c1(x, y);

	x = a.getX() + 700 * cosAng;
	y = a.getY() - 700 * sinAng;
	Point c2(x, y);

	x = a.getX() + 500 * cos(ang * M_PI / 180);
	y = a.getY() - 500 * sin(ang * M_PI / 180);
	this->generateRay(Point(x, y));

	vision = Tri(a, c1, b1);
	secondaryVision = Tri(a, c2, b2);

	return vision;
}

Tri Bot::getVision() {
	return vision;
}

void Bot::setBlindness(bool isBlind) {
	blind = isBlind;
}

bool Bot::isBlind() {
	return blind;
}

string Bot::getStatusS() {
	return statusMachine.getCurrentS();
}

int Bot::getStatusI() {
	return statusMachine.getCurrentI();
}

void Bot::setPathfinder(Pathfinder *pf) {
	this->pf = pf;
}

int Bot::isInsideFOV(Point p) {
	/*
	 * 0: no lo ve
	 * 1: esta en el FOV principal
	 * 2: esta en el FOV secundario
	 */
	int result = -1;

	if (vision.isInside(p) == 1) {
		result = 1;
	} else if (secondaryVision.isInside(p) == 1) {
		result = 2;
	} else {
		result = 0;
	}
	return result;
}

vector<Point> Bot::getPath() const {
	return path;
}

void Bot::setPath(vector<Point> path) {
	this->mov->setPath(path);
	this->path = path;
}

void Bot::calculatePath(Point destino) {
	if (pf != NULL) {
		path = pf->AStar(getCenter(), destino);
		path = pf->smoothPath(path);
		if (mov!=NULL){
			mov->setPath(path);
		}

	}
}

Entity * Bot::selectObjetive(EntityManager *manager) {
	Entity * objetivo = NULL;
	double objValue = 0.0;
	World *mundo = ResourceManager::getInstance()->getWorld();
	bool objectiveFound = false;

	list<int>::iterator liter = memory.begin();
	while (liter != memory.end()) {

		Character *posibleObjetivo = (Character *) manager->getEntity(*liter);
		bool flagBorrar = false;

		if (posibleObjetivo != NULL && !posibleObjetivo->isDead()) { // Si el entity no esta muerto
			Point centroObj = posibleObjetivo->getCenter();
			if (this->isInsideFOV(centroObj) > 0) { // Si esta en el campo de vision
				if (mundo->RayBody(this->getCenter(), centroObj).body == posibleObjetivo->getBody()->getBody()) { // Si tenemos linea de vision
					if (!objectiveFound) {
						objetivo = (Entity *) posibleObjetivo;
						objectiveFound = true;
						objValue = this->enemyValue(posibleObjetivo);

						if (currentObj != NULL){
							delete currentObj;
							currentObj = NULL;
						}
						currentObj = new Point(objetivo->getCenter());
					} else {
						double newValue = this->enemyValue(posibleObjetivo);
						if (newValue >= objValue) {
							objetivo = (Entity *) posibleObjetivo;
							objValue = newValue;

							if (currentObj != NULL){
								delete currentObj;
								currentObj = NULL;
							}
							currentObj = new Point(objetivo->getCenter());
						}
					}
				} else {
					flagBorrar = true;
				}
			} else {
				flagBorrar = true;
			}
		} else {
			flagBorrar = true;
		}

		if (flagBorrar) {
			liter = memory.erase(liter);
		} else {
			liter++;
		}
	}

	return objetivo;
}

bool Bot::Move(int radius){
	bool llegado = false;

	if (!path.empty()) {

		if (getCenter().isInRadius(path.front(), radius)) {
			path.erase(path.begin());
		}

		this->generateVisionRotation(path.front());

		float x = 50 * cos(getAngle());
		float y = 50 * sin(getAngle());

		addLinearVelocity(Force(x, y));

		//this->generateVisionRotation(path.back());
		this->generateRay(path.front());
		vision = this->generateVisionTri();

	} else {
		llegado = true;
	}

	return llegado;
}

bool Bot::Move() {
	mov->setPos(this->getCenter());
	mov->Update();

	//this->setCenter(mov->getPosP());

	Vector2D force(mov->getVelocity());
	setLinearVelocity(Force(force.x, force.y));

	double newAngle = mov->getVelocity().Angle();
	if(mov->getVelocity().y > 0)
		newAngle *= -1;

	this->setAngle(newAngle);

	Point enfrente(force.toPoint());

	enfrente += this->getCenter();

	this->generateVisionRotation(enfrente);
	this->generateRay(enfrente);
	this->generateVisionTri();

	Point currPoint = this->getCenter();
	Point destPoint;
	if (!path.empty()){
		destPoint = this->path.back();//TODO Cuidado, que da segmentacion
	}

	return currPoint.isInRadius(destPoint, 5);
}

void Bot::setLeader(MovementComp *mov){
	if(this->mov != NULL)
		this->mov->setLeader(mov);
}

void Bot::setOffset(Vector2D vec){
	if(this->mov != NULL)
		this->mov->setOffset(vec);
}

double Bot::enemyValue(Character *enemigo) {
	return 1.0 / Point::distance(this->getCenter(), enemigo->getCenter());
}

void Bot::setDebug(){
	statusMachine.updateStates(0);
}

bool Bot::enemySpotted(EntityManager* manager){
	bool atacar =false;
	if(!this->blind){
		Entity *auxEnt = NULL;
		vector<Entity *> entidades;

		if (goodPerson){
			entidades = manager->getBadPersons();
		}else{
			entidades = manager->getGoodPersons();
		}


		vector<Entity *>::iterator entIter;
		for(entIter = entidades.begin(); entIter != entidades.end(); entIter++){
			auxEnt = *entIter;
			if(auxEnt->getId() != this->id && auxEnt->soyVisible()){//Si no soy yo mismo
				Point ePos(auxEnt->getCenter());
				int isInside = vision.isInside(ePos);
				if(isInside == 1 || isInside == 0){//Si vemos al caballero buscado
					if(resource->getWorld()->RayBody(getCenter(), auxEnt->getCenter()).body == auxEnt->getBody()->getBody()){
						memory.push_back(auxEnt->getId());//pongo la entidad en la memoria
						atacar = true;
					}

				}
			}
		}
	}

	return atacar;
}
