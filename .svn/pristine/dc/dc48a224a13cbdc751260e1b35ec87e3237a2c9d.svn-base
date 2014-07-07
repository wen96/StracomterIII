/*
 * Particle.cc
 *
 *  Created on: May 18, 2012
 *      Author: Chutaos Team
 */

#include "ParticleNode.h"

ParticleNode::ParticleNode() {
	element = Core::Element::e_particle;
}

ParticleNode::~ParticleNode() {
}

ParticleNode::ParticleNode(const ParticleNode & p) {
	wParticle = new CompositeParticle(*p.wParticle);
}

ParticleNode & ParticleNode::operator =(const ParticleNode & p) {
	if( this != &p){
		if(wParticle != NULL)
			delete wParticle;
		wParticle = new CompositeParticle(*p.wParticle);
	}
	return *this;
}

ParticleNode::ParticleNode(CompositeParticle *p) {
	element = Core::Element::e_particle;
	wParticle = p;
}

void ParticleNode::Render() {
	if(wParticle != NULL ){
		wParticle->render();
	}
}

CompositeParticle * ParticleNode::getParticle(){
	return wParticle;
}
