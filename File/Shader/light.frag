#version 330

in vec3 f_position;
in vec3 f_normal;

out vec4 gl_Color;

uniform vec3 u_light_color;
uniform float u_light_strength;
uniform vec3 u_light_position;
uniform vec3 u_camera_position;
uniform mat4 u_model_matrix;

void main() {
    vec3 normal = normalize(mat3(transpose(inverse(u_model_matrix))) * f_normal);
    vec3 light_direction = normalize(u_light_position - f_position);
    vec3 view_direction = normalize(u_camera_position - f_position);
    vec3 reflect_direction = reflect(-light_direction, normal);

    gl_Color = u_light_strength * vec4(u_light_color, 1);
}
