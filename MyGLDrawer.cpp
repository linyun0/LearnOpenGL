#include "MyGLDrawer.h"
#include "Basic/Shader.h"
#include "BasicTexture.h"
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include "Resource/Library/stb_image/stb_image.h"
#include <QKeyEvent>
#include <QElapsedTimer>
#include "Basic/Model.h"
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 5.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

MyGLDrawer::MyGLDrawer(QWidget* parent):
    QOpenGLWidget(parent)
{
    setMouseTracking(true);    // 关键：开启鼠标追踪
    setFocusPolicy(Qt::StrongFocus); // 确保可以获得焦点
    
    this->setBaseSize(QSize(400, 400));
}

void MyGLDrawer::Active(Info& info)
{
    int a = 10;

}
void MyGLDrawer::Activate(DlgControl* control)
{
    int ID = control->GetId();
    switch (ID) {
    case Model_Index_X:
    case Model_Index_Y:
    case Model_Index_Z:
    case Model_Roate_X:
    case Model_Roate_Y:
    case Model_Roate_Z:
    case Model_Scale:
    {

        UpDateModelInfo();
        break;
    }
    case Camera_Position_X:
    case Camera_Position_Y:
    case Camera_Position_Z:
    case Camera_Target_X:
    case Camera_Target_Y:
    case Camera_Target_Z:
    {
        UpDateCamera();
        break;
    }
    default:
        break;
    }
}
void MyGLDrawer::InitUI()
{
    DlgControl* control = nullptr;
    control = dlgBox->GetControl(Model_Index_X);
    control->SetString(QString::number(0));
    control = dlgBox->GetControl(Model_Index_Y);
    control->SetString(QString::number(0));
    control = dlgBox->GetControl(Model_Index_Z);
    control->SetString(QString::number(0));
    control = dlgBox->GetControl(Model_Roate_X);
    control->SetString(QString::number(0));
    control = dlgBox->GetControl(Model_Roate_Y);
    control->SetString(QString::number(0));
    control = dlgBox->GetControl(Model_Roate_Z);
    control->SetString(QString::number(0));
    control = dlgBox->GetControl(Model_Scale);
    control->SetString(QString::number(1));

    control = dlgBox->GetControl(Model_Point_Val);
    if (control) {
        int pointNumber = model->getPointsNumber();
        QString info = QString::fromLocal8Bit("顶点个数:") + QString::number(pointNumber);
        control->SetString(info);
    }
}

void MyGLDrawer::UpDateCameraInfoToUI()
{
    glm::vec3 position = m_camera->Position;
    DlgControl* control = nullptr;
    control = dlgBox->GetControl(Camera_Position_X);
    control->SetString(QString::number(position.x));
    control = dlgBox->GetControl(Camera_Position_Y);
    control->SetString(QString::number(position.y));
    control = dlgBox->GetControl(Camera_Position_Z);
    control->SetString(QString::number(position.z));

    glm::vec3 target = m_camera->Front;
    control = dlgBox->GetControl(Camera_Target_X);
    control->SetString(QString::number(target.x));
    control = dlgBox->GetControl(Camera_Target_Y);
    control->SetString(QString::number(target.y));
    control = dlgBox->GetControl(Camera_Target_Z);
    control->SetString(QString::number(target.z));

}

void MyGLDrawer::UpDateCamera()
{
    glm::vec3 position;
    DlgControl* control = nullptr;
    control = dlgBox->GetControl(Camera_Position_X);
    position.x = control->GetString().toFloat();
    control = dlgBox->GetControl(Camera_Position_Y);
    position.y = control->GetString().toFloat();
    control = dlgBox->GetControl(Camera_Position_Z);
    position.z = control->GetString().toFloat();

    glm::vec3 target;
    control = dlgBox->GetControl(Camera_Target_X);
    target.x = control->GetString().toFloat();
    control = dlgBox->GetControl(Camera_Target_Y);
    target.y = control->GetString().toFloat();
    control = dlgBox->GetControl(Camera_Target_Z);
    target.z = control->GetString().toFloat();

    m_camera->Position = position;
    m_camera->Front = target;

    makeCurrent();
    m_shader->use();
    m_shader->setMat4("view", m_camera->GetViewMatrix());
    this->update();
}

void MyGLDrawer::UpDateModelInfo()
{
    DlgControl* control = nullptr;
    control = dlgBox->GetControl(Model_Index_X);
    double locx = control->GetString().toDouble();
    control = dlgBox->GetControl(Model_Index_Y);
    double locy = control->GetString().toDouble();
    control = dlgBox->GetControl(Model_Index_Z);
    double locz = control->GetString().toDouble();

    control = dlgBox->GetControl(Model_Roate_X);
    double rotx = control->GetString().toDouble();
    control = dlgBox->GetControl(Model_Roate_Y);
    double roty = control->GetString().toDouble();
    control = dlgBox->GetControl(Model_Roate_Z);
    double rotz = control->GetString().toDouble();

    control = dlgBox->GetControl(Model_Scale);
    double scale = control->GetString().toDouble();

    glm::mat4 matrix = glm::mat4(1.0f);
    matrix = glm::translate(matrix, glm::vec3(locx,locy,locz));

    matrix = glm::rotate(matrix, glm::radians(float(rotx)), glm::vec3(1.0f, 0.0f, 0.0f));
    matrix = glm::rotate(matrix, glm::radians(float(roty)), glm::vec3(0.0f, 1.0f, 0.0f));
    matrix = glm::rotate(matrix, glm::radians(float(rotz)), glm::vec3(0.0f, 0.0f, 1.0f));
    
    matrix = glm::scale(matrix,glm::vec3(float(scale), float(scale), float(scale)));

    makeCurrent();
    m_shader->use();
    m_shader->setMat4("model", matrix);
    this->update();
}

void MyGLDrawer::showEvent(QShowEvent* event)
{
    InitUI();
    UpDateCameraInfoToUI();
    QWidget::showEvent(event);
}
void MyGLDrawer::mouseMoveEvent(QMouseEvent* event)
{
    if (ctrlPressed&&leftButtonPressed) {
        QPoint currentPoint = event->pos();
        float xoffset = currentPoint.x() - lastPoint.x();
        float yoffset = currentPoint.y() - lastPoint.y();

        //int width = this->width()/2;
        //int height = this->height()/2;
        //
        //double AngleX = (xoffset / width) * 360;
        //double AngleY = (yoffset / height) * 360;
    
        m_camera->rotateAroundX(-1);
       // m_camera->rotateAroundY(AngleY);
        //m_camera->ProcessMouseMovement(xoffset, yoffset);
        makeCurrent();
        m_shader->use();
        m_shader->setMat4("view", m_camera->GetViewMatrix());
        this->update();
       // lastPoint = event->pos();
    }
    else {
        lastPoint = event->pos();
    }

    QWidget::mouseMoveEvent(event);
}

void MyGLDrawer::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton&&ctrlPressed) {
        leftButtonPressed = true;
    }
    
    QWidget::mousePressEvent(event);
}
void MyGLDrawer::mouseReleaseEvent(QMouseEvent* event)
{

    if (event->button() == Qt::LeftButton&&ctrlPressed) {
        
        leftButtonPressed = false;

    }

    QWidget::mouseReleaseEvent(event);
}

void MyGLDrawer::wheelEvent(QWheelEvent* event)
{
    if (ctrlPressed)
    {
        QPoint angleDelta = event->angleDelta();
        double scrollAmount = angleDelta.y() / 12.0;  // 调整灵敏度
        m_camera->ProcessMouseScroll(scrollAmount);
        makeCurrent();
        m_shader->use();

        glm::mat4 projection = glm::mat4(1.0f);
        float divideValue = (float)this->width() / (float)this->height();
        projection = glm::perspective(glm::radians(m_camera->Zoom), divideValue, 0.1f, 100.0f);
        m_shader->setMat4("projection", projection);

        this->update();
    }
    event->accept();
}
void MyGLDrawer::keyPressEvent(QKeyEvent* e)
{
    
    switch (e->key()) {
        case::Qt::Key_Up:
        {
            glm::vec3 moveStep(0.2f, 0.0f, 0.0f);
            if (m_shader) {
                m_camera->ProcessKeyboard(FORWARD, deltaTime);
                makeCurrent();
                m_shader->use();
                m_shader->setMat4("view", m_camera->GetViewMatrix());
                this->update();
            }
            //m_camera->ProcessMouseMovement(10, 10);
            //makeCurrent();
            //m_shader->use();
            //m_shader->setMat4("view", m_camera->GetViewMatrix());
            //this->update();
            break;
        }
        case::Qt::Key_Down:
        {
            glm::vec3 moveStep(0.2f, 0.0f, 0.0f);
            if (m_shader) {
                m_camera->ProcessKeyboard(BACKWARD, deltaTime);
                makeCurrent();
                m_shader->use();
                m_shader->setMat4("view", m_camera->GetViewMatrix());
                this->update();
            }
            break;
        }case::Qt::Key_Left:
        {
            glm::vec3 moveStep(0.2f, 0.0f, 0.0f);
            if (m_shader) {
                m_camera->ProcessKeyboard(LEFT, deltaTime);
                makeCurrent();
                m_shader->use();
                m_shader->setMat4("view", m_camera->GetViewMatrix());
                this->update();
            }
            break;
        }
        case::Qt::Key_Right:
        {
            glm::vec3 moveStep(0.2f, 0.0f, 0.0f);
            if (m_shader) {
                m_camera->ProcessKeyboard(RIGHT, deltaTime);
                makeCurrent();
                m_shader->use();
                m_shader->setMat4("view", m_camera->GetViewMatrix());
                this->update();
            }
            break;
        }
        case::Qt::Key_Control:
        {
            ctrlPressed = true;
            break;
        }
        default:
            break;
    }

}

void MyGLDrawer::keyReleaseEvent(QKeyEvent* e)
{
    if (e->key() == Qt::Key_Control)
    {
        ctrlPressed = false;
    }
    QWidget::keyReleaseEvent(e);
}


void MyGLDrawer::initializeGL()
{

    initializeOpenGLFunctions();
    glEnable(GL_DEPTH_TEST);
    m_camera = new Camera(glm::vec3(0.0f,0.0f,8.0f));
    model = new Model("D:/VisualStudio_Project/Qt_OpenGL/Resource/Models/backpack/backpack.obj");
    int number = model->getPointsNumber();

    std::string vertexShaderPath("Resource/ShaderSources/shader.vs");
    std::string fragmentShaderPath("Resource/ShaderSources/shader.fs");
    m_shader = new Shader(vertexShaderPath.c_str(), fragmentShaderPath.c_str());
   
    float divideValue = (float)this->width() / (float)this->height();
    projection = glm::perspective(glm::radians(45.0f), divideValue, 0.1f, 100.0f);
    modelmatrix = glm::scale(modelmatrix, glm::vec3(1.0f, 1.0f, 1.0f));	// it's a bit too big for our scene, so scale it down

    m_shader->use(); 
    m_shader->setMat4("projection", projection);
    m_shader->setMat4("view",m_camera->GetViewMatrix());
    m_shader->setMat4("model", modelmatrix);
    m_shader->setBool("isUseTexture",true);
    m_shader->setBool("isUseLight",false);

}

void  MyGLDrawer::resizeGL(int w, int h)
{
    // setup viewport, projection etc.:
    glViewport(0, 0, (GLint)w, (GLint)h);

}

void   MyGLDrawer::paintGL()
{
    QElapsedTimer timer;
    timer.start();
    // draw the scene:
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    m_shader->use();
    model->Draw(*m_shader);

    deltaTime = 1;

}
