#ifndef QTSPACE_SHADER_H
#define QTSPACE_SHADER_H

namespace VertexShaderLocation {
    enum Location {
        kPosition = 0,
        kNormal = 1,
        kUV0 = 2,
        kUV1 = 3,
        kColor = 4
    };
}

const QString DefaultVertexShader = "#version 330\n"
                                    "\n"
                                    "layout(location = 0) in vec3 position;\n"
                                    "layout(location = 1) in vec3 normal;\n"
                                    "layout(location = 2) in vec2 uv0;\n"
                                    "\n"
                                    "out vec4 positionColor;\n"
                                    "\n"
                                    "uniform mat4 mvpMatrix;\n"
                                    "uniform mat4 worldMatrix;\n"
                                    "\n"
                                    "void main() {\n"
                                    "\tgl_Position = mvpMatrix * worldMatrix * vec4(position, 1.0);\n"
                                    "\tpositionColor = gl_Position;\n"
                                    "}";

const QString DefaultFragmentShader = "#version 330\n"
                                      "\n"
                                      "in vec4 positionColor;\n"
                                      "out vec4 color;\n"
                                      "\n"
                                      "void main() {\n"
                                      "    color = vec4(0.5, 0, 0, 1);\n"
                                      "}";

#endif //QTSPACE_SHADER_H
