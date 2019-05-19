#include "SceneAnimator.h"

SceneAnimator::SceneAnimator(ScenePtr scene) : scene_(scene), anim_timer_(new QTime()) {}

void SceneAnimator::Animate(kStatePtr state, int frame_time_delta, QGLFunctionsPtr gl_functions_) {
    static int anim_timer_offset = 0;

    if (state->animating) {
        if (anim_timer_->isNull()) anim_timer_->start();
        current_anim_time_ = anim_timer_->elapsed() - anim_timer_offset;
        last_anim_time_ = current_anim_time_;
    } else {
        anim_timer_offset = anim_timer_->elapsed() - last_anim_time_;
    }

    if (state->camera_resetting) {
        scene_->camera_->ReSet();
    } else if (state->camera_orbiting) {
        scene_->camera_->Orbit(-state->mouse_y_delta * 0.2, -state->mouse_x_delta * 0.2, 0);
    }

    if (state->camera_zooming) {
        float camera_fov_delta = -state->mouse_z_delta / 120.0f;
        scene_->camera_->Zoom(camera_fov_delta);
        scene_->projection_.setToIdentity();
        scene_->projection_.perspective(scene_->camera()->fov(),
                                        state->window_width / float(state->window_height),
                                        0.01f, 100.0f);
    }
}

void SceneAnimator::Resize(kStatePtr state) {
    scene_->projection_.setToIdentity();
    scene_->projection_.perspective(scene_->camera_->fov(),
                                    state->window_width / float(state->window_height), 0.01f,
                                    100.0f);
}