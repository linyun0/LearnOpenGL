#include "Qt_OpenGL.h"
#include <QGLWidget>
#include "MyGLDrawer.h"
#include <FreeImage.h>
#include <iostream>


#include <FreeImage.h>
#include <iostream>
#include <string>
#include "UI/MyControlWidget.h"
#include "UI/DlgControl.h"

Qt_OpenGL::Qt_OpenGL(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    glDrawer =new MyGLDrawer(this);
    glDrawer->setMinimumSize(400, 300);
    this->setCentralWidget(glDrawer);
 
    
    dlgBox = new MyControlWidget(this,dynamic_cast<DialogCmd*>(glDrawer));
    glDrawer->SetDlgBox(dlgBox);
   
    dockWidget = new QDockWidget(this);
    dockWidget->setWidget(dlgBox);
    
    this->addDockWidget(Qt::RightDockWidgetArea, dockWidget);
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


    


