/*
 * Captain.cc
 *
 *  Created on: 15/02/2012
 *      Author: ruben
 */

#include "../include/Captain.h"

Captain::Captain() {
	// TODO Auto-generated constructor stub

}

Captain::~Captain() {
	// TODO Auto-generated destructor stub
}

void Captain::generateFSM(){

}

Captain::Captain(ResourceManager *r, Core::Entities::Type t, Pathfinder *pf_){
	features = NULL;
	id = 0;
	visible = true;
	small = false;
	resource = r;
	goodPerson = (t == Core::Entities::e_captain ||
				t == Core::Entities::e_especialist ||
				t == Core::Entities::e_tecnic ||
				t == Core::Entities::e_explosive);
	dead = false;
	blind = false;
	vision = Tri();
	generateFeatures(t);
	generateCollision();
	generateFSM();
	pf = pf_;
	idDisplay = t;
}

Captain::Captain(const int idG, const Point pos, float angle,
		ResourceManager *res, Core::Entities::Type t, Pathfinder *pf_) {
	features = NULL;
	id = idG;
	setCenter(pos);
	setAngle(angle);
	visible = true;
	small = false;
	resource = res;
	goodPerson = (t == Core::Entities::e_captain ||
			t == Core::Entities::e_especialist ||
			t == Core::Entities::e_tecnic ||
			t == Core::Entities::e_explosive);
	dead = false;
	blind = false;
	vision = Tri();
	generateFeatures(t);
	generateCollision();
	generateFSM();
	pf = pf_;
	idDisplay = t;
}
