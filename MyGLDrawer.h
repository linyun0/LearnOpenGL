#pragma once
#include <QGLWidget> 
#include <qopenglwidget.h>
#include <qopenglfunctions_3_3_core.h>
#include <gl/GLU.h>
#include "UI/Control.h"
#include "UI/DlgControl.h"
#include "Basic/Camera.h"
class QGLWidget;
class Shader;
class BasicTexture;
class Model;
class Camera;
class SLWDColorDialog;

class MyGLDrawer : public QOpenGLWidget,public QOpenGLFunctions_3_3_Core,public DialogCmd
{
    Q_OBJECT        // must include this if you use Qt signals/slots

public:
    MyGLDrawer(QWidget* parent);
    void Active(Info& info);
    void Activate(DlgControl* control);

    void Test();
private:
    void InitUI() override;
    void UpDateCameraInfoToUI();
    void UpDateCamera();
    void UpDateModelInfo();
    void UpDateLightColor(const QColor& color);
private:
    QTimer* timer=nullptr;
    unsigned int VAO, VBO, EBO, m_shaderProgram, shaderProgram;
    Shader* m_shader=nullptr;
    BasicTexture* m_texture=nullptr;
    unsigned int m_Tex;
    Model* model=nullptr;
private:
    void showEvent(QShowEvent* event) override;
private:
    virtual void mouseMoveEvent(QMouseEvent* event) override;
    virtual void mousePressEvent(QMouseEvent* event) override;
    virtual void mouseReleaseEvent(QMouseEvent* event) override;
    virtual void wheelEvent(QWheelEvent* event) override;
    virtual void keyPressEvent(QKeyEvent* e) override;
    virtual void keyReleaseEvent(QKeyEvent* e) override;
private slots:
    void OnColorChange(const QColor&);

private:
    Camera* m_camera = nullptr;
    double deltaTime = 0.0;
    bool ctrlPressed = false;
    bool leftButtonPressed = false;
    QPoint lastPoint;
    glm::mat4 modelmatrix=glm::mat4(1.0f);
    glm::mat4 projection =glm::mat4(1.0f);
    SLWDColorDialog* colorDlg = nullptr;
protected:
    void initializeGL() override;

    void resizeGL(int w, int h) override;

    void paintGL() override;

};
