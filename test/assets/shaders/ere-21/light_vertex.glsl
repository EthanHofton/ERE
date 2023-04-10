#version 410 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormals;
layout (location = 2) in vec2 aTexCoords;

uniform mat4 u_projection;
uniform mat4 u_view;
uniform mat4 u_model;

out vec3 Normals;
out vec3 FragPos;
out vec2 TexCoords;

void main() {
    // transform normals to view space
    Normals = mat3(transpose(inverse(u_model))) * aNormals;
    gl_Position = u_projection * u_view * u_model * vec4(aPos, 1.0);
    FragPos = vec3(u_model * vec4(aPos, 1.0));
    TexCoords = aTexCoords;
}
