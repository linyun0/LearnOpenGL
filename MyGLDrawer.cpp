#include "MyGLDrawer.h"
#include "Shader.h"
#include "BasicTexture.h"
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>

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

MyGLDrawer::MyGLDrawer(QWidget* parent):
    QOpenGLWidget(parent)
{
    setMouseTracking(true);    // 关键：开启鼠标追踪
    setFocusPolicy(Qt::StrongFocus); // 确保可以获得焦点

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
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
void MyGLDrawer::initializeGL()
{

    initializeOpenGLFunctions();
    glEnable(GL_DEPTH_TEST);

    std::string vertexShaderPath("Resource/ShaderSources/shader.vs");
    std::string fragmentShaderPath("Resource/ShaderSources/shader.fs");
    m_shader = new Shader(vertexShaderPath,fragmentShaderPath);
   
    // create transformations
    glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
    glm::mat4 projection = glm::mat4(1.0f);
  //  glm::mat4 view = glm::mat4(1.0f);
    model = glm::rotate(model, (float)45, glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, (float)45, glm::vec3(1.0f, 0.0f, 0.0f));
    //int width = this->width();
    //int height = this->height();
    float divideValue = (float)this->width() / (float)this->height();
    projection = glm::perspective(glm::radians(45.0f), divideValue, 0.1f, 100.0f);
    m_shader->loadModelMatrix(model);
    m_shader->loadViewMatrix(view);
    m_shader->loadProjectionViewMatrix(projection);
    
    m_texture = new BasicTexture("Resource/Textures/container.jpg");
    
    //float vertices[] = {
    //        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
    //         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
    //         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    //         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    //        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    //        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f
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

    //unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)3);
    glEnableVertexAttribArray(1);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0);
  

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
    //glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    //glClear(GL_COLOR_BUFFER_BIT);

   // m_shader->UseProgram();
   // glUseProgram(m_shaderProgram);
    //glBindVertexArray(VAO);
    //glDrawArrays(GL_TRIANGLES, 0, 3);
        // draw our first triangle
 //   glUseProgram(shaderProgram);
    m_shader->UseProgram();
    glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
    m_texture->setInt("texture1", 0);
    m_texture->bindTexture();
    glDrawArrays(GL_TRIANGLES, 0, 36);
}
