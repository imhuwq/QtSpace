#version 330 core

in vec3 f_uv;

out vec4 gl_Color;

uniform samplerCube u_skybox;

void main()
{    
    gl_Color = texture(u_skybox, f_uv);
}
