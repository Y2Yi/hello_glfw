#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

uniform vec3 offset_uniform;

out vec3 ourColor;

void main()
{
    gl_Position = vec4(aPos + offset_uniform, 1.0);
    ourColor = aColor;
}