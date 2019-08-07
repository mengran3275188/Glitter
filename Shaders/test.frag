#version 400 core

in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D diffuse;

out vec4 color;

void main()
{
    color = texture(diffuse, TexCoord);
}