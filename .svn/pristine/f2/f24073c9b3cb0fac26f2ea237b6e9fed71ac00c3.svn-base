/*
 * TPicture.h
 *
 *  Created on: 14/03/2012
 *      Author: gallardo
 */

#ifndef TPICTURE_H_
#define TPICTURE_H_

#include "TWidget.h"
#include "Textura.h"
/**\class TPicture
 * \brief Clase que representa una imagen para los formularios.*/
class TPicture : public TWidget {
public:
	/**\brief Constructor por defecto.*/
	TPicture();
	/**\brief Constructor sobrecargado.
	 * \param p Posición de la imagen.
	 * \param w Ancho de la imagen.
	 * \param h Alto de la imgen.
	 * \param i Ruta de la imagen.
	 */
	TPicture(Point, int, int, string);
	/**\brief Constructor de Copia.
	 * \param p Objeto a copiar.*/
	TPicture(const TPicture&);
	/**\brief Destructor.*/
	virtual ~TPicture();
	/**\brief Sobrecarga del operador de asignación.
	 * \param p Objeto a copiar.
	 * \return Devuelve una copia del objeto.*/
	TPicture& operator=(const TPicture &);
	/**\brief Creamos el body de la imagen.
	 * \param w mundo donde crear el body.*/
	void setBody(World* w);
	/**\brief Dibuja la imagen.*/
	void Draw();
    int getHeight() const;
    int getIdImage() const;
    string getImage() const;
    Point getPosition() const;
    int getWidth() const;
    void setHeight(int height);
    void setIdImage(int idImage);
    void setImage(string image);
    void setPosition(Point position);
    void setWidth(int width);
private:
	/**\brief Inicializa los valores de la clase.*/
	void Destructor();
	/**\brief Copia un Objeto.
	 * \param p Objeto a copiar.*/
	void Copiar(const TPicture &);
	/**\brief Posición de la imagen.*/
	Point position;
	/**\brief Ancho de la imagen.*/
	int width;
	/**\brief Alto de la imagen.*/
	int height;
	/**\brief Ruta de la imagen.*/
	string image;
	/**\brief Id de textura de la imagen.*/
	int idImage;
};

#endif /* TPICTURE_H_ */
