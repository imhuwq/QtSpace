#include "MainWindow.h"

#include <QStyle>
#include <QDesktopWidget>

#include "Application.h"

MainWindow::MainWindow(ControllerPtr controller, QWidget *parent) : controller_(controller) {
    InitWindow();
    InitGL();
}

void MainWindow::InitWindow() {
    kStatePtr state = controller_->state();
    setFixedSize(state->window_width, state->window_height);
    setWindowTitle("QtSpace");
    setObjectName("main_window");
    setAcceptDrops(true);

    setGeometry(
            QStyle::alignedRect(
                    Qt::LeftToRight,
                    Qt::AlignCenter,
                    size(),
                    Application::desktop()->availableGeometry()
            )
    );
}

void MainWindow::InitGL() {
    gl_widget_ = new MainLoop(controller_);
    if (centralWidget()) centralWidget()->setParent(nullptr);
    setCentralWidget(gl_widget_);
}
