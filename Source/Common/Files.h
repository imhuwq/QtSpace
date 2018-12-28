#ifndef QTSPACE_FILES_H
#define QTSPACE_FILES_H

#include <string>

using namespace std;

namespace Files {
    const string DefaultCubeModelFile = "File/Model/cube.fbx";
    const string DefaultVertexShader = "File/Shader/default.vert";
    const string DefaultFragmentShader = "File/Shader/default.frag";
    const string DefaultTexturePath = "File/Texture/Default.png";
    const string DefaultDiffuseTexturePath = "File/Texture/UVChecker.png";

    inline string GetFileExtension(const string &file_path) {
        size_t pos = file_path.find_last_of('.');
        return file_path.substr(pos);
    }
}

#endif //QTSPACE_FILES_H
