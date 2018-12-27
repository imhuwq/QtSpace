#ifndef QTSPACE_SCENERENDER_H
#define QTSPACE_SCENERENDER_H

#include <map>
#include <stack>
#include <memory>
#include <cstring>

#include <QOpenGLBuffer>
#include <QOpenGLTexture>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>

#include "Common/Files.h"
#include "Resource/Scene.h"
#include "MeshInstanceRender.h"
#include "Resource/GraphNode/MeshInstance.h"

using namespace std;

typedef shared_ptr<QOpenGLBuffer> glVBOPtr;
typedef shared_ptr<QOpenGLVertexArrayObject> glVAOPtr;
typedef shared_ptr<QOpenGLTexture> glTexturePtr;

class SceneRender;

typedef shared_ptr<SceneRender> SceneRenderPtr;
typedef shared_ptr<const SceneRender> kSceneRenderPtr;

class SceneRender : protected QOpenGLFunctions {
public:
    explicit SceneRender(kScenePtr scene);

    void Draw();

private:
    kScenePtr scene_;
    vector<MeshInstanceRenderPtr> mesh_instance_renders_;
    size_t vbo_size_;
    size_t ebo_size_;

    glShaderPtr shader_;
    glVAOPtr vao_;
    glVBOPtr vbo_;
    glVBOPtr ebo_;
    map<string, glTexturePtr> textures_;
    QOpenGLFunctions *gl_functions_;

    void CreateShaderProgram();

    void CreateMeshInstanceRenders(kNodePtr node, map<string, size_t> &mesh_buffer_size, QMatrix4x4 transformation);

    void CreateMeshInstanceRenders();

    void CreateGLBuffers();

    void CreateGLTextures();

    void PrepareGLBuffers(const kMeshInstanceRenderPtr &render);

    void PrepareMaterial();

    void PrepareGLTextures(const kMeshInstanceRenderPtr &render);

    void RenderMeshInstances();
};

#endif //QTSPACE_SCENERENDER_H
