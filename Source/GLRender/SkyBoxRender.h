#ifndef QTSPACE_SKYBOXRENDER_H
#define QTSPACE_SKYBOXRENDER_H

#include "Common/Consts.h"
#include "Common/TypeDef.h"
#include "Resource/Mesh.h"

#include "Resource/Material.h"
#include "Resource/GraphNode/Node.h"
#include "Resource/GraphNode/MeshInstance.h"

class SkyBoxRender {
public:
	SkyBoxRender(kNodePtr node,
		size_t index_buffer_size,
		QGLShaderPtr shader);

	kNodePtr node() const;

	void AddTexture(const std::string &texture_uuid, QGLTexturePtr texture);

	void Render(QGLFunctionsPtr gl_functions);

private:
	kNodePtr node_;
	size_t index_buffer_size_;
	QGLShaderPtr shader_;
	std::map<std::string, QGLTexturePtr> textures_;

	void PrepareBuffer();

	void PrepareCubemap();
};

#endif // QTSPACE_SKYBOXRENDER_H