#include "camera.hpp"

#include <iostream>
using namespace std;

#include <GL/gl.h>
#include <GL/glu.h>
#include <cmath>

Camera::Camera()
{
    p.angle = 45;
    p.ratio = 1;
    p.zFar = 100;
    p.zNear = 0.1;
    height = 100;
    width = 100;
    sX = 0;
    sY = 0;
    s.x = 1;
    s.y = 1;
    s.z = 1;
    t.x = 0;
    t.y = 0;
    t.z = 0;
}

Camera::Camera(const Camera &c)
{
    p = c.p;
    height = c.height;
    width = c.height;
    sX = c.sX;
    sY = c.sY;
    s = c.s;
    t = c.t;
}

Camera::~Camera()
{

}

void
Camera::set() const
{
	glLoadIdentity();   
    glViewport(sX, sY, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (usePerspective)
    {
        gluPerspective(p.angle, p.ratio, p.zNear, p.zFar);
    }
    else
    {
        gluPerspective(0, p.ratio, p.zNear, p.zFar);
    }
	glMatrixMode(GL_MODELVIEW);
}

void
Camera::setHeight (int val)
{
    height = val;
    p.ratio = (float)width / (float)(height>0?height:1);
}

void
Camera::setWidth (int val)
{
    width = val;
    p.ratio = (float) width / (float)(height>0?height:1);
}


/*~~~~~~~~~~~~~~*/


FreeCamera::FreeCamera() : Camera()
{
    t.x = 0;
    t.y = 0;
    t.z = 0;
    r.x = 0;
    r.y = 0;
    r.z = 0;
}

FreeCamera::FreeCamera(const FreeCamera & c) : Camera(c)
{
    t = c.t;
    r = c.r;
}


FreeCamera::~FreeCamera()
{

}

void
FreeCamera::render() const
{
    glLoadIdentity();
    glTranslatef(t.x, t.y, t.z);
    glRotatef(r.x, 1, 0 ,0);
    glRotatef(r.y, 0, 1 ,0);
    glRotatef(r.z, 0, 0 ,1);
    glScalef(s.x, s.y, s.z);
}


/*~~~~~~~~~~~~~~*/

LookAtCamera::LookAtCamera():Camera()
{
    end.x = end.y = end.z = 1;
    up.x = up.z = 0;
    up.y = 1;
}

LookAtCamera::LookAtCamera(const LookAtCamera& c):Camera(c)
{
    end = c.end;
    up = c.up;
}


LookAtCamera::~LookAtCamera()
{

}

void
LookAtCamera::render() const
{
    glLoadIdentity();
    gluLookAt(    t.x,     t.y,     t.z,
                end.x,   end.y,   end.z,
                 up.x,    up.y,    up.z);
    glScalef(s.x, s.y, s.z);
}

void
LookAtCamera::setStart(double x, double y, double z)
{
    t.x = x;
    t.y = y;
    t.z = z;
}

void
LookAtCamera::setEnd(double x, double y, double z)
{
    end.x = x;
    end.y = y;
    end.z = z;
}

void
LookAtCamera::setUp(double x, double y, double z)
{
    up.x = x;
    up.y = y;
    up.z = z;
}

/*~~~~~~~~~~~~~~*/

MyLookAtCamera::MyLookAtCamera():Camera()
{
    t.x = t.y = t.z = 0;
    s.x = s.y = s.z = 1;
}

MyLookAtCamera::MyLookAtCamera(const MyLookAtCamera& c):Camera(c)
{
    end = c.end;
    up = c.up;
    s = c.s;
}

MyLookAtCamera::~MyLookAtCamera()
{

}

void
MyLookAtCamera::render() const
{
    glLoadIdentity();
    glMultMatrixd(matrix); 
    glTranslatef (-t.x, -t.y, -t.z);
    glScalef(s.x, s.y, s.z);
}

void
MyLookAtCamera::setStart(double x, double y, double z)
{
    t.x = x;
    t.y = y;
    t.z = z;
    calcMatrix();
}

void
MyLookAtCamera::setEnd(double x, double y, double z)
{
    end.x = x;
    end.y = y;
    end.z = z;
    calcMatrix();
}

void
MyLookAtCamera::setUp(double x, double y, double z)
{
    up.x = x;
    up.y = y;
    up.z = z;
    calcMatrix();
}

void CrossProd( float x1, float y1, float z1,
                float x2, float y2, float z2,
                float res[3]) 
{ 
    res[0] = y1*z2 - y2*z1; 
    res[1] = x2*z1 - x1*z2; 
    res[2] = x1*y2 - x2*y1; 
} 

void
MyLookAtCamera::calcMatrix()
{

    float f[3];
    float s[3], u[3]; 
    
    f[0] = end.x - t.x;
    f[1] = end.y - t.y;
    f[2] = end.z - t.z;

    float fMag, upMag; 
    fMag = sqrt(f[0]*f[0] + f[1]*f[1] + f[2]*f[2]); 
    upMag = sqrt(up.x*up.x + up.y*up.y + up.z*up.z); 

    if ( fMag != 1 ) 
    { 
        f[0] = f[0]/fMag; 
        f[1] = f[1]/fMag; 
        f[2] = f[2]/fMag; 
    } 

    if ( upMag != 1 ) 
    { 
        up.x = up.x/upMag; 
        up.y = up.y/upMag; 
        up.z = up.z/upMag; 
    } 

    CrossProd(f[0], f[1], f[2], up.x, up.y, up.z, s); 
    CrossProd(s[0], s[1], s[2], f[0], f[1], f[2], u); 

    matrix[0] = s[0];
    matrix[1] = u[0];
    matrix[2] = -f[0];
    matrix[3] = 0;
    matrix[4] = s[1];
    matrix[5] = u[1];
    matrix[6] = -f[1];
    matrix[7] = 0;
    matrix[8] = s[2];
    matrix[9] = u[2];
    matrix[10] = -f[2];
    matrix[11] = 0;
    matrix[12] = 0;
    matrix[13] = 0;
    matrix[14] = 0; 
    matrix[15] = 1;
}




