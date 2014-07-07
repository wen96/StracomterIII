

#ifndef __PARTICLESTORAGE__H__
#define __PARTICLESTORAGE__H__

#include "particle.hpp"
#include "myVector.hpp"

class ParticleStorage
{

    public:
        ParticleStorage();
        ParticleStorage(const ParticleStorage&);
        ~ParticleStorage();

        void put(Particle*);
        void step(double timestep);
        void prepareFor(int);
        void render();

        Particle* &operator [](const int index)
        {
            return (*v)[index];
        }

        int size()
        {
            return cur;
        }
        
    private:
        myVector<Particle*>* v;
        int cur;
};

template <class T>
class TypedParticleStorage
{
    public:
        TypedParticleStorage()
        {
			v = new myVector<T*>();
			cur = 0;
		}
        TypedParticleStorage(const TypedParticleStorage& p)
        {
			v = new myVector<T*>(*(p.v));
			cur = p.cur;
		}
        ~TypedParticleStorage()
        {
			cur = -1;
			delete v;			
		}

        void put(T* p)
        {
			(*v)[cur] = p;
			cur++;
		}
        void step(double timestep)
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
		void prepareFor(int i)
        {
			if (i > 0)
			{
				v->setSize(cur+i);
			}			
		}
        void render()
        {
			for(int i = 0 ; i < cur; i++)
			{
				(*v)[i]->render();
			}			
		}

        T* &operator [](const int index)
        {
            return (*v)[index];
        }

        int size()
        {
            return cur;
        }
        
    private:
        myVector<T*>* v;
        int cur;
};


#endif
