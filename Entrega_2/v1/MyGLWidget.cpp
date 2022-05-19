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

MyGLWidget::~MyGLWidget()
{

}

void MyGLWidget::paintGL ()
{
// descomentar per canviar paràmetres
  // glViewport (0, 0, ample, alt);

  // Esborrem el frame-buffer
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Homer
  for (int i = 0; i < nHomer; ++i) {
      homersTransform(i);
      glBindVertexArray (VAO_Homer);
      glDrawArrays(GL_TRIANGLES, 0, modelHomer.faces().size()*3);
      glBindVertexArray (0);
  }
  

  // Terra
  terraTransform();
  glBindVertexArray (VAO_Terra);
  glDrawArrays(GL_TRIANGLES, 0, 6);
  glBindVertexArray (0);
}


void MyGLWidget::homersTransform(int num){
    glm::mat4 TG(1.0f);
    TG = glm::rotate(TG,(desfasament+float(num)*(2*float(M_PI)/nHomer)),glm::vec3(0.,1.,0.));
    TG = glm::translate(TG,glm::vec3(0.,0.,-radiH));
    TG = glm::scale(TG,glm::vec3(1.83/midaModelHomer,1.83/midaModelHomer,1.83/midaModelHomer));
    TG = glm::translate(TG, -baseHomer);
    glUniformMatrix4fv(transLoc, 1, GL_FALSE, &TG[0][0]);
}

void MyGLWidget::terraTransform(){
    glm::mat4 TG(1.0f);
    TG = glm::translate(TG, glm::vec3(-midaTerra/2.0,0.0,-midaTerra/2.0));
    TG = glm::scale(TG, glm::vec3(midaTerra, 1.0, midaTerra));
    glUniformMatrix4fv (transLoc, 1, GL_FALSE, &TG[0][0]);
} 


void MyGLWidget::iniCamera() {
  
    znear =  0.001;
    zfar  = 25;
    fov = float(M_PI)/4.0f;
    ra  = 1.0;
    viewTransform();
  LL2GLWidget::projectTransform();

}

void MyGLWidget::viewTransform () {
  glm::mat4 View(1.0f);
  View = glm::translate(View,glm::vec3(0.,0.,-19.5));
  View = glm::rotate(View, theta,glm::vec3(1.,0.,0.));
  View = glm::rotate(View, -psi, glm::vec3(0.,1.,0.));
  View = glm::translate(View,glm::vec3(0.,0.,0.5)); 
  glUniformMatrix4fv (viewLoc, 1, GL_FALSE, &View[0][0]);
}

void MyGLWidget::viewTransformO () {
  glm::mat4 View(1.0f);
  View = glm::lookAt (obs, vrp, up);
  glUniformMatrix4fv (viewLoc, 1, GL_FALSE, &View[0][0]);
}

void MyGLWidget::projectTransformO () {
  glm::mat4 Proj(1.0f);
  Proj = glm::ortho (left, right, bottom, top,znear,zfar);
  glUniformMatrix4fv (projLoc, 1, GL_FALSE, &Proj[0][0]);
}

void MyGLWidget::keyPressEvent(QKeyEvent* event)
{
  makeCurrent();
  switch (event->key()) {
      case Qt::Key_Plus :
            if(nHomer < 15)++nHomer;
          break;
      case Qt::Key_Minus :
            if(nHomer > 1)--nHomer;
          break;
      case Qt::Key_Up :
            if(radiH < 5.0) radiH+= 0.5;
          break;
      case Qt::Key_Down :
            if(radiH > 1.0) radiH-= 0.5;
          break;
      case Qt::Key_Right :
            if(desfasament > 2*float(M_PI)) desfasament = 0; 
            desfasament += float(M_PI)/36.0;
          break;
      case Qt::Key_Left :
            if(desfasament < 0) desfasament = 2*float(M_PI);
            desfasament -= float(M_PI)/36.0;
          break;
      case Qt::Key_C :
            if (!ortho) {
                obs = glm::vec3(0, 19.5, 0);
                vrp = glm::vec3(0, 0, 0);
                up = glm::vec3(0, 0, 1);
                viewTransformO();
                projectTransformO();
                ortho = true;
            } 
            else {ortho = false;
                fov = float(M_PI)/4.0f;
                ra  = 1.0;
                viewTransform();
                LL2GLWidget::projectTransform();
            }
          break; 
      case Qt::Key_R :
            nHomer = 10;
            radiH = 4;
            psi = 0.0;
            theta = M_PI/4.0;
            desfasament = 0;
            ortho = false;
            fov = float(M_PI)/4.0f;
            ra  = 1.0;
            viewTransform();
            LL2GLWidget::projectTransform();

          break;      

    default: event->ignore(); break;
  }
  update();
}


void MyGLWidget::mouseMoveEvent(QMouseEvent *e)
{
  makeCurrent();

    if (DoingInteractive == ROTATE) {
        float angleX = e->x() -xClick;
        float angleY = e->y() -yClick;
        psi += angleX*factorAngleX;
        theta += angleY*factorAngleY;
    }
   
  iniCamera();

  update ();
}
