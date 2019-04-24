#ifndef QTSPACE_SCENE_H
#define QTSPACE_SCENE_H

#include <QTime>
#include <QMatrix4x4>

#include "Skybox.h"
#include "Common/TypeDef.h"
#include "GraphNode/Camera.h"
#include "Control/Controller.h"
#include "GraphNode/Light/Light.h"

class Scene : public Resource {
    friend class SceneAnimator;

    friend class SceneRender;

public:
    Scene();

    void LoadModelFile(const std::string &file_path);

    void LoadDefaultModelFile();

    void InitCamera();

    void InitLight();

	void InitSkyBox();

    QMatrix4x4 transformation() const;

    QMatrix4x4 projection() const;

	std::vector<kNodePtr> nodes() const;

	std::vector<NodePtr> nodes();

    void AddNode(NodePtr node);

    size_t nodes_size() const;

    const kCameraPtr camera() const;

    const kLightPtr light() const;

private:
    QMatrix4x4 transform_;
    CameraPtr camera_;
    QMatrix4x4 projection_;
    LightPtr light_;
	SkyBoxPtr skybox_;

	std::vector<NodePtr> nodes_;
	std::map<std::string, wkMeshPtr> meshes_;
	std::map<std::string, wkMaterialPtr> materials_;
	std::map<std::string, wkTexturePtr> textures_;
};

#endif //QTSPACE_SCENE_H
