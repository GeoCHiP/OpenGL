#shader vertex
#version 330 core

layout (location = 0) in vec4 a_Position;
layout (location = 1) in vec3 a_Normal;
layout (location = 2) in vec2 a_TexCoords;

out vec2 v_TexCoords;
out vec3 v_Normal;
out vec3 v_FragmentPosition;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;

void main() {
    gl_Position = u_Projection * u_View * u_Model * a_Position;
    v_TexCoords = a_TexCoords;
    v_Normal = mat3(transpose(inverse(u_Model))) * a_Normal;
    v_FragmentPosition = (u_Model * a_Position).xyz;
}

#shader fragment
#version 330 core

layout (location = 0) out vec4 color;

in vec2 v_TexCoords;
in vec3 v_Normal;
in vec3 v_FragmentPosition;

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

struct Light {
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};

uniform Material u_Material;
uniform Light u_Light;

uniform vec3 u_ViewerPosition;

void main() {
    // diffuse factor
    vec3 normal = normalize(v_Normal);
    vec3 lightDirection = normalize(u_Light.position - v_FragmentPosition);
    float diff = max(dot(normal, lightDirection), 0.0f);

    // specular factor
    vec3 viewDirection = normalize(u_ViewerPosition - v_FragmentPosition);
    vec3 reflectDirection = reflect(-lightDirection, normal);
    float spec = pow(max(dot(viewDirection, reflectDirection), 0.0), u_Material.shininess * 128.0f);

    vec3 ambient = u_Light.ambient * vec3(texture(u_Material.diffuse, v_TexCoords));
    vec3 diffuse = u_Light.diffuse * diff * vec3(texture(u_Material.diffuse, v_TexCoords));
    vec3 specular = u_Light.specular * spec * vec3(texture(u_Material.specular, v_TexCoords));

    // attenuation factor
    float dist = length(u_Light.position - v_FragmentPosition);
    float attenuation = 1.0f / (u_Light.constant + u_Light.linear * dist + u_Light.quadratic * dist * dist);

    vec3 result = (ambient + diffuse + specular) * attenuation;
    color = vec4(result, 1.0f);
}
