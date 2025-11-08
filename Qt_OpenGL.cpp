#include "Qt_OpenGL.h"
#include <QGLWidget>
#include "MyGLDrawer.h"
#include <FreeImage.h>
#include <iostream>


#include <FreeImage.h>
#include <iostream>
#include <string>


Qt_OpenGL::Qt_OpenGL(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    glDrawer =new MyGLDrawer(this);
    this->setCentralWidget(glDrawer);
}

Qt_OpenGL::~Qt_OpenGL()
{
    if (glDrawer) {
        delete glDrawer;
    }
}


