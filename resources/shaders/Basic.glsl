#shader vertex
#version 330 core

layout (location = 0) in vec4 aPosition;
layout (location = 1) in vec2 aTexCoord;

out vec2 v_TexCoord;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;

void main() {
    gl_Position = u_Projection * u_View * u_Model * aPosition;
    v_TexCoord = aTexCoord;
}

#shader fragment
#version 330 core

layout (location = 0) out vec4 color;

in vec2 v_TexCoord;

uniform sampler2D u_Texture;

void main() {
    color = texture(u_Texture, v_TexCoord);
}
