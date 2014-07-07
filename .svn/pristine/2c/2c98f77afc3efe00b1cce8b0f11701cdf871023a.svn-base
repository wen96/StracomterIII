/*
 * Door.h
 *
 *  Created on: Apr 13, 2012
 *      Author: Chutaos Team
 */

#ifndef DOOR_H_
#define DOOR_H_

#include "Entity.h"
#include "Pathfinder.h"


class Door : public Entity {
public:
	Door();
	~Door();
	Door(const Door &door);
	Door & operator=(const Door &door);

	Door(int id_, Point p, vector<Point> contour, vector<int> vNodes, Pathfinder * pathf = NULL);

	void generateCollision();

	bool Open();
	bool Close();
	void Switch();

	bool isOpen();

	void setNodes(vector<int> insideNodes);

	void setPoints(vector<Point> puntos);
	vector<Point> getPoints();
	void setPF(Pathfinder *pf);
	void Rotate(double angle);
	void Move(Point p);

    double Width();

    double Height();
private:
	void copia(const Door &obj);
	void switchNodes();

	Pathfinder * pathf;
	bool open;

	/**
	 * Nodos que caen dentro de la puerta
	 */
	vector<int> nodes;

	/**
	 * Forma de la puerta
	 */
	vector<Point> points;
};


#endif /* DOOR_H_ */
