/*
 * AnimationControl.cc
 *
 *  Created on: 30/03/2012
 *      Author: Chutaos Team
 */

#include "AnimationControl.h"

AnimationControl * AnimationControl::_app = NULL;

AnimationControl* AnimationControl::getInstance(TWindow *w, GameMenu *gameMenu_) {
	if (_app == NULL) {
		_app = new AnimationControl(w,gameMenu_);
	}
	return _app;
}

AnimationControl* AnimationControl::getInstance() {
	if (_app == NULL) {
		_app = new AnimationControl(NULL,NULL);
	}
	return _app;
}

AnimationControl::AnimationControl(TWindow *w, GameMenu *gameMenu_) {
	animationsFinite.clear();
	animationsInfinite.clear();
	window = w;
	gameMenu = gameMenu_;
	time = 0;

}

AnimationControl::~AnimationControl() {
	vector<Animation*>::iterator iter;
	iter = animationsFinite.begin();
	while (iter != animationsFinite.end()){
		delete (*iter);
		animationsFinite.erase(iter);
	}
	animationsFinite.clear();
	iter = animationsInfinite.begin();
	while (iter != animationsInfinite.end()){
		delete (*iter);
		animationsInfinite.erase(iter);
	}
	animationsInfinite.clear();
	window = NULL;
	gameMenu = NULL;
	time = 0;
}

void AnimationControl::freeAllAnimations(){
	vector<Animation*>::iterator iter;
	iter = animationsFinite.begin();
	while (iter != animationsFinite.end()){
		delete (*iter);
		animationsFinite.erase(iter);
	}
	animationsFinite.clear();
	iter = animationsInfinite.begin();
	while (iter != animationsInfinite.end()){
		delete (*iter);
		animationsInfinite.erase(iter);
	}
	animationsInfinite.clear();
}

void AnimationControl::addFadeIn(Entity *ent, int time_) {
	Color<float> c = ent->getColor();
	c.setAlpha(1.0);
	vector<Color<float> >vec;
	vec.push_back(c);
	Animation *anim = new Animation(ent);
	anim->setTimeAnimation(time_);
	anim->createFade(vec);
	animationsFinite.push_back(anim);
}

void AnimationControl::addFadeOut(Entity *ent, int time_) {
	Color<float> c = ent->getColor();
	c.setAlpha(0);
	vector<Color<float> >vec;
	vec.push_back(c);
	Animation *anim = new Animation(ent);
	anim->setTimeAnimation(time_);
	anim->createFade(vec);
	animationsFinite.push_back(anim);
}

void AnimationControl::addRotationInfinite(Entity* ent, Transform *trans, int time_){
	Animation *anim = new Animation(ent);
	anim->setTimeAnimation(time_);
	vector<float>v;
	v.push_back(0);
	v.push_back(360);
	anim->createRotation(v);
	/*vector<Point>vp;
	Point aux = ent->getCenter();
	aux.setZ(10);
	vp.push_back(aux);
	aux.setZ(0);
	vp.push_back(aux);
	anim->createTranslation(vp);*/
	animationsInfinite.push_back(anim);
	((Object*)ent)->myAnimation = anim;
}

void AnimationControl::Update() {
	vector<Animation*>::iterator iter;
	iter = animationsFinite.begin();
	while (iter != animationsFinite.end()) {
		if ((*iter)->step()) {
			delete (*iter);
			animationsFinite.erase(iter);
		} else {
			iter++;
		}
	}
	iter = animationsInfinite.begin();
	while (iter != animationsInfinite.end()) {
		if ((*iter)->step()) {
			(*iter)->init();
		}
		iter++;
	}
}

bool AnimationControl::rermoveAnimation(Animation *anim){
	bool borrado = false;
	vector<Animation*>::iterator iter;
	iter = animationsInfinite.begin();
	while (iter != animationsInfinite.end()) {
		if ((*iter) == anim) {
			delete (*iter);
			animationsInfinite.erase(iter);
			break;
		}else{
			iter++;
		}
	}

	return borrado;
}

void AnimationControl::slide(Graphics::Menus::Index menu1,
		Graphics::Menus::Index menu2, Graphics::DirectNodesMenu::Index node,
		double despX, double despY) {
	if (window != NULL && gameMenu != NULL) {
		SceneManager *sm = SceneManager::getInstance();
		Transform *orig = new Transform(
				*(Transform*) sm->getNode(node)->getItem());

		Animation *animMenu1 = new Animation(orig);
		animMenu1->init();
		vector<Point> vectMen;
		vectMen.push_back(Point(despX, despY));
		animMenu1->createTranslationTransform(vectMen);
		animMenu1->setTimeAnimation(time);

		((Transform*) sm->getNode(node)->getItem())->addTranslation(-despX,
				-despY, 0);
		Animation *animMenu2 = new Animation(
				(Transform*) sm->getNode(node)->getItem());
		animMenu2->init();
		vectMen.clear();
		vectMen.push_back(Point(despX, despY));
		animMenu2->createTranslationTransform(vectMen);
		animMenu2->setTimeAnimation(time);

		bool terminadoMen1 = false;
		bool terminadoMen2 = false;
		while (!terminadoMen1 || !terminadoMen2) {
			//			cout << "Entra: " << terminadoMen1 << " | " << terminadoMen2 << endl;
			terminadoMen1 = animMenu1->step();
			terminadoMen2 = animMenu2->step();
			//			cout << "Sale: " << terminadoMen1 << " | " << terminadoMen2 << endl;

			sm->clean();
			animMenu2->getTranform()->exportOpenGL();
			gameMenu->setVisible(menu2);
			gameMenu->Render();
			animMenu1->getTranform()->exportOpenGL();
			gameMenu->setVisible(menu1);
			gameMenu->Render();
			window->display();

		}

		gameMenu->setVisible(menu2);

		delete orig;
		delete animMenu1;
		delete animMenu2;

	}
}

void AnimationControl::slideUp(Graphics::Menus::Index menu1,
		Graphics::Menus::Index menu2, Graphics::DirectNodesMenu::Index node) {
	this->slide(menu1, menu2, node, 0, -600);
}

void AnimationControl::slideDown(Graphics::Menus::Index menu1,
		Graphics::Menus::Index menu2, Graphics::DirectNodesMenu::Index node) {
	this->slide(menu1, menu2, node, 0, 600);
}
void AnimationControl::slideRight(Graphics::Menus::Index menu1,
		Graphics::Menus::Index menu2, Graphics::DirectNodesMenu::Index node) {
	this->slide(menu1, menu2, node, 800, 0);
}
void AnimationControl::slideLeft(Graphics::Menus::Index menu1,
		Graphics::Menus::Index menu2, Graphics::DirectNodesMenu::Index node) {
	this->slide(menu1, menu2, node, -800, 0);
}

int AnimationControl::getTime() const {
	return time;
}

void AnimationControl::setTime(int time) {
	this->time = time;
}

