#include "State.h"

State::State() {
    timer_ = make_shared<QTimer>();
    connect(timer_.get(), SIGNAL(timeout()), this, SLOT(Update()));
    timer_started_ = false;
}

void State::Update() {
// TODO: 这里可能会出问题，比如 fps 小于 (1000 / timer_interval) 的时候
    camera_orbiting = false;
    camera_zooming = false;
    mid_mouse_x_delta = 0;
    mid_mouse_y_delta = 0;
    mid_mouse_z_delta = 0;
}