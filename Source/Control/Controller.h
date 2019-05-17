#ifndef QTSPACE_CONTROLLER_H
#define QTSPACE_CONTROLLER_H

#include <QTimer>
#include <QDebug>
#include <QKeyEvent>

#include "State.h"

class Controller : QObject {
Q_OBJECT
public:
    Controller();

    void StartStateTimer();

    kStatePtr state() const;

    void ProcessKeyPressEvent(QKeyEvent *event);

    void ProcessKeyReleaseEvent(QKeyEvent *event);

    void ProcessMousePressEvent(QMouseEvent *event);

    void ProcessMouseMoveEvent(QMouseEvent *event);

    void ProcessMouseReleaseEvent(QMouseEvent *event);

    void ProcessWheelEvent(QWheelEvent *event);

    void ResizeWindow(int w, int h);

private:
    StatePtr state_;
};

#endif //QTSPACE_CONTROLLER_H
