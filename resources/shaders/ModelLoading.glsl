#shader vertex
#version 330 core

layout (location = 0) in vec3 a_Position;
layout (location = 1) in vec3 a_Normal;
layout (location = 2) in vec2 a_TexCoord;

out vec2 v_TexCoord;

uniform mat4 u_Model;
uniform mat4 u_ViewProjection;

void main() {
    gl_Position = u_ViewProjection * u_Model * vec4(a_Position, 1.0f);
    v_TexCoord = a_TexCoord;
}

#shader fragment
#version 330 core

layout (location = 0) out vec4 o_Color;

in vec2 v_TexCoord;

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;

void main() {
    o_Color = texture(texture_diffuse1, v_TexCoord);
}