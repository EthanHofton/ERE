#version 410 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aUv;

uniform mat4 u_projection;

out vec3 outColor;
out vec2 outUv;

void main() {
    gl_Position = u_projection * vec4(aPos, 1.0);
    outColor = aColor;
    outUv = aUv;
}
