#version 330

in vec2 f_uv0;
out vec4 gl_Color;

uniform sampler2D u_ambient_texture;
uniform sampler2D u_diffuse_texture;
uniform sampler2D u_specular_texture;

uniform vec3 u_light_color;

struct u_material {
    vec3 ambient_color;
    vec3 diffuse_color;
    vec3 specular_color;
    float shininess;
};


void main() {
    gl_Color = vec4(u_light_color, 1) * texture(u_diffuse_texture, f_uv0);
}
