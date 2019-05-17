#ifndef QTSPACE_SCENERENDER_H
#define QTSPACE_SCENERENDER_H

#include "Common/Files.h"
#include "Common/TypeDef.h"
#include "Resource/Scene.h"
#include "GLRender/MainLoop.h"
#include "LightRender.h"
#include "SkyBoxRender.h"
#include "MeshInstanceRender.h"
#include "Resource/GraphNode/MeshInstance.h"

class SceneRender : protected QOpenGLFunctions {
public:
    explicit SceneRender(kScenePtr scene);

    void Render(kStatePtr state, QGLFunctionsPtr gl_functions);

private:
    kScenePtr scene_;

    size_t vbo_size_;
    size_t ebo_size_;
    QGLVAOPtr vao_;
    QGLVBOPtr vbo_;
    QGLVBOPtr ebo_;
    QGLShaderPtr mi_shader_;
    std::map<std::string, wQGLTexturePtr> textures_;
    std::vector<MeshInstanceRenderPtr> mesh_instance_renders_;

    size_t light_vbo_size_;
    size_t light_ebo_size_;
    QGLVAOPtr light_vao_;
    QGLVBOPtr light_vbo_;
    QGLVBOPtr light_ebo_;
    QGLShaderPtr light_shader_;
    LightRenderPtr light_render_;

	size_t skybox_vbo_size_;
	size_t skybox_ebo_size_;
	QGLVAOPtr skybox_vao_;
	QGLVBOPtr skybox_vbo_;
	QGLVBOPtr skybox_ebo_;
	QGLShaderPtr skybox_shader_;
	SkyBoxRenderPtr skybox_render_;

    void CreateLightShader();

    void CreateLightRender();

    void CreateLightBuffer();

    void PrepareLightShader(QGLFunctionsPtr gl_functions);

    void PrepareLightBuffer(QGLFunctionsPtr gl_functions);

    void RenderLight(QGLFunctionsPtr gl_functions);

	void CreateSkyboxShaders();

	void CreateSkyboxRender();

	void CreateSkyboxBuffer();

	void CreateSkyboxTexture();

	void PrepareSkyboxShader(QGLFunctionsPtr gl_functions);

	void PrepareSkyboxBuffer(QGLFunctionsPtr gl_functions);

	void RenderSkybox(QGLFunctionsPtr gl_functions);

    void CreateMeshInstanceShaders();

    void CreateMeshInstanceRenders(kNodePtr node, std::map<std::string, size_t> &mesh_buffer_size, QMatrix4x4 transformation);

    void CreateMeshInstanceRenders();

    void CreateMeshInstanceBuffers();

    void CreateMeshInstanceTextures();

    void PrepareMeshInstanceBuffers(QGLFunctionsPtr gl_functions);

    void PrepareMeshInstanceShader(QGLFunctionsPtr gl_functions);

    void RenderMeshInstances(QGLFunctionsPtr gl_functions);
};

#endif //QTSPACE_SCENERENDER_H
