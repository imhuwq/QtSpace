#ifndef QTSPACE_STATE_H
#define QTSPACE_STATE_H

#include <memory>

#include <QTimer>
#include <QObject>

using namespace std;

class Controller;

class State : public QObject {
    friend Controller;
Q_OBJECT
public:
    State();

    int window_width = 1000;
    int window_height = 1000;

    bool mid_mouse_pressed = false;
    bool mid_mouse_dragging = false;
    int mid_mouse_x_last = 0;
    int mid_mouse_y_last = 0;
    int mid_mouse_x_delta = 0;
    int mid_mouse_y_delta = 0;
    int mid_mouse_z_delta = 0;

    bool animating = false;
    bool camera_orbiting = false;
    bool camera_zooming = false;

protected slots:

    void Update();

private:
    int timer_interval = 100;
    bool timer_started_ = false;
    shared_ptr<QTimer> timer_;
};

typedef shared_ptr<State> StatePtr;
typedef shared_ptr<const State> kStatePtr;

#endif //QTSPACE_STATE_H
