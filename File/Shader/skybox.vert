#version 330 core

layout (location = 0) in vec3 v_position;

out vec3 f_uv;

uniform mat4 u_vp_matrix;

void main()
{
    f_uv = v_position;
    gl_Position = u_vp_matrix * vec4(v_position, 1.0);
}
