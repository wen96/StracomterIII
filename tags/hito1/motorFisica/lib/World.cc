/*
 * World.cpp
 *
 *  Created on: 17/11/2011
 *      Author: Chutaos Team
 */

#include "World.h"

World::World(Force gravity, bool doSleep) {
	fps = 1.0/60.0;
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
	world->Step(fps, 10, 8);
	world->ClearForces();
}

bool
World::Ray(Point p1, Point p2) const{

	RayCastMultipleCallback callback;

	world->RayCast(&callback, Point2b2Vec2(p1), Point2b2Vec2(p2));

	return callback.m_count == 0;
}

std::vector<Point>
World::CutOffPoints(Point p1, Point p2) const{

	std::vector<Point> vP;

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

	RayCastClosestCallback callback;

	world->RayCast(&callback, Point2b2Vec2(p1), Point2b2Vec2(p2));

	Point p;
	p = b2Vec22Point(callback.m_point);


	return p;
}

RayData
World::RayBody(Point p1, Point p2) const {

	BodyRayCastCallback callback;
	RayData ray;

	if(p1 != p2)
	{
		world->RayCast(&callback, Point2b2Vec2(p1), Point2b2Vec2(p2));

		ray.hit = callback.m_hit;

		ray.body = callback.body;
		ray.normal = Force(callback.m_normal.x, callback.m_normal.y);
		ray.point = b2Vec22Point(callback.m_point);
		if (callback.m_hit){
			ray.centro = b2Vec22Point(callback.body->GetPosition());
		}else{
			ray.centro = Point(0,0);
		}
	}
	else
	{
		ray.hit = true;
		ray.point = p1;
	}


	return ray;
}

MultiRayData
World::MultiRayBody(Point p1, Point p2) const {


	MultiBodyRayCastCallback callback;

	world->RayCast(&callback, Point2b2Vec2(p1), Point2b2Vec2(p2));


	MultiRayData ray;

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


	return ray;
}

