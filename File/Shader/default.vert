#version 330

layout(location = 0) in vec3 mediump v_position;
layout(location = 1) in vec3 mediump v_normal;
layout(location = 2) in vec2 mediump v_uv0;
layout(location = 3) in vec2 mediump v_uv1;
layout(location = 4) in vec2 mediump v_color;

out vec3 mediump f_position;
out vec3 mediump f_normal;
out vec2 mediump f_uv0;

uniform mat4 u_vp_matrix;
uniform mat4 u_model_matrix;

void main() {
    f_position = (u_model_matrix * vec4(v_position, 1.0)).xyz;
    f_normal = v_normal;
    f_uv0 = v_uv0;

    gl_Position = u_vp_matrix * u_model_matrix * vec4(f_position, 1.0);
}
