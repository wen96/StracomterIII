/*
 * TConsole.h
 *
 *  Created on: Feb 6, 2012
 *      Author: Chutaos Team
 */

#ifndef TCONSOLE_H_
#define TCONSOLE_H_

using namespace std;
#include <vector>
#include <SFML/Graphics.hpp>
#include "CoreNamespace.h"
#include "GraphicsNamespace.h"
#include "IOControl.h"
#include "Scene.h"
#include "Text.h"
#include "SceneManager.h"
#include "Shape.h"

/**\class TConsole
 * Controla la consola del juego
 */
class TConsole{
public:

	/**\brief Constructor sobrecargado
	 * @param visibleLines Numero de lineas visibles
	 * @param io Gestor de I/O
	 */
	TConsole(int visibleLines, IOControl *io);

	/**\brief Destructor
	 */
	~TConsole();

	/**\brief Inicializa la consola
	 */
	void Init();

	/**\brief Obtiene el primer comando de la cola
	 * Se usa para ir obteniendo los comandos introducidos
	 * @return Primer comando
	 */
	vector<string> getCommand();

	/**\brief Obtiene todos los comando acumulados
	 * @return Lista de comandos
	 */
	vector<vector<string> > getCommandQueue();

	/**\brief Obtiene la linea actual
	 * @return String con la linea
	 */
	string getCurrLine();

	/**\brief Obtiene las lineas anteriores
	 * @return vector de strings
	 */
	vector<string> getPrevLines();

	/**\brief Hace una pasada por la E/S y captura los eventos
	 * @return Estado al que se cambia (o no)
	 */
	int getInput();

	/**\brief Muestra si esta abierta o cerrada
	 * @return true si esta abierta
	 */
	bool getStatus();

	/**\brief Abre la consola
	 */
	void Open();

	/**\brief Cierra la consola
	 */
	void Close();

	/**\brief Devuelve el numero maximo de lineas
	 * @return Maximas lineas
	 */
	int getMaxLines();

	/**\brief Pinta la consola en el motor 2D
	 */
	void Render();

	/**\brief Establece el puntero a la escena
	 * @param scene
	 */
	void setScene(Scene *scene);

private:
	/**\brief Lista de comandos
	 */
    vector<vector<string> > commandQueue;

    /**\brief Linea actual
     */
    string currLine;

    /**\brief Linea que se muestra
     * Se usa para tener el cursor, pero no modificar el comando
     */
    string displayLine;

    /**\brief Lineas previas
     */
	vector<string> prevLines;

	/**\brief Indice de en que linea previa estamos
	 */
	unsigned int prevLineIndex;

	/**\brief Posicion dentro de la cadena del cursor
	 */
	unsigned int cursorPos;

	/**\brief Flag de consola abierta
	 */
	bool open;

	/**\brief Maximo de lineas
	 */
	unsigned int maxLines;

	/**\brief COntrol de E/S
	 */
	IOControl *ioCont;

	/**\brief Escena 2D
	 */
	Scene *escena;

	/**\brief Escena 3D
	 */
	SceneManager *sManager;

	/**\brief Nodo 3D del que cuelga la consola
	 */
	GraphicNode * treeBranch;

	/**\brief Vector de punteros a Text
	 * Son los Text que se muestran en el motor 3D
	 */
	vector<Text *> textManager;

	/**\brief Fondo de la consola
	 */
	Shape *shBox;

	/**\brief DIvide una cadena por el caracter c
	 * @param cadena Cadena a cortar
	 * @param c Caracter por el que cortar
	 * @return Vector de strings con los resultados
	 */
	vector<string> split(string cadena, char c);

	/**\brief Actualiza los nodos del arbol cuando se modifica el texto
	 */
	void updateTextNodes();
};


#endif /* TCONSOLE_H_ */
