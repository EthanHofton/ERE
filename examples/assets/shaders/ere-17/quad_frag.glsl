#version 410 core

out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D color_buffer;

void main()
{    
    FragColor = texture(color_buffer, TexCoords);
}
