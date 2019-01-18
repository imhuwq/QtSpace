#include <QTimer>

#include "Controller.h"


void Controller::ProcessKeyPressEvent(QKeyEvent *event) {
    auto key = event->key();
    switch (key) {
        case Qt::Key_Space:
            state_->animating = !state_->animating;

        case Qt::Key_A:
        case Qt::Key_Left:
            state_->camera_moving_left = 1;
            break;
        case Qt::Key_D:
        case Qt::Key_Right:
            state_->camera_moving_right = 1;
            break;
        case Qt::Key_W:
        case Qt::Key_Up:
            state_->camera_moving_up = 1;
            break;
        case Qt::Key_S:
        case Qt::Key_Down:
            state_->camera_moving_down = 1;
            break;

        default:
            break;
    }

}

void Controller::ProcessKeyReleaseEvent(QKeyEvent *event) {
    auto key = event->key();
    switch (key) {
        case Qt::Key_A:
        case Qt::Key_Left:
            state_->camera_moving_left = 0;
            break;
        case Qt::Key_D:
        case Qt::Key_Right:
            state_->camera_moving_right = 0;
            break;
        case Qt::Key_W:
        case Qt::Key_Up:
            state_->camera_moving_up = 0;
            break;
        case Qt::Key_S:
        case Qt::Key_Down:
            state_->camera_moving_down = 0;
            break;

        default:
            break;
    }
}

void Controller::ProcessMousePressEvent(QMouseEvent *event) {

}

void Controller::ProcessMouseReleaseEvent(QMouseEvent *event) {

}

void Controller::ProcessWheelEvent(QWheelEvent *event) {
    auto point = event->angleDelta();
    auto delta_y = point.y();
    if (delta_y > 0) {
        state_->camera_moving_forward += delta_y;
        state_->camera_moving_backward = 0;
    } else {
        state_->camera_moving_forward = 0;
        state_->camera_moving_backward -= delta_y;
    }
}
