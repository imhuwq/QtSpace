#ifndef QTSPACE_SCENE_H
#define QTSPACE_SCENE_H

#include <vector>
#include <memory>

#include <QMatrix4x4>

#include "Resource/Resource.h"
#include "Resource/Model.h"
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
        projection_.setToIdentity();
    }

    static kScenePtr CreateDefault() {
        ScenePtr scene = make_shared<Scene>();
        return scene;
    }

    const size_t model_size() const { return models_.size(); }

    const kModelPtr GetModel(size_t index) const {
        if (index > models_.size() - 1) return nullptr;
        return models_[index];
    }

    QMatrix4x4 transformation() const { return transform_; }

    QMatrix4x4 projection() const { return projection_; }

    const Camera &camera() const { return camera_; }

private:
    QMatrix4x4 transform_;
    Camera camera_;
    QMatrix4x4 projection_;
    Light light_;
    vector<ModelPtr> models_;
};

#endif //QTSPACE_SCENE_H
