#shader vertex
#version 330 core

layout (location = 0) in vec3 a_Position;

uniform mat4 u_View;
uniform mat4 u_Projection;
uniform float u_AspectRatio;

void main() {
    gl_Position = u_Projection * u_View * vec4(a_Position.x, a_Position.y, a_Position.z, 1.0f);
}

#shader fragment
#version 330 core

layout (location = 0) out vec4 fragColor;

void main() {
    fragColor = vec4(1.0f);
}
