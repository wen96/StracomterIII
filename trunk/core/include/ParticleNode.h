/*
 * Particle.h
 *
 *  Created on: May 18, 2012
 *      Author: Chutaos Team
 */

#ifndef PARTICLE_H_
#define PARTICLE_H_

#include "compositeParticle.hpp"
#include "Element.h"

class ParticleNode : public Element {
public:
	ParticleNode();
	~ParticleNode();
	ParticleNode(const ParticleNode &p);
	ParticleNode & operator=(const ParticleNode &p);

	ParticleNode(CompositeParticle *p);

	void Render();

	CompositeParticle * getParticle();
private:
	CompositeParticle *wParticle;
};


#endif /* PARTICLE_H_ */
