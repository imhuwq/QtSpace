#include "GLRender/MainLoop.h"
#include "Resource/GraphNode/MeshInstance.h"

MainLoop::MainLoop() : scene_(nullptr),
                       shader_(new QOpenGLShaderProgram()) {
    QSurfaceFormat format;
    format.setRenderableType(QSurfaceFormat::OpenGL);
    format.setProfile(QSurfaceFormat::CoreProfile);
    format.setVersion(3, 3);
    format.setSamples(16);
    format.setDepthBufferSize(24);
    format.setStencilBufferSize(8);
    setFormat(format);

}


void MainLoop::CreateShaders() {
    shader_->addShaderFromSourceCode(QOpenGLShader::Vertex, DefaultVertexShader.toStdString().c_str());
    shader_->addShaderFromSourceCode(QOpenGLShader::Fragment, DefaultFragmentShader.toStdString().c_str());
    shader_->link();
}

void MainLoop::initializeGL() {
    initializeOpenGLFunctions();
    connect(this, SIGNAL(frameSwapped()), this, SLOT(update()));

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glClearColor(0.7f, 0.7f, 0.7f, 1.0f);

    CreateShaders();
    scene_ = Scene::CreateDefault();
    scene_render_ = make_shared<SceneRender>(scene_);
}

void MainLoop::resizeGL(int w, int h) {}


void MainLoop::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    scene_render_->Draw(shader_);
}

void MainLoop::TearDownGL() {}

void MainLoop::update() {
    QOpenGLWidget::update();
}
