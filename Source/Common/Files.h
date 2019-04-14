#ifndef QTSPACE_FILES_H
#define QTSPACE_FILES_H

#include <string>

using namespace std;

namespace Files {
    static const string DefaultCubeModel = "File/Model/cube.fbx";
    static const string DefaultSphereModel = "File/Model/sphere.fbx";
    static const string DefaultVertexShader = "File/Shader/default.vert";
    static const string DefaultFragmentShader = "File/Shader/default.frag";
    static const string DefaultTexturePath = "File/Texture/Default.png";
    static const string DefaultCubeAmbientTexture = "File/Texture/CubeAmbient.png";
    static const string DefaultCubeDiffuseTexture = "File/Texture/CubeDiffuse.png";
    static const string DefaultCubeSpecularTexture = "File/Texture/CubeSpecular.png";

    inline string GetFileExtension(const string &file_path) {
        size_t pos = file_path.find_last_of('.');
        return file_path.substr(pos);
    }
}

#endif //QTSPACE_FILES_H
