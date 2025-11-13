#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Qt_OpenGL.h"
#include "MyGLDrawer.h" 
#include <QDockWidget>
class MyControlWidget;
class Qt_OpenGL : public QMainWindow
{
    Q_OBJECT

public:
    Qt_OpenGL(QWidget *parent = nullptr);
    ~Qt_OpenGL();
private:
    Ui::Qt_OpenGLClass ui;
    QDockWidget* dockWidget = nullptr;
    MyControlWidget* dlgBox = nullptr;
    MyGLDrawer* glDrawer = nullptr;
};

