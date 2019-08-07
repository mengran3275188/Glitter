#version 400 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoords;

out vec3 WorldNormal;
out vec3 WorldPos;
out vec2 TexCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * vec4(position, 1.0f);
    WorldPos = vec3(model * vec4(position, 1.0f));
    WorldNormal = mat3(transpose(inverse(model))) * normal;
    TexCoords = texCoords;
}