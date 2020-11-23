#shader vertex
#version 330 core

layout (location = 0) in vec4 a_Position;

void main() {
    gl_Position = a_Position;
}

#shader fragment
#version 330 core

layout (location = 0) out vec4 fragColor;

uniform vec3 u_Color;

void main() {
    fragColor = vec4(u_Color, 1.0f);
}