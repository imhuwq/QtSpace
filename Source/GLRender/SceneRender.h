#ifndef QTSPACE_SCENERENDER_H
#define QTSPACE_SCENERENDER_H

#include "Common/Files.h"
#include "Common/TypeDef.h"
#include "Resource/Scene.h"
#include "GLRender/MainLoop.h"
#include "MeshInstanceRender.h"
#include "Resource/GraphNode/MeshInstance.h"

class SceneRender : protected QOpenGLFunctions {
public:
    explicit SceneRender(kScenePtr scene);

    void Render(kStatePtr state, QGLFunctionsPtr gl_functions);

private:
    kScenePtr scene_;
    std::vector<MeshInstanceRenderPtr> mesh_instance_renders_;
    size_t vbo_size_;
    size_t ebo_size_;

    QGLShaderPtr mesh_instance_shader_;
    QGLVAOPtr vao_;
    QGLVBOPtr vbo_;
    QGLVBOPtr ebo_;
	std::map<std::string, wQGLTexturePtr> textures_;
	std::map<std::string, wQGLTexturePtr> cubemaps_;

    void CreateMeshInstanceShader();

    void CreateMeshInstanceRenders(kNodePtr node, std::map<std::string, size_t> &mesh_buffer_size, QMatrix4x4 transformation);

    void CreateMeshInstanceRenders();

    void CreateMeshInstanceBuffers();

    void CreateMeshInstanceTextures();

	void CreateCubemaps();

    void PrepareMeshInstanceBuffers(QGLFunctionsPtr gl_functions);

    void PrepareMeshInstanceShader(QGLFunctionsPtr gl_functions);

    void RenderMeshInstances(QGLFunctionsPtr gl_functions);
};

#endif //QTSPACE_SCENERENDER_H
