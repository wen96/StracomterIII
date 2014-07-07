/*
 * Explosive.h
 *
 *  Created on: 15/02/2012
 *      Author: Chutaos team
 */

#ifndef EXPLOSIVE_H_
#define EXPLOSIVE_H_

#include "Bot.h"

class Explosive : public Bot{
public:
	Explosive();
	Explosive(ResourceManager *r, Core::Entities::Type t, Pathfinder *pf_);
	Explosive(const int, const Point, float, ResourceManager *r, Core::Entities::Type t, Pathfinder *pf_);
	Explosive(const  Explosive&);
	virtual ~Explosive();
	void updateAI(EntityManager* manager);
	void generateFSM();
	void FollowPlayer(EntityManager* manager);
	void Attack(EntityManager* manager);
	void ComeBack();
	void Debug();
	void goToComeBack(Point p);
	void gotoPosition(EntityManager* manager);
};

#endif /* EXPLOSIVE_H_ */
