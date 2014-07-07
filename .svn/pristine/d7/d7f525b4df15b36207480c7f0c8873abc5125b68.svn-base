/*
 * Model.cc
 *
 *  Created on: 15/11/2011
 *      Author: Chutaos team
 */

#include "Model2D.h"


Model2D::Model2D(int type){

	vector<Point> aux;
	switch(type){
	case Core::Entities::e_captain:
		//aux.push_back(Point(0,35));
		//aux.push_back(Point(-25,20));
		//shape = new Polygon(Point(0,0), aux);
		//shape = new Polygon(8,Point(0,0),30,45);
		//shape = new Polygon(4,Point(0,0),50,45);
		shape = new Polygon(Point(0,0), Core::Radius);
		//shape = new Polygon(Point(-50,0), Point(-200, 60));
		//shape = new Polygon(Point(0,0), 30);
		break;
	case Core::Entities::e_especialist:
		//shape = new Polygon(8,Point(0,0),30,45);
		shape = new Polygon(Point(0,0), Core::Radius);
		break;
	case Core::Entities::e_tecnic:
		//shape = new Polygon(8,Point(0,0),30,45);
		shape = new Polygon(Point(0,0), Core::Radius);
		break;
	case Core::Entities::e_explosive:
		//shape = new Polygon(8,Point(0,0),30,45);
		shape = new Polygon(Point(0,0), Core::Radius);
		break;
	case Core::Entities::e_enemy1:
		//shape = new Polygon(8,Point(0,0),0.05,45);
		//shape = new Polygon(4,Point(0,0),50,45);
		shape = new Polygon(Point(0,0), Core::Radius);
		//shape = new Polygon(8,Point(0,0),30,45);
		break;
	case Core::Entities::e_enemy2:
		//shape = new Polygon(8,Point(0,0),0.05,45);
		//shape = new Polygon(4,Point(0,0),50,45);
		shape = new Polygon(Point(0,0), Core::Radius);
		break;
	case Core::Entities::e_enemy3:
		//shape = new Polygon(8,Point(0,0),0.05,45);
		//shape = new Polygon(4,Point(0,0),50,45);
		shape = new Polygon(Point(0,0), Core::Radius);
		break;
	case Core::Entities::e_wall:
		//shape = new Polygon(4,Point(0,0),40,45);
		//shape = new Polygon(Point(0,0), 30);
		aux.push_back(Point(0,0));
		aux.push_back(Point(640,0));
		aux.push_back(Point(640, 5));
		aux.push_back(Point(0,5));
		//shape = new Polygon(aux);
		//shape = new Polygon(Point(0,0), Point(640, 0));
		shape = new Polygon(Point(0,0), aux);
		break;
	case Core::Entities::e_pointer:
		shape = new Polygon(Point(), 5);
		break;
	default:
		shape = NULL;
		break;
	}
}

Model2D::~Model2D(){
	if (shape!=NULL){
		delete shape;
		shape = NULL;
	}
}

void Model2D::setShape(Polygon *p){
	shape = p;
}
Polygon* Model2D::getShape(){
	return shape;
}

