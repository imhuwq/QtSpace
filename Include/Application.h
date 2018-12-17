#ifndef QTSPACE_APPLICATION_H
#define QTSPACE_APPLICATION_H

#include <QApplication>

#include "MainWindow.h"

class Application : public QApplication {
public:
    Application(int argc, char **argv) : QApplication(argc, argv),
                                         main_window_(new MainWindow()) {}

    ~Application() { delete main_window_; }

    int run() {
        main_window_->show();
        return QApplication::exec();
    }

private:
    MainWindow *main_window_;
};

#endif //QTSPACE_APPLICATION_H
