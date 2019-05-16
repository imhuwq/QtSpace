#version 330 core

out vec4 gl_Color;

in vec3 f_uv;

uniform samplerCube skybox;

void main()
{    
    gl_Color = texture(skybox, f_uv);
}
