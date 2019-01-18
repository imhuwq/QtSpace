#include "MainLoop.h"
#include "Resource/GraphNode/MeshInstance.h"

MainLoop::MainLoop() : scene_(nullptr), controller_(new Controller()) {
    QSurfaceFormat format;
    format.setRenderableType(QSurfaceFormat::OpenGL);
    format.setProfile(QSurfaceFormat::CoreProfile);
    format.setVersion(3, 3);
    format.setSamples(16);
    format.setDepthBufferSize(24);
    format.setStencilBufferSize(8);
    setFormat(format);
    setFocusPolicy(Qt::StrongFocus);
}

MainLoop::~MainLoop() {
    makeCurrent();  // http://doc.qt.io/qt-5/qopenglwindow.html#dtor.QOpenGLWindow
    TearDownGL();
}

void MainLoop::initializeGL() {
    initializeOpenGLFunctions();

    fps_ = 0;
    frame_count_ = 0;
    current_time_ = 0;
    last_time_ = 0;
    frame_delta_ = 0;
    timer_.start();

    connect(this, SIGNAL(frameSwapped()), this, SLOT(update()));

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glClearColor(0.7f, 0.7f, 0.7f, 1.0f);

    scene_ = make_shared<Scene>();
    scene_->LoadModelFile(Files::DefaultCubeModelFile);
    scene_render_ = make_shared<SceneRender>(scene_);
}

void MainLoop::resizeGL(int w, int h) {
    scene_->Resize(w, h);
}

void MainLoop::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    scene_->Animate(frame_delta_, controller_->state());
    scene_render_->Draw();

    frame_count_++;
    current_time_ = timer_.elapsed();
    frame_delta_ = current_time_ - last_time_;
    last_time_ = current_time_;
    fps_ = frame_count_ * 1000 / current_time_;
}

void MainLoop::TearDownGL() {}

void MainLoop::update() {
    QOpenGLWidget::update();
}

void MainLoop::keyPressEvent(QKeyEvent *event) {
    controller_->ProcessKeyPressEvent(event);
}

void MainLoop::keyReleaseEvent(QKeyEvent *event) {
    controller_->ProcessKeyReleaseEvent(event);

}

void MainLoop::mousePressEvent(QMouseEvent *event) {
    controller_->ProcessMousePressEvent(event);
}

void MainLoop::mouseReleaseEvent(QMouseEvent *event) {
    controller_->ProcessMouseReleaseEvent(event);
}

void MainLoop::wheelEvent(QWheelEvent *event) {
    controller_->ProcessWheelEvent(event);
}
