/*
 * MotorFisica.cpp
 *
 *  Created on: 28/10/2011
 *      Author: Chutaos Team
 */

#include "Box.h"


Box::Box(vector<b2Vec2> v, int n_vertex) {

	b2Vec2 vector[n_vertex];

	for(unsigned int i = 0; i < v.size(); i++)
	{
		vector[i].x = v[i].x;
		vector[i].y = v[i].y;
	}

	if(n_vertex == 2)
	{
		box = new b2EdgeShape();
		((b2EdgeShape *)box)->Set(vector[0],vector[1]);
	}
	else if(n_vertex >= 3)
	{
		box = new b2PolygonShape();
		((b2PolygonShape *)box)->Set(vector,n_vertex);
	}
	else
		box = NULL;
}

Box::Box(vector<Point> p, int n_vertex) {

	vector<b2Vec2> v = Point2b2Vec2(p);
	b2Vec2 vector[n_vertex];

	for(unsigned int i = 0; i < v.size(); i++)
	{
		vector[i].x = v[i].x;
		vector[i].y = v[i].y;
	}

	if(n_vertex == 2)
	{
		box = new b2EdgeShape();
		((b2EdgeShape *)box)->Set(vector[0],vector[1]);
	}
	else if(n_vertex >= 3)
	{

		box = new b2PolygonShape();
		((b2PolygonShape *)box)->Set(vector,n_vertex);
	}
	else
		box = NULL;
}

Box::Box(b2Vec2 p, float rad) {

	box = new b2CircleShape();
	((b2CircleShape*)box)->m_p = p;
	((b2CircleShape*)box)->m_radius = rad;
}

Box::Box(Point p, float rad) {

	b2Vec2 point;
	point.x = p.getX();
	point.y = p.getY();
	box = new b2CircleShape();
	((b2CircleShape*)box)->m_p = point;
	((b2CircleShape*)box)->m_radius = rad;
}

Box::Box(int n_vertex, vector<b2Vec2> v) {

	b2Vec2 vector[n_vertex];

	for(unsigned int i = 0; i < v.size(); i++)
	{
		vector[i].x = v[i].x;
		vector[i].y = v[i].y;
	}

	box = new b2ChainShape();
	((b2ChainShape *)box)->CreateChain(vector,n_vertex);
}

Box::Box(int n_vertex, vector<Point> v) {

	b2Vec2 vector[n_vertex];

	for(unsigned int i = 0; i < v.size(); i++)
	{
		vector[i].x = v[i].getX();
		vector[i].y = v[i].getY();
	}

	box = new b2ChainShape();
	((b2ChainShape *)box)->CreateChain(vector,n_vertex);
}

Box::Box(const Box &b)
{
	switch(b.getType())
	{
		case b2Shape::e_chain:

			//box = new b2ChainShape(*((b2ChainShape *) b.box));
			box = new b2ChainShape();
			((b2ChainShape *)box)->CreateChain(((b2ChainShape*) b.box)->m_vertices, ((b2ChainShape*) b.box)->m_count);
		break;
		case b2Shape::e_circle:
			box = new b2CircleShape(*((b2CircleShape *) b.box));
		break;
		case b2Shape::e_edge:
			box = new b2EdgeShape(*((b2EdgeShape *)b.box));

		break;
		case b2Shape::e_polygon:
			box = new b2PolygonShape(*((b2PolygonShape*)b.box));
		break;
	}
}

Box::Box(const Polygon &pol) {

	int n_vertex = pol.getNVertices();
	vector<Point> v = pol.getPuntos();
	b2Vec2 vector[n_vertex];
	b2Vec2 point;
	for(unsigned int i = 0; i < v.size(); i++)
	{
		vector[i].x = v[i].getX();
		vector[i].y = v[i].getY();
	}


	switch(pol.getType())
	{
	case POL_EDGE:
		box = new b2EdgeShape();
		((b2EdgeShape *)box)->Set(vector[0],vector[1]);
		break;
	case POL_CIRCLE:

		point = Point2b2Vec2(pol.getCentro());
		box = new b2CircleShape();
		((b2CircleShape*)box)->m_p = point;
		((b2CircleShape*)box)->m_radius = pol.getRadio();

		break;
	case POL_POLYGON:
		box = new b2PolygonShape();
		((b2PolygonShape *)box)->Set(vector,n_vertex);
		break;
	case POL_CHAIN:
		box = new b2ChainShape();
		((b2ChainShape *)box)->CreateLoop(vector,n_vertex);
		break;
	case POL_NONE:
		box = NULL;
		break;
	}
}

Box&
Box::operator=(const Box &b)
{
	if(this != &b)
	{
		this->~Box();
		switch(b.getType())
		{
			case b2Shape::e_chain:
				//box = new b2ChainShape(*((b2ChainShape *) b.box));
				box = new b2ChainShape();
				((b2ChainShape *)box)->CreateChain(((b2ChainShape*) b.box)->m_vertices, ((b2ChainShape*) b.box)->m_count);
			break;
			case b2Shape::e_circle:
				box = new b2CircleShape(*((b2CircleShape *) b.box));
			break;
			case b2Shape::e_edge:
				box = new b2EdgeShape(*((b2EdgeShape *)b.box));

			break;
			case b2Shape::e_polygon:
				box = new b2PolygonShape(*((b2PolygonShape*)b.box));
			break;
		}
	}

	return *this;
}
Box::~Box() {
	if(box != NULL){
		delete box;
		box = NULL;
	}
}

vector<b2Vec2> Point2b2Vec2(vector<Point> v) {

	vector<b2Vec2> b2vector;
	b2Vec2 aux;

	for(unsigned int i = 0; i < v.size(); i++)
	{
		aux.x = v[i].getX();
		aux.y = v[i].getY();
		b2vector.push_back(aux);
	}

	return b2vector;
}

b2Vec2 Point2b2Vec2(Point p)
{
	b2Vec2 tmp;
	tmp.x = p.getX();
	tmp.y = p.getY();

	return tmp;
}

Point b2Vec22Point(b2Vec2 p)
{
	Point tmp;
	tmp.setXY(p.x, p.y);

	return tmp;
}
