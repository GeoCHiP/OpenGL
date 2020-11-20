#shader vertex
#version 330 core

layout (location = 0) in vec4 aPosition;
layout (location = 1) in vec3 aNormal;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;

out vec3 v_Normal;
out vec3 v_FragmentPosition;

void main() {
    gl_Position = u_Projection * u_View * u_Model * aPosition;
    v_Normal = mat3(transpose(inverse(u_Model))) * aNormal;
    v_FragmentPosition = (u_Model * aPosition).xyz;
}

#shader fragment
#version 330 core

layout (location = 0) out vec4 color;

in vec3 v_Normal;
in vec3 v_FragmentPosition;

struct Material {
    vec3 ambient;
    vec3 diffuse;
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
    float spec = pow(max(dot(viewDirection, reflectDirection), 0.0), u_Material.shininess);

    vec3 ambient = u_Light.ambient * u_Material.ambient;
    vec3 diffuse = u_Light.diffuse * (diff * u_Material.diffuse);
    vec3 specular = u_Light.specular * (spec * u_Material.specular);

    vec3 result = ambient + diffuse + specular;
    color = vec4(result, 1.0f);
}
