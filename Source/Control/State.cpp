#include "State.h"

State::State() {
    timer_ = make_shared<QTimer>();
    connect(timer_.get(), SIGNAL(timeout()), this, SLOT(Update()));
    timer_started_ = false;
}

void State::Update() {
    camera_orbiting = false;
    mid_mouse_x_delta = 0;
    mid_mouse_y_delta = 0;
}