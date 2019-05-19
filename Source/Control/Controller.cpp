#include <QTimer>

#include "Controller.h"

using namespace std;

Controller::Controller() {
    state_ = make_shared<State>();
}

void Controller::Update() {

}

void Controller::LateUpdate() {
    state_->mouse_x_delta = 0;
    state_->mouse_y_delta = 0;
    state_->mouse_z_delta = 0;
    state_->camera_resetting = false;
}

void Controller::ProcessKeyPressEvent(QKeyEvent *event) {
    event->accept();

    auto key = event->key();
    switch (key) {
        case Qt::Key_Space:
            state_->animating = !state_->animating;
            state_->camera_resetting = true;
            break;

        default:
            break;
    }

}

void Controller::ProcessKeyReleaseEvent(QKeyEvent *event) {
    event->accept();

    auto key = event->key();
}

void Controller::ProcessMousePressEvent(QMouseEvent *event) {
    event->accept();

    int x = event->x();
    int y = event->y();
    state_->mouse_x_last = x;
    state_->mouse_y_last = y;

    switch (event->button()) {
        case Qt::LeftButton:
            state_->left_mouse_pressed = true;
            state_->camera_orbiting = true;
            break;
        case Qt::MidButton:
            state_->mid_mouse_pressed = true;
            break;
        case Qt::RightButton:
            state_->right_mouse_pressed = true;
            break;
        default:
            break;
    }

}

void Controller::ProcessMouseMoveEvent(QMouseEvent *event) {
    event->accept();

    int x = event->x();
    int y = event->y();
    state_->mouse_x_delta = x - state_->mouse_x_last;
    state_->mouse_y_delta = y - state_->mouse_y_last;
    state_->mouse_x_last = x;
    state_->mouse_y_last = y;
}

void Controller::ProcessMouseReleaseEvent(QMouseEvent *event) {
    event->accept();

    auto button = event->button();
    switch (button) {
        case Qt::LeftButton:
            state_->left_mouse_pressed = false;
            state_->camera_orbiting = false;
            break;
        case Qt::MidButton:
            state_->mid_mouse_pressed = false;
            break;
        case Qt::RightButton:
            state_->right_mouse_pressed = false;
            break;
        default:
            break;
    }
}

void Controller::ProcessWheelEvent(QWheelEvent *event) {
    event->accept();

    auto point = event->angleDelta();
    int delta = point.y();
    if (delta) {
        state_->camera_zooming = true;
        state_->mouse_z_delta = delta;
    }
}

void Controller::ResizeWindow(int w, int h) {
    state_->window_width = w;
    state_->window_height = h;
}

kStatePtr Controller::state() const { return state_; }
