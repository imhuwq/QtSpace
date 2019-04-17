#ifndef QTSPACE_SCENERENDER_H
#define QTSPACE_SCENERENDER_H

#include <map>
#include <stack>
#include <cstring>

#include "Common/Files.h"
#include "Common/TypeDef.h"
#include "Resource/Scene.h"
#include "GLRender/MainLoop.h"
#include "MeshInstanceRender.h"
#include "Resource/GraphNode/MeshInstance.h"

using namespace std;

class SceneRender : protected QOpenGLFunctions {
public:
    explicit SceneRender(kScenePtr scene);

    void Render(kStatePtr state, QOpenGLFunctionsPtr gl_functions);

private:
    kScenePtr scene_;
    vector<MeshInstanceRenderPtr> mesh_instance_renders_;
    size_t vbo_size_;
    size_t ebo_size_;

    QGLShaderPtr shader_;
    QGLVAOPtr vao_;
    QGLVBOPtr vbo_;
    QGLVBOPtr ebo_;
    map<string, QOpenGLTexturePtr> textures_;

    void CreateShaderProgram();

    void CreateMeshInstanceRenders(kNodePtr node, map<string, size_t> &mesh_buffer_size, QMatrix4x4 transformation);

    void CreateMeshInstanceRenders();

    void CreateBuffers();

    void CreateTextures();

    void PrepareGLBuffers(QOpenGLFunctionsPtr gl_functions);

    void PrepareGLShaderPrograms(QOpenGLFunctionsPtr gl_functions);

    void PrepareBuffers(const kMeshInstanceRenderPtr &render);

    void PrepareMaterials(const kMeshInstanceRenderPtr &render);

    void RenderMeshInstances(QOpenGLFunctionsPtr gl_functions);
};

#endif //QTSPACE_SCENERENDER_H
