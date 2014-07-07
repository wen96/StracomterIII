/*
 * Obstacle.cc
 *
 *  Created on: 12/11/2011
 *      Author: Chutaos Team
 */

#include "Obstacle.h"

Obstacle::Obstacle(){

}

Obstacle::Obstacle(Core::Obstacles::Type _type,ResourceManager *r, Point center_, float angle_) {
	setId(0);
	setType(Core::Entities::e_obstacle);
	setVisible(true);
	setSmall(true);
	setResource(r);
	obstacle = _type;
	idDisplay = _type + 1000;

	generateObstacleCollision(_type, center_);

	setAngle(angle_);
	setCenter(center_);

}

Obstacle::Obstacle(Core::Obstacles::Type _type,ResourceManager *r, Point center_, float angle_, string ruta, int w, int h, int alto) {
	setId(0);
	setType(Core::Entities::e_obstacle);
	setVisible(true);
	setSmall(true);
	setResource(r);
	obstacle = _type;
	idDisplay = glGenLists(1) + 1200;

	Textura textura(ruta, 1);

	glNewList(idDisplay, GL_COMPILE);
		textura.Activar();
		glBegin(GL_QUADS);
			glNormal3d(0,1,0);
			glColor3d(1,1,1);


			glTexCoord2d(0,0);
			glVertex3d(0, 0, alto + h);

			glTexCoord2d(0,1);
			glVertex3d(0, 0, alto);

			glTexCoord2d(1,1);
			glVertex3d(w, 0, alto);

			glTexCoord2d(1,0);
			glVertex3d(w, 0, alto + h);

		glEnd();
		textura.Desactivar();

	glEndList();

	//generateObstacleCollision(_type, center_);

	//cout << "id: " << idDisplay << endl;
	setAngle(angle_);
	setCenter(center_);

}

void Obstacle::generateObstacleCollision(Core::Obstacles::Type type, Point p) {

		Model2D model = Model2D(type);

		BodyData *bodyData;

		//switch(type){
			//case Core::Obstacles::obs_table:
			bodyData = new BodyData((*model.getShape()), b2_staticBody);
			bodyData->setDensity(1.0);
			bodyData->setMasa(50);
			bodyData->setFriction(0.0);
			bodyData->setLinearDamping(5);
			bodyData->setAngularDamping(5);
			bodyData->setObstacle();

			setColor(Color<float>(1,1,0));
				/*break;
			default:
				break;
		}*/


		World *auxWorld = getResource()->getWorld();
		body = new Body(*auxWorld,*bodyData);

		//body->setPosition(p);

		puntos = model.getShape()->getPuntos();
		if(bodyData != NULL)
		{
			delete bodyData;
			bodyData = NULL;
		}

}
Obstacle::Obstacle(Core::Entities::Type _type, const unsigned int idG, const Point pos, float angle, ResourceManager *r, Color<float> color_, vector<Point> vP) {
	setId(idG);
	setType(_type);
	setAngle(angle);
	setCenter(pos);
	setVisible(true);
	setSmall(false);
	setResource(r);
	setColor(color_);
	puntos = vP;
	idDisplay = _type + 1000;
}

Obstacle::Obstacle(const Obstacle &pare) {
	setId(pare.getId());
	setType(pare.getType());
	setVisible(pare.getVisible());
	setSmall(pare.getSmall());
	setResource(pare.getResource());
	setColor(pare.getColor());
	generateCollision();
}

Obstacle::~Obstacle() {
}

Obstacle&
Obstacle::operator=(const Obstacle &pare) {
	if(this != &pare)
	{
		/*this->~Obstacle();
		id=pare.id;
		type=e_Obstacle;
		visible=pare.visible;
		small=pare.small;
		center=pare.center;
		colision=pare.colision;*/
	}
	return *this;
}

ostream& operator<<(ostream &os, const Obstacle& obj)
{
	os<<"Entity";
	switch(obj.type)
	{
	case 11:
		os<< "(e_columne)";
		break;
	case 12:
		os<< "(e_table)";
		break;
	default:
		os<< "(e_none)";
		break;
	}

	return os;
}

Core::Obstacles::Type Obstacle::getObstacle() const
{
    return obstacle;
}

void Obstacle::setObstacle(Core::Obstacles::Type obstacle)
{
    this->obstacle = obstacle;
}

bool Obstacle::isInside(Point p){

	return body->TestPoint(p);
}

