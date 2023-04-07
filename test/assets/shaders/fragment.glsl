#version 410 core

in vec3 outColor;
in vec2 outUv;

uniform sampler2D uContainer;
uniform float u_time;

out vec4 FragColor;

void main() {
    FragColor = vec4(vec3(texture(uContainer, outUv)) * outColor * sin(u_time), 1.);
}
