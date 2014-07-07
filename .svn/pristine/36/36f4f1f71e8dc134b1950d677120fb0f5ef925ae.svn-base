/*
 * Path.cc
 *
 *  Created on: Feb 27, 2012
 *      Author: rellik
 */

#include "Path.h"

Path::Path() {
	loop = false;
	wpIter = waypoints.end();
}

Path::~Path() {
	waypoints.clear();
	wpIter = waypoints.end();
	loop = false;
}

Path::Path(const Path & path) {
	waypoints = path.waypoints;
	wpIter = path.wpIter;
	loop = path.loop;
}

Path & Path::operator =(const Path & path) {
	if(this != &path){
		waypoints = path.waypoints;
		wpIter = path.wpIter;
		loop = path.loop;
	}
	return *this;
}

Path::Path(vector<Point> camino, bool loop_) {
	if(camino.size() > 1){
		vector<Point>::iterator vIter;
		for(vIter = camino.begin(); vIter != camino.end() - 1; vIter++){
			Vector2D vec(*vIter, *(vIter +1));
			waypoints.push_back(vec);
		}
		wpIter = waypoints.begin();
	}
	loop = loop_;
}

Path::Path(vector<Vector2D> camino, bool loop_) {
	if(!camino.empty()){
		waypoints = camino;
		wpIter = camino.begin();
	}
	loop = loop_;
}

void Path::setWaypoints(vector<Point> camino, bool loop_) {
	if(camino.size() > 0){
		waypoints.clear();

		vector<Point>::iterator vIter;
		for(vIter = camino.begin(); vIter != camino.end(); vIter++){
			Vector2D vec(Point(), *vIter);
			waypoints.push_back(vec);
		}
		wpIter = waypoints.begin();
	}
	loop = loop_;
}

void Path::setWaypoints(vector<Vector2D> camino, bool loop_) {
	if(!camino.empty()){
		waypoints = camino;
		wpIter = camino.begin();
	}
	loop = loop_;
}

void Path::addWaypoint(Vector2D vec) {
	waypoints.push_back(vec);
}

void Path::addWaypoint(Point p) {
	if(!waypoints.empty()){
		Vector2D lastWP = waypoints.back();
		Vector2D newWP(Point(lastWP.x,lastWP.y), p);

		waypoints.push_back(newWP);
	}
}

vector<Point> Path::getWaypointsP() {
	//TODO
	return vector<Point>();
}

vector<Vector2D> Path::getWaypointsV() {
	return waypoints;
}

Point Path::getCurrentWaypointP() {
	//TODO
	return Point();
}

Vector2D Path::getCurrentWaypointV() {
	if(!waypoints.empty())
		return *wpIter;
	else
		return Vector2D();
}

bool Path::setCurrentWaypoint(Point p) {
	//TODO
	return true;
}

bool Path::setCurrentWaypoint(int index) {
	if(index < (int) waypoints.size()){
		wpIter = waypoints.begin() + index;
		return true;
	}
	return false;
}

bool Path::setNextWaypoint(){
	bool pasado = false;

	if(wpIter != waypoints.end()){
		wpIter++;
		if(loop){
			if(wpIter == waypoints.end()){
				wpIter = waypoints.begin();
			}
		}
		pasado = true;
	}

	return pasado;
}

void Path::setLoop(bool isALoop) {
	loop = isALoop;
}

bool Path::lastWaypoint(){
	if(!loop){
		if(!waypoints.empty()){
			return wpIter == (waypoints.end() - 1);
		}
	}
	return false;
}

bool Path::isFinished() {
	if(!loop){
		return wpIter >= waypoints.end();
	}
	return false;
}

