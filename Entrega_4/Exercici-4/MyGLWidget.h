// MyGLWidget.h
#include "LL4GLWidget.h"

class MyGLWidget : public LL4GLWidget {
  Q_OBJECT

  public:
    MyGLWidget(QWidget *parent=0) : LL4GLWidget(parent) {}
    ~MyGLWidget();

  protected:
    virtual void keyPressEvent(QKeyEvent* event);
    virtual void initializeGL ();
    virtual void paintGL ();
    void calculaPosFocusP ();
    virtual glm::mat4 calculaPatricioTG();

  private:
    int printOglError(const char file[], int line, const char func[]);
    GLuint focusLocC, fcolorLocC;
    GLuint focusLoc, fcolorLoc;
    GLuint focusLocP, fcolorLocP;
    glm::vec3 posFocus;
    glm::vec3 posFocusC;
    glm::vec3 posFocusP;
    glm::vec3 colFocus;
    glm::vec3 colFocusC;
    glm::vec3 colFocusP;
    glm::vec4 posFocusPTemp;
    float despX, despZ,desfasament;
    bool apagarFocusC,apagarFocusP,apagarFocus;


};
