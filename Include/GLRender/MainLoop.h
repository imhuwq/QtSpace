#ifndef QTSPACE_GLWIDGET_H
#define QTSPACE_GLWIDGET_H

#include <QString>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>

#include "Resource/Scene.h"
#include "SceneRender.h"

const QString DefaultVertexShader = "#version 330\n"
                                    "\n"
                                    "layout(location = 0) in vec3 position;\n"
                                    "\n"
                                    "out vec4 positionColor;\n"
                                    "\n"
                                    "uniform mat4 modelMatrix;\n"
                                    "uniform mat4 viewMatrix;\n"
                                    "uniform mat4 projectionMatrix;\n"
                                    "\n"
                                    "void main() {\n"
                                    "\tgl_Position = vec4(position, 1.0);\n"
                                    "\tpositionColor = gl_Position;\n"
                                    "}";

const QString DefaultFragmentShader = "#version 330\n"
                                      "\n"
                                      "in vec4 positionColor;\n"
                                      "out vec4 color;\n"
                                      "\n"
                                      "void main() {\n"
                                      "    color = positionColor;\n"
                                      "}";

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
    kScenePtr scene_ = nullptr;
    SceneRenderPtr scene_render_ = nullptr;
    ShaderPtr shader_ = nullptr;
};

#endif //QTSPACE_GLWIDGET_H
