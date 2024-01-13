#version 330 core

layout (location = 0) in vec3 aPos;

out vec3 TexCoords;

uniform mat4 modelP;
uniform mat4 projectionP;
uniform mat4 viewP;

void main()
{
    TexCoords = aPos;

    gl_Position = projectionP * viewP * modelP * vec4(aPos,1.0);

    //gl_Position = projectionP * viewP * vec4(aPos, 1.0);
}
