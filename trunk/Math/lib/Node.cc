/*
 * Node.cc
 *
 *  Created on: 06/11/2011
 *      Author: Chutaos Team
 */

#include "Node.h"


//TODO: No estoy seguro de que el = de la clase vector haga una copia
Node::Node() {
	id = 0;
	arists.clear();
}

Node::Node(int n){
	id = n;
	arists.clear();
}

Node::Node(Point n){
	id = 0;
	position = n;
	arists.clear();
}

Node::Node(vector<Node*> a){
	id = 0;
	arists = a;
}

Node::Node(int n, Point ps){
	id = n;
	position = ps;
	arists.clear();
}

Node::Node(int n, Point ps, vector<Node*> a){
	id = n;
	position = ps;
	arists = a;
}

Node::Node(const Node & obj){
	id = obj.id;
	position = obj.position;
	arists = obj.arists;
}

Node& Node::operator=(const Node &obj){
	if (this != &obj){
		this->~Node();
		id = obj.id;
		position = obj.position;
		arists = obj.arists;
	}
	return *this;
}

Node::~Node() {
	if (this!=NULL){
		id = 0;
		if (!arists.empty()){
			arists.clear();
		}
	}
}

vector<Node*> Node::getAdjacency(){
	return arists;
}



bool Node::addArist(Node *node){
	arists.push_back(node);
	return true;
}



bool Node::removeArist(Node* node){
	bool borrado = false;
	vector<Node*>::iterator iter;

	for (iter = arists.begin(); iter < arists.end(); iter++){
		if ((*iter) == node){
			arists.erase(iter);
			borrado = true;
			break;
		}
	}

	return borrado;
}

bool Node::removeAllArist(Node* node){
	bool borrado = false;
	vector<Node*>::iterator iter;

	for (iter = arists.begin(); iter < arists.end(); iter++){
		if ((*iter) == node){
			arists.erase(iter);
			borrado = true;
			iter--;
		}
	}

	return borrado;
}

bool Node::removeAllAristById(int n){
	bool borrado = false;
	vector<Node*>::iterator iter;

	for (iter = arists.begin(); iter < arists.end(); iter++){
		if ((*iter)->id == n){
			arists.erase(iter);
			borrado = true;
			iter--;
		}
	}
	return borrado;
}

bool Node::removeAristById(int n){
	bool borrado = false;
	vector<Node*>::iterator iter;

	for (iter = arists.begin(); iter < arists.end(); iter++){
		if ((*iter)->id == n){
			arists.erase(iter);
			borrado = true;
			iter--;
			break;
		}
	}
	return borrado;
}

Point Node::getPosition() const{
	return position;
}



int Node::getId() const{
	return id;
}



void Node::setPosition(Point n){
	position = n;
}

ostream&
operator<< (ostream &os, const Node &n){
	os << "Node " <<n.getId() <<" ";
	os << n.getPosition();

	vector<Node*>::const_iterator iter;
	for (iter = n.arists.begin(); iter < n.arists.end(); iter++){
		//cout << endl << "\t=>" << (*iter)->getId();
	}
	return os;
}

void Node::setId(int n){
	id = n;
}

vector<Node*> Node::getArists(){
	return arists;
}

bool Node::showArists()
{

	return true;
}







