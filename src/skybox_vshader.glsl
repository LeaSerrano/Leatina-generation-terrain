#version 330 core

layout (location = 0) in vec3 aPos;

out vec3 TexCoords;

uniform mat4 projectionS;
uniform mat4 viewS;

void main()
{
    TexCoords = aPos;
    gl_Position = projectionS * viewS * vec4(aPos, 1.0);
}
