/*
 * FSM.h
 *
 *  Created on: Dec 22, 2011
 *      Author: rellik
 */

#ifndef FSM_H_
#define FSM_H_

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

class FSMState;

/**\class Maquinas de Estados Finitos
 * \brief Maquinas de estados y sus transiciones
 *
 */
class FSM{
public:
	/**\brief Constructor vacio
	 */
	FSM();

	/**\brief Destructor
	 */
	~FSM();

	/**\brief Constructor de copia
	 * @param fsm Objeto a copiar
	 */
	FSM(const FSM &fsm);

	/**\brief Sobrecarga de la asignación
	 * @param fsm Objeto a copiar
	 * @return Objeto copiado
	 */
	FSM & operator=(const FSM &fsm);

	/**\brief Carga datos de un fichero
	 * @param fName Nombre del fichero
	 * @return True si se ha leido correctamente
	 */
	bool loadData(string fName);

	/**\brief Añadir un estado a la FSM
	 * @param name Estado a añadir
	 * @return Id del estado añadido
	 */
	int addState(string name);

	/**\brief Elimina un estado de la maquina
	 * Tambien elimina todas las transiciones relacionadas con el
	 * @param id Estado a eliminar
	 * @return True si se ha eliminado, false en caso contrario
	 */
	bool removeState(int id);

	/**\brief Añade una transicion a la FSM
	 * Añade una transicion a la FSM. Devuelve false si alguno de los estados no existe, o la transicion no es valida
	 * @param ori Estado de origen
	 * @param des Estado destino
	 * @param inp Input para transicionar
	 * @return true si el estado se ha añadido
	 */
	bool addTransition(int ori, int des, int inp);

	/**\brief Cambia el estado actual a state
	 * @param state Estado a cambiar
	 * @return True si se ha podido cambiar
	 */

	/**\brief ELimina la transicion entre ori y des
	 * @param ori Estado de origen
	 * @param des Estado de destino
	 * @return True si ha eliminado la transicion, false en caso contrario
	 */
	bool removeTransition(int ori, int des);

	/**\brief Cambia el estado actual
	 * @param state Nuevo estado actual
	 * @return True si se ha cambiado, false en caso contrario
	 */
	bool makeCurrent(int state);

	/**\brief Actualiza la FSM con la entrada input
	 * @param input Datos del mundo
	 * @return Estado al que se cambia
	 */
	int updateStates(int input);

	/**\brief Obtiene el id del estado actual
	 * @return id del estado actual
	 */
	int getCurrentI();

	/**\brief Obtiene el nombre del estado actual
	 * @return Nombre del estado actual
	 */
	string getCurrentS();

	/**\brief Obtiene el vector de estados actuales
	 * @return Vector de estados actuales
	 */
	vector<FSMState> getStates();

	/**\brief Obtiene el nombre de id
	 * @param id Id a buscar
	 * @return Su nombre
	 */
	string getName(int id);

	/**\brief Obtiene el id de name
	 * @param name Nombre del estado
	 * @return Id del estado
	 */
	int getId(string name);

	/**\brief Obtiene las transiciones del estado id
	 * @param id Id del estado
	 * @return Vector de transiciones
	 */
	vector<pair<int,int> > getTransitions(int id);

	/**\brief Cambia el estado de la FSM
	 * @param debugOn Si esta activado el modo debug o no
	 */
	void setDebug(bool debugOn);

	/**\brief Obtiene si el modo debug esta activo
	 * @return true debug activado
	 */
	bool getDebug();

private:
	/**\brief Estado actual de la FSM
	 */
	int currentState;

	/**\brief Vector de estados posibles de la FSM
	 */
	vector<FSMState> vStates;

	/**\brief Poximo estado a añadir
	 */
	int nState;

	/***\brief Modo debug
	 * Cuando esta activo se muestran las transiciones por consola
	 */
	bool debug;

};

class FSMState{
public:
	/**\brief Constructor vacio
	 */
	FSMState();

	/**\brief Destructor
	 */
	~FSMState();

	/**\brief Constructor de copia
	 * @param fsms Objeto a copiar
	 */
	FSMState(const FSMState &fsms);

	/**\brief Sobrecarga de la igualdad
	 * @param fsms Objeto a copiar
	 * @return Objeto copiado
	 */
	FSMState & operator=(const FSMState &fsms);

	/**\brief Constructor sobrecargado
	 * Obtiene el nombre y el Id del estado.
	 * @param Name Nobre del estado
	 * @param Id Id unico del estado
	 */
	FSMState(string Name, int Id);

	/**\brief Constructor sobrecargado
	 * Obtiene el nombre, el Id del estado y el vector de transiciones.
	 * @param Name Nobre del estado
	 * @param Id Id unico del estado
	 * @param Transitions Vector de transiciones
	 */
	FSMState(string Name, int Id, vector<pair<int,int> > Transitions);

	/**\brief Setter del nombre
	 * @param name Nombre a cambiar
	 */
	void setName(string name);

	/**\brief Setter del id
	 * @param nId Nuevo Id
	 */
	void setId(int nId);

	/**\brief Añade una transición
	 * Añade una transicion al vector de transiciones si el valor de entrada no esta siendo usado por otra transicion
	 * @param input Datos de entrada
	 * @param destination Estado al que se cambia
	 * @return bool true si se ha añadido
	 */
	bool addTransition(int input, int destination);

	/**\brief Elimina la transicion a des
	 * @param des estado destino
	 * @return True si se ha eliminado
	 */
	bool removeTransition(int des);

	/**\brief Obtiene una entrada y devuelve el estado al que se cambia
	 * @param input Valor de entrada
	 * @return int Estado de destino
	 */
	int updateState(int input);

	/**\brief Getter del nombre
	 * @return string Nombre del estado
	 */
	string getName();

	/**\brief Getter del Id
	 * @return int Id del estado
	 */
	int getId();

	/**\brief Getter del vector de transiciones
	 * @return Vector de transiciones
	 */
	vector<pair<int,int> > getTransitions();

private:
	/**\brief Nombre del estado
	 */
	string name;

	/**\brief Id unido del estado
	 */
	int id;

	/**\brief Vector de transiciones
	 */
	vector<pair<int, int> > vTransitions;

};



#endif /* FSM_H_ */
