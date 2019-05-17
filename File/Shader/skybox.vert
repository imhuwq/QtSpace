#version 330 core

layout (location = 0) in vec3 v_position;

out vec3 f_uv;

uniform mat4 u_model_matrix;
uniform mat4 u_vp_matrix;

void main()
{
    f_uv = v_position;
    vec4 pos = u_vp_matrix * u_model_matrix * vec4(v_position, 1.0);
    gl_Position = pos.xyww;
}
