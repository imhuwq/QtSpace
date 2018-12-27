#ifndef QTSPACE_GLWIDGET_H
#define QTSPACE_GLWIDGET_H

#include <QTime>
#include <QString>
#include <QOpenGLWidget>
#include <QOpenGLBuffer>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>

#include "SceneRender.h"
#include "Resource/Scene.h"

class MainLoop : public QOpenGLWidget, protected QOpenGLFunctions {
Q_OBJECT
public:
    MainLoop();

    ~MainLoop() override;

protected:
    void initializeGL() override;

    void resizeGL(int w, int h) override;

    void paintGL() override;

    void TearDownGL();

protected slots:

    void update();

private:
    ScenePtr scene_ = nullptr;
    SceneRenderPtr scene_render_ = nullptr;
    size_t gl_frame_count_;
    QTime gl_frame_timer_;
    float gl_this_frame_time_;
    float gl_last_frame_time_;
    float gl_frame_delta_;
    float gl_fps_;
};

#endif //QTSPACE_GLWIDGET_H
