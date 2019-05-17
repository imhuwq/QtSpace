#version 330

layout(location = 0) in vec3 v_position;
layout(location = 1) in vec3 v_normal;

out vec3 f_position;
out vec3 f_normal;

uniform mat4 u_vp_matrix;
uniform mat4 u_model_matrix;

void main() {
    f_position = (u_model_matrix * vec4(v_position, 1.0)).xyz;
    f_normal = v_normal;

    gl_Position = u_vp_matrix * u_model_matrix * vec4(f_position, 1.0);
}
