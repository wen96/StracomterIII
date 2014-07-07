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
	case Core::Entities::e_miniboss:
		//shape = new Polygon(8,Point(0,0),30,45);
		shape = new Polygon(Point(0,0), Core::Radius);
		break;
	case Core::Entities::e_megaboss:
		//shape = new Polygon(8,Point(0,0),30,45);
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

Model2D::Model2D(Core::Obstacles::Type t)
{


	vector<Point> vp;

	//cout << "Tipo: " << t << endl;
	switch(t) {

	case Core::Obstacles::obs_table:
		vp.push_back(Point(-20,-45));
		vp.push_back(Point(22,-45));
		vp.push_back(Point(22,45));
		vp.push_back(Point(-20,45));

		shape = new Polygon(Point(), vp);
		break;
	case Core::Obstacles::obs_desk:
		vp.push_back(Point(-65,-55));
		vp.push_back(Point(65,-55));
		vp.push_back(Point(65,55));
		vp.push_back(Point(-65,55));

		shape = new Polygon(Point(), vp);
		break;
	case Core::Obstacles::obs_shelf:
		vp.push_back(Point(-55,-25));
		vp.push_back(Point(45,-25));
		vp.push_back(Point(45,18));
		vp.push_back(Point(-55,18));

		shape = new Polygon(Point(), vp);
		break;
	case Core::Obstacles::obs_couch:
		vp.push_back(Point(-22,-20));
		vp.push_back(Point(22,-20));
		vp.push_back(Point(22,20));
		vp.push_back(Point(-22,20));

		shape = new Polygon(Point(), vp);
		break;
	case Core::Obstacles::obs_chair:
		vp.push_back(Point(-20,-20));
		vp.push_back(Point(20,-20));
		vp.push_back(Point(20,20));
		vp.push_back(Point(-20,20));

		shape = new Polygon(Point(), vp);
		break;
	case Core::Obstacles::obs_mesaConSillas:
		vp.push_back(Point(-50,-50));
		vp.push_back(Point(50,-50));
		vp.push_back(Point(50,50));
		vp.push_back(Point(-50,50));

		shape = new Polygon(Point(), vp);
		break;
	case Core::Obstacles::obs_plantPot:
		vp.push_back(Point(-10,-10));
		vp.push_back(Point(10,-10));
		vp.push_back(Point(10,10));
		vp.push_back(Point(-10,10));

		shape = new Polygon(Point(), vp);
		break;
	case Core::Obstacles::obs_sofa:
		vp.push_back(Point(-22,-60));
		vp.push_back(Point(22,-60));
		vp.push_back(Point(22,60));
		vp.push_back(Point(-22,60));

		shape = new Polygon(Point(), vp);
		break;
	default:
		vp.push_back(Point(-32,-70));
		vp.push_back(Point(32,-70));
		vp.push_back(Point(32,70));
		vp.push_back(Point(-32,70));

		shape = new Polygon(Point(), vp);
		break;
	}
}

Model2D::Model2D(Core::Objects::Class t)
{


	vector<Point> vp;

	switch(t) {

	case Core::Objects::health_pack_1 :
		vp.push_back(Point(-32,-32));
		vp.push_back(Point(32,-32));
		vp.push_back(Point(32,32));
		vp.push_back(Point(-32,32));

		shape = new Polygon(Point(), vp);
		break;
	case Core::Objects::health_pack_3 :
		vp.push_back(Point(-32,-32));
		vp.push_back(Point(32,-32));
		vp.push_back(Point(32,32));
		vp.push_back(Point(-32,32));

		shape = new Polygon(Point(), vp);
		break;
	case Core::Objects::health_pack_2 :
		vp.push_back(Point(-32,-32));
		vp.push_back(Point(32,-32));
		vp.push_back(Point(32,32));
		vp.push_back(Point(-32,32));

		shape = new Polygon(Point(), vp);
		break;
	case Core::Objects::ammo_pack_1 :
		vp.push_back(Point(-32,-32));
		vp.push_back(Point(32,-32));
		vp.push_back(Point(32,32));
		vp.push_back(Point(-32,32));

		shape = new Polygon(Point(), vp);
		break;
	case Core::Objects::ammo_pack_2 :
		vp.push_back(Point(-32,-32));
		vp.push_back(Point(32,-32));
		vp.push_back(Point(32,32));
		vp.push_back(Point(-32,32));

		shape = new Polygon(Point(), vp);
		break;
	case Core::Objects::ammo_pack_3 :
		vp.push_back(Point(-32,-32));
		vp.push_back(Point(32,-32));
		vp.push_back(Point(32,32));
		vp.push_back(Point(-32,32));

		shape = new Polygon(Point(), vp);
		break;
	default:
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

