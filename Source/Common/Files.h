#ifndef QTSPACE_FILES_H
#define QTSPACE_FILES_H

#include <string>

namespace Files {
    static const std::string CubeModel = "File/Model/cube.fbx";
    static const std::string SphereModel = "File/Model/sphere.fbx";

    static const std::string ObjectVertexShader = "File/Shader/object.vert";
    static const std::string ObjectFragmentShader = "File/Shader/object.frag";
    static const std::string LightVertexShader = "File/Shader/light.vert";
    static const std::string LightFragmentShader = "File/Shader/light.frag";
	static const std::string SkyboxVertexShader = "File/Shader/skybox.vert";
	static const std::string SkyboxFragmentShader = "File/Shader/skybox.frag";

    static const std::string TexturePath = "File/Texture/Default.png";
    static const std::string CubeAmbientTexture = "File/Texture/CubeAmbient.png";
    static const std::string CubeDiffuseTexture = "File/Texture/CubeDiffuse.png";
    static const std::string CubeSpecularTexture = "File/Texture/CubeSpecular.png";

    static const std::string CubemapFront = "File/Cubemap/front.jpg";
    static const std::string CubemapBack = "File/Cubemap/back.jpg";
    static const std::string CubemapUp = "File/Cubemap/up.jpg";
    static const std::string CubemapDown = "File/Cubemap/down.jpg";
    static const std::string CubemapLeft = "File/Cubemap/left.jpg";
    static const std::string CubemapRight = "File/Cubemap/right.jpg";

    inline std::string GetFileExtension(const std::string &file_path) {
        size_t pos = file_path.find_last_of('.');
        return file_path.substr(pos);
    }
}

namespace ModelFileType {
    static const std::string OBJ = ".obj";
    static const std::string FBX = ".fbx";
}

#endif //QTSPACE_FILES_H
