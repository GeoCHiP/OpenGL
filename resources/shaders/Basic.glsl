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

uniform vec3 u_ObjectColor;
uniform vec3 u_LightColor;
uniform vec3 u_LightPosition;
uniform vec3 u_ViewerPosition;

in vec3 v_Normal;
in vec3 v_FragmentPosition;

void main() {
    float ambientStrength = 0.1f;
    vec3 ambient = ambientStrength * u_LightColor;
    
    vec3 Normal = normalize(v_Normal);
    vec3 lightDirection = normalize(u_LightPosition - v_FragmentPosition);
    float diff = max(dot(Normal, lightDirection), 0.0f);
    vec3 diffuse = diff * u_LightColor;
    
    float specularStrength = 0.5f;
    vec3 viewDirection = normalize(u_ViewerPosition - v_FragmentPosition);
    vec3 reflectDirection = reflect(-lightDirection, Normal);
    float spec = pow(max(dot(viewDirection, reflectDirection), 0.0), 32);
    vec3 specular = specularStrength * spec * u_LightColor;

    color = vec4((ambient + diffuse + specular) * u_ObjectColor, 1.0f);
}
