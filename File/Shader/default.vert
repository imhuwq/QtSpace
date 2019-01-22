#version 330

layout(location = 0) in vec3 v_position;
layout(location = 1) in vec3 v_normal;
layout(location = 2) in vec2 v_uv0;
layout(location = 3) in vec2 v_uv1;
layout(location = 4) in vec2 v_color;

out vec2 f_uv0;

uniform mat4 u_vp_matrix;
uniform mat4 u_model_matrix;

void main() {
    gl_Position = u_vp_matrix * u_model_matrix * vec4(v_position, 1.0);
    f_uv0 = v_uv0;
}
