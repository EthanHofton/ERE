#version 410 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoords;
layout (location = 2) in vec2 aNormals;

uniform mat4 u_projection;
uniform mat4 u_view;

out vec2 TexCoords;

void main() {
    TexCoords = aTexCoords;    
    gl_Position = u_projection * u_view * vec4(aPos, 1.0);
}
