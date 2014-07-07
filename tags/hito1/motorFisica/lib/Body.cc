/*
 * Body.cpp
 *
 *  Created on: 16/11/2011
 *      Author: Chutaos Team
 */

#include "Body.h"

Body::Body(World &world_, BodyData bodyData_){

	world = &world_;
	bodydata = new BodyData(bodyData_);
	body = world_.getWorld()->CreateBody(bodydata->getBodyDef());
	body->CreateFixture(&bodydata->getFixtureDef());
	body->SetMassData(bodydata->getMass());
	body->SetFixedRotation(false);
}

Body::~Body() {

	/*if(body != NULL)
			body->SetActive(false);*/


	/*if(body != NULL)
	{
		body->SetActive(false);
	}*/
	/*if(body != NULL)
	{
		b2World *w = world->getWorld();
		w->DestroyBody(body);
		body = NULL;
	}*/
	if(bodydata != NULL)
	{
		delete bodydata;
		bodydata = NULL;
	}
	if(body != NULL)
	{
		body->DestroyFixture(body->GetFixtureList());
		//body->GetWorld()->DestroyBody(body);
		body = NULL;
	}
	world = NULL;
}

Body::Body(const Body &body_)
{
	b2World *world = body_.body->GetWorld();
	bodydata = new BodyData(*body_.bodydata);
	body = world->CreateBody(bodydata->getBodyDef());
	body->CreateFixture(&bodydata->getFixtureDef());
	body->SetMassData(bodydata->getMass());

}

Body&
Body::operator=(const Body &body_) {

	if(this != &body_)
	{
		this->~Body();
		b2World *world = body_.body->GetWorld();
		bodydata = new BodyData(*body_.bodydata);
		body = world->CreateBody(bodydata->getBodyDef());
		body->CreateFixture(&bodydata->getFixtureDef());
		body->SetMassData(bodydata->getMass());

	}

	return *this;
}

void
Body::setLinearVelocity(Force vel) {
	body->SetLinearVelocity(vel.getForce());
}

void
Body::addLinearVelocity(Force vel) {

	b2Vec2 aux = body->GetLinearVelocity();
	aux.x += vel.getForceX();
	aux.y += vel.getForceY();

	body->SetLinearVelocity(aux);
}
Force
Body::getLinearVelocity() const {

	Force f;
	b2Vec2 aux;

	aux = body->GetLinearVelocity();
	f.setForce(aux);

	return f;
}

Point
Body::getPosition() const {

	b2Vec2 aux;
	Point p;

	aux = body->GetPosition();
	p.setXY(aux.x, aux.y);

	return p;
}

void
Body::setPosition(Point p) {

	b2Vec2 aux;
	aux = Point2b2Vec2(p);
	body->SetTransform(aux, 0.0);
}

void
Body::setAngle(float angle) {

	float radian;
	radian = -1*angle*M_PI/180.0;
	body->SetTransform(body->GetPosition(), radian);
}

float
Body::getAngle() const{
	float angle;
	angle = body->GetAngle();
	angle = angle*180/M_PI;
	return angle;
}

void
Body::addAngle(float angle_) {

	float angle = getAngle();
	angle -= angle_;
	angle = angle * M_PI/180;
	body->SetTransform(body->GetPosition(), angle);

}
void
Body::setFixedRotation(bool fijo) {
	body->SetFixedRotation(fijo);
}

bool
Body::TestPoint(Point p) const {

	b2Shape *cuerpo = body->GetFixtureList()->GetShape();
	bool testPoint;
	b2Vec2 point = Point2b2Vec2(p);
	b2Transform tx = body->GetTransform();
	testPoint = cuerpo->TestPoint(tx, point);

	return testPoint;
}

vector<Point>
Body::solidContacts() const{
	vector<Point> v;

	b2ContactEdge* lista = body->GetContactList();
	if(lista != NULL)
	{
		b2Contact* contact = lista->contact;
		const b2Manifold* manifold = contact->GetManifold();
		if (manifold->pointCount != 0)
		{

			b2PointState state1[b2_maxManifoldPoints], state2[b2_maxManifoldPoints];
			b2GetPointStates(state1, state2, manifold, manifold);

			b2WorldManifold worldManifold;
			contact->GetWorldManifold(&worldManifold);

			for (int32 i = 0; i < manifold->pointCount; ++i)
			{
				v.push_back(b2Vec22Point(worldManifold.points[i]));
			}
		}

	}

	return v;

}

vector<Point>
Body::contact(const Body &b) const{


	//Vector Solución.
	vector<Point> puntos;

	World *w = getWorld();
	const b2Shape *box = bodydata->getShape();

	b2Vec2 *b2Points = NULL;
	int num_b2Points = 0;

	//Estructura del rayo.
	MultiRayData ray;

	//Puntos del Body1
	vector<Point> b1;

	//Puntos auxiliares para acalarar el código
	Point p1;
	Point p2;


	if(box->GetType() ==  b2Shape::e_chain)
	{
		b2Points = ((b2ChainShape*)box)->m_vertices;
		num_b2Points = ((b2ChainShape*)box)->m_count;
	}

	//Convierto de b2Vec2 a Points
	for(int i = 0; i < num_b2Points; i++)
	{
		b1.push_back(b2Vec22Point(b2Points[i]));
	}

	//Por cada lado lanzo un rayo
	for(unsigned int i = 0; i < b1.size(); i++)
	{
		if(i == b1.size() - 1)
		{
			p1 = b1[i];
			p2 = b1[0];
		}
		else
		{
			p1 = b1[i];
			p2 = b1[i+1];
		}

		//Si los puntos son distintos, lanzo el rayo.
		if(p1 != p2)
		{
			ray = w->MultiRayBody(p1,p2);
			if(ray.hit)
			{

				for(unsigned int j = 0; j < ray.point.size(); j++)
				{
					if(ray.body[j] == b.body) //Me quedo con los puntos que pertenecen al body2
					{
						puntos.push_back(ray.point[j]);
					}
				}

			}
		}
	}

	return puntos;
}
