#shader vertex
#version 330 core

layout (location = 0) in vec4 a_Position;
layout (location = 1) in vec3 a_Normal;
layout (location = 2) in vec2 a_TexCoords;

out vec2 v_TexCoords;
out vec3 v_Normal;
out vec3 v_FragmentPosition;

uniform mat4 u_Model;
uniform mat4 u_ViewProjection;

void main() {
    gl_Position = u_ViewProjection * u_Model * a_Position;
    v_TexCoords = a_TexCoords;
    v_Normal = mat3(transpose(inverse(u_Model))) * a_Normal;
    v_FragmentPosition = (u_Model * a_Position).xyz;
}

#shader fragment
#version 330 core

layout (location = 0) out vec4 fragColor;

in vec2 v_TexCoords;
in vec3 v_Normal;
in vec3 v_FragmentPosition;

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

struct DirectionalLight {
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float constant;
    float linear;
    float quadratic;
};

struct SpotLight {
    vec3 position;
    vec3 direction;
    float innerCutOff;
    float outerCutOff;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float constant;
    float linear;
    float quadratic;
};

#define NR_POINT_LIGHTS 4

uniform vec3 u_ViewerPosition;
uniform Material u_Material;

uniform DirectionalLight u_DirLight;
uniform PointLight u_PointLights[NR_POINT_LIGHTS];
uniform SpotLight u_SpotLight;


vec3 CalcDirLight(DirectionalLight dirLight, vec3 normal, vec3 viewDirection);
vec3 CalcPointLight(PointLight pointLight, vec3 normal, vec3 viewDirection, vec3 fragPosition);
vec3 CalcSpotLight(SpotLight spotLight, vec3 normal, vec3 viewDirection, vec3 fragPosition);


void main() {
    vec3 color = vec3(0.0f);
    vec3 normal = normalize(v_Normal);
    vec3 viewDirection = normalize(u_ViewerPosition - v_FragmentPosition);

    color += CalcDirLight(u_DirLight, normal, viewDirection);

    for (int i = 0; i < NR_POINT_LIGHTS; ++i) {
        color += CalcPointLight(u_PointLights[i], normal, v_FragmentPosition, viewDirection);
    }

    color += CalcSpotLight(u_SpotLight, normal, v_FragmentPosition, viewDirection);

    fragColor = vec4(color, 1.0f);
}

vec3 CalcDirLight(DirectionalLight dirLight, vec3 normal, vec3 viewDirection) {
    vec3 lightDirection = normalize(-dirLight.direction);

    // ambient shading
    vec3 ambient = dirLight.ambient * texture(u_Material.diffuse, v_TexCoords).rgb;

    // diffuse shading
    float diff = max(dot(normal, lightDirection), 0.0f);
    vec3 diffuse = dirLight.diffuse * diff * texture(u_Material.diffuse, v_TexCoords).rgb;

    // specular shading
    vec3 reflectedDirection = reflect(-lightDirection, normal);
    float spec = pow(max(dot(viewDirection, reflectedDirection), 0.0f), u_Material.shininess);
    vec3 specular = dirLight.specular * spec * texture(u_Material.specular, v_TexCoords).rgb;

    return (ambient + diffuse + specular);
}

vec3 CalcPointLight(PointLight pointLight, vec3 normal, vec3 fragPosition, vec3 viewDirection) {
    vec3 lightDirection = normalize(pointLight.position - fragPosition);

    // ambient shading
    vec3 ambient = pointLight.ambient * texture(u_Material.diffuse, v_TexCoords).rgb;

    // diffuse shading
    float diff = max(dot(normal, lightDirection), 0.0f);
    vec3 diffuse = pointLight.diffuse * diff * texture(u_Material.diffuse, v_TexCoords).rgb;

    // specular shading
    vec3 reflectedDirection = reflect(-lightDirection, normal);
    float spec = pow(max(dot(reflectedDirection, viewDirection), 0.0f), u_Material.shininess);
    vec3 specular = pointLight.specular * spec * texture(u_Material.specular, v_TexCoords).rgb;

    // attenuation factor
    float dist = length(pointLight.position - fragPosition);
    float attenuation = 1.0f / (pointLight.constant + pointLight.linear * dist + pointLight.quadratic * dist * dist);

    return (ambient + diffuse + specular) * attenuation;
}

vec3 CalcSpotLight(SpotLight spotLight, vec3 normal, vec3 fragPosition, vec3 viewDirection) {
    vec3 lightDirection = normalize(spotLight.position - fragPosition);

    // ambient shading
    vec3 ambient = spotLight.ambient * texture(u_Material.diffuse, v_TexCoords).rgb;

    // diffuse shading
    float diff = max(dot(normal, lightDirection), 0.0f);
    vec3 diffuse = spotLight.diffuse * diff * texture(u_Material.diffuse, v_TexCoords).rgb;

    // specular shading
    vec3 reflectedDirection = reflect(-lightDirection, normal);
    float spec = pow(max(dot(reflectedDirection, viewDirection), 0.0f), u_Material.shininess);
    vec3 specular = spotLight.specular * spec * texture(u_Material.specular, v_TexCoords).rgb;

    // attenuation factor
    float dist = length(spotLight.position - fragPosition);
    float attenuation = 1.0f / (spotLight.constant + spotLight.linear * dist + spotLight.quadratic * dist * dist);

    // intensity factor
    float theta = max(dot(lightDirection, normalize(-spotLight.direction)), 0.0f);
    float epsilon = spotLight.innerCutOff - spotLight.outerCutOff;
    float intensity = clamp((theta - spotLight.outerCutOff) / epsilon, 0.0f, 1.0f);

    return (ambient + diffuse + specular) * attenuation * intensity;
}