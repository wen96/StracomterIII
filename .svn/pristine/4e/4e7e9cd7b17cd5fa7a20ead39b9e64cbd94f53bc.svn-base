#ifndef __COMPOSITEPARTICLE__HPP__
#define __COMPOSITEPARTICLE__HPP__

#include <GL/gl.h>
using namespace std;

#include "particle.hpp"
#include "structures.hpp"
#include "texture.hpp"
#include <map>
#include <vector>
#include <iostream>
using namespace std;

class ParticleMover
{
    public:
        ParticleMover(map<string, double>);
        ParticleMover(const ParticleMover&);
        virtual ~ParticleMover() {};

        virtual void step(PARTICLE_REAL_PRECISION timestep) = 0;
        virtual void render() const;
        
        static vector<string> getRequiredValues();

		triangle getRot() const {return rot;};
		triangle getPos() const {return t;};
		triangle getOrig() const {return origT;};
		triangle getTraveled() const {return t - origT;};

    protected:
        triangle t;
        triangle origT;
        triangle rot;        
    private:
};

class ParticleRenderer
{
    public:
        ParticleRenderer(map<string, double>) {};
        ParticleRenderer(const ParticleRenderer&) {};
        virtual ~ParticleRenderer() {};

		static vector<string> getRequiredValues() {return vector<string>();};

        virtual void step(PARTICLE_REAL_PRECISION timeStep) = 0;
        virtual void render(ParticleMover*) const = 0;

    private:
};

class CompositeParticle: public Particle
{
    public:
        CompositeParticle(PARTICLE_REAL_PRECISION life, ParticleMover* m, ParticleRenderer* r) {billboarding = false; lifeTime = life;pm = m; pr = r;};
        CompositeParticle(const CompositeParticle& p) {this->lifeTime = p.lifeTime;};
        virtual ~CompositeParticle() {delete pm; delete pr;};

        virtual void step (PARTICLE_REAL_PRECISION timeStep);
        virtual void render() const;
        virtual bool isDead() const {return lifeTime < 0 && lifeTime > -9999;};
        
        CompositeParticle* setBillboarding(bool bb) {billboarding = bb; return this;};
        
        ParticleMover* getParticleMover() {return pm;};
        ParticleRenderer* getParticleRenderer() {return pr;};

    private:
        PARTICLE_REAL_PRECISION lifeTime;
        bool billboarding;
        ParticleMover* pm;
        ParticleRenderer* pr;
};

class ParticleMoverPVA: public ParticleMover
{
    public:
        ParticleMoverPVA(map<string, double>);
        ParticleMoverPVA(const ParticleMoverPVA&);
        virtual ~ParticleMoverPVA() {};

        virtual void step(PARTICLE_REAL_PRECISION timeStep);
        
        static vector<string> getRequiredValues();

    private:
        
        triangle v;
        triangle a;
};

class ParticleMoverPVD: public ParticleMover
{
    public:
        ParticleMoverPVD(map<string, double>);
        ParticleMoverPVD(const ParticleMoverPVD&);
        virtual ~ParticleMoverPVD() {};

        virtual void step(PARTICLE_REAL_PRECISION timeStep);

		static vector<string> getRequiredValues();
		
    private:

        triangle v;
        triangle travelled;
        PARTICLE_REAL_PRECISION totalLifeTime;
        PARTICLE_REAL_PRECISION currLifeTime;
        PARTICLE_REAL_PRECISION decel;       
};

class ParticleMoverSin: public ParticleMover
{
    public:
        ParticleMoverSin(map<string, double>);
        ParticleMoverSin(const ParticleMoverSin&);
        virtual ~ParticleMoverSin() {};

        virtual void step(PARTICLE_REAL_PRECISION timeStep);

		static vector<string> getRequiredValues();
		
    private:

        triangle v;
        triangle a;
        PARTICLE_REAL_PRECISION acumTime;
        PARTICLE_REAL_PRECISION amplitude;   
};


class ParticleMoverForces: public ParticleMover
{
    public:
        ParticleMoverForces(map<string, double>);
        ParticleMoverForces(const ParticleMoverForces&);
        virtual ~ParticleMoverForces();

        virtual void step(PARTICLE_REAL_PRECISION);

		static Quad* addGlobalDragPoint(Quad p);
		static void clearGlobalDragPoints();
		static vector<Quad*> getGlobalDragPoints() {return globalDragPoints;};
		
		Quad* addLocalDragPoint(Quad p);
		void clearLocalDragPoints();
		vector<Quad*> getLocalDragPoints() {return localDragPoints;};
		
		ParticleMoverForces* setLocalPosition(Quad* q){localPosition = q; return this;}
		
		static vector<string> getRequiredValues();
    private:
		
		triangle v;
		triangle force;
		double mass;
		static vector<Quad*> globalDragPoints;
		vector<Quad*> localDragPoints;
		Quad* localPosition;
};

class ParticleMoverForcesInertia: public ParticleMover
{
    public:
        ParticleMoverForcesInertia(map<string, double>);
        ParticleMoverForcesInertia(const ParticleMoverForcesInertia&);
        virtual ~ParticleMoverForcesInertia();

        virtual void step(PARTICLE_REAL_PRECISION);

		static Quad* addGlobalDragPoint(Quad p);
		static void clearGlobalDragPoints();
		static vector<Quad*> getGlobalDragPoints() {return globalDragPoints;};
		
		Quad* addLocalDragPoint(Quad p);
		void clearLocalDragPoints();
		vector<Quad*> getLocalDragPoints() {return localDragPoints;};
		
		ParticleMoverForcesInertia* setLocalPosition(Quad* q){localPosition = q; return this;}
		
		static vector<string> getRequiredValues();
    private:
		
		triangle v;
		triangle force;
		double mass;
		static vector<Quad*> globalDragPoints;
		vector<Quad*> localDragPoints;
		Quad* localPosition;
};

class ParticleRendererColorFading: public ParticleRenderer
{
    public:
        ParticleRendererColorFading(map<string, double>);
        ParticleRendererColorFading(const ParticleRendererColorFading&);
        virtual ~ParticleRendererColorFading() {};

		static vector<string> getRequiredValues();
	
        virtual void step(PARTICLE_REAL_PRECISION timeStep);
        virtual void render(ParticleMover*) const;

    private:
        Quad c;
        PARTICLE_REAL_PRECISION decrement;
};

class ParticleRendererColorUA: public ParticleRenderer
{
    public:
        ParticleRendererColorUA(map<string, double>);
        ParticleRendererColorUA(const ParticleRendererColorUA&);
        virtual ~ParticleRendererColorUA() {};

		static vector<string> getRequiredValues();
	
        virtual void step(PARTICLE_REAL_PRECISION timeStep);
        virtual void render(ParticleMover*) const;

    private:
        Quad c;
        Quad v;
        Quad a;
        bool round;
        PARTICLE_REAL_PRECISION decrement;
};

class ParticleRendererSecuentialColorFading: public ParticleRenderer
{
    public:
        ParticleRendererSecuentialColorFading(map<string, double>);
        ParticleRendererSecuentialColorFading(const ParticleRendererSecuentialColorFading&);
        virtual ~ParticleRendererSecuentialColorFading() {};

		static vector<string> getRequiredValues();
	
        virtual void step(PARTICLE_REAL_PRECISION timeStep);
        virtual void render(ParticleMover*) const;

    private:
        Quad c;
        static Quad nextColor;
        PARTICLE_REAL_PRECISION decrement;
};

class ParticleRendererTextureFading: public ParticleRenderer
{
    public:
        ParticleRendererTextureFading(map<string, double>);
        ParticleRendererTextureFading(const ParticleRendererTextureFading&);
        virtual ~ParticleRendererTextureFading() {};

		static vector<string> getRequiredValues();
	
        virtual void step(PARTICLE_REAL_PRECISION timeStep);
        virtual void render(ParticleMover*) const;
        
        static void addTexture(Texture* t) {textures.push_back(t);};
        static vector<Texture*> getTextures() {return textures;};

    private:
        Quad c;
        int textureNum;
        PARTICLE_REAL_PRECISION decrement;
        static vector<Texture*> textures;
};

class ParticleRendererColorTracer : public ParticleRenderer
{
	public:
        ParticleRendererColorTracer(map<string, double>);
        ParticleRendererColorTracer(const ParticleRendererColorTracer&);
        virtual ~ParticleRendererColorTracer() {};

		static vector<string> getRequiredValues();
	
        virtual void step(PARTICLE_REAL_PRECISION timeStep);
        virtual void render(ParticleMover*) const;

    private:
        Quad c;
        PARTICLE_REAL_PRECISION decrement;
		mutable vector<triangle> oldPositions;
		static unsigned int maxLong;
};

class ParticleRendererColorTracerConstantLength : public ParticleRenderer
{
	public:
        ParticleRendererColorTracerConstantLength(map<string, double>);
        ParticleRendererColorTracerConstantLength(const ParticleRendererColorTracerConstantLength&);
        virtual ~ParticleRendererColorTracerConstantLength() {};

		static vector<string> getRequiredValues();
	
        virtual void step(PARTICLE_REAL_PRECISION timeStep);
        virtual void render(ParticleMover*) const;

    private:
        Quad c;
        PARTICLE_REAL_PRECISION decrement;
		mutable vector<triangle> oldPositions;
		static unsigned int maxLong;
};

#endif
