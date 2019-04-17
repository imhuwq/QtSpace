#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <QtMath>

#include "Scene.h"
#include "Common/Files.h"
#include "Common/Consts.h"
#include "GraphNode/MeshInstance.h"
#include "GraphNode/Light/DirectionLight.h"
#include "IO/ModelFileLoader/ModelFileLoader.h"

Scene::Scene() {
    transform_.setToIdentity();
    projection_.setToIdentity();
    InitCamera();
    InitLight();
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

void Scene::InitCamera() { camera_ = make_shared<Camera>("camera"); }

void Scene::InitLight() {
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
