#include "compositeParticle.hpp"

#include <iostream>
using namespace std;
#include <cstdlib>
#include <cmath>

#define RANDOM0_1 (float)((rand()%101)/100.0)

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//



ParticleMover::ParticleMover(map<string, double> values)
{
    t.x = values["positionX"];
    t.y = values["positionY"];
    t.z = values["positionZ"];
    rot.x = RANDOM0_1;
    rot.y = RANDOM0_1;
    rot.z = RANDOM0_1;
    origT = t;

}

ParticleMover::ParticleMover(const ParticleMover& p)
{
    t = p.t;
    rot = p.rot;
    origT = p.origT;
}

void
ParticleMover::render() const
{
    glPushMatrix();
    glTranslatef(t.x, t.y, t.z);
    glRotatef(360*rot.x, 1,0,0);
    glRotatef(360*rot.y, 0,1,0);
    glRotatef(360*rot.z, 0,0,1);
    glScalef(2, 2, 2);
}

vector<string> 
ParticleMover::getRequiredValues()
{
	vector<string> ret;
	ret.push_back("positionX");
	ret.push_back("positionY");
	ret.push_back("positionZ");
	return ret;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//


void
CompositeParticle::step (float timeStep)
{
    lifeTime -= timeStep;
    pm->step(timeStep);
    pr->step(timeStep);
}

void 
CompositeParticle::render() const 
{
	pm->render();
	if (billboarding)
	{
		float modelview[16];
		unsigned int i,j;
		
		glGetFloatv(GL_MODELVIEW_MATRIX , modelview);

		for( i=0; i<3; i++ ) 
			for( j=0; j<3; j++ ) {
				if ( i==j )
					modelview[i*4+j] = 1.0;
				else
					modelview[i*4+j] = 0.0;
			}

		glLoadMatrixf(modelview);
		//~ glRotatef(pm->getRot().z*360, 0 , 0, 1);
		glScalef(0.2, 0.2, 0.2);
	} 
	glDisable(GL_TEXTURE_2D);
	pr->render(pm);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//


ParticleMoverPVA::
ParticleMoverPVA(map<string, double> values):ParticleMover(values)
{
   
    v.x = values["speedX"];
    v.y = values["speedY"];
    v.z = values["speedZ"];
    
    a.x = values["accelX"];
    a.y = values["accelY"];
    a.z = values["accelZ"];

}

ParticleMoverPVA::
ParticleMoverPVA(const ParticleMoverPVA &p):ParticleMover(p)
{
    v = p.v;
    a = p.a;
}

void
ParticleMoverPVA::step (PARTICLE_REAL_PRECISION timeStep)
{
    t.x += timeStep * v.x;
    t.y += timeStep * v.y;
    t.z += timeStep * v.z;

    v.x += timeStep * a.x;
    v.y += timeStep * a.y;
    v.z += timeStep * a.z;
}

vector<string> 
ParticleMoverPVA::getRequiredValues()
{
	vector<string> ret;
	ret.push_back("positionX");
	ret.push_back("positionY");
	ret.push_back("positionZ");
	ret.push_back("speedX");
	ret.push_back("speedY");
	ret.push_back("speedZ");
	ret.push_back("accelX");
	ret.push_back("accelY");
	ret.push_back("accelZ");
	return ret;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//


//x, y, z, vx, vy, vz, decel
ParticleMoverPVD::
ParticleMoverPVD(map<string, double> values):ParticleMover(values)
{
   
    v.x = values["speedX"];
    v.y = values["speedY"];
    v.z = values["speedZ"];

    travelled.x = 0;
    travelled.y = 0;
    travelled.z = 0;

    this->decel = values["decel"];
    this->totalLifeTime = values["lifeTime"];
    this->currLifeTime = values["lifeTime"];
}

ParticleMoverPVD::
ParticleMoverPVD(const ParticleMoverPVD &p) : ParticleMover(p)
{
    v = p.v;
    travelled = p.travelled;

    decel = p.decel;
    totalLifeTime = p.totalLifeTime;
    currLifeTime = p.currLifeTime;
}

void
ParticleMoverPVD::step (PARTICLE_REAL_PRECISION timeStep)
{
    travelled.x += v.x * timeStep;
    travelled.y += v.y * timeStep;
    travelled.z += v.z * timeStep;

    v.x /= 1 + abs(travelled.x) * decel;
    v.y /= 1 + abs(travelled.y) * decel;
    v.z /= 1 + abs(travelled.z) * decel;

    t.x += v.x;
    t.y += v.y;
    t.z += v.z;
}


vector<string> 
ParticleMoverPVD::getRequiredValues()
{
	vector<string> ret;
	ret.push_back("positionX");
	ret.push_back("positionY");
	ret.push_back("positionZ");
	ret.push_back("speedX");
	ret.push_back("speedY");
	ret.push_back("speedZ");
	ret.push_back("decel");
	ret.push_back("lifeTime");
	return ret;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

ParticleMoverSin::
ParticleMoverSin(map<string, double> values):ParticleMover(values)
{
   
    v.x = values["speedX"];
    v.y = values["speedY"];
    v.z = values["speedZ"];
    a.x = values["accelX"];
    a.y = values["accelY"];
    a.z = values["accelZ"];
    
    amplitude = values["amplitude"];

	acumTime = RANDOM0_1*3;
}

ParticleMoverSin::
ParticleMoverSin(const ParticleMoverSin &p):ParticleMover(p)
{
    v = p.v;
    amplitude = p.amplitude;
    acumTime = p.acumTime;
}

void
ParticleMoverSin::step (PARTICLE_REAL_PRECISION timeStep)
{
    t.x += timeStep * v.x;
    t.y += timeStep * v.y;
    t.z += timeStep * v.z;
        
    v.x += sin(a.x*acumTime)*amplitude;
    v.y += sin(a.y*acumTime)*amplitude;
    v.z += sin(a.z*acumTime)*amplitude;
        
    acumTime += timeStep;
}

vector<string> 
ParticleMoverSin::getRequiredValues()
{
	vector<string> ret;
	ret.push_back("positionX");
	ret.push_back("positionY");
	ret.push_back("positionZ");
	ret.push_back("speedX");
	ret.push_back("speedY");
	ret.push_back("speedZ");
	ret.push_back("accelX");
	ret.push_back("accelY");
	ret.push_back("accelZ");
	ret.push_back("amplitude");
	return ret;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

vector<Quad*> ParticleMoverForces::globalDragPoints;

ParticleMoverForces::
ParticleMoverForces(map<string, double> values):ParticleMover(values)
{
	v.x = values["speedX"];
	v.y = values["speedY"];
	v.z = values["speedZ"];
	mass = values["mass"];
	localPosition = NULL;
}

ParticleMoverForces::
ParticleMoverForces(const ParticleMoverForces &p):ParticleMover(p)
{
    localDragPoints = p.localDragPoints;
    Quad* q,* aux;
    for (unsigned int i = 0; i < p.localDragPoints.size(); i++)
    {
		q = new Quad();
		aux = p.localDragPoints[i];
		q->r = aux->r;
		q->g = aux->g;
		q->b = aux->b;
		q->a = aux->a;
		localDragPoints.push_back(q);
	}
	v = p.v;
	force = p.force;
    mass = p.mass;
}

ParticleMoverForces::
~ParticleMoverForces()
{
	clearLocalDragPoints();
}

Quad* 
ParticleMoverForces::addGlobalDragPoint(Quad p)
{
	Quad* q;
	q = new Quad();
	q->r = p.r;
	q->g = p.g;
	q->b = p.b;
	q->a = p.a;
	globalDragPoints.push_back(q);	
	return q;
}

void 
ParticleMoverForces::clearGlobalDragPoints()
{
    for (unsigned int i = 0; i < globalDragPoints.size(); i++)
    {
		delete globalDragPoints[i];
	}	
	globalDragPoints.clear();
}
		
Quad* 
ParticleMoverForces::addLocalDragPoint(Quad p)
{
	Quad* q;
	q = new Quad();
	q->r = p.r;
	q->g = p.g;
	q->b = p.b;
	q->a = p.a;
	localDragPoints.push_back(q);		
	return q;
}

void 
ParticleMoverForces::clearLocalDragPoints()
{
    for (unsigned int i = 0; i < localDragPoints.size(); i++)
    {
		delete localDragPoints[i];
	}	
	localDragPoints.clear();	
}

double modulo2 (triangle o , Quad d)
{
	double inX = o.x - d.r;
	double inY = o.y - d.g;
	double inZ = o.z - d.b;
	inX *= inX;
	inY *= inY;
	inZ *= inZ;
	return (inX + inY + inZ);
}

void
ParticleMoverForces::step (PARTICLE_REAL_PRECISION timeStep)
{
	if (localPosition)
	{
		localPosition->r = t.x;
		localPosition->g = t.y;
		localPosition->b = t.z;
		localPosition->a = mass;
	}
	triangle force;
	Quad* curPoint;
	double mod = 0;
	unsigned int i;
	force.x = 0;
	force.y = 0;
	force.z = 0;
	for (i = 0; i < localDragPoints.size(); i++)
	{
		curPoint = localDragPoints[i];
		mod = modulo2(t, *curPoint);
		if (mod < 1)
			mod = 1;
		force.x += curPoint->a * (curPoint->r -t.x) / mod;
		force.y += curPoint->a * (curPoint->g -t.y) / mod;
		force.z += curPoint->a * (curPoint->b -t.z) / mod;
	}
	for (i = 0; i < globalDragPoints.size(); i++)
	{
		curPoint = globalDragPoints[i];
		mod = modulo2(t, *curPoint);
		if (mod < 1)
			mod = 1;
		force.x += curPoint->a * (curPoint->r -t.x) / mod;
		force.y += curPoint->a * (curPoint->g -t.y) / mod;
		force.z += curPoint->a * (curPoint->b -t.z) / mod;
	}
	
	t.x += force.x * timeStep;
	t.y += force.y * timeStep;
	t.z += force.z * timeStep;	

}


vector<string> 
ParticleMoverForces::getRequiredValues()
{
	vector<string> ret;
	ret.push_back("positionX");
	ret.push_back("positionY");
	ret.push_back("positionZ");
	ret.push_back("speedX");
	ret.push_back("speedY");
	ret.push_back("speedZ");
	ret.push_back("mass");
	return ret;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

vector<Quad*> ParticleMoverForcesInertia::globalDragPoints;

ParticleMoverForcesInertia::
ParticleMoverForcesInertia(map<string, double> values):ParticleMover(values)
{
	v.x = values["speedX"];
	v.y = values["speedY"];
	v.z = values["speedZ"];
	mass = values["mass"];
	localPosition = NULL;
}

ParticleMoverForcesInertia::
ParticleMoverForcesInertia(const ParticleMoverForcesInertia &p):ParticleMover(p)
{
    localDragPoints = p.localDragPoints;
    Quad* q,* aux;
    for (unsigned int i = 0; i < p.localDragPoints.size(); i++)
    {
		q = new Quad();
		aux = p.localDragPoints[i];
		q->r = aux->r;
		q->g = aux->g;
		q->b = aux->b;
		q->a = aux->a;
		localDragPoints.push_back(q);
	}
	v = p.v;
	force = p.force;
    mass = p.mass;
}

ParticleMoverForcesInertia::
~ParticleMoverForcesInertia()
{
	clearLocalDragPoints();
}

Quad* 
ParticleMoverForcesInertia::addGlobalDragPoint(Quad p)
{
	Quad* q;
	q = new Quad();
	q->r = p.r;
	q->g = p.g;
	q->b = p.b;
	q->a = p.a;
	globalDragPoints.push_back(q);	
	return q;
}

void 
ParticleMoverForcesInertia::clearGlobalDragPoints()
{
    for (unsigned int i = 0; i < globalDragPoints.size(); i++)
    {
		delete globalDragPoints[i];
	}	
	globalDragPoints.clear();
}
		
Quad* 
ParticleMoverForcesInertia::addLocalDragPoint(Quad p)
{
	Quad* q;
	q = new Quad();
	q->r = p.r;
	q->g = p.g;
	q->b = p.b;
	q->a = p.a;
	localDragPoints.push_back(q);		
	return q;
}

void 
ParticleMoverForcesInertia::clearLocalDragPoints()
{
    for (unsigned int i = 0; i < localDragPoints.size(); i++)
    {
		delete localDragPoints[i];
	}	
	localDragPoints.clear();	
}

void
ParticleMoverForcesInertia::step (PARTICLE_REAL_PRECISION timeStep)
{
	if (localPosition)
	{
		localPosition->r = t.x;
		localPosition->g = t.y;
		localPosition->b = t.z;
		localPosition->a = mass;
	}
	triangle force;
	Quad* curPoint;
	double mod = 0;
	unsigned int i;
	force.x = 0;
	force.y = 0;
	force.z = 0;
	for (i = 0; i < localDragPoints.size(); i++)
	{
		curPoint = localDragPoints[i];
		mod = modulo2(t, *curPoint);
		if (mod < 1)
			mod = 1;
		force.x += curPoint->a * (curPoint->r -t.x) / mod;
		force.y += curPoint->a * (curPoint->g -t.y) / mod;
		force.z += curPoint->a * (curPoint->b -t.z) / mod;
	}
	for (i = 0; i < globalDragPoints.size(); i++)
	{
		curPoint = globalDragPoints[i];
		mod = modulo2(t, *curPoint);
		if (mod < 1)
			mod = 1;
		force.x += curPoint->a * (curPoint->r -t.x) / mod;
		force.y += curPoint->a * (curPoint->g -t.y) / mod;
		force.z += curPoint->a * (curPoint->b -t.z) / mod;
	}
	
	t.x += v.x * timeStep;
	t.y += v.y * timeStep;
	t.z += v.z * timeStep;
	
	v.x = (v.x + force.x * timeStep);
	v.y = (v.y + force.y * timeStep);
	v.z = (v.z + force.z * timeStep);
}

vector<string> 
ParticleMoverForcesInertia::getRequiredValues()
{
	vector<string> ret;
	ret.push_back("positionX");
	ret.push_back("positionY");
	ret.push_back("positionZ");
	ret.push_back("speedX");
	ret.push_back("speedY");
	ret.push_back("speedZ");
	ret.push_back("mass");
	return ret;
}



//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

ParticleRendererColorFading::ParticleRendererColorFading
    (map<string, double> values):ParticleRenderer(values)
{
    c.r = values["colorR"];
    c.g = values["colorG"];
    c.b = values["colorB"];
    c.a = values["colorA"];

    if (values["fade"] > 0.5)
    {
        decrement = c.a/values["lifeTime"];
    }
    else
    {
        decrement = 0;
    }
}

ParticleRendererColorFading::ParticleRendererColorFading
    (const ParticleRendererColorFading& p):ParticleRenderer(p)
{
    c = p.c;
    decrement = p.decrement;
}

void
ParticleRendererColorFading::step(float timeStep)
{
    c.a -= timeStep*decrement;
}

void
ParticleRendererColorFading::render(ParticleMover* pm) const
{
    glColor4f(c.r,c.g,c.b,c.a);
    glNormal3f(0,0,1);
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

vector<string> 
ParticleRendererColorFading::getRequiredValues()
{
	vector<string> ret;
	ret.push_back("colorR");
	ret.push_back("colorG");
	ret.push_back("colorB");
	ret.push_back("colorA");
	ret.push_back("lifeTime");
	ret.push_back("fade");
	return ret;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

ParticleRendererColorUA::ParticleRendererColorUA
    (map<string, double> values):ParticleRenderer(values)
{
    c.r = values["colorR"];
    c.g = values["colorG"];
    c.b = values["colorB"];
    c.a = values["colorA"];
    v.r = values["colorVR"];
    v.g = values["colorVG"];
    v.b = values["colorVB"];
    v.a = values["colorVA"];
    a.r = values["colorAR"];
    a.g = values["colorAG"];
    a.b = values["colorAB"];
    a.a = values["colorAA"];

    if (values["fade"] > 0.5)
    {
        decrement = c.a/values["lifeTime"];
    }
    else
    {
        decrement = 0;
    }
    
    round = values["round"]>0.5;
}

ParticleRendererColorUA::ParticleRendererColorUA
    (const ParticleRendererColorUA& p):ParticleRenderer(p)
{
    c = p.c;
    v = p.v;
    a = p.a;
    decrement = p.decrement;
    round = p.round;
}

void
ParticleRendererColorUA::step(float timeStep)
{
    c.a -= timeStep*decrement;
    
    c.r += timeStep * v.r;
    c.g += timeStep * v.g;
    c.b += timeStep * v.b;
    c.a += timeStep * v.a;
    
    if (round)
    {
		while (c.r > 1)
		{
			c.r = 1;
			v.r = -v.r;
		}
		while (c.g > 1)
		{
			c.g = 1;
			v.g = -v.g;
		}
		while (c.b > 1)
		{
			c.b = 1;
			v.b = -v.b;
		}
		while (c.a > 1)
		{
			c.a = 1;
			v.a = -v.a;
		}
		while (c.r < 0)
		{
			c.r = 0;
			v.r = -v.r;
		}
		while (c.g < 0)
		{
			c.g = 0;
			v.g = -v.g;
		}
		while (c.b < 0)
		{
			c.b = 0;
			v.b = -v.b;
		}
		while (c.a < 0)
		{
			c.a = 0;
			v.a = -v.a;
		}
	}
	else
	{
		if (c.r > 1)
		{
			c.r = 1;
			v.r = 0;
			a.r = 0;
		}
		if (c.g > 1)
		{
			c.g = 1;
			v.g = 0;
			a.g = 0;
		}
		if (c.b > 1)
		{
			c.b = 1;
			v.b = 0;
			a.b = 0;
		}
		if (c.a > 1)
		{
			c.a = 1;
			v.a = 0;
			a.a = 0;
		}
		if (c.r < 0)
		{
			c.r = 0;
			v.r = 0;
			a.r = 0;
		}
		if (c.g < 0)
		{
			c.g = 0;
			v.g = 0;
			a.g = 0;
		}
		if (c.b < 0)
		{
			c.b = 0;
			v.b = 0;
			a.b = 0;
		}
		if (c.a < 0)
		{
			c.a = 0;
			v.a = 0;
			a.a = 0;
		}

	}
}

void
ParticleRendererColorUA::render(ParticleMover* pm) const
{
    glColor4f(c.r,c.g,c.b,c.a);
    glNormal3f(0,0,1);
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

vector<string> 
ParticleRendererColorUA::getRequiredValues()
{
	vector<string> ret;
	ret.push_back("colorR");
	ret.push_back("colorG");
	ret.push_back("colorB");
	ret.push_back("colorA");
	ret.push_back("colorVR");
	ret.push_back("colorVG");
	ret.push_back("colorVB");
	ret.push_back("colorVA");
	ret.push_back("colorAR");
	ret.push_back("colorAG");
	ret.push_back("colorAB");
	ret.push_back("colorAA");
	ret.push_back("lifeTime");
	ret.push_back("fade");
	ret.push_back("round");
	return ret;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

Quad ParticleRendererSecuentialColorFading::nextColor;

ParticleRendererSecuentialColorFading::ParticleRendererSecuentialColorFading
    (map<string, double> values):ParticleRenderer(values)
{
	if (nextColor.a != 0)
	{
		nextColor.r = nextColor.g = nextColor.b = nextColor.a = 0;
	}
	c.r = nextColor.r;
	c.g = nextColor.g;
	c.b = nextColor.b;
    c.a = values["colorA"];

    if (values["fade"] > 0.5)
    {
        decrement = c.a/values["lifeTime"];
    }
    else
    {
        decrement = 0;
    }
    
	int r = rand()%3;
	if (r == 0)
	{
		nextColor.r = nextColor.r>0.99?0:(nextColor.r+.1);
	}
	if (r == 1)
	{
		nextColor.g = nextColor.g>0.99?0:(nextColor.g+.1);
	}
	if (r == 2)
	{
		nextColor.b = nextColor.b>0.99?0:(nextColor.b+.1);
	}
}

ParticleRendererSecuentialColorFading::ParticleRendererSecuentialColorFading
    (const ParticleRendererSecuentialColorFading& p):ParticleRenderer(p)
{
    c = p.c;
    decrement = p.decrement;
}

void
ParticleRendererSecuentialColorFading::step(float timeStep)
{
    c.a -= timeStep*decrement;
}

void
ParticleRendererSecuentialColorFading::render(ParticleMover* pm) const
{
    glColor4f(c.r,c.g,c.b,c.a);
    glNormal3f(0,0,1);
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

vector<string> 
ParticleRendererSecuentialColorFading::getRequiredValues()
{
	vector<string> ret;
	ret.push_back("colorA");
	ret.push_back("lifeTime");
	ret.push_back("fade");
	return ret;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

vector<Texture*> ParticleRendererTextureFading::textures;

ParticleRendererTextureFading::ParticleRendererTextureFading
    (map<string, double> values):ParticleRenderer(values)
{
    c.r = values["colorR"];
    c.g = values["colorG"];
    c.b = values["colorB"];
    c.a = values["colorA"];

    if (values["fade"] > 0.5)
    {
        decrement = c.a/values["lifeTime"];
    }
    else
    {
        decrement = 0;
    }
    
    textureNum = round(values["textureNum"]);
}

ParticleRendererTextureFading::ParticleRendererTextureFading
    (const ParticleRendererTextureFading& p):ParticleRenderer(p)
{
    c = p.c;
    decrement = p.decrement;
    textureNum = p.textureNum;
}

void
ParticleRendererTextureFading::step(float timeStep)
{
    c.a -= timeStep*decrement;
}

void
ParticleRendererTextureFading::render(ParticleMover* pm) const
{
    glColor4f(c.r,c.g,c.b,c.a);
    glNormal3f(0,0,1);
    glDisable(GL_CULL_FACE);
    textures[textureNum]->bind();
    glEnable(GL_TEXTURE_2D);
    glBegin(GL_QUADS);
        glTexCoord2f(0,0); glVertex3f( -1.0f, -1.0f,  0.0f );
        glTexCoord2f(1,0); glVertex3f(  1.0f, -1.0f,  0.0f );
        glTexCoord2f(1,1); glVertex3f(  1.0f,  1.0f,  0.0f );
        glTexCoord2f(0,1); glVertex3f( -1.0f,  1.0f,  0.0f );
    glEnd();
    glEnable(GL_CULL_FACE);
    glPopMatrix();
}

vector<string> 
ParticleRendererTextureFading::getRequiredValues()
{
	vector<string> ret;
	ret.push_back("colorR");
	ret.push_back("colorG");
	ret.push_back("colorB");
	ret.push_back("colorA");
	ret.push_back("lifeTime");
	ret.push_back("fade");
	ret.push_back("textureNum");
	return ret;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

unsigned int ParticleRendererColorTracer::maxLong = 20;

ParticleRendererColorTracer::ParticleRendererColorTracer
    (map<string, double> values):ParticleRenderer(values)
{
    c.r = values["colorR"];
    c.g = values["colorG"];
    c.b = values["colorB"];
    c.a = values["colorA"];

    if (values["fade"] > 0.5)
    {
        decrement = c.a/values["lifeTime"];
    }
    else
    {
        decrement = 0;
    }
}

ParticleRendererColorTracer::ParticleRendererColorTracer
    (const ParticleRendererColorTracer& p):ParticleRenderer(p)
{
    c = p.c;
	oldPositions = p.oldPositions;
}

void
ParticleRendererColorTracer::step(float timeStep)
{
    c.a -= timeStep*decrement;
}

void
ParticleRendererColorTracer::render(ParticleMover* pm) const
{
	//Dont use the position render
	glPopMatrix();
	glPushMatrix();
    glColor4f(c.r,c.g,c.b,c.a);
    glNormal3f(0,0,1);
    glDisable(GL_CULL_FACE);
    triangle pos = pm->getPos();
    oldPositions.push_back(pos);
    if (oldPositions.size() > maxLong)
		oldPositions.erase(oldPositions.begin());
    glBegin(GL_LINE_STRIP);
		for (unsigned int i = 0; i < oldPositions.size(); i++)
		{
			pos = oldPositions[i];
			glVertex3f(pos.x, pos.y, pos.z);
		}
        //~ glTexCoord2f(0,0); glVertex3f( -1.0f, -1.0f,  0.0f );
        //~ glTexCoord2f(1,0); glVertex3f(  1.0f, -1.0f,  0.0f );
        //~ glTexCoord2f(1,1); glVertex3f(  1.0f,  1.0f,  0.0f );
        //~ glTexCoord2f(0,1); glVertex3f( -1.0f,  1.0f,  0.0f );
    glEnd();
    glPopMatrix();
}

vector<string> 
ParticleRendererColorTracer::getRequiredValues()
{
	vector<string> ret;
	ret.push_back("colorR");
	ret.push_back("colorG");
	ret.push_back("colorB");
	ret.push_back("colorA");
	ret.push_back("lifeTime");
	ret.push_back("fade");
	return ret;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

unsigned int ParticleRendererColorTracerConstantLength::maxLong = 20;

ParticleRendererColorTracerConstantLength::ParticleRendererColorTracerConstantLength
    (map<string, double> values):ParticleRenderer(values)
{
    c.r = values["colorR"];
    c.g = values["colorG"];
    c.b = values["colorB"];
    c.a = values["colorA"];

    if (values["fade"] > 0.5)
    {
        decrement = c.a/values["lifeTime"];
    }
    else
    {
        decrement = 0;
    }
}

ParticleRendererColorTracerConstantLength::ParticleRendererColorTracerConstantLength
    (const ParticleRendererColorTracerConstantLength& p):ParticleRenderer(p)
{
    c = p.c;
	oldPositions = p.oldPositions;
}

void
ParticleRendererColorTracerConstantLength::step(float timeStep)
{
    c.a -= timeStep*decrement;
}

void
ParticleRendererColorTracerConstantLength::render(ParticleMover* pm) const
{
	//Dont use the position render
	glPopMatrix();
	glPushMatrix();
    glColor4f(c.r,c.g,c.b,c.a);
    glNormal3f(0,0,1);
    glDisable(GL_CULL_FACE);
    triangle pos;    
    if (oldPositions.size() == 0)
    {
		oldPositions.push_back(pm->getPos());
	}
	else 
	{
		if (pm->getPos().modulo(oldPositions.back())>0.01)
		{
			oldPositions.push_back(pm->getPos());
			if (oldPositions.size() > maxLong)
				oldPositions.erase(oldPositions.begin());
		}
	}

    glBegin(GL_LINE_STRIP);
		for (unsigned int i = 0; i < oldPositions.size(); i++)
		{
			pos = oldPositions[i];
			glVertex3f(pos.x, pos.y, pos.z);
		}
        //~ glTexCoord2f(0,0); glVertex3f( -1.0f, -1.0f,  0.0f );
        //~ glTexCoord2f(1,0); glVertex3f(  1.0f, -1.0f,  0.0f );
        //~ glTexCoord2f(1,1); glVertex3f(  1.0f,  1.0f,  0.0f );
        //~ glTexCoord2f(0,1); glVertex3f( -1.0f,  1.0f,  0.0f );
    glEnd();
    glPopMatrix();
}

vector<string> 
ParticleRendererColorTracerConstantLength::getRequiredValues()
{
	vector<string> ret;
	ret.push_back("colorR");
	ret.push_back("colorG");
	ret.push_back("colorB");
	ret.push_back("colorA");
	ret.push_back("lifeTime");
	ret.push_back("fade");
	return ret;
}
