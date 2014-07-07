/*
 * Technic.h
 *
 *  Created on: 15/02/2012
 *      Author: ruben
 */

#ifndef TECHNIC_H_
#define TECHNIC_H_

#include "Bot.h"

class Technic: public Bot {
public:
	Technic();
	Technic(ResourceManager *r, Core::Entities::Type t, Pathfinder *pf_);
	Technic(const int, const Point, float, ResourceManager *r, Core::Entities::Type t, Pathfinder *pf_);
	Technic(const  Technic&);
	virtual ~Technic();
	void updateAI(EntityManager* manager);
	void generateFSM();
	void FollowPlayer(EntityManager* manager);
	void Attack(EntityManager* manager);
	void ComeBack();
	void Debug();
	void goToComeBack(Point p);
	void gotoPosition(EntityManager* manager);
};

#endif /* TECHNIC_H_ */
