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

using namespace std;

Scene::Scene() {
    transform_.setToIdentity();
    projection_.setToIdentity();
    InitCamera();
    InitLight();
	InitSkyBox();
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

void Scene::LoadDefaultModelFile() {
    LoadModelFile(Files::DefaultCubeModel);
}

void Scene::InitCamera() { camera_ = make_shared<Camera>("camera"); }

void Scene::InitLight() {
    light_ = make_shared<DirectionLight>("light");
    light_->TranslateTo(-2, 2, 2);
    light_->Scale(0.8, 0.8, 0.8);
    vector<float> light_color = {255/255.0f, 183/255.0f, 130/255.0f};
    light_->SetColor(light_color[0], light_color[1], light_color[2]);

    string file_path = Files::DefaultSphereModel;
    ModelFileLoaderPtr loader = ModelFileLoader::CreateLoader(file_path);
    if (!loader) {
        cerr << "Scene::LoadModelFile: Cannot create loader for file '" << file_path << "'." << endl;
        return;
    }

    NodePtr light_model = loader->Load(file_path)->nodes()[0];
    MeshInstancePtr light_instance = dynamic_pointer_cast<MeshInstance>(light_model);
    MaterialPtr light_material = light_instance->material();
    light_material->SetDiffuseColor(light_color[0], light_color[1], light_color[2]);
    light_material->SetAmbientColor(light_color[0], light_color[1], light_color[2]);
    light_material->SetSpecularColor(light_color[0], light_color[1], light_color[2]);
    light_material->SetDiffuseStrength(1.0f);
    light_material->SetAmbientStrength(1.0f);
    light_material->SetSpecularStrength(1.0f);

    light_->AddNode(light_model);
    AddNode(light_);
}

void Scene::InitSkyBox() {
	skybox_ = make_shared<SkyBox>();

	string file_path = Files::DefaultCubeModel;
	ModelFileLoaderPtr loader = ModelFileLoader::CreateLoader(file_path);
	if (!loader) {
		cerr << "Scene::LoadModelFile: Cannot create loader for file '" << file_path << "'." << endl;
		return;
	}

	NodePtr box_model = loader->Load(file_path)->nodes()[0];
	skybox_->SetBox(box_model);

	CubemapPtr cubemap = Cubemap::CreateDefault();
	skybox_->SetCubemap(cubemap);
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
