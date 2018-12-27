#ifndef QTSPACE_APPLICATION_H
#define QTSPACE_APPLICATION_H

#include <QApplication>

#include "MainWindow.h"

class Application : public QApplication {
public:
    Application(int argc, char **argv);

    ~Application();

    int Run();

private:
    MainWindow *main_window_;
};

#endif //QTSPACE_APPLICATION_H
