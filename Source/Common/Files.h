#ifndef QTSPACE_FILES_H
#define QTSPACE_FILES_H

#include <string>

namespace Files {
    static const std::string DefaultCubeModel = "File/Model/cube.fbx";
    static const std::string DefaultSphereModel = "File/Model/sphere.fbx";

    static const std::string DefaultVertexShader = "File/Shader/default.vert";
    static const std::string DefaultFragmentShader = "File/Shader/default.frag";
    static const std::string DefaultLightVertexShader = "File/Shader/light.vert";
    static const std::string DefaultLightFragmentShader = "File/Shader/light.frag";
	static const std::string DefaultSkyboxVertexShader = "File/Shader/skybox.vert";
	static const std::string DefaultSkyboxFragmentShader = "File/Shader/skybox.frag";

    static const std::string DefaultTexturePath = "File/Texture/Default.png";
    static const std::string DefaultCubeAmbientTexture = "File/Texture/CubeAmbient.png";
    static const std::string DefaultCubeDiffuseTexture = "File/Texture/CubeDiffuse.png";
    static const std::string DefaultCubeSpecularTexture = "File/Texture/CubeSpecular.png";

    static const std::string DefaultCubemapFront = "File/Cubemap/front.jpg";
    static const std::string DefaultCubemapBack = "File/Cubemap/back.jpg";
    static const std::string DefaultCubemapUp = "File/Cubemap/up.jpg";
    static const std::string DefaultCubemapDown = "File/Cubemap/down.jpg";
    static const std::string DefaultCubemapLeft = "File/Cubemap/left.jpg";
    static const std::string DefaultCubemapRight = "File/Cubemap/right.jpg";

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
