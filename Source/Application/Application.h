#ifndef QTSPACE_APPLICATION_H
#define QTSPACE_APPLICATION_H

#include <QApplication>

#include "MainWindow.h"
#include "Control/State.h"
#include "Control/Controller.h"

class Application : public QApplication {
public:
    Application(int argc, char **argv);

    ~Application();

    int Run();

private:
    MainWindow *main_window_;
    ControllerPtr controller_;
};

#endif //QTSPACE_APPLICATION_H
