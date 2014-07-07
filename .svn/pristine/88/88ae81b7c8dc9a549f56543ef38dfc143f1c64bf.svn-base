/*
 * Material.h
 *
 *  Created on: 26/02/2012
 *      Author: Chutaos Team
 */

#ifndef MATERIAL_H_
#define MATERIAL_H_

#include <iostream>
#include <GL/gl.h>
#include "Color.h"

using namespace std;

/**\class Material
 * Define los materiales de un objeto segun OpenGL*/
class Material {

public:
	static void resetMaterial();
	/**\brief Constructor por defecto*/
	Material();
	/**\brief Desstructor por defecto*/
	virtual ~Material();
	/**\brief Constructor de copia
	 *\param material - Material a copiar*/
	Material(const Material &material);
	/**\brief Operador de igualdad
	 *\param material - Material a asignar
	 *\return this - elemento asignado*/
	Material& operator=(const Material &material);
	/**\brief Obtener atributo: valor de rojo de la luz ambiente
	 *\return ambiente[0] */

    /**\brief Obtener atributo: Color de luz ambiente
     *\return ambiente*/
    Color<float> getAmbiente() const;
    /**\brief Asigna valores de ambiente con un float[4] RGBA
     *\param ambiente - nuevos valores de ambiente*/
    void setAmbiente(Color<float> ambiente);
    /**\brief Asigna valores de ambiente con un 4 floats RGBA
     *\param r - valor de ambiente[0]
     *\param g - valor de ambiente[1]
     *\param b - valor de ambiente[2]
     *\param a - valor de ambiente[3]*/
    void setAmbiente(float r,float g,float b,float a=1.0);

    /**\brief Obtener atributo: Color de luz difusa
     *\return difusa*/
    Color<float> getDifusa() const;
    /**\brief Asigna valores de difusa con un float[4] RGBA
     *\param difusa - nuevos valores de difusa*/
    void setDifusa(Color<float> difusa);
    /**\brief Asigna valores de difusa con un 4 floats RGBA
     *\param r - valor de difusa[0]
     *\param g - valor de difusa[1]
     *\param b - valor de difusa[2]
     *\param a - valor de difusa[3]*/
    void setDifusa(float r,float g,float b,float a=1.0);

    /**\brief Obtener atributo: Color de luz especular
     *\return especular*/
    Color<float> getEspecular() const;
    /**\brief Asigna valores de especular con un float[4] RGBA
     *\param especular - nuevos valores de especular*/
    void setEspecular(Color<float> especular);
    /**\brief Asigna valores de especular con un 4 floats RGBA
     *\param r - valor de especular[0]
     *\param g - valor de especular[1]
     *\param b - valor de especular[2]
     *\param a - valor de especular[3]*/
    void setEspecular(float r,float g,float b,float a=1.0);

    /**\brief Obtener atributo: Color de luz brillo
     *\return brillo*/
    float getBrillo() const;
    /**\brief Asigna valores de brillo con un float[4] RGBA
    *\param brillo - nuevos valores de brillo*/
    void setBrillo(float brillo);
    /**\brief Asigna valores de brillo con un 4 floats RGBA
     *\param r - valor de brillo[0]
     *\param g - valor de brillo[1]
     *\param b - valor de brillo[2]
     *\param a - valor de brillo[3]*/


    /**\brief exportOpenGL
     * Funcion encargada de traducir los valores de a clase a OpenGL*/
    void exportOpenGL() const;
    /**\brief Desactivar
     * Funcion que desactiva los menus*/
    void Desactivar() const;

private:
    /**\brief color ambiente*/
    Color<float> ambiente;
    /**\brief color difuso*/
    Color<float> difusa;
    /**\brief color especular*/
    Color<float> especular;
    /**\brief intensidad de brillo*/
    float brillo;

};
#endif /* MATERIAL_H_ */
