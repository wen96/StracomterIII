/*
 * Textura.h
 *
 *  Created on: 05/03/2012
 *      Author: gallardo
 */

#ifndef TEXTURE_H_
#define TEXTURE_H_

#include <iostream>
#include <GL/gl.h>
#include <GL/glu.h>
#include "loadjpeg.h"
using namespace std;

/**\class Textura
 * \brief Clase para incluir texturas.*/
class Textura {
public:
	/**\brief Permite activar una textura.
	 * \param id Id de la textura a activar*/
	static void ActivarTextura(unsigned int id);
	/**\brief Permite desactivar las texturas.*/
	static void DesactivarTextura();

	/**\brief Constructor por defecto.*/
	Textura();
	/**\brief Constructor sobrecargado.
	 * \param ruta_ Ruta hasta la textura.
	 * \param name_ id de la textura.*/
	Textura(string ruta_, int name_ = -1);
	/**\brief Destructor de la textura.*/
	virtual ~Textura();
	/**\brief Constructor de copia.
	 * \param t Textura a copiar.*/
	Textura(const Textura&);
	/**\brief Sobrecarga del operador de asignación.
	 * \param t Textura a copiar.
	 * \return Textura copiada.*/
	Textura & operator=(const Textura &);

	/**\brief Accede al atributo privado height.
	 * \return Devuelve la altura de la textura.*/
    int getHeight() const;
    /**\brief Accede al atributo privado ruta.
	 * \return Devuelve la ruta de la textura.*/
    string getRuta() const;
    /**\brief Accede al atributo privado width.
	 * \return Devuelve la anchura de la textura.*/
    int getWidth() const;
    /**\brief Asigna un nuveo valor al atributo privado height.
	 * \param height nueva altura de la textura.*/
    void setHeight(int height);
    /**\brief Asigna un nuveo valor al atributo privado ruta.
	 * \param ruta nueva ruta de la textura.*/
    void setRuta(string ruta);
    /**\brief Asigna un nuveo valor al atributo privado width.
	 * \param width nueva anchura de la textura.*/
    void setWidth(int width);
    /**\brief Genera la textura.*/
    void generateTexture();
    /**\brief Devuelve el id de la textura.
     * \return Devuelve el identificador de la textura.*/
    unsigned int getTexture() const;
    /**\brief Asigna un nuevo valor al id de la textura.
     * \param id Nuevo valor de la textura.*/
    void setTexture(unsigned int id);
    /**\brief Activa la textura actual.*/
    void Activar();
    /**\brief Activa la textura indicada.
     * \param textura_ Id de la textura a activar.*/
    void Activar(unsigned int textura_);
    /**\brief Desactiva las texturas.*/
    void Desactivar();
private:
    /**\brief Inicializa los valores de la textura.*/
    void Destructor();
    /**\brief Copia un objeto textura.
     * \para t Textura a copiar.*/
    void Copiar(const Textura &t);
    /**\brief Anchura de la Textura.*/
	int width;
	 /**\brief Altura de la Textura.*/
	int height;
	 /**\brief Id de la Textura.*/
	unsigned int texture;
	 /**\brief Ruta de la Textura.*/
	string ruta;
};

#endif /* TEXTURE_H_ */
