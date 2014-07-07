/*
 * Captain.h
 *
 *  Created on: 15/02/2012
 *      Author: ruben
 */

#ifndef CAPTAIN_H_
#define CAPTAIN_H_

#include "Bot.h"

class Captain : public Bot {
public:
	Captain();
	Captain(ResourceManager *r, Core::Entities::Type t, Pathfinder *pf_);
	Captain(const int, const Point, float, ResourceManager *r, Core::Entities::Type t, Pathfinder *pf_);
	Captain(const  Captain&);
	virtual ~Captain();
	void updateAI(vector<Entity*> entidades_){}
	void generateFSM();
	void goToComeBack(){}
};

#endif /* CAPTAIN_H_ */
