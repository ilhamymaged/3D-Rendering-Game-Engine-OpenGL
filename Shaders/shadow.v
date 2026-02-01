#version 460 core
layout (location = 0) in vec3 aPos;

uniform mat4 model;

void main()
{
    vec3 worldPos = aPos;
    vec4 fragWorld = model * vec4(worldPos, 1.0);
    gl_Position = fragWorld;
}