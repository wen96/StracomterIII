#include <iostream>
using namespace std;
#include <cmath>
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <GL/glu.h>


#include "compositeEmitter.hpp"
#include "compositeParticle.hpp"
#include "particleStorage.hpp"
#include "texture.hpp"
#include "camera.hpp"
#include "time.hpp"

Quad *q;

int mousex;
int mousey;
int fps;

double texIncX;
double texIncY;

Utils::CTimer renderTime;

int sizeX;
int sizeY;

Texture* t;
triangle pAct;

MyLookAtCamera* c;
ParticleStorage* ps = new ParticleStorage();

CompositeEmitter<ParticleMoverPVA , ParticleRendererTextureFading> fuego;
CompositeEmitter<ParticleMoverSin , ParticleRendererTextureFading> humo;
CompositeEmitter<ParticleMoverPVA , ParticleRendererSecuentialColorFading> arcoiris;
CompositeEmitter<ParticleMoverForces, ParticleRendererColorUA> fuerzas;
CompositeEmitter<ParticleMoverForcesInertia, ParticleRendererSecuentialColorFading> inercia;

double mouseForce = 5;

double cameraPoints[4][3] = 
{
	{5,0,0},
	{0,0,5},
	{-5,0,0},
	{0,0,-5}
};

int currentCameraPoint = 0;
bool inTransit = false;
void nextCameraPoint()
{
	currentCameraPoint++;
	inTransit = true;
	if (currentCameraPoint > 3)
	{
		currentCameraPoint = 0;
	}
	c->setEnd(cameraPoints[currentCameraPoint][0], 
				cameraPoints[currentCameraPoint][1],
				cameraPoints[currentCameraPoint][2]);
}


void updateCamera()
{

}

Quad* mouseQuad = NULL;

void keyPressed (unsigned char key, int x, int y)
{
	string s(1, key);

	if (key == '+')
	{
		mouseForce += 0.1;
	}
	if (key == '-')
	{
		mouseForce -= 0.1;
	}
	if (key == ' ')
	{
		nextCameraPoint();
	}
	
	if (mouseQuad == NULL)
	{
		Quad q;
		q.r = 0;
		q.g = 0;
		q.b = 0;
		q.a = 0;
		mouseQuad = ParticleMoverForces::addGlobalDragPoint(q);
	}
	
	mouseQuad->r = 15;
	mouseQuad->g = 5 - (y/(double)sizeY * 10);
	mouseQuad->b = (x/(double)sizeX * 10) - 5;
	mouseQuad->a = mouseForce;
}

void spPressed (int key, int x, int y)
{

}

void mouseAction (int button, int state, int x, int y)
{
    mousex = x;
    mousey = y;
}

void mouseMove(int x, int y)
{
    mousex = x;
    mousey = y;
}


void passiveMouse(int x, int y)
{
    mousex = x;
    mousey = y;
	
	if (mouseQuad == NULL)
	{
		Quad q;
		q.r = 0;
		q.g = 0;
		q.b = 0;
		q.a = 0;
		mouseQuad = ParticleMoverForces::addGlobalDragPoint(q);
	}
	
	mouseQuad->r = 15;
	mouseQuad->g = 5 - (y/(double)sizeY * 10);
	mouseQuad->b = (x/(double)sizeX * 10) - 5;
	mouseQuad->a = mouseForce;
}

void genParticles()
{
	ps->put(humo.getParticle());
	ps->put(fuego.getParticle());
	ps->put(arcoiris.getParticle());
	ps->put(inercia.getParticle());
}

double rot = 0;

void renderScene()
{
    float timeDiff = renderTime.GetSecondes();
    renderTime.start();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    glDisable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
    glLoadIdentity();
	glRotatef(rot, 0, 1, 0);
	glScalef(0.02, 0.02, 0.02);
	rot += 1;
    glBlendFunc(GL_SRC_ALPHA,GL_ONE);
    glEnable(GL_BLEND);
    glDisable(GL_LIGHTING);
	ps->render();
	glEnable(GL_BLEND);
	ps->step(timeDiff);
	glutSwapBuffers();
	genParticles();
}

void changeSize(int width, int height)
{
    sizeX = width;
    sizeY = height;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    gluPerspective(45, height/width, 0.1, 100);
    glMatrixMode(GL_MODELVIEW);
}

void glutInit(int num, char** args, int width, int height)
{
    glutInit(&num, args);
    glutInitWindowPosition(-1,-1);
    glutInitWindowSize(width,height);
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    gluPerspective(45, height/width, 0.1, 100);
    glMatrixMode(GL_MODELVIEW);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("Wankel Particles v1.0");
    glutDisplayFunc(renderScene);
    glutReshapeFunc(changeSize);
	glutIdleFunc(renderScene);
    glutKeyboardFunc(keyPressed);
    glutSpecialFunc(spPressed);
    glutMouseFunc(mouseAction);
    glutMotionFunc(mouseMove);
    glutPassiveMotionFunc(passiveMouse);
}

void setParticles()
{
	humo.setMinValue("lifeTime", 2);
	humo.setMaxValue("lifeTime", 5);
	humo.setMinValue("positionX", 0);
	humo.setMaxValue("positionX", 0);
	humo.setMinValue("positionY", 0);
	humo.setMaxValue("positionY", 0);
	humo.setMinValue("positionZ", 10);
	humo.setMaxValue("positionZ", 10);
	humo.setMinValue("speedX", -.1);
	humo.setMaxValue("speedX", .1);
	humo.setMinValue("speedY", -0);
	humo.setMaxValue("speedY", 1);
	humo.setMinValue("speedZ", -.1);
	humo.setMaxValue("speedZ", .1);	
	humo.setMinValue("accelX", -0.02);
	humo.setMaxValue("accelX", 0.02);
	humo.setMinValue("accelY", 0.2);
	humo.setMaxValue("accelY", 0.1);
	humo.setMinValue("accelZ", -0.02);
	humo.setMaxValue("accelZ", 0.02);	
	humo.setMinValue("colorR", 0.6);
	humo.setMaxValue("colorR", .6);	
	humo.setMinValue("colorG", 0.6);
	humo.setMaxValue("colorG", 0.6);	
	humo.setMinValue("colorB", 0.6);
	humo.setMaxValue("colorB", 0.6);	
	humo.setMinValue("colorA", 1);
	humo.setMaxValue("colorA", 1);	
	humo.setMinValue("fade", 1);
	humo.setMaxValue("fade", 1);	
	humo.setMinValue("amplitude", 0);
	humo.setMaxValue("amplitude", 0.25);	
	humo.setMinValue("textureNum", 0);
	humo.setMaxValue("textureNum", 2);	
	humo.setMinValue("round", 1);
	humo.setMaxValue("round", 1);	

	ParticleRendererTextureFading::addTexture(new TextureImage("fuego1.jpg"));
	ParticleRendererTextureFading::addTexture(new TextureImage("fuego2.jpg"));
	ParticleRendererTextureFading::addTexture(new TextureImage("fuego3.jpg"));
	
	fuego.setMinValue("lifeTime", 3);
	fuego.setMaxValue("lifeTime", 6);
	fuego.setMinValue("positionX", 0);
	fuego.setMaxValue("positionX", 0);
	fuego.setMinValue("positionY", 0);
	fuego.setMaxValue("positionY", 0);
	fuego.setMinValue("positionZ", 10);
	fuego.setMaxValue("positionZ", 10);
	fuego.setMinValue("speedX", -.1);
	fuego.setMaxValue("speedX", .1);
	fuego.setMinValue("speedY", -.1);
	fuego.setMaxValue("speedY", 1);
	fuego.setMinValue("speedZ", -.1);
	fuego.setMaxValue("speedZ", .1);	
	fuego.setMinValue("accelX", -0.08);
	fuego.setMaxValue("accelX", 0.08);
	fuego.setMinValue("accelY", 0.4);
	fuego.setMaxValue("accelY", 0.1);
	fuego.setMinValue("accelZ", -0.08);
	fuego.setMaxValue("accelZ", 0.08);	
	fuego.setMinValue("colorR", 0.6);
	fuego.setMaxValue("colorR", 1);	
	fuego.setMinValue("colorG", 0);
	fuego.setMaxValue("colorG", 0.4);	
	fuego.setMinValue("colorB", 0);
	fuego.setMaxValue("colorB", 0);	
	fuego.setMinValue("colorA", 1);
	fuego.setMaxValue("colorA", 1);	
	fuego.setMinValue("colorVR", 5);
	fuego.setMaxValue("colorVR", 10);	
	fuego.setMinValue("colorVG", 5);
	fuego.setMaxValue("colorVG", 10);	
	fuego.setMinValue("colorVB", 5);
	fuego.setMaxValue("colorVB", 10);	
	fuego.setMinValue("colorVA", -.001);
	fuego.setMaxValue("colorVA", -.002);	
	fuego.setMinValue("colorAR", 0);
	fuego.setMaxValue("colorAR", 0);	
	fuego.setMinValue("colorAG", 0);
	fuego.setMaxValue("colorAG", 0);	
	fuego.setMinValue("colorAB", 0);
	fuego.setMaxValue("colorAB", 0);	
	fuego.setMinValue("colorAA", 0);
	fuego.setMaxValue("colorAA", 0);	
	fuego.setMinValue("fade", 1);
	fuego.setMaxValue("fade", 1);	
	fuego.setMinValue("amplitude", 0);
	fuego.setMaxValue("amplitude", 0.01);	
	fuego.setMinValue("textureNum", 0);
	fuego.setMaxValue("textureNum", 2);	
	fuego.setMinValue("round", 1);
	fuego.setMaxValue("round", 1);	


	arcoiris.setMinValue("lifeTime", 3);
	arcoiris.setMaxValue("lifeTime", 5);
	arcoiris.setMinValue("positionX", -25);
	arcoiris.setMaxValue("positionX", -25);
	arcoiris.setMinValue("positionY", 0);
	arcoiris.setMaxValue("positionY", 0);
	arcoiris.setMinValue("positionZ", 0);
	arcoiris.setMaxValue("positionZ", 0);
	arcoiris.setMinValue("speedX", 0);
	arcoiris.setMaxValue("speedX", 0);
	arcoiris.setMinValue("speedY", .2);
	arcoiris.setMaxValue("speedY", .1);
	arcoiris.setMinValue("speedZ", -5);
	arcoiris.setMaxValue("speedZ", -10);	
	arcoiris.setMinValue("accelX", 0);
	arcoiris.setMaxValue("accelX", 0);
	arcoiris.setMinValue("accelY", -3);
	arcoiris.setMaxValue("accelY", -3.4);
	arcoiris.setMinValue("accelZ", .1);
	arcoiris.setMaxValue("accelZ", .3);	
	arcoiris.setMinValue("colorR", 0);
	arcoiris.setMaxValue("colorR", 1);	
	arcoiris.setMinValue("colorG", 0);
	arcoiris.setMaxValue("colorG", 1);	
	arcoiris.setMinValue("colorB", 0);
	arcoiris.setMaxValue("colorB", 1);	
	arcoiris.setMinValue("colorA", 1);
	arcoiris.setMaxValue("colorA", 1);	
	arcoiris.setMinValue("colorVR", 5);
	arcoiris.setMaxValue("colorVR", 10);	
	arcoiris.setMinValue("colorVG", 5);
	arcoiris.setMaxValue("colorVG", 10);	
	arcoiris.setMinValue("colorVB", 5);
	arcoiris.setMaxValue("colorVB", 10);	
	arcoiris.setMinValue("colorVA", -.001);
	arcoiris.setMaxValue("colorVA", -.002);	
	arcoiris.setMinValue("colorAR", 0);
	arcoiris.setMaxValue("colorAR", 0);	
	arcoiris.setMinValue("colorAG", 0);
	arcoiris.setMaxValue("colorAG", 0);	
	arcoiris.setMinValue("colorAB", 0);
	arcoiris.setMaxValue("colorAB", 0);	
	arcoiris.setMinValue("colorAA", 0);
	arcoiris.setMaxValue("colorAA", 0);	
	arcoiris.setMinValue("fade", 1);
	arcoiris.setMaxValue("fade", 1);	
	arcoiris.setMinValue("amplitude", 0);
	arcoiris.setMaxValue("amplitude", 0.01);	
	arcoiris.setMinValue("textureNum", 0);
	arcoiris.setMaxValue("textureNum", 2);	
	arcoiris.setMinValue("round", 1);
	arcoiris.setMaxValue("round", 1);	

	fuerzas.setMinValue("lifeTime", -100000);
	fuerzas.setMaxValue("lifeTime", -100000);
	fuerzas.setMinValue("positionX", 10);
	fuerzas.setMaxValue("positionX", 10);
	fuerzas.setMinValue("positionY", 0);
	fuerzas.setMaxValue("positionY", 0);
	fuerzas.setMinValue("positionZ", 0);
	fuerzas.setMaxValue("positionZ", 0);
	fuerzas.setMinValue("speedX", 0);
	fuerzas.setMaxValue("speedX", 0);
	fuerzas.setMinValue("speedY", 0);
	fuerzas.setMaxValue("speedY", 0);
	fuerzas.setMinValue("speedZ", 0);
	fuerzas.setMaxValue("speedZ", 0);	
	fuerzas.setMinValue("accelX", -0.02);
	fuerzas.setMaxValue("accelX", 0.02);
	fuerzas.setMinValue("accelY", 0.4);
	fuerzas.setMaxValue("accelY", 0.1);
	fuerzas.setMinValue("accelZ", -0.02);
	fuerzas.setMaxValue("accelZ", 0.02);	
	fuerzas.setMinValue("colorR", 0);
	fuerzas.setMaxValue("colorR", 1);	
	fuerzas.setMinValue("colorG", 0);
	fuerzas.setMaxValue("colorG", 1);	
	fuerzas.setMinValue("colorB", 0);
	fuerzas.setMaxValue("colorB", 1);	
	fuerzas.setMinValue("colorA", 1);
	fuerzas.setMaxValue("colorA", 1);	
	fuerzas.setMinValue("colorVR", 1);
	fuerzas.setMaxValue("colorVR", 5);	
	fuerzas.setMinValue("colorVG", 1);
	fuerzas.setMaxValue("colorVG", 5);	
	fuerzas.setMinValue("colorVB", 1);
	fuerzas.setMaxValue("colorVB", 5);	
	fuerzas.setMinValue("colorVA", -.001);
	fuerzas.setMaxValue("colorVA", -.002);	
	fuerzas.setMinValue("colorAR", 0);
	fuerzas.setMaxValue("colorAR", 0);	
	fuerzas.setMinValue("colorAG", 0);
	fuerzas.setMaxValue("colorAG", 0);	
	fuerzas.setMinValue("colorAB", 0);
	fuerzas.setMaxValue("colorAB", 0);	
	fuerzas.setMinValue("colorAA", 0);
	fuerzas.setMaxValue("colorAA", 0);	
	fuerzas.setMinValue("fade", 1);
	fuerzas.setMaxValue("fade", 1);	
	fuerzas.setMinValue("amplitude", 0);
	fuerzas.setMaxValue("amplitude", 0.01);	
	fuerzas.setMinValue("textureNum", 0);
	fuerzas.setMaxValue("textureNum", 2);	
	fuerzas.setMinValue("round", 1);
	fuerzas.setMaxValue("round", 1);	
	fuerzas.setMinValue("mass", 0.1);
	fuerzas.setMaxValue("mass", 0.1);	
	
	CompositeParticle *cp;
	Quad q;
	
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			fuerzas.setMinValue("positionX", 15);
			fuerzas.setMaxValue("positionX", 15);
			fuerzas.setMinValue("positionY", 5-i/2.0);
			fuerzas.setMaxValue("positionY", 5-i/2.0);
			fuerzas.setMinValue("positionZ", 5-j/2.0);
			fuerzas.setMaxValue("positionZ", 5-j/2.0);
			cp = fuerzas.getParticle();
			q.r = 15;
			q.b = 5-j/2.0;
			q.g = 5-i/2.0;
			q.a = 5;
			((ParticleMoverForces*)cp->getParticleMover())->addLocalDragPoint(q);
			ps->put(cp);	
		}
	}
	
	inercia.setMinValue("lifeTime", 10);
	inercia.setMaxValue("lifeTime", 20);
	inercia.setMinValue("positionX", 0);
	inercia.setMaxValue("positionX", 0);
	inercia.setMinValue("positionY", 0);
	inercia.setMaxValue("positionY", 0);
	inercia.setMinValue("positionZ", -15);
	inercia.setMaxValue("positionZ", -15);
	inercia.setMinValue("speedX", 1);
	inercia.setMaxValue("speedX", 1);
	inercia.setMinValue("speedY", -.3);
	inercia.setMaxValue("speedY", -.3);
	inercia.setMinValue("speedZ", 1);
	inercia.setMaxValue("speedZ", 1);		
	inercia.setMinValue("colorR", 0);
	inercia.setMaxValue("colorR", 1);	
	inercia.setMinValue("colorG", 0);
	inercia.setMaxValue("colorG", 1);	
	inercia.setMinValue("colorB", 0);
	inercia.setMaxValue("colorB", 1);	
	inercia.setMinValue("colorA", 1);
	inercia.setMaxValue("colorA", 1);	
	inercia.setMinValue("colorVR", 1);
	inercia.setMaxValue("colorVR", 5);	
	inercia.setMinValue("colorVG", 1);
	inercia.setMaxValue("colorVG", 5);	
	inercia.setMinValue("colorVB", 1);
	inercia.setMaxValue("colorVB", 5);	
	inercia.setMinValue("colorVA", -.001);
	inercia.setMaxValue("colorVA", -.002);	
	inercia.setMinValue("colorAR", 0);
	inercia.setMaxValue("colorAR", 0);	
	inercia.setMinValue("colorAG", 0);
	inercia.setMaxValue("colorAG", 0);	
	inercia.setMinValue("colorAB", 0);
	inercia.setMaxValue("colorAB", 0);	
	inercia.setMinValue("colorAA", 0);
	inercia.setMaxValue("colorAA", 0);	
	inercia.setMinValue("fade", 1);
	inercia.setMaxValue("fade", 1);		
	inercia.setMinValue("round", 1);
	inercia.setMaxValue("round", 1);	

	q.r = 5;
	q.g = 3;
	q.b = -15;
	q.a = 15;
	ParticleMoverForcesInertia::addGlobalDragPoint(q);

}

int main(int num, char** args)
{
    sizeX = 1024;
    sizeY = 800;
    glutInit(num, args, sizeX, sizeY);
    c = new MyLookAtCamera();
    c->setStart(0,0,0);
    c->setEnd(5,0,0);
    pAct.x = 5;
    pAct.y = 0;
    pAct.z = 0;

    renderTime.start();

    q = new Quad();
    q->r = 1;
    q->g = 1;
    q->b = 1;
    q->a = 1;
    
    setParticles();
    changeSize(sizeX, sizeY);
    
    glutMainLoop();

}
