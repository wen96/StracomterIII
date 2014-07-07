#include "particleStorage.hpp"


ParticleStorage::ParticleStorage()
{
    v = new myVector<Particle*>();
    cur = 0;
}

ParticleStorage::ParticleStorage(const ParticleStorage& p)
{
    v = new myVector<Particle*>(*(p.v));
    cur = p.cur;
}

ParticleStorage::~ParticleStorage()
{   
    cur = -1;
    delete v;
}
    
void ParticleStorage::put(Particle* p)
{
    (*v)[cur] = p;
    cur++;
}

void ParticleStorage::step(double timestep)
{
    int dest = cur-1;

    for (int i = 0; i <= dest;)
    {
        (*v)[i]->step(timestep);

        if ((*v)[i]->isDead())
        {
            delete (*v)[i];
            (*v)[i] =  NULL;
            v->swap(i, dest);
            dest--;
        }
        else
        {
            i++;
        }
    }

    v->setSize(dest+1);
    cur = dest+1;
}

void ParticleStorage::render()
{
	for(int i = 0 ; i < cur; i++)
	{
		(*v)[i]->render();
	}
}

void ParticleStorage::prepareFor(int i)
{
    if (i > 0)
    {
        v->setSize(cur+i);
    }
}
