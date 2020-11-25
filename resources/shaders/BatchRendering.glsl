#shader vertex
#version 330 core

layout (location = 0) in vec3 a_Position;
layout (location = 1) in vec2 a_TexCoord;
layout (location = 2) in float a_Index;

uniform mat4 u_ViewProjection;
uniform float u_AspectRatio;

out vec2 v_TexCoord;
out float v_Index;

void main() {
    gl_Position = u_ViewProjection * vec4(a_Position.x, a_Position.y * u_AspectRatio, a_Position.z, 1.0f);
    v_TexCoord = a_TexCoord;
    v_Index = a_Index;
}

#shader fragment
#version 330 core

layout (location = 0) out vec4 o_Color;

uniform sampler2D u_TextureA;
uniform sampler2D u_TextureB;

in vec2 v_TexCoord;
in float v_Index;

void main() {
    int index = int(v_Index);
    if (index == 0)
        o_Color = texture(u_TextureA, v_TexCoord);
    else if (index == 1)
        o_Color = texture(u_TextureB, v_TexCoord);
}
