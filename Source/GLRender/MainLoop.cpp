#include "GLRender/MainLoop.h"
#include "Resource/GraphNode/MeshInstance.h"

MainLoop::MainLoop() : scene_(nullptr){
    QSurfaceFormat format;
    format.setRenderableType(QSurfaceFormat::OpenGL);
    format.setProfile(QSurfaceFormat::CoreProfile);
    format.setVersion(3, 3);
    format.setSamples(16);
    format.setDepthBufferSize(24);
    format.setStencilBufferSize(8);
    setFormat(format);
}

void MainLoop::initializeGL() {
    initializeOpenGLFunctions();

    gl_fps_ = 0;
    gl_frame_count_ = 0;
    gl_this_frame_time_ = 0;
    gl_last_frame_time_ = 0;
    gl_frame_delta_ = 0;
    gl_frame_timer_.start();

    connect(this, SIGNAL(frameSwapped()), this, SLOT(update()));

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glClearColor(0.7f, 0.7f, 0.7f, 1.0f);

    scene_ = Scene::CreateDefault();
    scene_render_ = make_shared<SceneRender>(scene_);
}

void MainLoop::resizeGL(int w, int h) {
    scene_->Resize(w, h);
}

void MainLoop::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    scene_->Animate(gl_frame_delta_);
    scene_render_->Draw();

    gl_frame_count_++;
    gl_this_frame_time_ = (float) gl_frame_timer_.elapsed();
    gl_frame_delta_ = (gl_this_frame_time_ - gl_last_frame_time_) / float(1000);
    gl_last_frame_time_ = gl_this_frame_time_;
    gl_fps_ = gl_frame_count_ * 1000 / gl_this_frame_time_;
}

void MainLoop::TearDownGL() {}

void MainLoop::update() {
    QOpenGLWidget::update();
}
