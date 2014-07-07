#ifndef __PARTICLE_HPP__
#define __PARTICLE_HPP__

#include <GL/gl.h>
using namespace std;

#include "structures.hpp"


class Particle
{   
    public:
        Particle() {};
        Particle(const Particle&) {};
        virtual ~Particle() {};

        virtual void step(PARTICLE_REAL_PRECISION) = 0;
        virtual void render() const = 0;
        virtual bool isDead() const = 0;
};

class RandomColorPVAParticle: public Particle
{
    public:
        RandomColorPVAParticle(
                    PARTICLE_REAL_PRECISION lifeTime,
                    float a, bool fade,
                    PARTICLE_REAL_PRECISION = 0.0,PARTICLE_REAL_PRECISION = 0.0,PARTICLE_REAL_PRECISION = 0.0,
                    PARTICLE_REAL_PRECISION = 0.0,PARTICLE_REAL_PRECISION = 0.0,PARTICLE_REAL_PRECISION = 0.0,
                    PARTICLE_REAL_PRECISION = 0.0,PARTICLE_REAL_PRECISION = 0.0,PARTICLE_REAL_PRECISION = 0.0);

        RandomColorPVAParticle(const RandomColorPVAParticle&);
        virtual ~RandomColorPVAParticle ();

        virtual void step(PARTICLE_REAL_PRECISION timestep);
        virtual void render() const;
        virtual bool isDead() const {return lifeTime < 0;};
        
        
    private:
		
        triangle p;
        triangle v;
        triangle a;
        Quad c;
        triangle r;
        PARTICLE_REAL_PRECISION alphaDecrement;
        PARTICLE_REAL_PRECISION lifeTime;
};

class ColorPVAParticle: public Particle
{
    public:
        ColorPVAParticle(
                    PARTICLE_REAL_PRECISION lifeTime,
                    float r, float g, float b, float a, bool fade,
                    PARTICLE_REAL_PRECISION = 0.0,PARTICLE_REAL_PRECISION = 0.0,PARTICLE_REAL_PRECISION = 0.0,
                    PARTICLE_REAL_PRECISION = 0.0,PARTICLE_REAL_PRECISION = 0.0,PARTICLE_REAL_PRECISION = 0.0,
                    PARTICLE_REAL_PRECISION = 0.0,PARTICLE_REAL_PRECISION = 0.0,PARTICLE_REAL_PRECISION = 0.0);

        ColorPVAParticle(const ColorPVAParticle&);
        virtual ~ColorPVAParticle ();

        virtual void step(PARTICLE_REAL_PRECISION timestep);
        virtual void render() const;
        virtual bool isDead() const {return lifeTime < 0;};
        
        
    private:
		
        triangle p;
        triangle v;
        triangle a;
        Quad c;
        triangle r;
        PARTICLE_REAL_PRECISION alphaDecrement;
        PARTICLE_REAL_PRECISION lifeTime;
};

class ColorPVDParticle: public Particle
{
    public:
        ColorPVDParticle(
                    PARTICLE_REAL_PRECISION lifeTime,
                    float r, float g, float b, float a, bool fade,
                    PARTICLE_REAL_PRECISION = 0.0,PARTICLE_REAL_PRECISION = 0.0,PARTICLE_REAL_PRECISION = 0.0,
                    PARTICLE_REAL_PRECISION = 0.0,PARTICLE_REAL_PRECISION = 0.0,PARTICLE_REAL_PRECISION = 0.0,
                    PARTICLE_REAL_PRECISION = 1);

        ColorPVDParticle(const ColorPVDParticle&);
        virtual ~ColorPVDParticle ();

        virtual void step(PARTICLE_REAL_PRECISION timestep);
        virtual void render() const;
        virtual bool isDead() const {return lifeTime < 0;};
        
        
    private:
		
        triangle p;
        triangle v;
        PARTICLE_REAL_PRECISION decel;
        Quad c;
        triangle r;
        PARTICLE_REAL_PRECISION alphaDecrement;
        PARTICLE_REAL_PRECISION lifeTime;
};

class ColorSinParticle: public Particle
{
    public:
        ColorSinParticle(
                    PARTICLE_REAL_PRECISION lifeTime,
                    float r, float g, float b, float a, bool fade,
                    PARTICLE_REAL_PRECISION = 0.0,PARTICLE_REAL_PRECISION = 0.0,PARTICLE_REAL_PRECISION = 0.0,
                    PARTICLE_REAL_PRECISION = 0.0,PARTICLE_REAL_PRECISION = 0.0,PARTICLE_REAL_PRECISION = 0.0,
                    PARTICLE_REAL_PRECISION = 0.0,PARTICLE_REAL_PRECISION = 0.0,PARTICLE_REAL_PRECISION = 0.0, PARTICLE_REAL_PRECISION = 0.001);

        ColorSinParticle(const ColorSinParticle&);
        virtual ~ColorSinParticle ();

        virtual void step(PARTICLE_REAL_PRECISION timestep);
        virtual void render() const;
        virtual bool isDead() const {return lifeTime < 0;};
        
        
    private:
		
        triangle p;
        triangle v;
        triangle a;
        Quad c;
        triangle r;
        PARTICLE_REAL_PRECISION alphaDecrement;
        PARTICLE_REAL_PRECISION lifeTime;
        PARTICLE_REAL_PRECISION amplitude;

};

#endif
