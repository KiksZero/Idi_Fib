#include "LL2GLWidget.h"

#include "model.h"

class MyGLWidget : public LL2GLWidget {
  Q_OBJECT

  public:
    MyGLWidget(QWidget *parent=0) : LL2GLWidget(parent) {}
    ~MyGLWidget();

    virtual void paintGL ();
    virtual void iniCamera(); 
    virtual void viewTransform ();
    void viewTransformO ();
    void projectTransformO ();
    void homersTransform(int num);
    virtual void terraTransform();

    void keyPressEvent(QKeyEvent* event);
    void mouseMoveEvent(QMouseEvent *e);

    int nHomer = 10;
    float radiH = 4.0; //Radi cercle d'Homers
    float psi = 0.0;
    float theta = M_PI/4.0;
    float desfasament = 0;
    float xant = 0;
    float yant = 0;
    bool ortho = false;
    float left = -5*sqrt(2);
    float right =5*sqrt(2);
    float bottom =-5*sqrt(2);
    float top = 5*sqrt(2);

  private:
    int printOglError(const char file[], int line, const char func[]);
    
    
};
