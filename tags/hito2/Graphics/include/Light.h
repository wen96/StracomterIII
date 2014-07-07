/*
 * Light.h
 *
 *  Created on: 02/02/2012
 *      Author: Chutao Team
 */

#ifndef LIGHT_H_
#define LIGHT_H_

#include "Element.h"
#include "LightManager.h"
#include "Color.h"
#include "Point.h"

/**\class LightManager
 * \brief Clase que gestiona las luces.*/
class LightManager;

/**\class Light
 * \brief Clase que representa las luces de OpenGL.*/
class Light : public Element {

	/**\brief Sobrecarga del operador de salida.
	 * \param os ostrea donde volcar la salida.
	 * \param l Luz a exportar.*/
	friend ostream& operator<<(ostream &os, const Light &l);
public:
	/**\brief Constructor por defecto de Light*/
	Light();
	/**\brief Constructor sobrecargado.
	 * \param amb Luz ambiente.
	 * \param dif Luz difusa.
	 * \param esp Luz especular.
	 * \param pos Posición.*/
	Light(Color<float>, Color<float>, Color<float>, Point);
	/**\brief Constructor sobrecargado.
	 * \param amb Luz ambiente.
	 * \param dif Luz difusa.
	 * \param esp Luz especular.
	 * \param pos Posición.
	 * \param id_ Id de la Luz.*/
	Light(Color<float>, Color<float>, Color<float>, Point, int);
	/**\brief Constructor sobrecargado.
	 * \param id_ Id de la luz.*/
	Light(int);
	/**\brief Constructor de Copia.
	 * \param light_ Luz a copiar.*/
	Light(const Light &);
	/**\brief Sobrecarga del operador de asignación.
	 * \param light_ Luz a copiar.
	 * \return Devuelve una copia del objeto.*/
	Light& operator=(const Light &);
	/**\brief Destructor de luz*/
	virtual ~Light();

	/**\brief Accede al atributo ambiente.
	 * \return Devuelve la luz Ambiente.*/
    Color<float> getAmbiente() const;
    /**\brief Accede al atributo difusa.
	 * \return Devuelve la luz Difusa.*/
    Color<float> getDifusa() const;
    /**\brief Accede al atributo especular.
	 * \return Devuelve la luz Especular.*/
    Color<float> getEspecular() const;
    /**\brief Accede al atributo position.
	 * \return Devuelve la posición de la luz.*/
    Point getPosicion() const;
    /**\brief Accede al atributo id.
	 * \return Devuelve el id de la luz.*/
    int getId() const;
    /**\brief Asigna un nuevo valor a ambiente.
     * \param ambiente_ Nuevo valor de la Luz Ambiente.*/
    void setAmbiente(Color<float> ambiente_);
    /**\brief Asigna un nuevo valor a difusa.
	 * \param difusa_ Nuevo valor de la Luz Difusa.*/
    void setDifusa(Color<float> difusa_);
    /**\brief Asigna un nuevo valor a especular.
	 * \param especular_ Nuevo valor de la Luz Especular.*/
    void setEspecular(Color<float> especular_);
    /**\brief Asigna un nuevo valor a position.
	 * \param posicion_ Nuevo valor de la posición de la luz.*/
    void setPosicion(Point posicion_);
    /**\brief Asigna un nuevo valor al Id.
	 * \param id_ Nuevo valor del Id de la Luz.*/
    void setId(int);
    /**\brief Enciende la luz.*/
    void switchOn();
    /**\brief Apaga la luz.*/
    void switchOff();

    /**\brief Exporta la Luz a OpenGL.*/
    void exportOpenGL();
    /**\brief Exporta la Luz a OpenGL en la GL_LIGHT deseada.
     * \param num_luz Número de luz donde exportarla.*/
    void exportOpenGL(int);
    /**\brief Asigna un valor de luz para exportar a OpenGL.*/
    void setLight(int);
private:
    /**\brief Copia una luz.
     * \param light_ Luz a copiar.*/
    void Copiar(const Light& );
    /**\brief Color de la luz Especular.*/
    Color<float> especular;
    /**\brief Color de la luz Difusa.*/
    Color<float> difusa;
    /**\brief Color de la luz Ambiente.*/
    Color<float> ambiente;
    /**\brief CPosición de la Luz*/
    Point posicion;
    /**\brief Id de la Luz.*/
    int id;
    /**\brief Número de la luz.*/
    int light;
    /**\brief Incica si está activa o no.*/
    bool active;
};

#endif /* LIGHT_H_ */
