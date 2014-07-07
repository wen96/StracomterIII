#ifndef AI_H_
#define AI_H_

#include "Pathfinder.h"
#include "FSM.h"
#include "Map.h"
#include "CoreNamespace.h"
#include "EntityManager.h"
#include "Character.h"
#include "World.h"
#include "Polygon.h"
#include "BodyData.h"
#include "Body.h"
#include "Tri.h"
#include "EventControl.h"

/**\class IA
 *\brief Interfaz con la IA para el juego. Permite hacer maquinas de estados y peticiones de pathfinding.
 */
class AI{
public:
	/**\brief Constructor vacio
	 */
	AI();

	/**\brief Constructor con puntero al EntityManager
	 */
	AI(EntityManager *manager);

	/**\brief Destructor
	 */
	~AI();

	/**\brief Constructor de copia
	 * @param ia IA a copiar
	 */
	AI(const AI &ai);

	/**\brief Sobrecarga de la igualdad
	 * @param ia Objeto a copiar
	 * @return Objeto copiado
	 */
	AI & operator=(const AI &ai);

	void setManager(EntityManager *manager);
	EntityManager * getManager();

	void setControler(EventControl *events);

	void Update();

	void Init();

	int updateFSM(Core::SmartEntities::Type entidad, int estado, int input);

	void setMap(Map * mapa);
	vector<Point> getPath(Point a, Point b);

	NavGraph * getTriangulation();
    Pathfinder *getPf();

    void Reset();

private:
	vector<FSM > fsmV;
	Pathfinder * pf;
	EventControl * eventos;
	EntityManager *entMan;

	static FSM makeFSM(Core::SmartEntities::Type entidad);

};

#endif
