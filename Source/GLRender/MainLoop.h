#ifndef QTSPACE_GLWIDGET_H
#define QTSPACE_GLWIDGET_H

#include <QTime>
#include <QString>
#include <QKeyEvent>
#include <QOpenGLWidget>
#include <QOpenGLBuffer>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>

#include "SceneRender.h"
#include "Resource/Scene.h"
#include "Control/Controller.h"

class MainLoop : public QOpenGLWidget, protected QOpenGLFunctions {
Q_OBJECT
public:
    MainLoop();

    ~MainLoop() override;

protected:
    void initializeGL() override;

    void resizeGL(int w, int h) override;

    void paintGL() override;

    void keyPressEvent(QKeyEvent *event) override;

    void keyReleaseEvent(QKeyEvent *event) override;

    void mousePressEvent(QMouseEvent *event) override;

    void mouseReleaseEvent(QMouseEvent *event) override;

    void wheelEvent(QWheelEvent * event) override;

    void TearDownGL();

protected slots:

    void update();

private:
    ScenePtr scene_ = nullptr;
    SceneRenderPtr scene_render_ = nullptr;
    int frame_count_;
    QTime timer_;
    int current_time_;
    int last_time_;
    int frame_delta_;
    int fps_;

    ControllerPtr controller_;
};

#endif //QTSPACE_GLWIDGET_H
