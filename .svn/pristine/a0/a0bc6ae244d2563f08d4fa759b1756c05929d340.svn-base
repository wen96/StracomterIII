/*
 * Door.cc
 *
 *  Created on: Apr 13, 2012
 *      Author: Chutaos Team
 */

#include "Door.h"

#include "GraphicTree.h"
#include "AnimationControl.h"

class GraphicNode;

Door::Door() {
	open = false;
	pathf = NULL;
}

Door::~Door() {
	open = false;
	pathf = NULL;
	nodes.clear();
}

Door::Door(const Door & door) {
	this->copia(door);
}

Door & Door::operator =(const Door & door) {
	if(this != &door){
		this->copia(door);
	}
	return *this;
}

Door::Door(int id_, Point p, vector<Point> contour, vector<int> vNodes, Pathfinder *pf) {
	this->id = id_;
	setCenter(p);
	setType(Core::Entities::e_door);
	points = contour;
	color = Color<float>(0.8,0.8,0.8);
	generateCollision();
	idDisplay = ResourceManager::getInstance()->generateDoor(points);
	open = false;
	nodes = vNodes;
	pathf = pf;
}

void Door::generateCollision() {

	Polygon pol(Point(), points);
	pol.Reverse();

	BodyData *aux = new BodyData(pol);
	aux->setNeutral();

	World *auxWorld = ResourceManager::getInstance()->getWorld();
	body = new Body(*auxWorld, *aux);
	body->setPosition(center);
	body->setAngle(angle);
}

bool Door::Open() {
	if(open)
		return false;

	open = true;

	switchNodes();

	// Hacemos los cambios graficos necesarios
	this->getNodo()->setVisible(false);
	this->getBody()->Active(false);

	return true;
}

bool Door::Close() {
	if(!open)
		return false;

	open = false;

	switchNodes();

	// Hacemos los cambios graficos necesarios
	this->getNodo()->setVisible(true);
	this->getBody()->Active(true);

	return true;
}

void Door::Switch(){
	open = !open;

	switchNodes();

	// Hacemos los cambios graficos necesarios
	if(open){
		//this->getNodo()->setVisible(false);
		AnimationControl *ac = AnimationControl::getInstance();
		ac->addFadeOut(this,1000);
		this->getBody()->Active(false);
	}else{
		//this->getNodo()->setVisible(true);
		AnimationControl *ac = AnimationControl::getInstance();
		ac->addFadeIn(this,1000);
		this->getBody()->Active(true);
	}
}

bool Door::isOpen(){
	return open;
}

void Door::setNodes(vector<int> insideNodes){
	nodes = insideNodes;
}

void Door::setPoints(vector<Point> puntos){
	points = puntos;
}

vector<Point> Door::getPoints(){
	return points;
}

void Door::setPF(Pathfinder *pf){
	pathf = pf;
}

void Door::copia(const Door &obj){
	this->open = obj.open;
	this->nodes = obj.nodes;
	this->pathf = obj.pathf;
}

void Door::switchNodes(){
	if(pathf != NULL){
		vector<int>::iterator iIter;
		for(iIter = nodes.begin(); iIter != nodes.end(); iIter++){
			pathf->getDualGraph()->changeNodeState(*iIter, open);
		}
	}
}

void Door::Rotate(double a){
	setAngle(this->getAngle() + a);

	double despX = abs(points[2].getX() - points[1].getX()) / 2,
		   despY = abs(points[1].getY() - points[0].getY()) / 2,
		   x = points[0].getX() + despX,
		   y = points[0].getY() + despY;

	points[0] = Point(x - despY, y - despX);
	points[1] = Point(x - despY, y + despX);
	points[2] = Point(x + despY, y + despX);
	points[3] = Point(x + despY, y - despX);

	if(body != NULL)
		delete body;
	generateCollision();

	idDisplay = ResourceManager::getInstance()->generateDoor(points, idDisplay);
}

void Door::Move(Point p) {

	setCenter(p);

	double xDesp = max(abs(points[0].getX() - points[1].getX()),
					   abs(points[0].getX() - points[2].getX())) / 2.0;
	double yDesp = max(abs(points[0].getY() - points[1].getY()),
					   abs(points[0].getY() - points[2].getY())) / 2.0;

	double x = p.getX();
	double y = p.getY();

	Point a(x - xDesp, y - yDesp);
	Point b(x - xDesp, y + yDesp);
	Point c(x + xDesp, y + yDesp);
	Point d(x + xDesp, y - yDesp);

	points.clear();
	points.push_back(a);
	points.push_back(b);
	points.push_back(c);
	points.push_back(d);

	if(body != NULL)
		delete body;
	generateCollision();

	idDisplay = ResourceManager::getInstance()->generateDoor(points);
}

double Door::Width(){
	if(points[2].getY() == points[1].getY())
		return abs(points[2].getX() - points[1].getX());
	else
		return abs(points[0].getX() - points[1].getX());
}

double Door::Height(){
	if(points[1].getX() == points[0].getX())
		return abs(points[1].getY() - points[0].getY());
	else
		return abs(points[1].getY() - points[2].getY());
}
