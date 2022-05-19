// MyGLWidget.cpp
#include "MyGLWidget.h"
#include <iostream>
#include <stdio.h>

#define printOpenGLError() printOglError(__FILE__, __LINE__)
#define CHECK() printOglError(__FILE__, __LINE__,__FUNCTION__)
#define DEBUG() std::cout << __FILE__ << " " << __LINE__ << " " << __FUNCTION__ << std::endl;

int MyGLWidget::printOglError(const char file[], int line, const char func[]) 
{
    GLenum glErr;
    int    retCode = 0;

    glErr = glGetError();
    const char * error = 0;
    switch (glErr)
    {
        case 0x0500:
            error = "GL_INVALID_ENUM";
            break;
        case 0x501:
            error = "GL_INVALID_VALUE";
            break;
        case 0x502: 
            error = "GL_INVALID_OPERATION";
            break;
        case 0x503:
            error = "GL_STACK_OVERFLOW";
            break;
        case 0x504:
            error = "GL_STACK_UNDERFLOW";
            break;
        case 0x505:
            error = "GL_OUT_OF_MEMORY";
            break;
        default:
            error = "unknown error!";
    }
    if (glErr != GL_NO_ERROR)
    {
        printf("glError in file %s @ line %d: %s function: %s\n",
                             file, line, error, func);
        retCode = 1;
    }
    return retCode;
}

MyGLWidget::~MyGLWidget() {
}

void MyGLWidget::initializeGL (){
    LL4GLWidget::initializeGL();
    despX= 5;
    despZ= 2;
    desfasament=0;
    apagarFocusC = false;
    apagarFocusP = false;
    apagarFocus = false;

    focusLocC = glGetUniformLocation(program->programId(),"posFocusC");
    fcolorLocC= glGetUniformLocation(program->programId(),"colFocusC");

    focusLoc = glGetUniformLocation(program->programId(),"posFocus");
    fcolorLoc= glGetUniformLocation(program->programId(),"colFocus");

    focusLocP = glGetUniformLocation(program->programId(),"posFocusP");
    fcolorLocP= glGetUniformLocation(program->programId(),"colFocusP");

    
}

void MyGLWidget::calculaPosFocusP(){ 
float minx, miny, minz, maxx, maxy, maxz;
  minx = maxx = patr.vertices()[0];
  miny = maxy = patr.vertices()[1];
  minz = maxz = patr.vertices()[2];
  for (unsigned int i = 3; i < patr.vertices().size(); i+=3)
  {
    if (patr.vertices()[i+0] < minx)
      minx = patr.vertices()[i+0];
    if (patr.vertices()[i+0] > maxx)
      maxx = patr.vertices()[i+0];
    if (patr.vertices()[i+1] < miny)
      miny = patr.vertices()[i+1];
    if (patr.vertices()[i+1] > maxy)
      maxy = patr.vertices()[i+1];
    if (patr.vertices()[i+2] < minz)
      minz = patr.vertices()[i+2];
    if (patr.vertices()[i+2] > maxz)
      maxz = patr.vertices()[i+2];
  }
  posFocusPTemp[0] = minx; 
  posFocusPTemp[1] = (miny+maxy)/2.0;
  posFocusPTemp[2] = (minz+maxz)/2.0; 
  posFocusPTemp[3] = 1.0;
}


void MyGLWidget::paintGL(){


    posFocusC = glm::vec3(0,0,0);
    
    if (!apagarFocusC) colFocusC= glm::vec3(0.9,0.2,0.2);
    else colFocusC= glm::vec3(0.,0.,0.);

    glUniform3fv(focusLocC,1,&posFocusC[0]);
    glUniform3fv(fcolorLocC,1,&colFocusC[0]);

    posFocus = glm::vec3(View*glm::vec4(8.0,3.0,2.0,1.0));
    if (!apagarFocus)colFocus = glm::vec3(0.2,0.9,0.2);
    else colFocus= glm::vec3(0.,0.,0.);

    glUniform3fv(focusLoc,1,&posFocus[0]);
    glUniform3fv(fcolorLoc,1,&colFocus[0]);


    calculaPosFocusP();
    posFocusP = glm::vec3(View*calculaPatricioTG()*posFocusPTemp);
    if (!apagarFocusP) colFocusP= glm::vec3(0.2,0.2,0.9);
    else colFocusP= glm::vec3(0.,0.,0.);

    glUniform3fv(focusLocP,1,&posFocusP[0]);
    glUniform3fv(fcolorLocP,1,&colFocusP[0]);



    LL4GLWidget::paintGL();
}

glm::mat4 MyGLWidget::calculaPatricioTG()
{

  glm::mat4 tg = glm::translate(glm::mat4(1.f), glm::vec3(despX,0,despZ));
  tg = glm::rotate(tg,desfasament,glm::vec3(0.,1.,0.));
  tg = glm::scale(tg, glm::vec3(escala, escala, escala));
  tg = glm::translate(tg, -centreBasePatr);
  return tg;
}

void MyGLWidget::keyPressEvent(QKeyEvent* event) {
  makeCurrent();
  switch (event->key()) {

  case Qt::Key_Right:
      if(despX<8)++despX;
    break;

  case Qt::Key_Left:
      if(despX>2)--despX;
    break;

  case Qt::Key_Up:
      if(despZ<9)++despZ;
    break;

  case Qt::Key_Down:
      if(despZ>1)--despZ;
    break;

  case Qt::Key_R:
      if(desfasament > 2*float(M_PI)) desfasament = 0; 
      desfasament += float(M_PI)/4;
    break;

  case Qt::Key_C:
     if (not apagarFocusC) apagarFocusC= true;
     else apagarFocusC= false;
    break;

  case Qt::Key_E:
      if (not apagarFocus) apagarFocus= true;
      else apagarFocus= false;
    break;

  case Qt::Key_P:
      if (not apagarFocusP) apagarFocusP= true;
      else apagarFocusP= false;
    break;

  default: LL4GLWidget::keyPressEvent(event); break;
  }
  update();
}
