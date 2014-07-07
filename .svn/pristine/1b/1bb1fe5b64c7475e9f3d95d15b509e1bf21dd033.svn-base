/*
 * SceneManager.h
 *
 *  Created on: 10/02/2012
 *      Author: Chutaos Team.
 */

#ifndef SCENEMANAGER_H_
#define SCENEMANAGER_H_

#include <vector>
#include "GraphicTree.h"
#include "Color.h"
#include "EntityManager.h"
#include "MotorGrafico.h"
#include "Entity.h"
#include "ResourceManager.h"
#include "Polygon.h"
#include "Transformacion.h"
#include "GraphicsNamespace.h"
#include "CoreNamespace.h"
#include "TPicture.h"

class SceneManager {
public:
	/**\brief Crea la unica instancia de SceneManager
	 *	Comprueba que no exista ninguna instancia de SceneManager, si la hay devuelve un puntero,
	 *	 si no la crea y devuelve el puntero.
	 *\return Un puntero a la instancia de SceneManager
	 */
	static SceneManager* getInstance();
	/**\brief Crea la unica instancia de SceneManager
	 * CON UN ARBOL POR PARAMETRO
	 *	Comprueba que no exista ninguna instancia de SceneManager, si la hay devuelve un puntero,
	 *	 si no la crea y devuelve el puntero.
	 *\param scene - arbol con el que crear la escena
	 *\return Un puntero a la instancia de SceneManager
	 */
	static SceneManager* getInstance(GraphicTree* scene);

	/**\brief Destructor por defecto*/
	virtual ~SceneManager();
	/**\brief Obtiene el arbol de la escena
	 * \return scene - arbol del la escena*/
    GraphicTree* getScene() const;
	/**\brief Asigna el arbol de la escena
	 * \param scene - arbol del la escena*/
    void setScene(GraphicTree* scene);
	/**\brief Pinta la escena*/
    void DrawScene();
	/**\brief Inicializa los valores de OpenGL para la escena
	 * NECESARIO ANTES DE PINTAR*/
    void InitializeScene();
	/**\brief Obtiene el modo de la escena
	 * \return modo - modo de la escena*/
    Graphics::ModeRender::Mode getMode() const;
	/**\brief Obtiene si esta activo el culling de la escena
	 * \return culling - culling de la escena*/
    bool isCulling() const;
	/**\brief Obtiene si esta activo el smooth de la escena
	 * \return smooth - smooth de la escena*/
    bool isSmooth() const;
	/**\brief Obtiene si esta activo el zbuffer de la escena
	 * \return zbuffer - zbuffer de la escena*/
    bool isZbuffer() const;
	/**\brief Obtiene si esta activo el lighting de la escena
	 * \return linghting - linghting de la escena*/
    bool isLighting() const;
	/**\brief Asigna si esta activo el culling de la escena
	 * \param culling - culling de la escena*/
    void setCulling(bool culling);
	/**\brief Asigna el modo de la escena
	 * \param mode - modo de la escena*/
    void setMode(Graphics::ModeRender::Mode mode);
	/**\brief Asigna si esta activo el smooth de la escena
	 * \param smooth - smooth de la escena*/
    void setSmooth(bool smooth);
	/**\brief Asigna si esta activo el zbuffer de la escena
	 * \param zbuffer - zbuffer de la escena*/
    void setZbuffer(bool zbuffer);
	/**\brief Asigna si esta activo el lighting de la escena
	 * \param l - linghting de la escena*/
    void setLighting(bool l);
	/**\brief Obtiene la luz ambient de la escena
	 * \return luzAmbiente - luz ambiente de la escena*/
    Color<float> getLuzAmbiente() const;
	/**\brief Asigna la luz ambiente de la escena
	 * \param luzAmbiente - luz ambiente de la escena*/
    void setLuzAmbiente(Color<float> luzAmbiente);
    /**\brief Carga en el arbol las entidades del EntityManager
     * \param em - EntityManager a leer
   	 * \param raiz -  de donde colgar toda la rama*/
    void loadTree(EntityManager* em,Element* raiz);
    /**\brief Carga elementos de un elemento raiz
     * \param vec - vector de elementos a cargar
   	 * \param raiz -  de donde colgar toda la rama*/
    void addElement(vector<Element*> vec,Element* raiz);
    /**\brief Carga elemento de un elemento raiz (elemento)
     * \param elem - elemento a cargar
   	 * \param raiz -  de donde colgar toda la rama*/
    void addCharacter(Element* elem,Element* raiz);
    /**\brief Carga elemento de un elemento raiz(nodo)
     * \param elem - elemento a cargar
   	 * \param raiz -  de donde colgar toda la rama*/
    void addCharacter(Element* elem,GraphicNode* raiz);
    /**\brief Carga elemento de un elemento raiz(elemento)
     * \param elem - elemento a cargar
   	 * \param raiz -  de donde colgar toda la rama*/
    void addElement(Element* elem,Element* raiz = NULL);
    /**\brief Carga elemento de un elemento raiz(nodo)
     * \param elem - elemento a cargar
   	 * \param raiz -  de donde colgar toda la rama*/
    void addElement(Element* elem,GraphicNode* raiz);
    /**\brief Elemina elemento (elemento)
     * \param elem - elemento a borrar*/
    void removeElement(Element* elem);
    /**\brief Elemina elemento
     * \param elem - elemento a borrar*/
    void removeCharacter(Element* elem);
    /**\brief Elemina elemento (nodo)
     * \param elem - elemento a borrar*/
    void removeElement(GraphicNode* elem);
    /**\brief Inicializa el arbol
     * \param elem - elemento raiz*/
    void initTree(Element *elem);

	/**\brief Obtiene vector de punteros directos
	 * \return directNodes -  nodos directos*/
    vector<GraphicNode*> getDirectNodes() const;
	/**\brief Asignar vector de punteros directos
	 * \param directNodes -  nodos directos*/
    void setDirectNodes(vector<GraphicNode*> directNodes);
	/**\brief Añada nodo al vector de punteros directos
	 * \param node - nuevo nodo directo*/
    void addDirectNodes(GraphicNode* node);
	/**\brief Obtiene el nodo del vector de punteros directos (Stratree)
	 * \param index - indice del nodo directo
	 * \return nodo -  nodo al que apunta el directNode*/
    GraphicNode* getNode(Graphics::DirectNodes::Index);
	/**\brief Obtiene el nodo del vector de punteros directos (Menutree)
	 * \param index - indice del nodo directo
	 * \return nodo -  nodo al que apunta el directNode*/
    GraphicNode* getNode(Graphics::DirectNodesMenu::Index);

	/**\brief Crear el arbol Stratree*/
    void makeStracomterTree();
    /**\brief Borrar el arbol Stratree*/
    void removeStracomterTree();
    /**\brief Crear el arbol Menutree*/
    void makeMenuTree();
    /**\brief Borrar el arbol Menutree*/
    void removeMenuTree();
private:
    /**\brief Constructor por defecto*/
    SceneManager();
    /**\brief Constructor
     *\param scene - arbol con de la escena*/
    SceneManager(GraphicTree *scene);
    /**\brief SceneManager*/
    static SceneManager *_sm;
    /**\brief Arbol de la escena (menutree y stratree)*/
    GraphicTree *scene;
    /**\brief Vetor de punteros directos*/
    vector<GraphicNode*> directNodes;
    /**\brief Luz ambiente de la escena*/
    Color<float> luzAmbiente;
    /**\brief Modo activado: zbuffer*/
    bool zbuffer;
    /**\brief Modo activado: culling*/
    bool culling;
    /**\brief Modo activado: smooth*/
    bool smooth;
    /**\brief Modo activado: lighting*/
    bool lighting;
    /**\brief Modo de renderizado: poligono, alambrico o puntos*/
    Graphics::ModeRender::Mode mode;
    /**\brief Typo de arbol: Stratree o Menutree*/
    Graphics::StracomerTrees::Type tree;
};

#endif /* SCENEMANAGER_H_ */
