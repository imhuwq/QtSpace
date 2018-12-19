#include <QStyle>
#include <QDesktopWidget>

#include "Application.h"
#include "MainWindow.h"

void MainWindow::InitWindow() {
    setFixedSize(1000, 1000);
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
    if (!gl_widget_) gl_widget_ = new MainLoop();
    if (centralWidget()) centralWidget()->setParent(nullptr);
    setCentralWidget(gl_widget_);
}
