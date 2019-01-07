#include <iostream>

#include "Scene.h"
#include "Common/Files.h"
#include "GraphNode/MeshInstance.h"
#include "IO/ModelFileLoader/ModelFileLoader.h"

Scene::Scene() : camera_("camera"),
                 light_("sun", NodeType::kLight, LightType::kDirectionLight) {
    transform_.setToIdentity();
//        transform_.rotate(QQuaternion::fromEulerAngles(45.0f, 0, 45.0f));
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

void Scene::Animate(float time_delta) {
    transform_.rotate(QQuaternion::fromAxisAndAngle(1.0f, 0.0f, 0.0f, 50.0f * time_delta));
}
