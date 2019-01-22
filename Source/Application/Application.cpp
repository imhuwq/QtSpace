#include "Application.h"

Application::Application(int argc, char **argv) : QApplication(argc, argv),
                                                  controller_(new Controller()) {
    main_window_ = new MainWindow(controller_);
}

Application::~Application() { delete main_window_; }

int Application::Run() {
    main_window_->show();
    return QApplication::exec();
}