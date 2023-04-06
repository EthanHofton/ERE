#version 410 core

in vec3 outColor;
in vec2 outUv;

uniform sampler2D uContainer;

out vec4 FragColor;

void main() {
    FragColor = texture(uContainer, outUv);
}
