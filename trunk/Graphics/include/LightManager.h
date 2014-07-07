/*
 * LightManager.h
 *
 *  Created on: 02/02/2012
 *      Author: Chutaos Team
 */

#ifndef LIGHTMANAGER_H_
#define LIGHTMANAGER_H_

#include <iostream>
#include <vector>
#include "Color.h"
#include "Point.h"
#include "Light.h"

using namespace std;

/**\class Light
 * \brief Clase que representa las luces de OpenGL.*/
class Light;

/**\class LightManager
 * \brief Clase que gestiona las luces.*/
class LightManager {
	/**\brief Sobrecarga del operador de salida.
	 * \param os ostrea donde volcar la salida.
	 * \param m Gestor de luces a exportar.*/
	friend ostream& operator<<(ostream &os, const LightManager &m);
public:
	/**\brief Constructor por defecto.*/
	LightManager();
	/**\brief Destructor.*/
	virtual ~LightManager();
	/**\brief Añade una luz por defecto al Gestor.
	 * \return Devuelve el identificador de la luz.*/
	int addLight();
	/**\brief Añade una luz al Gestor.
	 * \param amb Luz ambiente.
	 * \param dif Luz difusa.
	 * \param esp Luz especular.
	 * \param pos Posición.
	 * \return Devuelve el identificador de la luz.*/
	int addLight(Color<float> amb, Color<float> dif, Color<float> esp, Point pos);
	/**\brief Indica si una luz está activa o no.
	 * \param luz Número de la luz a consultar.
	 * \return Devuelve true si está activada y false en caso contraria.*/
	bool isActive(int);
	/**\brief Elimina una luz del gestor.
	 * \param id_ Número de la luz a eliminar.*/
	void deleteLight(int);
	/**\brief Accede a una luz por si Id.
	 * \param num_luz Número de la luz.
	 * \return Devuelve un puntero a dicha luz.*/
	Light* getLight(int);
	/**\brief Exporta a OpenGL las luces activas.*/
	void exportOpenGL();
	/**\brief Exporta a OpenGL las luces idicadas.
	 * \param luz0 Luz a exportar en GL_LIGHT0.
	 * \param luz1 Luz a exportar en GL_LIGHT1.
	 * \param luz2 Luz a exportar en GL_LIGHT2.
	 * \param luz3 Luz a exportar en GL_LIGHT3.
	 * \param luz4 Luz a exportar en GL_LIGHT4.
	 * \param luz5 Luz a exportar en GL_LIGHT5.
	 * \param luz6 Luz a exportar en GL_LIGHT6.
	 * \param luz7 Luz a exportar en GL_LIGHT7.*/
	void exportOpenGL(int,int,int,int,int,int,int,int);
	/**\brief Exporta a OpenGL las luces idicadas.
	 * \param luz vector con las luces a exportar.*/
	void exportOpenGL(vector<int>);
	/**\brief Exporta a OpenGL la luz idicada.
	 * \param luz Id de la luz.*/
	void exportOpenGL(int);
	/**\brief Exporta a OpenGL la luz idicada en la posición indicada.
	 * \param luz Id de la luz.
	 * \param pos Posición en OpenGL GL_LIGHTpos.*/
	void exportOpenGL(int, int);
	/**\brief Enciende una luz.
	 * \param luz Id de la luz.*/
	void switchOn(int);
	/**\brief Apaga una luz.
	 * \param luz Id de la luz.*/
	void switchOff(int);
	/**\brief Selecciona una luz.
	 * \param id_ Id de la luz.
	 * \param light_ posición de la luz.*/
	void selectLight(int, int);
private:
	/**\brief Vector de luces.*/
	vector<Light*> luces;
	/**\brief Vector de luces asignadas.*/
	vector<int> asignadas;
	/**\brief Vector de luces activas.*/
	vector<bool> activas;
	/**\brief Siguiente Id a asginar.*/
	int id;
	/**\brief Luz de error, para cuando no se puede devolver una luz.*/
	Light *error;
};

#endif /* LIGHTMANAGER_H_ */
