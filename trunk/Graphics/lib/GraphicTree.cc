/*
 * GraphicTree.cpp
 *
 *  Created on: 19/01/2012
 *      Author: Chutaos Team
 */

#include "GraphicTree.h"
#include "Aplication.h"

GraphicNode::GraphicNode() {
	item = new Element();
	id = -1;
	visible = false;
}

GraphicNode::GraphicNode(Element *element, int id_) {
	item = element;
	id = id_;
	visible = true;
}

GraphicNode::~GraphicNode() {
	GraphicTree *aux;
	if (item != NULL) {
		//delete item;
		item = NULL;
	}
	while (!hijos.empty()) {
		aux = hijos[0];
		hijos.erase(hijos.begin());

		if (aux != NULL) {
			delete aux;
			aux = NULL;
		}
	}
	id = -1;
	visible = false;
	/*for(unsigned int i=0; i<hijos.size(); i++)
	 {
	 if(hijos[i]!=NULL)
	 {
	 delete hijos[i];
	 hijos[i]=NULL;
	 }
	 }
	 hijos.clear();*/
}

GraphicNode::GraphicNode(const GraphicNode & node) {
	//item= new Element(*node.item);//Borrar en arreglar lo comentado de abajo.
	/*switch (node.item->getElementType())
	 {
	 case Core::Element::e_camera:
	 item= new Camera(*(Camera*)node.item);
	 break;
	 case Core::Element::e_light:
	 item= new Light(*(Light*)node.item);
	 break;
	 case Core::Element::e_transform:
	 item= new Transform(*(Transform*)node.item);
	 break;
	 case Core::Element::e_entity:
	 //	CREAR SWITCH PARA IDENTIFICAR QUE TIPO DE ENTIDAD ES.
	 //item= new Entity(*(Entity*)node.item);
	 switch(((Entity*)node.item)->getType()) {
	 case Core::Entities::e_captain:
	 break;
	 case Core::Entities::e_enemy1:
	 case Core::Entities::e_enemy2:
	 case Core::Entities::e_enemy3:
	 //TODO item= new Bot(*(Bot*)node.item);
	 break;
	 //case Core::Entities::e_columne

	 }
	 break;
	 default:
	 cerr << "Warning: Element con tipo none no copiado" << endl;
	 break;
	 }*/
	item = node.item;

	for (unsigned int i = 0; i < node.hijos.size(); i++) {
		hijos.push_back(new GraphicTree(*hijos[i]));
	}
}

int GraphicNode::getId() const {
	return id;
}

bool GraphicNode::getVisible() const {
	return visible;
}

void GraphicNode::setId(int id_) {
	id = id_;
}

void GraphicNode::setVisible(bool visible_) {
	visible = visible_;
}

GraphicNode & GraphicNode::operator =(const GraphicNode & node) {
	if (this != &node) {
		//this->~GraphicNode();
		GraphicTree *aux;
		if (item != NULL) {
			//delete item;
			item = NULL;
		}
		while (!hijos.empty()) {
			aux = hijos[0];
			hijos.erase(hijos.begin());

			if (aux != NULL) {
				delete aux;
				aux = NULL;
			}
		}
		/*if(item!=NULL)
		 delete item;*/
		//item= new Element(*node.item);
		item = node.item;
		/*if(!hijos.empty())
		 {
		 for(unsigned int i=0; i<hijos.size(); i++)
		 {
		 if(hijos[i]!=NULL)
		 {
		 delete hijos[i];
		 hijos[i]=NULL;
		 }
		 }
		 hijos.clear();
		 }*/
		for (unsigned int i = 0; i < node.hijos.size(); i++) {
			hijos.push_back(new GraphicTree(*hijos[i]));
		}
	}
	return *this;
}

GraphicTree::GraphicTree() {
	raiz = NULL;
}

GraphicTree::~GraphicTree() {
	if (raiz != NULL) {
		delete raiz;
		raiz = NULL;
	}
}

GraphicTree::GraphicTree(const GraphicTree & tree) {
	if (tree.raiz != NULL) {
		/*GraphicNode *aux = new GraphicNode();
		 aux->item = new Element(*tree.raiz->item); //Cambiado de aux->item = tree.raiz->item;
		 raiz=aux;
		 aux=NULL;*/
		raiz = new GraphicNode(new Element(*tree.raiz->item));

		for (unsigned int i = 0; i < tree.raiz->hijos.size(); i++) {
			raiz->hijos.push_back(new GraphicTree(*tree.raiz->hijos[i]));
		}
	}
}

GraphicTree & GraphicTree::operator=(const GraphicTree & tree) {
	if (this != &tree) {
		if (raiz != NULL) {
			delete raiz;
			raiz = NULL;
		}
		//this->~GraphicTree();
		if (tree.raiz != NULL) {
			//GraphicNode *aux = new GraphicNode();
			//aux->item = new Element(*tree.raiz->item); //Cambiado de aux->item = tree.raiz->item;
			raiz = new GraphicNode(new Element(*tree.raiz->item));
			//raiz = aux;
			//aux = NULL;

			/*if(!raiz->hijos.empty())
			 {
			 for(unsigned int i=0; i<raiz->hijos.size(); i++)
			 {
			 if(raiz->hijos[i]!=NULL)
			 {
			 delete raiz->hijos[i];
			 raiz->hijos[i]=NULL;
			 }
			 }
			 raiz->hijos.clear();
			 }*/
			for (unsigned int i = 0; i < tree.raiz->hijos.size(); i++) {
				raiz->hijos.push_back(new GraphicTree(*tree.raiz->hijos[i]));
			}
		}
	}
	return *this;
}

void GraphicTree::PreordenAux(vector<Element*>& aux) const {

	if (raiz != NULL) {
		aux.push_back(raiz->item);
		for (unsigned int i = 0; i < raiz->hijos.size(); i++) {
			raiz->hijos[i]->PreordenAux(aux);
		}
	}
}

vector<Element*> GraphicTree::Preorden() const {
	vector<Element*> elements;
	PreordenAux(elements);
	return elements;
}

GraphicNode *
GraphicTree::Insertar(Element *element, Element *padre) {

	GraphicNode *nodo = raiz;

	//if(!Existe(element))
	//{
	if (raiz != NULL) {
		nodo = BuscarElemento(padre);
		if (nodo != NULL) {
			GraphicNode *aux = new GraphicNode(element);
			GraphicTree *tmp = new GraphicTree();
			tmp->raiz = aux;
			nodo->hijos.push_back(tmp);
			nodo = aux;
		}
		/*else
		 {
		 ////cout << "Nodo de búsqueda es igual a NULL" << endl;
		 GraphicNode *aux = new GraphicNode(element);
		 raiz = aux;
		 }*/
	} else {
		GraphicNode *aux = new GraphicNode(element);
		raiz = aux;
		nodo = aux;
	}
	//}

	return nodo;
}
/*
 GraphicNode *
 GraphicTree::Insertar(Element *element, Element *padre) {

 GraphicNode *nodo = raiz;

 //if(!Existe(element))
 //{
 if(raiz != NULL)
 {
 nodo = BuscarElemento(padre);
 if(nodo != NULL)
 {
 GraphicNode *aux = new GraphicNode(element);
 GraphicTree *tmp = new GraphicTree();
 tmp->raiz = aux;
 nodo->hijos.push_back(tmp);
 nodo = aux;
 }
 else
 {
 ////cout << "Nodo de búsqueda es igual a NULL" << endl;
 GraphicNode *aux = new GraphicNode(element);
 raiz = aux;
 }
 }
 else
 {
 GraphicNode *aux = new GraphicNode(element);
 raiz = aux;
 nodo = aux;
 }
 //}

 return nodo;
 }*/

GraphicNode*
GraphicTree::Insertar(Element *element, GraphicNode *padre) {

	GraphicNode *nodo = raiz;

	//if(!Existe(element))
	//{
	if (raiz != NULL) {
		nodo = BuscarElemento(padre);
		if (nodo != NULL) {
			GraphicNode *aux = new GraphicNode(element);
			GraphicTree *tmp = new GraphicTree();
			tmp->raiz = aux;
			nodo->hijos.push_back(tmp);
			nodo = aux;
		}
		/*else
		 {
		 ////cout << "Nodo de búsqueda es igual a NULL" << endl;
		 GraphicNode *aux = new GraphicNode(element);
		 raiz = aux;
		 }*/
	} else {
		GraphicNode *aux = new GraphicNode(element);
		raiz = aux;
		nodo = aux;
	}
	//}

	return nodo;
}

GraphicNode*
GraphicTree::BuscarElemento(Element *elemento) const {

	GraphicNode *nodo = NULL;

	if (raiz != NULL) {
		if (raiz->item == elemento) {
			nodo = raiz;
		} else {
			nodo = BuscarElementoAux(elemento, nodo);
		}
	}

	return nodo;
}

GraphicNode*
GraphicTree::BuscarElemento(int id_) const {

	GraphicNode *nodo = NULL;

	if (raiz != NULL) {
		if (raiz->getId() == id_) {
			nodo = raiz;
		} else {
			nodo = BuscarElementoAux(id_, nodo);
		}
	}

	return nodo;
}

GraphicNode*
GraphicTree::BuscarElementoAux(Element *elemento, GraphicNode *nodo) const {

	if (nodo == NULL) {
		if (raiz->item == elemento) {
			nodo = raiz;
		} else {
			for (unsigned int i = 0; i < raiz->hijos.size() && nodo == NULL; i++) {
				nodo = raiz->hijos[i]->BuscarElementoAux(elemento, nodo);
			}
		}
	}

	return nodo;

}

GraphicNode*
GraphicTree::BuscarElementoAux(int id_, GraphicNode *nodo) const {

	if (nodo == NULL) {
		if (raiz->getId() == id_) {
			nodo = raiz;
		} else {
			for (unsigned int i = 0; i < raiz->hijos.size() && nodo == NULL; i++) {
				nodo = raiz->hijos[i]->BuscarElementoAux(id_, nodo);
			}
		}
	}

	return nodo;

}

GraphicNode*
GraphicTree::BuscarElemento(GraphicNode* elemento) const {

	GraphicNode *nodo = NULL;

	if (raiz != NULL) {
		if (raiz == elemento) {
			nodo = raiz;
		} else {
			nodo = BuscarElementoAux(elemento, nodo);
		}
	}

	return nodo;
}

GraphicNode*
GraphicTree::BuscarElementoAux(GraphicNode* elemento, GraphicNode *nodo) const {

	if (nodo == NULL) {
		if (raiz == elemento) {
			nodo = raiz;
		} else {
			for (unsigned int i = 0; i < raiz->hijos.size() && nodo == NULL; i++) {
				nodo = raiz->hijos[i]->BuscarElementoAux(elemento, nodo);
			}
		}
	}

	return nodo;

}

GraphicNode*
GraphicTree::getRaiz() const {
	return raiz;
}

GraphicNode*
GraphicTree::getNode(Element *element) const {

	GraphicNode *nodo = NULL;

	nodo = BuscarElemento(element);

	return nodo;
}

GraphicNode*
GraphicTree::getNodeById(int id_) const {

	GraphicNode *nodo = NULL;

	nodo = BuscarElemento(id_);

	return nodo;
}

bool GraphicTree::Existe(Element *element) const {

	bool existe = false;

	if (raiz != NULL) {
		if (raiz->item == element) {
			existe = true;
		} else {
			ExisteAux(element, existe);
		}
	}

	return existe;
}

bool GraphicTree::ExisteAux(Element *element, bool &existe) const {

	if (raiz != NULL) {
		if (raiz->item == element) {
			existe = true;
		} else {
			for (unsigned int i = 0; i < raiz->hijos.size() && !existe; i++) {
				raiz->hijos[i]->ExisteAux(element, existe);
			}
		}
	}

	return existe;
}

ostream&
operator<<(ostream &os, const GraphicTree &tree) {

	vector<Element*> elements;

	elements = tree.Preorden();

	for (unsigned int i = 0; i < elements.size(); i++) {
		os << elements[i]->getName() << " ";
	}

	return os;
}

void GraphicTree::BorrarElemento(Element *elemento) const {
	GraphicNode *nodo = BuscarElemento(elemento);
	if (nodo != NULL) {
		GraphicNode *padre = getPadre(nodo);
		if (padre != NULL) {
			bool borrado = false;
			GraphicTree *tmp;
			vector<GraphicTree*>::iterator it;

			for (it = padre->hijos.begin(); it != padre->hijos.end() && !borrado; it++) {
				if ((*it)->raiz == nodo) {
					tmp = *it;
					padre->hijos.erase(it);
					if (tmp != NULL) {
						delete tmp;
						tmp = NULL;
					}
					borrado = true;
				}
			}
		} else {
			this->~GraphicTree();
		}
	}
}

GraphicNode*
GraphicTree::getPadre(GraphicNode* elemento) const {

	GraphicNode *nodo = NULL;

	if (raiz != NULL) {
		if (raiz == elemento) {
			nodo = NULL;
		} else {
			nodo = getPadreAux(elemento, nodo, raiz);
		}
	}
	return nodo;
}

GraphicNode*
GraphicTree::getPadreAux(GraphicNode* elemento, GraphicNode *nodo, GraphicNode* padre) const {

	if (nodo == NULL) {
		if (raiz == elemento) {
			nodo = padre;
		} else {
			for (unsigned int i = 0; i < raiz->hijos.size() && nodo == NULL; i++) {
				nodo = raiz->hijos[i]->getPadreAux(elemento, nodo, raiz);
			}
		}
	}
	return nodo;
}

vector<GraphicTree*> GraphicNode::getHijos() const {
	return hijos;
}

Element *GraphicNode::getItem() const {
	return item;
}

void GraphicNode::setHijos(vector<GraphicTree*> hijos) {
	//todo copiar contenido no punteros.
	this->hijos = hijos;
}

void GraphicNode::setItem(Element *item) {
	this->item = item;
}

void GraphicTree::Render() const {

	Point pos;
	Color<float> color;
	if (raiz != NULL) {
		Element *it = raiz->getItem();

		if (it != NULL && raiz->getVisible()) {
			switch (it->getElementType()) {

			case Core::Element::e_camera:
				////cout << "GT Cámara" << endl;
				((Camera*) raiz->item)->exportOpenGL();
				glMatrixMode(GL_MODELVIEW);
				glLoadIdentity();
				break;
			case Core::Element::e_transform:
				////cout << "GT Transform" << endl;
				////cout << *((Transform*)raiz->item) << endl;
				((Transform*) raiz->item)->addOpenGL();
				break;
			case Core::Element::e_light:
				////cout << "GT Light" << endl;
				((Light*) raiz->item)->exportOpenGL();
				break;
			case Core::Element::e_entity:

				if (((Entity*) raiz->item)->getType() == Core::Entities::e_pointer) {
					DrawPolygon(Polygon(((Entity*) raiz->item)->getCenter(), 8), Color<float>(0.5, 1, 0));
				} else if (((Entity*) raiz->item)->getType() == Core::Entities::e_door) {
					if (SceneManager::getInstance()->isShaderActive())
						ResourceManager::getInstance()->activateShader(Graphics::Shader::Phong);

					Color<float> c = ((Entity*) raiz->item)->getColor();
					c.exportOpenGL();
					if (c.getAlpha() == 0) {
						glDisable(GL_DEPTH_TEST);
					} else {
						glEnable(GL_DEPTH_TEST);
					}

					glCallList(((Entity*) raiz->item)->getIdDisplay());
					glEnable(GL_DEPTH_TEST);

					if (SceneManager::getInstance()->isShaderActive())
						ResourceManager::getInstance()->deactivateShader(Graphics::Shader::Phong);

				} else {
					int tipo = (int) ((Entity*) raiz->item)->getType();

					if (SceneManager::getInstance()->isShaderActive()){
						if(tipo != 0 && tipo < 10){
							ResourceManager::getInstance()->activateShader(Graphics::Shader::Phong);
						}else{
							ResourceManager::getInstance()->activateShader(Graphics::Shader::Phong);
						}
					}

					//(((Entity*)raiz->item)->getColor()).exportOpenGL();
					glColor3d(1, 1, 1);
					glCallList(((Entity*) raiz->item)->getIdDisplay());

					if (SceneManager::getInstance()->isShaderActive()){
						if(tipo != 0 && tipo < 10){
							ResourceManager::getInstance()->deactivateShader(Graphics::Shader::Phong);
						}else{
							ResourceManager::getInstance()->deactivateShader(Graphics::Shader::Phong);
						}
					}
				}
				break;
			case Core::Element::e_shape:
				////cout << "GT Shape" << endl;
				((Shape*) raiz->item)->exportOpenGL();
				break;
			case Core::Element::e_model:
				////cout << "GT Modelo" << endl;
				((Model*) raiz->item)->exportOpenGL();
				break;
			case Core::Element::e_texture:
				////cout << "GT Texture" << endl;
				//((Model*)raiz->item)->exportOpenGL();
				break;
			case Core::Element::e_text:
				//pintamos el texto
				((Text *) raiz->item)->exportOpenGL();
				break;
			case Core::Element::e_menu:
				//pintamos el menu que este activo
				////cout << "GT Menu" << endl;
				((GameMenu *) raiz->item)->Render();
				break;
			case Core::Element::e_form:
				((TForm *) raiz->item)->Draw();
				break;
			case Core::Element::e_particle:
				((ParticleNode *) raiz->item)->Render();
				break;
			case Core::Element::e_none:
				////cout << "No exporto nada" << endl;
				break;
			}
		} else {
			////cout << "GT NULL" << endl;
		}

		if (raiz->getVisible()) {
			for (unsigned int i = 0; i < raiz->hijos.size(); i++) {
				if (it != NULL) {
					if (raiz->item->getElementType() == Core::Element::e_transform) {
						glPushMatrix();
						raiz->hijos[i]->Render();
						glPopMatrix();
					} else
						raiz->hijos[i]->Render();
				} else
					raiz->hijos[i]->Render();

			}
		}
	}
}

void GraphicTree::BorrarRama(Element* elem) {

	GraphicNode *nodo = getNode(elem);
	vector<GraphicTree*> h;

	if (nodo != NULL) {
		if (elem != NULL) {
			delete elem;
			elem = NULL;
		}

		h = nodo->getHijos();
		for (unsigned int i = 0; i < h.size(); i++) {
			BorrarRama(h[i]->raiz);
		}

		if (nodo != NULL) {
			delete nodo;
			nodo = NULL;
		}
	}
}

void GraphicTree::BorrarRama(GraphicNode* nodo) {

	Element *elem = NULL;
	vector<GraphicTree*> h;

	if (nodo != NULL) {
		elem = nodo->getItem();
		if (elem != NULL) {
			delete elem;
			elem = NULL;
		}

		h = nodo->getHijos();
		for (unsigned int i = 0; i < h.size(); i++) {
			BorrarRama(h[i]->raiz);
		}

		if (nodo != NULL) {
			delete nodo;
			nodo = NULL;
		}
	}
}
void GraphicNode::Render() {

	Point pos;
	Color<float> color;

	if (item != NULL && visible) {
		switch (item->getElementType()) {

		case Core::Element::e_camera:
			////cout << "GT Cámara" << endl;
			((Camera*) item)->exportOpenGL();
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			break;
		case Core::Element::e_transform:
			////cout << "GT Transform" << endl;
			// ////cout << *((Transform*)raiz->item) << endl;
			((Transform*) item)->addOpenGL();
			break;
		case Core::Element::e_light:
			////cout << "GT Light" << endl;
			((Light*) item)->exportOpenGL();
			break;
		case Core::Element::e_entity:

			ResourceManager::getInstance()->activateShader(Graphics::Shader::Phong);
			//(((Entity*)item)->getColor()).exportOpenGL();
			glColor3d(1, 1, 1);
			glCallList(((Entity*) item)->getType());
			ResourceManager::getInstance()->deactivateShader(Graphics::Shader::Phong);

			break;
		case Core::Element::e_shape:
			////cout << "GT Shape" << endl;
			((Shape*) item)->exportOpenGL();
			break;
		case Core::Element::e_model:
			////cout << "GT Modelo" << endl;
			((Model*) item)->exportOpenGL();
			break;
		case Core::Element::e_texture:
			////cout << "GT Texture" << endl;
			//((Model*)raiz->item)->exportOpenGL();
			break;
		case Core::Element::e_text:
			//pintamos el texto
			((Text *) item)->exportOpenGL();
			break;
		case Core::Element::e_menu:
			//pintamos el menu que este activo
			////cout << "GT Menu" << endl;
			((GameMenu *) item)->Render();
			break;
		case Core::Element::e_form:
			////cout << "GT e_form" << endl;
			((TForm *) item)->Draw();
			break;
		case Core::Element::e_none:
			////cout << "No exporto nada" << endl;
			break;
		default:
			break;
		}
	} else {
		////cout << "GT NULL" << endl;
	}

	if (visible) {
		for (unsigned int i = 0; i < hijos.size(); i++) {
			if (item != NULL) {
				if (item->getElementType() == Core::Element::e_transform) {
					glPushMatrix();
					hijos[i]->Render();
					glPopMatrix();
				} else
					hijos[i]->Render();
			} else
				hijos[i]->Render();

		}
	}

}

