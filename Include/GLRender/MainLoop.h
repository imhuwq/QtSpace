#ifndef QTSPACE_GLWIDGET_H
#define QTSPACE_GLWIDGET_H

#include <QTime>
#include <QString>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>

#include "Resource/Scene.h"
#include "SceneRender.h"

class MainLoop : public QOpenGLWidget, protected QOpenGLFunctions {
Q_OBJECT
public:
    MainLoop();

    ~MainLoop() {
        makeCurrent();  // http://doc.qt.io/qt-5/qopenglwindow.html#dtor.QOpenGLWindow
        TearDownGL();
    }

protected:
    void CreateShaders();

    void initializeGL() override;

    void resizeGL(int w, int h) override;

    void paintGL() override;

    void TearDownGL();

protected slots:

    void update();

private:
    ScenePtr scene_ = nullptr;
    SceneRenderPtr scene_render_ = nullptr;
    ShaderPtr shader_ = nullptr;
    QOpenGLFunctions *gl_function_;
    size_t gl_frame_count_;
    QTime gl_frame_timer_;
    float gl_this_frame_time_;
    float gl_last_frame_time_;
    float gl_frame_delta_;
    float gl_fps_;
};

#endif //QTSPACE_GLWIDGET_H
