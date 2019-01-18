#ifndef QTSPACE_CONTROLLER_H
#define QTSPACE_CONTROLLER_H

#include <string>
#include <vector>
#include <memory>

#include <QTimer>
#include <QDebug>
#include <QKeyEvent>

using namespace std;

class Controller;

struct State : public QObject {
Q_OBJECT
public:
    State() {
        timer_ = make_shared<QTimer>();
        connect(timer_.get(), SIGNAL(timeout()), this, SLOT(update()));
        timer_->start(100);
    }

    int animating = 0;
    int camera_moving_left = 0;
    int camera_moving_right = 0;
    int camera_moving_forward = 0;
    int camera_moving_backward = 0;
    int camera_moving_up = 0;
    int camera_moving_down = 0;

protected slots:

    void update() {
        if (camera_moving_forward > 0) {
            camera_moving_forward = 0;
        }
        if (camera_moving_backward > 0) {
            camera_moving_backward = 0;
        }
    }

private:
    shared_ptr<QTimer> timer_;
};

typedef shared_ptr<State> StatePtr;
typedef shared_ptr<const State> kStatePtr;
typedef shared_ptr<Controller> ControllerPtr;
typedef shared_ptr<const Controller> kControllerPtr;

class Controller {
public:
    Controller() {
        state_ = make_shared<State>();
    }

    void ProcessKeyPressEvent(QKeyEvent *event);

    void ProcessKeyReleaseEvent(QKeyEvent *event);

    void ProcessMousePressEvent(QMouseEvent *event);

    void ProcessMouseReleaseEvent(QMouseEvent *event);

    void ProcessWheelEvent(QWheelEvent *event);

    kStatePtr state() const { return state_; }

private:
    StatePtr state_;
};

#endif //QTSPACE_CONTROLLER_H
