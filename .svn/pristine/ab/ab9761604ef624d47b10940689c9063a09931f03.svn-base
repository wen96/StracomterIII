/*
 * Captain.h
 *
 *  Created on: 15/02/2012
 *      Author: Chutaos team
 */

#ifndef CAPTAIN_H_
#define CAPTAIN_H_

#include "Bot.h"

class Captain: public Bot {
public:
	Captain();
	Captain(ResourceManager *r, Core::Entities::Type t, Pathfinder *pf_);
	Captain(const int, const Point, float, ResourceManager *r, Core::Entities::Type t, Pathfinder *pf_);
	Captain(const  Captain&);
	virtual ~Captain();
	void updateAI(EntityManager* manager);
	void generateFSM();
	void FollowPlayer(EntityManager* manager);
	void Attack(EntityManager* manager);
	void ComeBack();
	void Debug();
	void goToComeBack(Point p);
	void gotoPosition(EntityManager* manager);
};

#endif /* CAPTAIN_H_ */
