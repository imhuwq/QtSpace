#ifndef QTSPACE_SCENE_H
#define QTSPACE_SCENE_H

#include <QTime>
#include <QMatrix4x4>

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


    QMatrix4x4 transformation() const;

    QMatrix4x4 projection() const;

    vector<kNodePtr> nodes() const;

    vector<NodePtr> nodes();

    void AddNode(NodePtr node);

    size_t nodes_size() const;

    const kCameraPtr camera() const;

    const kLightPtr light() const;

private:
    QMatrix4x4 transform_;
    CameraPtr camera_;
    QMatrix4x4 projection_;
    LightPtr light_;

    vector<NodePtr> nodes_;
    map<string, kMeshPtr> meshes_;
    map<string, kMaterialPtr> materials_;
    map<string, kTexturePtr> textures_;
};

#endif //QTSPACE_SCENE_H
