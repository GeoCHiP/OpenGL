#shader vertex
#version 330 core

layout (location = 0) in vec4 aPosition;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;

out vec2 v_TexCoords;
out vec3 v_Normal;
out vec3 v_FragmentPosition;

void main() {
    gl_Position = u_Projection * u_View * u_Model * aPosition;
    v_TexCoords = aTexCoords;
    v_Normal = mat3(transpose(inverse(u_Model))) * aNormal;
    v_FragmentPosition = (u_Model * aPosition).xyz;
}

#shader fragment
#version 330 core

layout (location = 0) out vec4 color;

in vec2 v_TexCoords;
in vec3 v_Normal;
in vec3 v_FragmentPosition;

struct Material {
    sampler2D diffuse;
    vec3 specular;
    float shininess;
};

struct Light {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform Material u_Material;
uniform Light u_Light;

uniform vec3 u_ViewerPosition;

void main() {
    // diffuse factor    
    vec3 Normal = normalize(v_Normal);
    vec3 lightDirection = normalize(u_Light.position - v_FragmentPosition);
    float diff = max(dot(Normal, lightDirection), 0.0f);

    // specular factor
    vec3 viewDirection = normalize(u_ViewerPosition - v_FragmentPosition);
    vec3 reflectDirection = reflect(-lightDirection, Normal);
    float spec = pow(max(dot(viewDirection, reflectDirection), 0.0), u_Material.shininess * 128.0f);

    vec3 ambient = u_Light.ambient * vec3(texture(u_Material.diffuse, v_TexCoords));
    vec3 diffuse = u_Light.diffuse * diff * vec3(texture(u_Material.diffuse, v_TexCoords));
    vec3 specular = u_Light.specular * spec * u_Material.specular;

    vec3 result = ambient + diffuse + specular;
    color = vec4(result, 1.0f);
}
