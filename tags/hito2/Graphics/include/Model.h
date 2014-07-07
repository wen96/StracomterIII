/*
 * Model.h
 *
 *  Created on: 15/02/2012
 *      Author: Chutaos Team
 */

#ifndef _MODEL_H_
#define _MODEL_H_

#include "Element.h"
#include "CoreNamespace.h"
#include <GL/gl.h>
#include <iostream>
#include <cstdlib>
#include "Textura.h"
#include "load3ds.h"
#include "Color.h"
#include "Material.h"
using namespace std;

/**\class Model
 * \brief Clase para cargar modelos.*/
class Model : public Element {
public:
	/**\brief Constructor por defecto.*/
	Model();
	/**\brief Constructor sobrecargado.
	 * \param ruta_ Indica la ruta hasta el modelo 3ds
	 * \param id_ Id del modelo.*/
	Model(string, int);
	/**\brief Constructor sobrecargado.
	 * \param ruta_ Indica la ruta hasta el modelo 3ds
	 * \param id_ Id del modelo.
	 * \param textura_ Textura del modelo.*/
	Model(string, int, Textura);
	/**\brief Constructor de Copia.
	 * \param m Modelo a copiar.*/
	Model(const Model&);
	/**\brief Sobrecarga del operador de asignación.
	 * \param m Modelo a copiar.
	 * \return modelo copiado.*/
	Model& operator=(const Model&);
	/**\brief Destructor.*/
	virtual ~Model();
	/**\brief Devuelve los puntos del modelo.
	 * \return Devuelve los puntos del modelo.*/
    float *getPuntos() const;
    /**\brief Indica el número de vértices del modelo.
     * \return Número de vértices del modelo.*/
    int getVertices() const;
    /**\brief Devuelve el id de la DisplayList.
     * \return id de la DisplayList.*/
    int getCall() const;
    /**\brief Devuelve el color.
     * \return Devuelve el color del modelo.*/
    Color<float> getColor() const;
    /**\brief Permite actualizar los puntos del modelo.
     * \param puntos_ Nuevos puntos del modelo.*/
    void setPuntos(float *puntos_);
    /**\brief Permite actualizar el número de vértices del modelo.
     * \param vertices_ Número de vértices.*/
    void setVertices(int vertices_);
    /**\brief Permite cambiar el número de displayList del modelo.
     * \param id_ Nuevo id de displayList.*/
    void setCall(int id_);
    /**\brief Permite cambiar el color del modelo.
	* \param color_ Nuevo color del modelo.*/
    void setColor(Color<float>);
    /**\brief Crea la DisplayList*/
    void createDisplayList();
    /**\brief Crea la DisplayList en el valor indicado.
     * \param id_ Id de la DisplayList.*/
    void createDisplayList(int);
    /**\brief Exporta el modelo a OpenGL.*/
    void exportOpenGL();
    /**\brief Permite cambiar la textura.
     * \param textura_ Nuevo valor de la textura.*/
    void setTexture(Textura);
    /**\brief Indica la textura del modelo.
     * \return Devuelve  la textura del modelo.*/
    Textura* getTextura() const;

    /**\brief Permite cambiar el Material del modelo.
     * \param m Nuevo Material.*/
    void setMaterial(Material);
    /**\brief Indica el material del modelo.
	 * \return Devuelve el material del modelo.*/
    Material getMaterial();

    /**\brief Activa o deaciva el material.
     * \param m indica si se quiere activar el material.*/
    void activeMaterial(bool);
private:
    /**\brief Inicializa los valores del modelo.*/
    void Destructor();
    /**\brief Puntos del modelo.*/
	float *puntos;
	/**\brief Número de puntos del modelo.*/
	int n_vertices;
	/**\brief Id de Display del modelo.*/
	int id;
	/**\brief Ruta del modelo.*/
	string ruta;
	/**\brief Color del modelo.*/
	Color<float> color;
	/**\brief Textura del modelo.*/
	Textura *textura;
	/**\brief Material del modelo.*/
	Material material;
	/**\brief Indica si el Maerial está activo en el modelo.*/
	bool materialActive;
};

#endif /* MODEL_H_ */
