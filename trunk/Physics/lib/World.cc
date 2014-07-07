/*
 * World.cpp
 *
 *  Created on: 17/11/2011
 *      Author: Chutaos Team
 */

#include "World.h"
#include "Body.h"
#include "Aplication.h"

World::World(Force gravity, bool doSleep) {
	fps = 60;
	world = new b2World(gravity.getForce());
	world->SetAllowSleeping(doSleep);
}

World::World(float frame, Force gravity, bool doSleep) {

	fps = frame;
	world = new b2World(gravity.getForce());
	world->SetAllowSleeping(doSleep);
}

World::~World() {

	if(world != NULL)
	{
		delete world;
		world = NULL;
	}
}

World::World(const World &w)
{
	//world = new b2World(*(w.world));
	world = w.world; //Se copia el puntero porque no se puede tener más de un mundo.

}

World&
World::operator=(const World &w){
	world = w.world;
	return *this;
}

b2World *
World::getWorld(){
	return world;
}

void
World::UpdateWorld() {
	fps = Aplication::getInstance()->getFps();
	world->Step(1.0/fps, 8, 3);
}
void
World::UpdateWorld(float fps_) {
	fps = fps_;
	world->Step(1.0/fps, 8, 3);
}

bool
World::Ray(Point p1, Point p2) const{

	bool llega = false;
	//Para evitar que sean iguales, pero con Z distinta
	p1.setZ(0);
	p2.setZ(0);

	if(p1 != p2)
	{
		RayCastMultipleCallback callback;

		world->RayCast(&callback, Point2b2Vec2(p1), Point2b2Vec2(p2));

		llega = (callback.m_count == 0);
	}

	return llega;
}

std::vector<Point>
World::CutOffPoints(Point p1, Point p2) const{

	std::vector<Point> vP;

	//Para evitar que sean iguales, pero con Z distinta
	p1.setZ(0);
	p2.setZ(0);
	if(p1 != p2)
	{
		RayCastMultipleCallback callback;

		world->RayCast(&callback, Point2b2Vec2(p1), Point2b2Vec2(p2));

		for(int i = 0; i < callback.m_count; i++){
			Point p(callback.m_points[i].x,callback.m_points[i].y);

			if(!(p.isInRadius(p1,2) || p.isInRadius(p2,2))){
				vP.push_back(p);
			}
		}
	}

	return vP;
}

Point
World::CutOffPoint(Point p1, Point p2) const {

	Point p;

	//Para evitar que sean iguales, pero con Z distinta
	p1.setZ(0);
	p2.setZ(0);

	if(p1 != p2)
	{
		RayCastClosestCallback callback;

		world->RayCast(&callback, Point2b2Vec2(p1), Point2b2Vec2(p2));


		p = b2Vec22Point(callback.m_point);
	}

	return p;
}

RayData
World::RayBody(Point p1, Point p2) const {

	RayData ray;
	BodyRayCastCallback callback;


	//Para evitar que sean iguales, pero con Z distinta
	p1.setZ(0);
	p2.setZ(0);
	if(p1 != p2)
	{
		world->RayCast(&callback, Point2b2Vec2(p1), Point2b2Vec2(p2));

		ray.hit = callback.m_hit;

		ray.body = callback.body;
		ray.normal = Force(callback.m_normal.x, callback.m_normal.y);

		//Punto
		if (callback.m_hit){
			ray.centro = b2Vec22Point(callback.body->GetPosition());
			ray.point = b2Vec22Point(callback.m_point);
		}else{
			ray.centro = Point(0,0);
			ray.point = Point(0,0);
		}
	}
	else
	{
		ray.hit = true;
		ray.point = p1;
	}



	return ray;
}

bool World::canSee(Body *b1, Body *b2) const
{
	bool see = false;

	if(b1 != NULL && b2 != NULL)
	{
		Point p1, p2;

		p1 = b1->getPosition();
		p2 = b2->getPosition();
		//Para evitar que sean iguales, pero con Z distinta
		p1.setZ(0);
		p2.setZ(0);
		if(p1 != p2)
		{
			RayData ray;
			ray = RayBody(p1, p2);

			if(ray.body == b2->getBody())
				see = true;
		}
	}

	return see;
}

MultiRayData
World::MultiRayBody(Point p1, Point p2) const {


	//Para evitar que sean iguales, pero con Z distinta
	p1.setZ(0);
	p2.setZ(0);
	MultiRayData ray;

	if(p1 != p2)
	{
		MultiBodyRayCastCallback callback;

		world->RayCast(&callback, Point2b2Vec2(p1), Point2b2Vec2(p2));




		if(callback.m_count > 0)
			ray.hit = true;
		else
			ray.hit = false;


		for(int i = 0; i < callback.m_count; i++)
		{
			ray.body.push_back(callback.m_body[i]);
			ray.normal.push_back(Force(callback.m_normals[i].x, callback.m_normals[i].y));
			ray.point.push_back(b2Vec22Point(callback.m_points[i]));
			ray.centro.push_back(b2Vec22Point(callback.m_body[i]->GetPosition()));
		}
		ray.last = b2Vec22Point(callback.m_points[callback.m_count-1]);

	}


	return ray;
}

