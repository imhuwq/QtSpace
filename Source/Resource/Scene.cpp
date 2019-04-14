#include <stdlib.h>
#include <stdio.h>
#include <QtMath>

#include "Scene.h"
#include "Common/Files.h"
#include "Common/Consts.h"
#include "GraphNode/MeshInstance.h"
#include "GraphNode/Light/DirectionLight.h"
#include "IO/ModelFileLoader/ModelFileLoader.h"

Scene::Scene() : current_anim_time_(0),
                 last_anim_time_(0) {
    transform_.setToIdentity();
    projection_.setToIdentity();
    AddCamera();
    AddLight();
}

void Scene::LoadModelFile(const string &file_path) {
    ModelFileLoaderPtr loader = ModelFileLoader::CreateLoader(file_path);
    if (!loader) {
        cerr << "Scene::LoadModelFile: Cannot create loader for file '" << file_path << "'." << endl;
        return;
    }

    kModelPtr model = nullptr;
    model = loader->Load(file_path, nullptr);
    if (model) AddModel(model);
    else cerr << "Scene::LoadModelFile: Cannot load file '" << file_path << "'." << endl;
}

void Scene::AddCamera() { camera_ = make_shared<Camera>("camera"); }

void Scene::AddLight() {
    light_ = make_shared<DirectionLight>("light");
    light_->TranslateTo(0, 2, 0);

    string file_path = Files::DefaultSphereModel;
    ModelFileLoaderPtr loader = ModelFileLoader::CreateLoader(file_path);
    if (!loader) {
        cerr << "Scene::LoadModelFile: Cannot create loader for file '" << file_path << "'." << endl;
        return;
    }

    ModelPtr light_model = nullptr;
    light_model = loader->Load(file_path, light_);

    if (!light_model) {
        cerr << "Scene::LoadModelFile: Cannot load file '" << file_path << "'." << endl;
        return;
    }
    AddModel(light_model);
}

size_t Scene::model_size() const { return models_.size(); }

kModelPtr Scene::GetModel(size_t index) const {
    if (index > models_.size() - 1) return nullptr;
    return models_[index];
}

void Scene::AddModel(const kModelPtr &model) { models_.push_back(model); }

QMatrix4x4 Scene::transformation() const { return transform_; }

QMatrix4x4 Scene::projection() const { return projection_; }

const kCameraPtr Scene::camera() const { return camera_; }

const kLightPtr Scene::light() const { return light_; }

void Scene::Resize(const kStatePtr &state) {
    projection_.setToIdentity();
    projection_.perspective(camera_->fov(), state->window_width / float(state->window_height), 0.01f, 100.0f);
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
        float camera_orbiting_y_degree = 0;
        float camera_orbiting_x_degree = 0;
        if (abs(state->mid_mouse_x_delta) > abs(state->mid_mouse_y_delta)) {
            camera_orbiting_y_degree = state->mid_mouse_x_delta * mouse2degree;
        } else {
            camera_orbiting_x_degree = state->mid_mouse_y_delta * mouse2degree;
        }
        camera_->Orbit(camera_orbiting_y_degree, camera_orbiting_x_degree);
    }

    if (state->camera_zooming) {
        float camera_fov_delta = -state->mid_mouse_z_delta / 120.0f;
        camera_->Zoom(camera_fov_delta);
        projection_.setToIdentity();
        projection_.perspective(camera_->fov(), state->window_width / float(state->window_height), 0.01f, 100.0f);
    }
}
