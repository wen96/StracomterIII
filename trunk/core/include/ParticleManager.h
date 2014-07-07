/*
 * ParticleManager.h
 *
 *  Created on: May 18, 2012
 *      Author: Chutaos Team
 */

#ifndef PARTICLEMANAGER_H_
#define PARTICLEMANAGER_H_

#include "compositeEmitter.hpp"
#include "compositeParticle.hpp"
#include "particleStorage.hpp"
#include "texture.hpp"
#include "Point.h"
#include "Vector2D.h"
#include "ParticleNode.h"
#include "Clock.h"
#include "GraphicsNamespace.h"

class SceneManager;

/**
 * Estructura auxiliar para almacenar los emisorees de particulas.
 */
struct AuxPart {
	AuxPart(Point p, Graphics::Particle::Type t) {
		pos = p;
		tipo = t;
		life.Start();
	}

	AuxPart(Point p, Vector2D d, Graphics::Particle::Type t) {
		Vector2D aux(d);
		aux.Normalize();
		aux *= -30;
		aux += Vector2D(p);
		pos = aux.toPoint();
		dir = d;
		tipo = t;
		life.Start();
	}

	Point pos;
	Vector2D dir;
	Graphics::Particle::Type tipo;
	Clock life;
};

/**
 * Manager de particulas, permite colocar emisores de particulas en la escena
 */
class ParticleManager {
public:
	static ParticleManager * getInstance();
	~ParticleManager();

	/**
	 * Genera una explosion
	 * @param p Posicion de la explosion
	 */
	void doExplosion(Point p);

	/**
	 * Genera un chorro de sangre
	 * @param p Origen del chorro
	 * @param v Dirreccion del chorro
	 */
	void doBloodBurst(Point p, Vector2D v);

	/**
	 * Actualiza las particulas y los emisores
	 */
	void Update();

private:
	static ParticleManager * _inst;
	ParticleManager();
	ParticleManager(const ParticleManager &pm);
	ParticleManager & operator=(const ParticleManager &pm);

	/**
	 * Carga los datos y confgura los emisores
	 */
	void loadData();

	SceneManager *sm;

	Clock timer;
	vector<AuxPart *> emisores;

	vector<ParticleNode *> particles;

	/**
	 * Emisor de las explosiones
	 */
	CompositeEmitter<ParticleMoverPVA, ParticleRendererColorFading> debris;

	/**
	 * Emisores de la sangre
	 */
	CompositeEmitter<ParticleMoverPVA, ParticleRendererColorTracerConstantLength> bloodT;
	CompositeEmitter<ParticleMoverPVA, ParticleRendererColorFading> bloodQ;
};

#endif /* PARTICLEMANAGER_H_ */
