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
    transform_.rotate(QQuaternion::fromEulerAngles(15, 15, 15));
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

void Scene::Resize(int w, int h) {
    projection_.setToIdentity();
    projection_.perspective(camera_.fov(), w / float(h), 0.01f, 100.0f);
}

void Scene::Animate(int frame_time_delta, const kStatePtr &state) {
    static int anim_timer_offset = 0;

    if (state->animating) {
        if (anim_timer_.isNull()) anim_timer_.start();
        current_anim_time_ = anim_timer_.elapsed() - anim_timer_offset;

        // auto orbit the camera
//        float camera_radius = 25.0f;
//        float time_normal = (current_anim_time_ % 360000 / 1000.0f);
//        float camera_x = qSin(time_normal) * camera_radius;
//        float camera_z = qCos(time_normal) * camera_radius;
//        camera_.TranslateTo(camera_x, 0, camera_z);
//        camera_.LookAt(0, 0, 0);

        last_anim_time_ = current_anim_time_;

    } else {
        anim_timer_offset = anim_timer_.elapsed() - last_anim_time_;
    }

    QVector3D camera_movement = QVector3D(0, 0, 0);
    float move_speed = camera_.move_speed() * frame_time_delta / 1000.0f;

    if (state->camera_moving_left) {
        camera_movement += move_speed * Vector3D::Left();
    }
    if (state->camera_moving_right) {
        camera_movement += move_speed * Vector3D::Right();
    }
    if (state->camera_moving_up) {
        camera_movement += move_speed * Vector3D::Up();
    }
    if (state->camera_moving_down) {
        camera_movement += move_speed * Vector3D::Down();
    }
    if (state->camera_moving_forward) {
        camera_movement += move_speed * state->camera_moving_forward / 20.0f * Vector3D::Forward();
    }
    if (state->camera_moving_backward) {
        camera_movement += move_speed * state->camera_moving_backward / 20.0f * Vector3D::Backward();
    }

    camera_.Translate(camera_movement.x(), camera_movement.y(), camera_movement.z());
}
