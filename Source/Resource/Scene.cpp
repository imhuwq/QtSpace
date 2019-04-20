#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <queue>
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

    NodePtr model_root_node = loader->Load(file_path);
    AddNode(model_root_node);
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

    NodePtr light_model_root = loader->Load(file_path);
    light_->AddNode(light_model_root);
    AddNode(light_);
}

void Scene::AddNode(NodePtr node) {
    nodes_.push_back(node);

    queue<NodePtr> nodes_queue;
    nodes_queue.push(node);
    while (!nodes_queue.empty()) {
        node = nodes_queue.front();
        nodes_queue.pop();

        if (node->node_type() == NodeType::kMeshInstance) {
            auto mesh_instance = dynamic_pointer_cast<MeshInstance>(node);

            auto mesh = mesh_instance->mesh();
            meshes_[mesh->uuid()] = mesh;

            auto material = mesh_instance->material();
            materials_[material->uuid()] = material;
            for (auto texture :material->textures()) textures_[texture->uuid()] = texture;
        }

        for (auto child_node: node->nodes()) nodes_queue.push(child_node);
    }
}

QMatrix4x4 Scene::transformation() const { return transform_; }

QMatrix4x4 Scene::projection() const { return projection_; }

vector<kNodePtr> Scene::nodes() const {
    vector<kNodePtr> nodes_vec;
    for (NodePtr node: nodes_) nodes_vec.push_back(node);
    return nodes_vec;
}

vector<NodePtr> Scene::nodes() { return nodes_; }

size_t Scene::nodes_size() const { return nodes_.size(); }

const kCameraPtr Scene::camera() const { return camera_; }

const kLightPtr Scene::light() const { return light_; }

