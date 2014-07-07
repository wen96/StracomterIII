

#ifndef __EMITTER__HPP__
#define __EMITTER__HPP__

#include "particle.hpp"
#include "compositeParticle.hpp"


class Emitter
{
    public:

        Emitter(double, double,
                float = 0, float = 0, float = 0, float = 0, float = 0, float = 0,
                float = 0, float = 0, float = 0, float = 0, float = 0, float = 0,
                float = 0, float = 0, float = 0, float = 0, float = 0, float = 0);
        Emitter(const Emitter&);
        ~Emitter();
        
        Particle* getColoredDecoratedParticle();
        Particle* getColoredDecoratedDecelParticle(double);
        Particle* getColoredDecoratedDecelParticleSphere(double, double);

        Particle* getColoredParticle();
        Particle* getColoredParticle(const Quad*, bool);
        Particle* getColoredDecelParticle(const Quad*, bool, double, double);
        Particle* getColoredDecelParticle(double, double);
        Particle* getSinParticle(const Quad*, bool, double);


        void setPosIX(float val) {ox = val;};
        void setPosIY(float val) {oy = val;};
        void setPosIZ(float val) {oz = val;};
        void setPosFX(float val) {rx = val;};
        void setPosFY(float val) {ry = val;};
        void setPosFZ(float val) {rz = val;};

        void setVelIX(float val) {ovx = val;};
        void setVelIY(float val) {ovy = val;};
        void setVelIZ(float val) {ovz = val;};
        void setVelFX(float val) {rvx = val;};
        void setVelFY(float val) {rvy = val;};
        void setVelFZ(float val) {rvz = val;};

        void setAccIX(float val) {oax = val;};
        void setAccIY(float val) {oay = val;};
        void setAccIZ(float val) {oaz = val;};
        void setAccFX(float val) {rax = val;};
        void setAccFY(float val) {ray = val;};
        void setAccFZ(float val) {raz = val;};
        
        void addPosIX(float val) {ox += val;};
        void addPosIY(float val) {oy += val;};
        void addPosIZ(float val) {oz += val;};
        void addPosFX(float val) {rx += val;};
        void addPosFY(float val) {ry += val;};
        void addPosFZ(float val) {rz += val;};

        void addVelIX(float val) {ovx += val;};
        void addVelIY(float val) {ovy += val;};
        void addVelIZ(float val) {ovz += val;};
        void addVelFX(float val) {rvx += val;};
        void addVelFY(float val) {rvy += val;};
        void addVelFZ(float val) {rvz += val;};

        void addAccIX(float val) {oax += val;};
        void addAccIY(float val) {oay += val;};
        void addAccIZ(float val) {oaz += val;};
        void addAccFX(float val) {rax += val;};
        void addAccFY(float val) {ray += val;};
        void addAccFZ(float val) {raz += val;};

        void translate (float x, float y, float z);
        
    private:

        float ox, oy, oz;
        float ovx, ovy, ovz;
        float oax, oay, oaz;

        float rx,  ry,  rz;
        float rvx, rvy, rvz;
        float rax, ray, raz;

        double ot, rt, rangeT;
};


#endif
