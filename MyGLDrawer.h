#pragma once
#include <QGLWidget> 
#include <qopenglwidget.h>
#include <qopenglfunctions_3_3_core.h>
#include <gl/GLU.h>
class QGLWidget;
class Shader;
class BasicTexture;
//const char* vertexShaderSource = "#version 330 core\n"
//"layout (location = 0) in vec3 aPos;\n"
//"void main()\n"
//"{\n"
//"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
//"}\0";
//const char* fragmentShaderSource = "#version 330 core\n"
//"out vec4 FragColor;\n"
//"void main()\n"
//"{\n"
//"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
//"}\n\0";


class MyGLDrawer : public QOpenGLWidget,QOpenGLFunctions_3_3_Core
{
    Q_OBJECT        // must include this if you use Qt signals/slots

public:
    MyGLDrawer(QWidget* parent);
private:
    unsigned int VAO, VBO, EBO, m_shaderProgram, shaderProgram;
    Shader* m_shader=nullptr;
    BasicTexture* m_texture=nullptr;

private:

    virtual void mouseMoveEvent(QMouseEvent* event) override;

    virtual void mousePressEvent(QMouseEvent* event) override;

protected:
    void initializeGL() override;

    void resizeGL(int w, int h) override;

    void paintGL() override;

};
