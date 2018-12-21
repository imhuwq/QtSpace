#version 330

in vec2 vertexUV0;
out vec4 gl_Color;

uniform sampler2D ambientTexture;
uniform sampler2D diffuseTexture;
uniform sampler2D specularTexture;

struct Material {
    vec3 ambientColor;
    vec3 diffuseColor;
    vec3 specularColor;
    float shininess;
};


void main() {
    gl_Color = texture(diffuseTexture, vertexUV0);
}
