#ifndef __CAMERA__HPP__
#define __CAMERA__HPP__

#include <GL/gl.h>

struct perspective
{
    float angle;
    double ratio;
    double zNear;
    double zFar;
};

struct tri
{
    double x;
    double y;
    double z;
};

class Camera
{
    public:
        Camera();
        Camera(const Camera&);
        virtual ~Camera();

        virtual void set() const;
        virtual void render() const= 0;

        void setRatio(double val) {p.ratio = val;};
        void setAngle(double val) {p.angle = val;};
        void setNear (double val) {p.zNear = val;};
        void setFar  (double val) {p.zFar = val;};

        void setHeight (int val);
        void setWidth (int val);

        void setPerspective() {usePerspective = true;};
        void unsetPerspective() {usePerspective = false;};

        virtual void setPosX(double val) {t.x = val;};
        virtual void setPosY(double val) {t.y = val;};
        virtual void setPosZ(double val) {t.z = val;};
        virtual void setRotX(double val) {};
        virtual void setRotY(double val) {};
        virtual void setRotZ(double val) {};
        virtual void setScaX(double val) {s.x = val;};
        virtual void setScaY(double val) {s.y = val;};
        virtual void setScaZ(double val) {s.z = val;};
        virtual void addPosX(double val) {t.x += val;};
        virtual void addPosY(double val) {t.y += val;};
        virtual void addPosZ(double val) {t.z += val;};
        virtual void addRotX(double val) {};
        virtual void addRotY(double val) {};
        virtual void addRotZ(double val) {};
        virtual void addScaX(double val) {s.x += val;};
        virtual void addScaY(double val) {s.y += val;};
        virtual void addScaZ(double val) {s.z += val;};
        
    protected:
        tri s;
        tri t;


    private:
        bool usePerspective;
        perspective p;
        int height;
        int width;
        int sX;
        int sY;
};

class FreeCamera : public Camera
{
    public:
        FreeCamera();
        FreeCamera(const FreeCamera&);
        ~FreeCamera();

        virtual void render() const;

        virtual void setRotX(double val) {r.x = val;};
        virtual void setRotY(double val) {r.y = val;};
        virtual void setRotZ(double val) {r.z = val;};
        virtual void addRotX(double val) {r.x += val;};
        virtual void addRotY(double val) {r.y += val;};
        virtual void addRotZ(double val) {r.z += val;};


    private:
        tri r;
};

class LookAtCamera: public Camera
{
    public:
        LookAtCamera();
        LookAtCamera(const LookAtCamera&);
        virtual ~LookAtCamera();

        virtual void render() const;

        virtual void setRotX(double val) {up.x = val;};
        virtual void setRotY(double val) {up.y = val;};
        virtual void setRotZ(double val) {up.z = val;};
        virtual void addRotX(double val) {up.x += val;};
        virtual void addRotY(double val) {up.y += val;};
        virtual void addRotZ(double val) {up.z += val;};

        void setStart(double x, double y, double z);
        void setEnd(double x, double y, double z);
        void setUp(double x, double y, double z);

    private:
        tri end;
        tri up;
};
class MyLookAtCamera: public Camera
{
    public:
        MyLookAtCamera();
        MyLookAtCamera(const MyLookAtCamera&);
        virtual ~MyLookAtCamera();

        virtual void render() const;

        
        virtual void setPosX(double val) {Camera::setPosX(val);calcMatrix();};
        virtual void setPosY(double val) {Camera::setPosY(val);calcMatrix();};
        virtual void setPosZ(double val) {Camera::setPosZ(val);calcMatrix();};
        virtual void addPosX(double val) {Camera::addPosX(val);calcMatrix();};
        virtual void addPosY(double val) {Camera::addPosY(val);calcMatrix();};
        virtual void addPosZ(double val) {Camera::addPosZ(val);calcMatrix();};
        virtual void setRotX(double val) {end.x = val/100;calcMatrix();};
        virtual void setRotY(double val) {end.y = val/100;calcMatrix();};
        virtual void setRotZ(double val) {end.z = val/100;calcMatrix();};
        virtual void addRotX(double val) {end.x += val/100;calcMatrix();};
        virtual void addRotY(double val) {end.y += val/100;calcMatrix();};
        virtual void addRotZ(double val) {end.z += val/100;calcMatrix();};

        void setStart(double x, double y, double z);
        void setEnd(double x, double y, double z);
        void setUp(double x, double y, double z);

    private:

        void calcMatrix();
    
        GLdouble matrix[16];
        tri end;
        tri up;
};


#endif
