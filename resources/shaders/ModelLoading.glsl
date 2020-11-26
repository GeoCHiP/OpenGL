#shader vertex
#version 330 core

layout (location = 0) in vec3 a_Position;
layout (location = 1) in vec3 a_Normal;
layout (location = 2) in vec2 a_TexCoord;

out vec3 v_Normal;
out vec2 v_TexCoord;
out vec3 v_FragmentPosition;

uniform mat4 u_Model;
uniform mat4 u_ViewProjection;

void main() {
    gl_Position = u_ViewProjection * u_Model * vec4(a_Position, 1.0f);
    v_TexCoord = a_TexCoord;
    v_Normal = a_Normal;
    v_FragmentPosition = (u_Model * vec4(a_Position, 1.0f)).xyz;
}

#shader fragment
#version 330 core

layout (location = 0) out vec4 o_Color;

in vec3 v_Normal;
in vec2 v_TexCoord;
in vec3 v_FragmentPosition;

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;

uniform vec3 u_ViewerPosition;

struct PointLight {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float constant;
    float linear;
    float quadratic;
};

uniform PointLight u_PointLight;

vec3 CalcPointLight(PointLight pointLight, vec3 normal, vec3 viewDirection, vec3 fragPosition);

void main() {
    vec3 color = vec3(0.0f);
    vec3 viewDirection = normalize(u_ViewerPosition - v_FragmentPosition);
    color += CalcPointLight(u_PointLight, normalize(v_Normal), viewDirection,v_FragmentPosition);
    o_Color = vec4(color, 1.0f);
}

vec3 CalcPointLight(PointLight pointLight, vec3 normal, vec3 fragPosition, vec3 viewDirection) {
    vec3 lightDirection = normalize(pointLight.position - fragPosition);

    // ambient shading
    vec3 ambient = pointLight.ambient * texture(texture_diffuse1, v_TexCoord).rgb;

    // diffuse shading
    float diff = max(dot(normal, lightDirection), 0.0f);
    vec3 diffuse = pointLight.diffuse * diff * texture(texture_diffuse1, v_TexCoord).rgb;

    // specular shading
    vec3 reflectedDirection = reflect(-lightDirection, normal);
    float spec = pow(max(dot(reflectedDirection, viewDirection), 0.0f), 64.0f);
    vec3 specular = pointLight.specular * spec * texture(texture_specular1, v_TexCoord).rgb;

    // attenuation factor
    float dist = length(pointLight.position - fragPosition);
    float attenuation = 1.0f / (pointLight.constant + pointLight.linear * dist + pointLight.quadratic * dist * dist);

    return (ambient + diffuse + specular) * attenuation;
}