#ifndef QTSPACE_SCENE_H
#define QTSPACE_SCENE_H

#include <QTime>
#include <QMatrix4x4>

#include "Model.h"
#include "Common/TypeDef.h"
#include "GraphNode/Camera.h"
#include "Control/Controller.h"
#include "GraphNode/Light/Light.h"

class Scene : public Resource {
	friend class SceneAnimator;
	friend class SceneRender;

public:
    Scene();

    void LoadModelFile(const string &file_path);

    void InitCamera();

    void InitLight();

    size_t model_size() const;

    kModelPtr GetModel(size_t index) const;

    void AddModel(const kModelPtr &model);

    QMatrix4x4 transformation() const;

    QMatrix4x4 projection() const;

    const kCameraPtr camera() const;

    const kLightPtr light() const;

    void Resize(const kStatePtr &state);

private:
    QMatrix4x4 transform_;
    CameraPtr camera_;
    QMatrix4x4 projection_;
    LightPtr light_;
    vector<kModelPtr> models_;
};

#endif //QTSPACE_SCENE_H
