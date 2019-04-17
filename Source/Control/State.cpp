#include "State.h"

State::State(): timer_(new QTimer()) {
    connect(timer_.get(), SIGNAL(timeout()), this, SLOT(Update()));
    timer_started_ = false;
}

void State::Update() {
    camera_orbiting = false;
    camera_zooming = false;
    mid_mouse_x_delta = 0;
    mid_mouse_y_delta = 0;
    mid_mouse_z_delta = 0;
}