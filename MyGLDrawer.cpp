#include "MyGLDrawer.h"
#include "Shader.h"
#include "BasicTexture.h"
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include "Resource/Library/stb_image/stb_image.h"
#include <QKeyEvent>
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n\0";
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 5.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
MyGLDrawer::MyGLDrawer(QWidget* parent):
    QOpenGLWidget(parent)
{
    setMouseTracking(true);    // 关键：开启鼠标追踪
    setFocusPolicy(Qt::StrongFocus); // 确保可以获得焦点
    

}

void MyGLDrawer::Active(Info& info)
{
    int a = 10;

}
void MyGLDrawer::mouseMoveEvent(QMouseEvent* event)
{
    int a = 10;
    QWidget::mouseMoveEvent(event);
}

void MyGLDrawer::mousePressEvent(QMouseEvent* event)
{
    int a = 10;
    QWidget::mousePressEvent(event);
}
void MyGLDrawer::keyPressEvent(QKeyEvent* e)
{
    
    switch (e->key()) {
        case::Qt::Key_Up:
        {
            glm::vec3 moveStep(0.2f, 0.0f, 0.0f);
            if (m_shader) {
                makeCurrent();
                m_shader->moveModel(moveStep);
                this->update();
            }
            break;
        }
        case::Qt::Key_Down:
        {
            glm::vec3 moveStep(-0.2f, 0.0f, 0.0f);
            if (m_shader) {
                makeCurrent();
                m_shader->moveModel(moveStep);
                this->update();
            }
            break;
        }case::Qt::Key_Left:
        {
            glm::vec3 direction(0.0f, 1.0f, 0.0f);
            float degree = 10;
            if (m_shader) {
                makeCurrent();
                m_shader->rotateModel(direction,degree);
                this->update();
            }
            break;
        }
        case::Qt::Key_Right:
        {
            glm::vec3 direction(0.0f, 1.0f, 0.0f);
            float degree = -10;
            if (m_shader) {
                makeCurrent();
                m_shader->rotateModel(direction, degree);
                this->update();
            }
            break;
        }
        default:
            break;
    }

}

void MyGLDrawer::test()
{
    glm::mat4 rotaX(1.0f);
    rotaX = glm::rotate(rotaX, float(45), glm::vec3(1.0f, 0.0f, 0.0f));
    if (m_shader) {

        m_shader->loadModelMatrix(rotaX);
    }
}

void MyGLDrawer::initializeGL()
{

    initializeOpenGLFunctions();
    glEnable(GL_DEPTH_TEST);

    std::string vertexShaderPath("Resource/ShaderSources/shader.vs");
    std::string fragmentShaderPath("Resource/ShaderSources/shader.fs");
    m_shader = new Shader(vertexShaderPath,fragmentShaderPath);
   
    glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
    glm::mat4 projection = glm::mat4(1.0f);
    model = glm::rotate(model, (float)45, glm::vec3(0.0f, 1.0f, 0.0f));
    float divideValue = (float)this->width() / (float)this->height();
    projection = glm::perspective(glm::radians(45.0f), divideValue, 0.1f, 100.0f);

    m_shader->UseProgram();
    m_shader->loadModelMatrix(model);
    m_shader->loadViewMatrix(view);
    m_shader->loadProjectionViewMatrix(projection);
    
    m_texture = new BasicTexture("Resource/Textures/container.jpg");
    //m_texture = new BasicTexture("C:/Users/25097/Pictures/a.png");
    
    //float vertices[] = {
    //    // positions          // colors           // texture coords
    //     0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
    //     0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
    //    -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
    //    -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
    //};
    //unsigned int indices[] = {
    //    0, 1, 3, // first triangle
    //    1, 2, 3  // second triangle
    //};
    float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);


  

}

void  MyGLDrawer::resizeGL(int w, int h)
{
    // setup viewport, projection etc.:
    glViewport(0, 0, (GLint)w, (GLint)h);
}

void   MyGLDrawer::paintGL()
{

    // draw the scene:
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    m_texture->bindTexture();
    m_shader->UseProgram();
    glm::mat4 move(1.0f);
    move = glm::translate(move,glm::vec3(1.0f, 0.0f, 0.0f));
   // m_shader->loadModelMatrix(move);
    glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

    glDrawArrays(GL_TRIANGLES, 0, 36);


}
