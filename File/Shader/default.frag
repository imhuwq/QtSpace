#version 330

struct direction_light {
    vec3 mediump color;
    float mediump strength;
    vec3 mediump position;
};

struct material {
    vec3 mediump ambient_color;
    float mediump ambient_strength;
    sampler2D ambient_texture;
    vec3 mediump diffuse_color;
    float mediump diffuse_strength;
    sampler2D diffuse_texture;
    vec3 mediump specular_color;
    float mediump specular_strength;
    sampler2D specular_texture;
    float mediump shininess;
};

in vec3 mediump f_position;
in vec3 mediump f_normal;
in vec2 mediump f_uv0;
out vec4 gl_Color;

uniform vec3 mediump u_camera_position;
uniform mat4 u_model_matrix;
uniform direction_light u_global_light;
uniform material u_material;

void main() {
    vec3 mediump normal = normalize(mat3(transpose(inverse(u_model_matrix))) * f_normal);
    vec3 mediump light_direction = normalize(u_global_light.position - f_position);
    vec3 mediump view_direction = normalize(u_camera_position - f_position);
    vec3 mediump reflect_direction = reflect(-light_direction, normal);

    vec4 ambient_color = vec4(u_material.ambient_color, 1) * texture(u_material.ambient_texture, f_uv0);
    ambient_color = u_material.ambient_strength * ambient_color;

    float mediump diffuse = max(dot(normal, light_direction), 0);
    vec4 diffuse_color = vec4(u_material.diffuse_color, 1) * texture(u_material.diffuse_texture, f_uv0);
    diffuse_color = diffuse * u_material.diffuse_strength * diffuse_color;


    float mediump specular = max(dot(view_direction, reflect_direction), 0);
    specular = pow(specular, u_material.shininess);
    vec4 specular_color = vec4(u_material.specular_color, 1) * texture(u_material.specular_texture, f_uv0);
    specular_color = specular * u_material.specular_strength * specular_color;

    vec4 global_light_color = u_global_light.strength * vec4(u_global_light.color, 1);
    gl_Color = global_light_color * (ambient_color + diffuse_color + specular_color);
}
