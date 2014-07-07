/*
 * Especialist.h
 *
 *  Created on: 15/02/2012
 *      Author: ruben
 */

#ifndef ESPECIALIST_H_
#define ESPECIALIST_H_

#include "Bot.h"

class Especialist : public Bot {
public:
	Especialist();
	Especialist(ResourceManager *r, Core::Entities::Type t, Pathfinder *pf_);
	Especialist(const int, const Point, float, ResourceManager *r, Core::Entities::Type t, Pathfinder *pf_);
	Especialist(const  Especialist&);
	virtual ~Especialist();
	void updateAI(EntityManager* manager);
	void generateFSM();
	void FollowPlayer(EntityManager* manager);
	void Attack(EntityManager* manager);
	void ComeBack();
	void Debug();
	void goToComeBack(Point p);
	void gotoPosition(EntityManager* manager);
};

#endif /* ESPECIALIST_H_ */
