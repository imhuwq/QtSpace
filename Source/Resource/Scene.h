#ifndef QTSPACE_SCENE_H
#define QTSPACE_SCENE_H

#include <QMatrix4x4>

#include "Model.h"
#include "GraphNode/Light.h"
#include "GraphNode/Camera.h"

using namespace std;

class Scene;

typedef shared_ptr<Scene> ScenePtr;
typedef shared_ptr<const Scene> kScenePtr;

class Scene : public Resource {
public:
    Scene();

    static ScenePtr CreateCube();

    size_t model_size() const;

    kModelPtr GetModel(size_t index) const;

    void AddModel(const ModelPtr &model);

    QMatrix4x4 transformation() const;

    QMatrix4x4 projection() const;

    const Camera &camera() const;

    void Resize(int w, int h);

    void Animate(float time_delta);

private:
    QMatrix4x4 transform_;
    Camera camera_;
    QMatrix4x4 projection_;
    Light light_;
    vector<ModelPtr> models_;
};

#endif //QTSPACE_SCENE_H
