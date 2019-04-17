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

#include "SceneAnimator.h"
#include "SceneRender.h"
#include "Resource/Scene.h"
#include "Control/Controller.h"


class MainLoop : public QOpenGLWidget, protected QOpenGLFunctions {
Q_OBJECT
public:
    MainLoop(ControllerPtr controller);

    ~MainLoop() override;

protected:
    void initializeGL() override;

    void resizeGL(int w, int h) override;

    void paintGL() override;

    void keyPressEvent(QKeyEvent *event) override;

    void keyReleaseEvent(QKeyEvent *event) override;

    void mousePressEvent(QMouseEvent *event) override;

    void mouseMoveEvent(QMouseEvent *event) override;

    void mouseReleaseEvent(QMouseEvent *event) override;

    void wheelEvent(QWheelEvent *event) override;

    void TearDownGL();

protected slots:

    void update();

private:
	ControllerPtr controller_ = nullptr;
	QTimePtr timer_ = nullptr;
	QOpenGLFunctionsPtr gl_functions_ = nullptr;

	SceneAnimatorPtr scene_animator_ = nullptr;
	SceneRenderPtr scene_render_ = nullptr;
    ScenePtr scene_ = nullptr;

    int frame_count_ = 0;
    int current_time_ = 0;
    int last_time_ = 0;
    int frame_delta_ = 0;
    int fps_ = 0;

	void InitializeOpenGLFormat();

	void InitializeOpenGLFunctions();

	void InitializeOpenGLFeatures();

	void InitializeScene();
};

#endif //QTSPACE_GLWIDGET_H
