/*
 * Text.h
 *
 *  Created on: Feb 9, 2012
 *      Author: Chutaos Team
 */

#ifndef TEXTMANAGER_H_
#define TEXTMANAGER_H_

#include <string>
#include "Element.h"
#include "Point.h"
#include "Color.h"
#include "FTGL/ftgl.h"
#include "ResourceManager.h"
#include "CoreNamespace.h"

using namespace std;

/**\class Text
 * \brief Permite mostrar texto por pantalla
 *
 * Para usar Text se debe hacer lo siguiente:
 * 	Usar el constructor sobrecargado Text(int, Point, Color, double, string),
 * 	o el vacio y usar los setters de Font, Position, Color, Size y Text. Una vez que
 * 	tengamos texto creado tendremos que colgarlo del arbol donde queramos pintarlo
 * 	(posicion en el arbol). El GraphicTree se encarga de llamar a su exportOpenGL
 * 	cuando lo necesita.
 *
 * 	Si no usamos el constructor sobrecargado y no usamos los setters, los valores por defecto son:
 * 		font 		-> NULL
 * 		position 	-> (0,0)
 * 		fontColor 	-> (1,1,1,1)
 * 		fontSIze 	-> 0
 * 		cadena		-> ""
 */
class Text: public Element{
public:
	/**\brief Constructor vacio
	 */
	Text();

	/**\brief Destructor
	 */
	~Text();

	/**\brief Constructor de copia
	 * @param text objeto a copiar
	 */
	Text(const Text &text);

	/**\brief Sobrecarga de la asignación
	 * @param text Objeto a copiar
	 * @return Objeto copiado
	 */
	Text & operator=(const Text &text);

	/**\brief Constructor sobrecargado
	 *
	 * @param fuente Fuente a utilizar
	 * @param pos Posicion donde renderizar
	 * @param color Color del texto
	 * @param size Tamaño del texto
	 * @param texto Cadena a renderizar
	 */
	Text(Graphics::Font::Name fuente, Point pos, Color<float> color, double size, string texto);

	/**\brief Cambia la fuente
	 * Cambia la fuente que esta usando ahroa mismo por fuente
	 * @param fuente letra que pasara a usar
	 * @return bool si es una fuente correcta (!= NULL)
	 */
	bool setFont(FTGLTextureFont *fuente);

	bool setFont(Graphics::Font::Name fuente);

	/**\brief Setter del texto a escribir
	 * @param cadena texto que se mostrará por pantalla
	 */
	void setText(string cadena);

	/**\brief Cambia el tamaño de la fuente
	 * @param size Nuevo tamaño de letra
	 * @return bool true si es un tamaño valido ( > 0 )
	 */
	bool setSize(double size);

	/**\brief Cambia el color
	 * @param color Nuevo color
	 */
	void setColor(Color<float> color);

	/**\brief Cambia la posicion del texto
	 * @param pos Nueva posicion
	 */
	void setPosition(Point pos);

	/**\brief Pinta texto por pantalla
	 * @param cadena 	Texto a pintar
	 * @param pos		Posición donde pintarlo
	 * @param size		Tamaño del texto
	 * @param color		Color del texto
	 */
	void renderText(string cadena, Point pos, float size, Color<float> color);

	/**\brief Pinta texto por pantalla
	 * Pinta el texto en la posicion pos con el color y tamaño puestos anteriormente
	 * @param cadena 	Texto a pintar
	 * @param pos		Posicion donde pintarlo
	 */
	void renderText(string cadena, Point pos);

	/**\brief Pinta texto por pantalla
	 * Pinta el string cadena en la posicion (0,0), con el color y tamaño puestos anteriormente
	 * @param cadena 	Texto a pintar
	 */
	void renderText(string cadena);

	/**\brief Hace lo necesario para pintar cadena en la pantalla
	 */
	void exportOpenGL();

	/**\brief Getter de la fuente
	 * @return Fuente que se esta usando actualmente
	 */
    FTGLTextureFont *getFont() const;

    /**\brief Getter del color
     * @return Color actual
     */
    Color<float> getColor() const;

    /**\brief Getter del tamaño
     * @return tamaño actual
     */
    double getSize() const;

    /**\brief Getter de la posicion
     * @return Posicion del texto
     */
    Point getPosition() const;

    /**\brief Getter del texto a mostrar por pantalla
     * @return texto que se va a mostrar por pantalla
     */
    string getText() const;

private:
    /**\brief Fuente que se esta usando
     * Puntero a un FTGLTextureFont, que es el tipo de renderizado que usamos para las fuentes (por texturas)
     */
    FTGLTextureFont *font;

    Graphics::Font::Name fontName;

    /**\brief Tamaño de la fuente
     */
    double fontSize;

    /**\brief Color de la fuente
     */
    Color<float> fontColor;

    /**\brief Posicion del texto
     */
    Point posicion;

    /**\brief texto a renderizar
     */
    string cadena;
};


#endif /* TEXTMANAGER_H_ */
