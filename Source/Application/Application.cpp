#include "Application.h"

Application::Application(int argc, char **argv) : QApplication(argc, argv),
                                                  main_window_(new MainWindow()) {}

Application::~Application() { delete main_window_; }

int Application::Run() {
    main_window_->show();
    return QApplication::exec();
}