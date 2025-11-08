#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Qt_OpenGL.h"
#include "MyGLDrawer.h" 
class Qt_OpenGL : public QMainWindow
{
    Q_OBJECT

public:
    Qt_OpenGL(QWidget *parent = nullptr);
    ~Qt_OpenGL();
private:
    Ui::Qt_OpenGLClass ui;

    MyGLDrawer* glDrawer = nullptr;
};

