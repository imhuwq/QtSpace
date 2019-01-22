#ifndef QTSPACE_CONTROLLER_H
#define QTSPACE_CONTROLLER_H

#include <string>
#include <vector>
#include <memory>

#include <QTimer>
#include <QDebug>
#include <QKeyEvent>

#include "State.h"

using namespace std;

class Controller;

typedef shared_ptr<Controller> ControllerPtr;
typedef shared_ptr<const Controller> kControllerPtr;

class Controller {
public:
    Controller();

    void StartStateTimer();

    void ProcessKeyPressEvent(QKeyEvent *event);

    void ProcessKeyReleaseEvent(QKeyEvent *event);

    void ProcessMousePressEvent(QMouseEvent *event);

    void ProcessMouseMoveEvent(QMouseEvent *event);

    void ProcessMouseReleaseEvent(QMouseEvent *event);

    void ProcessWheelEvent(QWheelEvent *event);

    void ResizeWindow(int w, int h);

    kStatePtr state() const;

private:
    StatePtr state_;
};

#endif //QTSPACE_CONTROLLER_H
