#include <QTimer>

#include "Controller.h"

Controller::Controller() {
    state_ = make_shared<State>();
}

void Controller::StartStateTimer() {
    // 认定所有的渲染行为都在设置状态后的 0.1 秒之内完成，否则 fps 小于 10，那时候再来优化吧
    state_->timer_->start(100);
}

void Controller::ProcessKeyPressEvent(QKeyEvent *event) {
    auto key = event->key();
    switch (key) {
        case Qt::Key_Space:
            state_->animating = !state_->animating;
            break;

        default:
            break;
    }

}

void Controller::ProcessKeyReleaseEvent(QKeyEvent *event) {
    auto key = event->key();
    switch (key) {

        default:
            break;
    }
}

void Controller::ProcessMousePressEvent(QMouseEvent *event) {
    auto button = event->button();
    int x = event->x();
    int y = event->y();

    switch (button) {
        case Qt::MidButton:
            state_->mid_mouse_x_last = x;
            state_->mid_mouse_y_last = y;
            state_->mid_mouse_pressed = true;

            break;
        default:
            break;
    }

}

void Controller::ProcessMouseMoveEvent(QMouseEvent *event) {
    auto button = event->button();
    int x = event->x();
    int y = event->y();

    if (button == Qt::NoButton) {
        state_->mid_mouse_x_delta = x - state_->mid_mouse_x_last;
        state_->mid_mouse_y_delta = y - state_->mid_mouse_y_last;

        state_->mid_mouse_x_last = x;
        state_->mid_mouse_y_last = y;

        if (state_->mid_mouse_pressed) {
            state_->mid_mouse_dragging = true;
            state_->camera_orbiting = true;
        }
    }
}

void Controller::ProcessMouseReleaseEvent(QMouseEvent *event) {
    auto button = event->button();

    switch (button) {
        case Qt::MidButton:
            state_->mid_mouse_x_delta = 0;
            state_->mid_mouse_y_delta = 0;

            state_->mid_mouse_pressed = false;
            state_->mid_mouse_dragging = false;
            state_->camera_orbiting = false;
            break;
        default:
            break;
    }
}

void Controller::ProcessWheelEvent(QWheelEvent *event) {
    auto point = event->angleDelta();
}

kStatePtr Controller::state() const { return state_; }
