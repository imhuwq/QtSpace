#ifndef QTSPACE_MESHINSTANCERENDER_H
#define QTSPACE_MESHINSTANCERENDER_H

#include "Common/Consts.h"
#include "Common/TypeDef.h"
#include "Resource/Mesh.h"

#include "Resource/Material.h"
#include "Resource/GraphNode/Node.h"
#include "Resource/GraphNode/MeshInstance.h"

class MeshInstanceRender {
public:
    MeshInstanceRender(kNodePtr node,
                       size_t index_buffer_size,
                       size_t vertex_buffer_offset,
                       size_t index_buffer_offset,
                       const QMatrix4x4 &transformation,
					   QGLShaderPtr shader);

	kNodePtr node() const;

	void AddTexture(const std::string& texture_uuid, QGLTexturePtr texture);

	void Render(QGLFunctionsPtr gl_functions);

private:
    kNodePtr node_;
    QMatrix4x4 transformation_;
    size_t vertex_buffer_offset_;
    size_t index_buffer_offset_;
    size_t index_buffer_size_;
	QGLShaderPtr shader_;
	std::map<std::string, QGLTexturePtr> textures_;

	void PrepareBuffer();

	void PrepareMaterial();
};

#endif //QTSPACE_MESHINSTANCERENDER_H
