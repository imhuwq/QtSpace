#ifndef QTSPACE_SCENE_H
#define QTSPACE_SCENE_H

#include <QTime>
#include <QMatrix4x4>

#include "Model.h"
#include "GraphNode/Camera.h"
#include "GraphNode/Light/Light.h"
#include "Control/Controller.h"

using namespace std;

class Scene;

typedef shared_ptr<Scene> ScenePtr;
typedef shared_ptr<const Scene> kScenePtr;

class Scene : public Resource {
public:
    Scene();

    void LoadModelFile(const string &file_path);

    void AddCamera();

    void AddLight();

    size_t model_size() const;

    kModelPtr GetModel(size_t index) const;

    void AddModel(const kModelPtr &model);

    QMatrix4x4 transformation() const;

    QMatrix4x4 projection() const;

    const kCameraPtr camera() const;

    const kLightPtr light() const;

    void Resize(const kStatePtr &state);

    void Animate(const kStatePtr &state, int frame_time_delta);

private:
    QMatrix4x4 transform_;
    CameraPtr camera_;
    QMatrix4x4 projection_;
    LightPtr light_;
    vector<kModelPtr> models_;

    QTime anim_timer_;
    int current_anim_time_;
    int last_anim_time_;
};

#endif //QTSPACE_SCENE_H
