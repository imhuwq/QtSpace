#version 330

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 uv0;
layout(location = 3) in vec2 uv1;
layout(location = 4) in vec2 color;

out vec2 vertexUV0;

uniform mat4 mvpMatrix;
uniform mat4 worldMatrix;

void main() {
    gl_Position = mvpMatrix * worldMatrix * vec4(position, 1.0);
    vertexUV0 = uv0;
}
