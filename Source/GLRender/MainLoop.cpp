#include "MainLoop.h"
#include "Resource/GraphNode/MeshInstance.h"

using namespace std;

MainLoop::MainLoop(ControllerPtr controller) : controller_(controller), timer_(new QTime()) {
	InitializeOpenGLFormat();
}

MainLoop::~MainLoop() {
    makeCurrent();  // http://doc.qt.io/qt-5/qopenglwindow.html#dtor.QOpenGLWindow
    TearDownGL();
}

void MainLoop::initializeGL() {
	InitializeOpenGLFunctions();
	InitializeOpenGLFeatures();

	InitializeScene();
}

void MainLoop::resizeGL(int w, int h) {
    controller_->ResizeWindow(w, h);
    scene_animator_->Resize(controller_->state());
}

void MainLoop::paintGL() {
	scene_animator_->Animate(controller_->state(), frame_delta_, gl_functions_);
    scene_render_->Render(controller_->state(), gl_functions_);

    frame_count_++;
    current_time_ = timer_->elapsed();
    frame_delta_ = current_time_ - last_time_;
    last_time_ = current_time_;
    fps_ = frame_count_ * 1000 / current_time_;
}

void MainLoop::InitializeOpenGLFormat() {
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

void MainLoop::InitializeOpenGLFunctions() {
	initializeOpenGLFunctions();
	gl_functions_ = QOpenGLFunctionsPtr(QOpenGLContext::currentContext()->functions());
	connect(this, SIGNAL(frameSwapped()), this, SLOT(update()));
}

void MainLoop::InitializeOpenGLFeatures() {
	gl_functions_->glEnable(GL_DEPTH_TEST);
	gl_functions_->glEnable(GL_CULL_FACE);
	gl_functions_->glClearColor(0, 0, 0, 0);
}

void MainLoop::InitializeScene() {
	timer_->start();
	scene_ = make_shared<Scene>();
	scene_->LoadDefaultModelFile();
	scene_animator_ = make_shared<SceneAnimator>(scene_);
	scene_render_ = make_shared<SceneRender>(scene_);
	controller_->StartStateTimer();
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

void MainLoop::mouseMoveEvent(QMouseEvent *event) {
    controller_->ProcessMouseMoveEvent(event);
};

void MainLoop::mouseReleaseEvent(QMouseEvent *event) {
    controller_->ProcessMouseReleaseEvent(event);
}

void MainLoop::wheelEvent(QWheelEvent *event) {
    controller_->ProcessWheelEvent(event);
}
