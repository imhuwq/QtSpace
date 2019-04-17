#include "SceneAnimator.h"

SceneAnimator::SceneAnimator(ScenePtr scene) : scene_(scene), anim_timer_(new QTime()) {}

void SceneAnimator::Animate(kStatePtr state, int frame_time_delta, QOpenGLFunctionsPtr gl_functions_) {
	static int anim_timer_offset = 0;

	if (state->animating) {
		if (anim_timer_->isNull()) anim_timer_->start();
		current_anim_time_ = anim_timer_->elapsed() - anim_timer_offset;
		last_anim_time_ = current_anim_time_;
	}
	else {
		anim_timer_offset = anim_timer_->elapsed() - last_anim_time_;
	}

	if (state->camera_orbiting) {
		static const float mouse2degree = 9.0f / 25.0f;
		float camera_orbiting_y_degree = 0;
		float camera_orbiting_x_degree = 0;
		if (abs(state->mid_mouse_x_delta) > abs(state->mid_mouse_y_delta)) {
			camera_orbiting_y_degree = state->mid_mouse_x_delta * mouse2degree;
		}
		else {
			camera_orbiting_x_degree = state->mid_mouse_y_delta * mouse2degree;
		}
		scene_->camera_->Orbit(camera_orbiting_y_degree, camera_orbiting_x_degree);
	}

	if (state->camera_zooming) {
		float camera_fov_delta = -state->mid_mouse_z_delta / 120.0f;
		scene_->camera_->Zoom(camera_fov_delta);
		scene_->projection_.setToIdentity();
		scene_->projection_.perspective(scene_->camera()->fov(), state->window_width / float(state->window_height), 0.01f, 100.0f);
	}
}