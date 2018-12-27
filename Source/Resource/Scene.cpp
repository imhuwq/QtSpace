#include "Scene.h"
#include "GraphNode/MeshInstance.h"

Scene::Scene() : camera_("camera"),
                 light_("sun", NodeType::kLight, LightType::kDirectionLight) {
    transform_.setToIdentity();
//        transform_.rotate(QQuaternion::fromEulerAngles(45.0f, 0, 45.0f));
    projection_.setToIdentity();
}

ScenePtr Scene::CreateCube() {
    ScenePtr scene = make_shared<Scene>();

    ModelPtr model = make_shared<Model>();

    MeshInstancePtr mesh_instance = MeshInstance::CreateCube();
    model->AddMesh(const_pointer_cast<Mesh>(mesh_instance->mesh()));

    MaterialPtr material = const_pointer_cast<Material>(mesh_instance->material());
    model->AddMaterial(material);

    model->root_node()->AddChild(mesh_instance);

    scene->AddModel(model);
    return scene;
}

size_t Scene::model_size() const { return models_.size(); }

kModelPtr Scene::GetModel(size_t index) const {
    if (index > models_.size() - 1) return nullptr;
    return models_[index];
}

void Scene::AddModel(const ModelPtr &model) { models_.push_back(model); }

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
