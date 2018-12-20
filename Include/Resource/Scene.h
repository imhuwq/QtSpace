#ifndef QTSPACE_SCENE_H
#define QTSPACE_SCENE_H

#include <vector>
#include <memory>

#include <QMatrix4x4>

#include "Resource/Resource.h"
#include "Resource/Model.h"
#include "Resource/GraphNode/MeshInstance.h"
#include "GraphNode/Light.h"
#include "GraphNode/Camera.h"

using namespace std;

class Scene;

typedef shared_ptr<Scene> ScenePtr;
typedef shared_ptr<const Scene> kScenePtr;

class Scene : public Resource {
public:
    Scene() : camera_("camera"),
              light_("sun", NodeType::kLight, LightType::kDirectionLight) {
        transform_.setToIdentity();
        transform_.rotate(QQuaternion::fromEulerAngles(45.0f, 0, 45.0f));
        projection_.setToIdentity();
        camera_.Translate(0, 0, -10);
    }

    static ScenePtr CreateDefault() {
        ScenePtr scene = make_shared<Scene>();

        ModelPtr model = make_shared<Model>();

        VertexSemantic vertex_semantic(false, true, false, false, false);
        MeshPtr mesh = make_shared<Mesh>(36, vertex_semantic);
        vector<vector<float>> vertex_buffer = {
                {-0.5f, -0.5f, -0.5f, 0.0f, 0.0f},
                {0.5f,  -0.5f, -0.5f, 1.0f, 0.0f},
                {0.5f,  0.5f,  -0.5f, 1.0f, 1.0f},

                {0.5f,  0.5f,  -0.5f, 1.0f, 1.0f},
                {-0.5f, 0.5f,  -0.5f, 0.0f, 1.0f},
                {-0.5f, -0.5f, -0.5f, 0.0f, 0.0f},

                {-0.5f, -0.5f, 0.5f,  0.0f, 0.0f},
                {0.5f,  -0.5f, 0.5f,  1.0f, 0.0f},
                {0.5f,  0.5f,  0.5f,  1.0f, 1.0f},

                {0.5f,  0.5f,  0.5f,  1.0f, 1.0f},
                {-0.5f, 0.5f,  0.5f,  0.0f, 1.0f},
                {-0.5f, -0.5f, 0.5f,  0.0f, 0.0f},

                {-0.5f, 0.5f,  0.5f,  1.0f, 0.0f},
                {-0.5f, 0.5f,  -0.5f, 1.0f, 1.0f},
                {-0.5f, -0.5f, -0.5f, 0.0f, 1.0f},

                {-0.5f, -0.5f, -0.5f, 0.0f, 1.0f},
                {-0.5f, -0.5f, 0.5f,  0.0f, 0.0f},
                {-0.5f, 0.5f,  0.5f,  1.0f, 0.0f},

                {0.5f,  0.5f,  0.5f,  1.0f, 0.0f},
                {0.5f,  0.5f,  -0.5f, 1.0f, 1.0f},
                {0.5f,  -0.5f, -0.5f, 0.0f, 1.0f},

                {0.5f,  -0.5f, -0.5f, 0.0f, 1.0f},
                {0.5f,  -0.5f, 0.5f,  0.0f, 0.0f},
                {0.5f,  0.5f,  0.5f,  1.0f, 0.0f},

                {-0.5f, -0.5f, -0.5f, 0.0f, 1.0f},
                {0.5f,  -0.5f, -0.5f, 1.0f, 1.0f},
                {0.5f,  -0.5f, 0.5f,  1.0f, 0.0f},

                {0.5f,  -0.5f, 0.5f,  1.0f, 0.0f},
                {-0.5f, -0.5f, 0.5f,  0.0f, 0.0f},
                {-0.5f, -0.5f, -0.5f, 0.0f, 1.0f},

                {-0.5f, 0.5f,  -0.5f, 0.0f, 1.0f},
                {0.5f,  0.5f,  -0.5f, 1.0f, 1.0f},
                {0.5f,  0.5f,  0.5f,  1.0f, 0.0f},

                {0.5f,  0.5f,  0.5f,  1.0f, 0.0f},
                {-0.5f, 0.5f,  0.5f,  0.0f, 0.0f},
                {-0.5f, 0.5f,  -0.5f, 0.0f, 1.0f}
        };

        for (size_t i = 0; i < 36; i++) mesh->SetVertex(vertex_buffer[i], i);
        model->AddMesh(mesh);

        string mesh_instance_name = "cube";
        MeshInstancePtr mesh_instance = make_shared<MeshInstance>(mesh_instance_name, mesh);
        for (unsigned int i = 0; i < 36; i += 3) mesh_instance->AddTriangle(i, i + 1, i + 2);

        NodePtr root_node = model->root_node();
        root_node->AddChild(mesh_instance);

        scene->AddModel(model);
        return scene;
    }

    const size_t model_size() const { return models_.size(); }

    const kModelPtr GetModel(size_t index) const {
        if (index > models_.size() - 1) return nullptr;
        return models_[index];
    }

    void AddModel(const ModelPtr &model) { models_.push_back(model); }

    QMatrix4x4 transformation() const { return transform_; }

    QMatrix4x4 projection() const { return projection_; }

    const Camera &camera() const { return camera_; }

    void Resize(int w, int h) {
        projection_.setToIdentity();
        projection_.perspective(camera_.fov(), w / float(h), 0.001, 100.0f);
    }

    void Animate(float time_delta) {
        transform_.rotate(QQuaternion::fromAxisAndAngle(1.0f, 1.0f, 0.0f, 50.0f * time_delta));
    }

private:
    QMatrix4x4 transform_;
    Camera camera_;
    QMatrix4x4 projection_;
    Light light_;
    vector<ModelPtr> models_;
};

#endif //QTSPACE_SCENE_H
