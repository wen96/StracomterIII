/*
 * World.h
 *
 *  Created on: 17/11/2011
 *      Author: sergio
 */

#ifndef WORLD_H_
#define WORLD_H_

#include <iostream>
using namespace std;
#include "Box2D/Box2D.h"
#include "Box.h"
#include "Point.h"
#include "Polygon.h"
#include "Force.h"

/**\brief RayData
 * Almacena los datos de un rayo.*/
typedef struct {
	/**\brief Cuerpo con el que choca el rayo.*/
	b2Body *body;
	/**\brief Punto de corte del rayo.*/
	Point point;
	/**\brief Centro del Body*/
	Point centro;
	/**\brief Normal de la colisón.*/
	Force normal;
	/**\brief Indica si intersecta o no.*/
	bool hit;

} RayData;

/**\brief MultiRayData
 * Almacena los datos de un multirayo.*/
typedef struct {
	/**\brief Vector de Body(s)*/
	vector<b2Body*>body;
	/**\brief Vector de puntos de corte*/
	vector<Point> point;
	/**\brief Vector de centros de los Body(s)*/
	vector<Point> centro;
	/**\brief Último punto de corte*/
	Point last;
	/**\brief Vector de las normales de las colisiones*/
	vector<Force> normal;
	/**\brief Indica si hay colisión o no.*/
	bool hit;

} MultiRayData;

/**\class World
 * Clase que almacena el mundo físico donde interactúan los objetos.*/
class World {
public:
	/**\brief Constructor por defecto (puede no recibir parámetros).
	 * \param gravity Force que indica la gravedad del mundo.
	 * \param doSleep permite dormirse a los objetos sin movimiento.*/
	World(Force gravity = (Force(0.0,0.0)), bool doSleep = true);
	/**\brief Constructor sobrecargado.
	 * \param frame FPS a los que se actualiza el mundo.
	 * \param gravity Force que indica la gravedad del mundo.
	 * \param doSleep permite dormirse a los objetos sin movimiento.*/
	World(float, Force gravity = (Force(0.0,0.0)), bool doSleep = true);
	/**\brief Destructor*/
	virtual ~World();
	/**\brief Constructor de copia.
	 * \param w Mundo a copiar.*/
	World(const World &);
	/**\brief Sobrecarga del operador de asignación.
	 * \param w Mundo a copiar.*/
	World& operator=(const World &);
	/**\brief Devuelve el mundo.
	 * \return Devuelve un puntero a objeto b2World*/
	b2World* getWorld();
	/**\brief Acutaliza el mundo físico*/
	void UpdateWorld();
	/**\brief Indica si hay visibilidad entre dos puntos.
	 * \param p1 Punto 1 del rayo.
	 * \param p2 Punto 2 del rayo.
	 * \return true si hay visibilidad y false en caso contrario.*/
	bool Ray(Point, Point) const;
	/**\brief Devuelve los 10 primero puntos de corte de un rayo.
	 * \param p1 Punto 1 del rayo.
	 * \param p2 Punto 2 del rayo.
	 * \return Vector de puntos.*/
	vector<Point> CutOffPoints(Point, Point) const;
	/**\brief Devuelve el primero punto de corte del rayo.
	 * \param p1 Punto 1 del rayo.
	 * \param p2 Punto 2 del rayo.
	 * \return Punto de corte.*/
	Point CutOffPoint(Point, Point) const;
	/**\brief Asigna un valor de FPS para la acutalización del mundo.
	 * \param frame Valor de nuevo FPS.*/
	void setFrame(float frame) {
		fps = frame;
	}
	/**\brief Devuelve los FPS.
	 * \return Devuelve el valor de los FPS.*/
	float getFrame() const{
		return fps;
	}
	/**\brief Asigna un nuevo mundo.
	 * \param w Objeto b2World que contiene el nuevo mundo.*/
	void setWorld(b2World *w)
	{
		world = w;
	}
	/**\brief Lanza un rayo y devuelve los datos del rayo.
	 * \param p1 Punto 1 del rayo.
	 * \param p2 Punto 2 del rayo.
	 * \return Devuelve un objeto RayData con los datos del rayo.*/
	RayData RayBody(Point, Point) const;
	/**\brief Lanza un rayo y devuelve los datos del rayo.
	 * \param p1 Punto 1 del rayo.
	 * \param p2 Punto 2 del rayo.
	 * \return Devuelve un objeto MultiRayData con los datos del rayo.*/
	MultiRayData MultiRayBody(Point, Point) const;
private:
	/**\brief Mundo físico*/
	b2World *world;
	/**\brief FPS al que se actualiza el mundo*/
	float fps;
};



/**\class BodyRayCastCallback
 * Clase que hereda de b2RayCastCallback que sirve para llamar al rayo y devolver un objeto RayData.*/
class BodyRayCastCallback : public b2RayCastCallback
{
public:
	BodyRayCastCallback()
	{
		m_hit = false;
	}

	/**\brief Función que nos devuelve los datos del rayo.
	 * \param fixture Forma del objeto
	 * \param point Punto de corte.
	 * \param normal Normal del corte del rayo,
	 * \param fraction del rayo.*/
	float32 ReportFixture(	b2Fixture* fixture, const b2Vec2& point,
		const b2Vec2& normal, float32 fraction)
	{
		body = fixture->GetBody();
		void* userData = body->GetUserData();
		if (userData)
		{
			int32 index = *(int32*)userData;
			if (index == 0)
			{
				// filter
				return -1.0f;
			}
		}

		m_hit = true;
		m_point = point;
		m_normal = normal;
		return fraction;
	}

	/**\brief Indica si corta o no*/
	bool m_hit;
	/**\brief Punto de corte.*/
	b2Vec2 m_point;
	/**\brief Normal con el rayo.*/
	b2Vec2 m_normal;
	/**\brief Body con el que corta*/
	b2Body *body;
};

/**\class MultiBodyRayCastCallback
 * Clase que hereda de b2RayCastCallback que sirve para llamar al rayo y devolver MultRayData*/
class MultiBodyRayCastCallback : public b2RayCastCallback
{
public:
	enum
	{
		e_maxCount = 100
	};

	MultiBodyRayCastCallback()
	{
		m_count = 0;
	}

	/**\brief Función que nos devuelve los datos del rayo.
	 * \param fixture Forma del objeto
	 * \param point Punto de corte.
	 * \param normal Normal del corte del rayo,
	 * \param fraction del rayo.*/
	float32 ReportFixture(	b2Fixture* fixture, const b2Vec2& point,
		const b2Vec2& normal, float32 fraction)
	{
		b2Body* body = fixture->GetBody();
		void* userData = body->GetUserData();
		if (userData)
		{
			int32 index = *(int32*)userData;
			if (index == 0)
			{
				// filter
				return -1.0f;
			}
		}

		b2Assert(m_count < e_maxCount);

		m_points[m_count] = point;
		m_normals[m_count] = normal;
		m_body[m_count] = body;
		++m_count;

		if (m_count == e_maxCount)
		{
			return 0.0f;
		}

		return 1.0f;
	}

	/**\brief Vector de puntos de corte.*/
	b2Vec2 m_points[e_maxCount];
	/**\brief Vector de normales con el rayo.*/
	b2Vec2 m_normals[e_maxCount];
	/**\brief Vector de Body(s) que cortan con el rayo.*/
	b2Body *m_body[e_maxCount];
	/**\brief Contador de los cortes del rayo.*/
	int32 m_count;
};


/*
* Copyright (c) 2006-2009 Erin Catto http://www.box2d.org
*
* This software is provided 'as-is', without any express or implied
* warranty.  In no event will the authors be held liable for any damages
* arising from the use of this software.
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it
* freely, subject to the following restrictions:
* 1. The origin of this software must not be misrepresented; you must not
* claim that you wrote the original software. If you use this software
* in a product, an acknowledgment in the product documentation would be
* appreciated but is not required.
* 2. Altered source versions must be plainly marked as such, and must not be
* misrepresented as being the original software.
* 3. This notice may not be removed or altered from any source distribution.
*/

/**\class RayCastMultipleCallback
 * Clase que hereda de b2RayCastCallback que sirve para llamar al rayo y devolver varios puntos*/
class RayCastMultipleCallback : public b2RayCastCallback
{
public:
	enum
	{
		e_maxCount = 100
	};

	RayCastMultipleCallback()
	{
		m_count = 0;
	}

	/**\brief Función que nos devuelve los datos del rayo.
	 * \param fixture Forma del objeto
	 * \param point Punto de corte.
	 * \param normal Normal del corte del rayo,
	 * \param fraction del rayo.*/
	float32 ReportFixture(	b2Fixture* fixture, const b2Vec2& point,
		const b2Vec2& normal, float32 fraction)
	{
		b2Body* body = fixture->GetBody();
		void* userData = body->GetUserData();
		if (userData)
		{
			int32 index = *(int32*)userData;
			if (index == 0)
			{
				// filter
				return -1.0f;
			}
		}

		b2Assert(m_count < e_maxCount);

		m_points[m_count] = point;
		m_normals[m_count] = normal;
		++m_count;

		if (m_count == e_maxCount)
		{
			return 0.0f;
		}

		return 1.0f;
	}

	/**\brief Vector de puntos de corte.*/
	b2Vec2 m_points[e_maxCount];
	/**\brief Vector de normales con el rayo.*/
	b2Vec2 m_normals[e_maxCount];
	/**\brief Contador de los cortes del rayo.*/
	int32 m_count;
};

/**\class RayCastClosestCallback
 * Clase que hereda de b2RayCastCallback que sirve para llamar al rayo y devolver un punto.*/
class RayCastClosestCallback : public b2RayCastCallback
{
public:
	RayCastClosestCallback()
	{
		m_hit = false;
	}

	/**\brief Función que nos devuelve los datos del rayo.
	 * \param fixture Forma del objeto
	 * \param point Punto de corte.
	 * \param normal Normal del corte del rayo,
	 * \param fraction del rayo.*/
	float32 ReportFixture(	b2Fixture* fixture, const b2Vec2& point,
		const b2Vec2& normal, float32 fraction)
	{
		b2Body* body = fixture->GetBody();
		void* userData = body->GetUserData();
		if (userData)
		{
			int32 index = *(int32*)userData;
			if (index == 0)
			{
				// filter
				return -1.0f;
			}
		}

		m_hit = true;
		m_point = point;
		m_normal = normal;
		return fraction;
	}

	/**\brief Indica si corta o no*/
	bool m_hit;
	/**\brief Punto de corte.*/
	b2Vec2 m_point;
	/**\brief Normal de corte.*/
	b2Vec2 m_normal;
};
#endif /* WORLD_H_ */
