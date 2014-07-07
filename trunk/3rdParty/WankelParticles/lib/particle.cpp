#include "particle.hpp"

#include <iostream>
using namespace std;
#include <cstdlib>
#include <cmath>

#define RANDOM0_1 (float)((rand()%101)/100.0)

#define PARTICLE_REAL_PRECISION float

RandomColorPVAParticle::RandomColorPVAParticle(
                    PARTICLE_REAL_PRECISION lifeTime,
                    float a, bool fade,
                    PARTICLE_REAL_PRECISION  x,  PARTICLE_REAL_PRECISION  y   ,PARTICLE_REAL_PRECISION  z,
                    PARTICLE_REAL_PRECISION vx,  PARTICLE_REAL_PRECISION vy   ,PARTICLE_REAL_PRECISION vz,
                    PARTICLE_REAL_PRECISION ax,  PARTICLE_REAL_PRECISION ay   ,PARTICLE_REAL_PRECISION az) : Particle()
{
    p.x = x;
    p.y = y;
    p.z = z;
    
    v.x = vx;
    v.y = vy;
    v.z = vz;
    
    this->a.x = ax;
    this->a.y = ay;
    this->a.z = az;

    c.r = RANDOM0_1;
    c.g = RANDOM0_1;
    c.b = RANDOM0_1;
    c.a = a;

    r.x = RANDOM0_1;
    r.y = RANDOM0_1;
    r.z = RANDOM0_1;

    this->lifeTime = lifeTime;

    if (fade)
        alphaDecrement = c.a/lifeTime;
    else
        alphaDecrement = 0;
}

RandomColorPVAParticle::RandomColorPVAParticle(const RandomColorPVAParticle& r)
{
    p = r.p;
    v = r.v;
    a = r.a;
    c = r.c;
    lifeTime = r.lifeTime;
    alphaDecrement = r.alphaDecrement;
}

RandomColorPVAParticle::~RandomColorPVAParticle()
{

}

void
RandomColorPVAParticle::step (PARTICLE_REAL_PRECISION timeStep)
{
    lifeTime -= timeStep;

    c.a -= timeStep * alphaDecrement;

    p.x += timeStep * v.x;
    p.y += timeStep * v.y;
    p.z += timeStep * v.z;

    v.x += timeStep * a.x;
    v.y += timeStep * a.y;
    v.z += timeStep * a.z; 
}

void
RandomColorPVAParticle::render() const
{
    glColor4f(c.r,c.g,c.b,c.a);
    glNormal3f(0,0,1);
    glPushMatrix();
    glTranslatef(p.x, p.y, p.z);
    glRotatef(360*r.x, 1,0,0);
    glRotatef(360*r.y, 0,1,0);
    glRotatef(360*r.z, 0,0,1);
    glScalef(0.1, 0.1, 0.1);

    glDisable(GL_CULL_FACE);
    glBegin(GL_QUADS);
        glVertex3f( -1.0f, -1.0f,  0.0f );
        glVertex3f(  1.0f, -1.0f,  0.0f );
        glVertex3f(  1.0f,  1.0f,  0.0f );
        glVertex3f( -1.0f,  1.0f,  0.0f );
    glEnd();
    glEnable(GL_CULL_FACE);
    glPopMatrix();
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

ColorPVAParticle::ColorPVAParticle(
                    PARTICLE_REAL_PRECISION lifeTime,
                    float r, float g, float b, float a, bool fade,
                    PARTICLE_REAL_PRECISION  x,  PARTICLE_REAL_PRECISION  y   ,PARTICLE_REAL_PRECISION  z,
                    PARTICLE_REAL_PRECISION vx,  PARTICLE_REAL_PRECISION vy   ,PARTICLE_REAL_PRECISION vz,
                    PARTICLE_REAL_PRECISION ax,  PARTICLE_REAL_PRECISION ay   ,PARTICLE_REAL_PRECISION az) : Particle()
{
    p.x = x;
    p.y = y;
    p.z = z;
    
    v.x = vx;
    v.y = vy;
    v.z = vz;
    
    this->a.x = ax;
    this->a.y = ay;
    this->a.z = az;

    c.r = r;
    c.g = g;
    c.b = b;
    c.a = a;

    this->r.x = RANDOM0_1;
    this->r.y = RANDOM0_1;
    this->r.z = RANDOM0_1;

    this->lifeTime = lifeTime;

    if (fade)
        alphaDecrement = c.a/lifeTime;
    else
        alphaDecrement = 0;
}

ColorPVAParticle::ColorPVAParticle(const ColorPVAParticle& r)
{
    p = r.p;
    v = r.v;
    a = r.a;
    c = r.c;
    lifeTime = r.lifeTime;
    alphaDecrement = r.alphaDecrement;
}

ColorPVAParticle::~ColorPVAParticle()
{

}

void
ColorPVAParticle::step (PARTICLE_REAL_PRECISION timeStep)
{
    lifeTime -= timeStep;

    c.a -= timeStep * alphaDecrement;

    p.x += timeStep * v.x;
    p.y += timeStep * v.y;
    p.z += timeStep * v.z;

    v.x += timeStep * a.x;
    v.y += timeStep * a.y;
    v.z += timeStep * a.z; 
}

void
ColorPVAParticle::render() const
{
    glColor4f(c.r,c.g,c.b,c.a);
    glNormal3f(0,0,1);
    glPushMatrix();
    glTranslatef(p.x, p.y, p.z);
    glRotatef(360*r.x, 1,0,0);
    glRotatef(360*r.y, 0,1,0);
    glRotatef(360*r.z, 0,0,1);
    glScalef(0.01, 0.01, 0.01);

    glDisable(GL_CULL_FACE);
    glBegin(GL_QUADS);
        glVertex3f( -1.0f, -1.0f,  0.0f );
        glVertex3f(  1.0f, -1.0f,  0.0f );
        glVertex3f(  1.0f,  1.0f,  0.0f );
        glVertex3f( -1.0f,  1.0f,  0.0f );
    glEnd();
    glEnable(GL_CULL_FACE);
    glPopMatrix();
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

ColorPVDParticle::ColorPVDParticle(
                    PARTICLE_REAL_PRECISION lifeTime,
                    float r, float g, float b, float a, bool fade,
                    PARTICLE_REAL_PRECISION  x,  PARTICLE_REAL_PRECISION  y   ,PARTICLE_REAL_PRECISION  z,
                    PARTICLE_REAL_PRECISION vx,  PARTICLE_REAL_PRECISION vy   ,PARTICLE_REAL_PRECISION vz,
                    float decel) : Particle()
{
    p.x = x;
    p.y = y;
    p.z = z;
    
    v.x = vx;
    v.y = vy;
    v.z = vz;
    
    this->decel = decel*lifeTime;

    c.r = r;
    c.g = g;
    c.b = b;
    c.a = a;

    this->r.x = RANDOM0_1;
    this->r.y = RANDOM0_1;
    this->r.z = RANDOM0_1;

    this->lifeTime = lifeTime;

    if (fade)
        alphaDecrement = c.a/lifeTime;
    else
        alphaDecrement = 0;
}

ColorPVDParticle::ColorPVDParticle(const ColorPVDParticle& r)
{
    p = r.p;
    v = r.v;
    decel = r.decel;
    c = r.c;
    lifeTime = r.lifeTime;
    alphaDecrement = r.alphaDecrement;
}

ColorPVDParticle::~ColorPVDParticle()
{

}

void
ColorPVDParticle::step (PARTICLE_REAL_PRECISION timeStep)
{
    lifeTime -= timeStep;

    c.a -= timeStep * alphaDecrement;

    p.x += timeStep * v.x;
    p.y += timeStep * v.y;
    p.z += timeStep * v.z;

    v.x *= decel/(1/(1-timeStep));
    v.y *= decel/(1/(1-timeStep));
    v.z *= decel/(1/(1-timeStep));
}

void
ColorPVDParticle::render() const
{
    glColor4f(c.r,c.g,c.b,c.a);
    glNormal3f(0,0,1);
    glPushMatrix();
    glTranslatef(p.x, p.y, p.z);
    glRotatef(360*r.x, 1,0,0);
    glRotatef(360*r.y, 0,1,0);
    glRotatef(360*r.z, 0,0,1);
    glScalef(0.05, 0.05, 0.05);

    glDisable(GL_CULL_FACE);
    glBegin(GL_QUADS);
        glVertex3f( -1.0f, -1.0f,  0.0f );
        glVertex3f(  1.0f, -1.0f,  0.0f );
        glVertex3f(  1.0f,  1.0f,  0.0f );
        glVertex3f( -1.0f,  1.0f,  0.0f );
    glEnd();
    glEnable(GL_CULL_FACE);
    glPopMatrix();
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

ColorSinParticle::ColorSinParticle(
                    PARTICLE_REAL_PRECISION lifeTime,
                    float r, float g, float b, float a, bool fade,
                    PARTICLE_REAL_PRECISION  x,  PARTICLE_REAL_PRECISION  y   ,PARTICLE_REAL_PRECISION  z,
                    PARTICLE_REAL_PRECISION vx,  PARTICLE_REAL_PRECISION vy   ,PARTICLE_REAL_PRECISION vz,
                    PARTICLE_REAL_PRECISION ax,  PARTICLE_REAL_PRECISION ay   ,PARTICLE_REAL_PRECISION az, PARTICLE_REAL_PRECISION amplitude) : Particle()
{
    p.x = x;
    p.y = y;
    p.z = z;
    
    v.x = vx;
    v.y = vy;
    v.z = vz;
    
    this->a.x = ax;
    this->a.y = ay;
    this->a.z = az;

    c.r = r;
    c.g = g;
    c.b = b;
    c.a = a;

    this->r.x = RANDOM0_1;
    this->r.y = RANDOM0_1;
    this->r.z = RANDOM0_1;

    this->lifeTime = lifeTime;

    if (fade)
        alphaDecrement = c.a/lifeTime;
    else
        alphaDecrement = 0;

    this->amplitude = amplitude;
}

ColorSinParticle::ColorSinParticle(const ColorSinParticle& r)
{
    p = r.p;
    v = r.v;
    a = r.a;
    c = r.c;
    lifeTime = r.lifeTime;
    alphaDecrement = r.alphaDecrement;
    amplitude = r.amplitude;
}

ColorSinParticle::~ColorSinParticle()
{

}

void
ColorSinParticle::step (PARTICLE_REAL_PRECISION timeStep)
{
    lifeTime -= timeStep;

    c.a -= timeStep * alphaDecrement;

    p.x += timeStep * v.x;
    p.y += timeStep * v.y;
    p.z += timeStep * v.z;

    v.x += sin(lifeTime*a.x)*amplitude;
    v.y += sin(lifeTime*a.y)*amplitude;
    v.z += sin(lifeTime*a.z)*amplitude;
}

void
ColorSinParticle::render() const
{
    glColor4f(c.r,c.g,c.b,c.a);
    glNormal3f(0,0,1);
    glPushMatrix();
    glTranslatef(p.x, p.y, p.z);
    glRotatef(360*r.x, 1,0,0);
    glRotatef(360*r.y, 0,1,0);
    glRotatef(360*r.z, 0,0,1);
    glScalef(0.05, 0.05, 0.05);

    glDisable(GL_CULL_FACE);
    glBegin(GL_QUADS);
        glVertex3f( -1.0f, -1.0f,  0.0f );
        glVertex3f(  1.0f, -1.0f,  0.0f );
        glVertex3f(  1.0f,  1.0f,  0.0f );
        glVertex3f( -1.0f,  1.0f,  0.0f );
    glEnd();
    glEnable(GL_CULL_FACE);
    glPopMatrix();
}
