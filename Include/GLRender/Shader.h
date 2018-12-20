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
                                    "\n"
                                    "out vec4 positionColor;\n"
                                    "\n"
                                    "uniform mat4 modelMatrix;\n"
                                    "uniform mat4 viewMatrix;\n"
                                    "uniform mat4 projectionMatrix;\n"
                                    "\n"
                                    "void main() {\n"
                                    "\tgl_Position = vec4(position, 1.0);\n"
                                    "\tpositionColor = gl_Position;\n"
                                    "}";

const QString DefaultFragmentShader = "#version 330\n"
                                      "\n"
                                      "in vec4 positionColor;\n"
                                      "out vec4 color;\n"
                                      "\n"
                                      "void main() {\n"
                                      "    color = positionColor;\n"
                                      "}";

#endif //QTSPACE_SHADER_H
