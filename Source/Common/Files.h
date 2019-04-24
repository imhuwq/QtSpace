#ifndef QTSPACE_FILES_H
#define QTSPACE_FILES_H

#include <string>

namespace Files {
    static const std::string DefaultCubeModel = "File/Model/cube.fbx";
    static const std::string DefaultSphereModel = "File/Model/sphere.fbx";
    static const std::string DefaultVertexShader = "File/Shader/default.vert";
    static const std::string DefaultFragmentShader = "File/Shader/default.frag";
    static const std::string DefaultTexturePath = "File/Texture/Default.png";
    static const std::string DefaultCubeAmbientTexture = "File/Texture/CubeAmbient.png";
    static const std::string DefaultCubeDiffuseTexture = "File/Texture/CubeDiffuse.png";
    static const std::string DefaultCubeSpecularTexture = "File/Texture/CubeSpecular.png";

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
