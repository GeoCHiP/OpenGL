#shader vertex
#version 330 core

layout (location = 0) in vec4 aPosition;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;

out vec3 v_Color;

void main() {
    gl_Position = u_Projection * u_View * u_Model * aPosition;
}

#shader fragment
#version 330 core

layout (location = 0) out vec4 color;

uniform vec3 u_Color;

void main() {
    color = vec4(u_Color, 1.0f);
}
