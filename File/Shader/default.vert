#version 330

layout(location = 0) in vec3 v_position;
layout(location = 1) in vec3 v_normal;
layout(location = 2) in vec2 v_uv0;
layout(location = 3) in vec2 v_uv1;
layout(location = 4) in vec4 v_color;

out vec3 f_position;
out vec3 f_normal;
out vec2 f_uv0;
out vec4 f_color;

uniform bool u_vertex_color;
uniform mat4 u_vp_matrix;
uniform mat4 u_model_matrix;

void main() {
    f_position = (u_model_matrix * vec4(v_position, 1.0)).xyz;
    f_normal = v_normal;
    f_uv0 = v_uv0;
    if (u_vertex_color) { f_color = v_color; }

    gl_Position = u_vp_matrix * u_model_matrix * vec4(f_position, 1.0);
}
