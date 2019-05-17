#version 330

struct direction_light {
    vec3 color;
    float strength;
    vec3 position;
};

struct material {
    vec3 ambient_color;
    float ambient_strength;
    sampler2D ambient_texture;
    vec3 diffuse_color;
    float diffuse_strength;
    sampler2D diffuse_texture;
    vec3 specular_color;
    float specular_strength;
    sampler2D specular_texture;
    float shininess;
};

in vec3 f_position;
in vec3 f_normal;
in vec2 f_uv0;
in vec4 f_color;

out vec4 gl_Color;

uniform bool u_vertex_color;
uniform vec3 u_camera_position;
uniform mat4 u_model_matrix;
uniform direction_light u_global_light;
uniform material u_material;
uniform samplerCube u_skybox;

void main() {
    vec3 normal = normalize(mat3(transpose(inverse(u_model_matrix))) * f_normal);
    vec3 light_direction = normalize(u_global_light.position - f_position);
    vec3 view_direction = normalize(u_camera_position - f_position);
    vec3 light_reflect_direction = reflect(-light_direction, normal);
    vec3 view_reflect_direction = reflect(-view_direction, normal);

    vec4 ambient_color = vec4(u_material.ambient_color, 1) * texture(u_material.ambient_texture, f_uv0);
    ambient_color = u_material.ambient_strength * ambient_color;

    float diffuse = max(dot(normal, light_direction), 0);
    vec4 diffuse_color = vec4(u_material.diffuse_color, 1) * texture(u_material.diffuse_texture, f_uv0);
    diffuse_color = diffuse * u_material.diffuse_strength * diffuse_color;

    float specular = max(dot(view_direction, light_reflect_direction), 0);
    specular = pow(specular, u_material.shininess);
    vec4 specular_color = vec4(u_material.specular_color, 1) * texture(u_material.specular_texture, f_uv0);
    specular_color = specular * u_material.specular_strength * specular_color;

    vec4 global_light_color = u_global_light.strength * vec4(u_global_light.color, 1);

    vec4 cubemap_reflect_color = vec4(texture(u_skybox, view_reflect_direction).rgb, 1.0);

    vec4 final_color = cubemap_reflect_color * global_light_color * (ambient_color + diffuse_color + specular_color);
    if (u_vertex_color) final_color = f_color * final_color;
    gl_Color = final_color;
}
