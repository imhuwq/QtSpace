#include <iostream>
#include <QtMath>

#include "Scene.h"
#include "Common/Files.h"
#include "Common/Consts.h"
#include "GraphNode/MeshInstance.h"
#include "IO/ModelFileLoader/ModelFileLoader.h"

Scene::Scene() : camera_("camera"),
                 current_anim_time_(0),
                 last_anim_time_(0),
                 light_("sun", LightType::kDirectionLight) {
    transform_.setToIdentity();
    projection_.setToIdentity();
}

void Scene::LoadModelFile(const string &file_path) {
    ModelFileLoaderPtr loader = ModelFileLoader::CreateLoader(file_path);
    if (!loader) {
        cerr << "Scene::LoadModelFile: Cannot create loader for file '" << file_path << "'." << endl;
        return;
    }

    kModelPtr model = nullptr;
    if (loader) model = loader->Load(file_path);
    if (model) AddModel(model);
}

size_t Scene::model_size() const { return models_.size(); }

kModelPtr Scene::GetModel(size_t index) const {
    if (index > models_.size() - 1) return nullptr;
    return models_[index];
}

void Scene::AddModel(const kModelPtr &model) { models_.push_back(model); }

QMatrix4x4 Scene::transformation() const { return transform_; }

QMatrix4x4 Scene::projection() const { return projection_; }

const Camera &Scene::camera() const { return camera_; }

const Light &Scene::light() const { return light_; }

void Scene::Resize(const kStatePtr &state) {
    projection_.setToIdentity();
    projection_.perspective(camera_.fov(), state->window_width / float(state->window_height), 0.01f, 100.0f);
}

void Scene::Animate(const kStatePtr &state, int frame_time_delta) {
    static int anim_timer_offset = 0;

    if (state->animating) {
        if (anim_timer_.isNull()) anim_timer_.start();
        current_anim_time_ = anim_timer_.elapsed() - anim_timer_offset;
        last_anim_time_ = current_anim_time_;
    } else {
        anim_timer_offset = anim_timer_.elapsed() - last_anim_time_;
    }

    if (state->camera_orbiting) {
        static const float mouse2degree = 9.0f / 25.0f;
        float camera_orbiting_y_degree = state->mid_mouse_x_delta * mouse2degree;
        float camera_orbiting_x_degree = state->mid_mouse_y_delta * mouse2degree;
        camera_.Orbit(camera_orbiting_y_degree, camera_orbiting_x_degree);
    }

    if (state->camera_zooming) {
        float camera_fov_delta = -state->mid_mouse_z_delta / 120.0f;
        camera_.Zoom(camera_fov_delta);
        projection_.setToIdentity();
        projection_.perspective(camera_.fov(), state->window_width / float(state->window_height), 0.01f, 100.0f);
    }
}
