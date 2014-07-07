#include "emitter.hpp"
#include <cstdlib>
#include <ctime>
#include <cmath>

#include <iostream>
using namespace std;

#define RANDOM0_1 (float)((rand()%101)/100.0)
#define BIGFLOAT 1000000.0


Emitter::Emitter(   double ot, double dt,
                    float ox, float oy, float oz,
                    float dx, float dy, float dz,
                    float ovx, float ovy, float ovz,
                    float dvx, float dvy, float dvz,
                    float oax, float oay, float oaz,
                    float dax, float day, float daz)
{

    //Initial value
    this->ox = ox;
    this->oy = oy;
    this->oz = oz;
    this->ovx = ovx;
    this->ovy = ovy;
    this->ovz = ovz;
    this->oax = oax;
    this->oay = oay;
    this->oaz = oaz;

    //range
    this->rx = dx-ox;
    this->ry = dy-oy;
    this->rz = dz-oz;
    this->rvx = dvx-ovx;
    this->rvy = dvy-ovy;
    this->rvz = dvz-ovz;
    this->rax = dax-oax;
    this->ray = day-oay;
    this->raz = daz-oaz;

    //Initial lifeTime and range
    this->ot = ot;
    this->rt = dt-ot;
    rangeT = rt-ot;
    
    srand(time(NULL));
}

Emitter::Emitter(const Emitter &e)
{
    this->ox = e.ox;
    this->oy = e.oy;
    this->oz = e.oz;
    this->ovx = e.ovx;
    this->ovy = e.ovy;
    this->ovz = e.ovz;
    this->oax = e.oax;
    this->oay = e.oay;
    this->oaz = e.oaz;

    this->rx = e.rx;
    this->ry = e.ry;
    this->rz = e.rz;
    this->rvx = e.rvx;
    this->rvy = e.rvy;
    this->rvz = e.rvz;
    this->rax = e.rax;
    this->ray = e.ray;
    this->raz = e.raz;

    this->ot = e.ot;
    this->rt = e.rt;
    this->rangeT = e.rangeT;
}

Emitter::~Emitter()
{

}



Particle* Emitter::getColoredParticle()
{
    return new RandomColorPVAParticle (ot + rt*RANDOM0_1,
        1, true,
        ox + rx*RANDOM0_1, oy + ry*RANDOM0_1, oz + rz*RANDOM0_1,
        ovx + rvx*RANDOM0_1, ovy + rvy*RANDOM0_1, ovz + rvz*RANDOM0_1,
        oax + rax*RANDOM0_1, oay + ray*RANDOM0_1, oaz + raz*RANDOM0_1);
}



Particle* Emitter::getColoredParticle(const Quad* pc, bool fade)
{    
    return new ColorPVAParticle (ot + rt*RANDOM0_1,
        pc->r*RANDOM0_1, pc->g*RANDOM0_1, pc->b*RANDOM0_1, pc->a, fade,
        ox + rx*RANDOM0_1, oy + ry*RANDOM0_1, oz + rz*RANDOM0_1,
        ovx + rvx*RANDOM0_1, ovy + rvy*RANDOM0_1, ovz + rvz*RANDOM0_1,
        oax + rax*RANDOM0_1, oay + ray*RANDOM0_1, oaz + raz*RANDOM0_1);
}

Particle* Emitter::getColoredDecelParticle(const Quad* pc, bool fade, double decel, double maxRadius = BIGFLOAT)
{    
    return new ColorPVAParticle (ot + rt*RANDOM0_1,
        pc->r, pc->g, pc->b, pc->a, fade,
        ox + rx*RANDOM0_1, oy + ry*RANDOM0_1, oz + rz*RANDOM0_1,
        ovx + rvx*RANDOM0_1, ovy + rvy*RANDOM0_1, ovz + rvz*RANDOM0_1,
        decel);
}

Particle* Emitter::getColoredDecelParticle(double decel, double maxRadius = BIGFLOAT)
{
    float vx, vy, vz;
    do
    {
        vx = ovx + rvx*RANDOM0_1;
        vy = ovy + rvy*RANDOM0_1;
        vz = ovz + rvz*RANDOM0_1;
    }
    while (sqrt(vx*vx+vy*vy+vz*vz)>1);

    cout <<ot + rt*RANDOM0_1 <<endl;

    
    return new ColorPVDParticle (ot + rt*RANDOM0_1,
        0.4+0.6*RANDOM0_1,0.4*RANDOM0_1,0.4*RANDOM0_1,1,true,
        ox + rx*RANDOM0_1, oy + ry*RANDOM0_1, oz + rz*RANDOM0_1,
        vx, vy, vz,
        decel);
}

Particle* Emitter::getSinParticle(const Quad* pc, bool fade, double amplitude = 0.001)
{    
    return new ColorSinParticle (ot + rt*RANDOM0_1,
        pc->r, pc->g, pc->b, pc->a, fade,
        ox + rx*RANDOM0_1, oy + ry*RANDOM0_1, oz + rz*RANDOM0_1,
        ovx + rvx*RANDOM0_1, ovy + rvy*RANDOM0_1, ovz + rvz*RANDOM0_1,
        oax + rax*RANDOM0_1, oay + ray*RANDOM0_1, oaz + raz*RANDOM0_1, amplitude);
}

//~ Particle* Emitter::getColoredDecoratedParticle()
//~ {
    //~ double lifeTime = ot + rt*RANDOM0_1;
    //~ return new CompositeParticle( lifeTime,
        //~ new ParticleMoverPVA (
                //~ ox + rx*RANDOM0_1, oy + ry*RANDOM0_1, oz + rz*RANDOM0_1,
            //~ ovx + rvx*RANDOM0_1, ovy + rvy*RANDOM0_1, ovz + rvz*RANDOM0_1,
            //~ oax + rax*RANDOM0_1, oay + ray*RANDOM0_1, oaz + raz*RANDOM0_1),
        //~ new ParticleRendererColorFading( lifeTime,
            //~ RANDOM0_1, RANDOM0_1, RANDOM0_1, RANDOM0_1, true));
//~ 
//~ }

//~ Particle* Emitter::getColoredDecoratedDecelParticle(double dampen)
//~ {
    //~ double lifeTime = ot + rt*RANDOM0_1;
    //~ return new CompositeParticle( lifeTime,
        //~ new ParticleMoverPVD ( lifeTime, 
                //~ ox + rx*RANDOM0_1, oy + ry*RANDOM0_1, oz + rz*RANDOM0_1,
            //~ ovx + rvx*RANDOM0_1, ovy + rvy*RANDOM0_1, ovz + rvz*RANDOM0_1,
            //~ dampen),
        //~ new ParticleRendererColorFading( lifeTime,
            //~ RANDOM0_1, RANDOM0_1, RANDOM0_1, RANDOM0_1, true));
//~ 
//~ }

//~ Particle* Emitter::getColoredDecoratedDecelParticleSphere(double dampen, double maxRadius = BIGFLOAT)
//~ {
    //~ float vx, vy, vz;
    //~ do
    //~ {
        //~ vx = ovx + rvx*RANDOM0_1;
        //~ vy = ovy + rvy*RANDOM0_1;
        //~ vz = ovz + rvz*RANDOM0_1;
    //~ }
    //~ while (sqrt(vx*vx+vy*vy+vz*vz)>maxRadius);
    //~ 
    //~ double lifeTime = ot + rt*RANDOM0_1;
    //~ return new CompositeParticle( lifeTime,
        //~ new ParticleMoverPVD ( lifeTime, 
            //~ ox + rx*RANDOM0_1, oy + ry*RANDOM0_1, oz + rz*RANDOM0_1,
            //~ vx, vy, vz,
            //~ dampen),
        //~ new ParticleRendererColorFading( lifeTime,
            //~ RANDOM0_1, RANDOM0_1, RANDOM0_1, RANDOM0_1, true));
//~ 
//~ }

void
Emitter::translate (float x, float y, float z)
{
    ox += x;
    rx += x;
    oy += y;
    ry += y;
    oz += z;
    rz += z;
}
