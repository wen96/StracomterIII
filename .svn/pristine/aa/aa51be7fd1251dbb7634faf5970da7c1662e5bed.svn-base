/*
 * GameMenu.h
 *
 *  Created on: 26/12/2011
 *      Author: Chutaos Team
 */

#ifndef GAMEMENU_H_
#define GAMEMENU_H_

#include "Element.h"
#include "GraphicsNamespace.h"
#include "TForm.h"
#include "HIDControl.h"
#include "TPicture.h"


/**\class GameMenu
 * Es la clase encargada del control de menus a lo largo del juego
 * tanto en el modo accion como en el estrategia, asi como cuando
 * ninguno de ellos esta funcionando.
 * Herencia: hereda de Element para poder ser pintado por el arbol*/
class GameMenu: public Element{
public:
	/**\brief Constructor por defecto.*/
	GameMenu(HIDControl *hid_);
	/**\brief Destructor por defecto.*/
	virtual ~GameMenu();
	/**\brief Inicializador de componentes.
	 * Necesario ejecutar antes de hacer update y render*/
	void StartUp();
	/**\brief Devuelve un enumerado con el menu
	 * que se encuentra visible
	 *\return atributo visible*/
    Graphics::Menus::Index getVisible() const;
	/**\brief Asigna el menu visible
	 *\param visible - nuevo menu visible*/
    void setVisible(Graphics::Menus::Index visible);
	/**\brief Añade un nuevo menu al vector menus
	 *\param index - posicion del vector donde va el menu
	 *\param menu - nuevo menu*/
	void addMenu(Graphics::Menus::Index index, TForm *menu);
	/**\brief Exporta el menu a OpenGL.****
	 * FUNCION EN DESUSO, UTILIZAR FUNCION RENDER PARA PINTAR*/
	void exportOpenGL();
	/** Bucle encargado de analizar y controlar cambios y eventos en el menu activo
	 *\return entero con el estado en que ha terminado*/
	int Update();
	/**\brief Funcion encargada de pintar el menu visible*/
	void Render();
	/**\brief obetener el vector de menus
	 *\return menus - vector de menus*/
    vector<TForm*> getMenus() const;
	/**\brief Añade un nuevo vector de menus
	 *\param menus - nuevo vector de menus*/
    void setMenus(vector<TForm*> menus);
private:
    /**
     * Vector de formularios que contiene los menus
     */
	vector<TForm*> menus;
    /**
     * Enumerado para controlar que menu esta visible
     */
    Graphics::Menus::Index visible;
    /**
     * Enumerado para controlar que controlador ejecutar
     */
    Core::GameMode::Mode currentMode;
    /**
     * HID para control de eventos de menu
     */
    HIDControl *hid;
};

#endif /* GAMEMENU_H_ */
