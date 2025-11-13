#include "Qt_OpenGL.h"
#include <QGLWidget>
#include "MyGLDrawer.h"
#include <FreeImage.h>
#include <iostream>


#include <FreeImage.h>
#include <iostream>
#include <string>
#include "UI/MyControlWidget.h"


Qt_OpenGL::Qt_OpenGL(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    glDrawer =new MyGLDrawer(this);
    this->setCentralWidget(glDrawer);
    dlgBox = new MyControlWidget(this,glDrawer);
    dockWidget = new QDockWidget(this);
    this->addDockWidget(Qt::RightDockWidgetArea, dockWidget);
    dockWidget->setWidget(dlgBox);
}

Qt_OpenGL::~Qt_OpenGL()
{
    if (glDrawer) {
        delete glDrawer;
    }
    if (dockWidget) {
        delete dockWidget;
    }
}


