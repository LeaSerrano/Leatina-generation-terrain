#version 330 core

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inNormal;

out vec3 fragNormal;
out vec3 fragPosition;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    fragNormal = mat3(transpose(inverse(model))) * inNormal;
    fragPosition = vec3(model * vec4(inPosition, 1.0));
    gl_Position = projection * view * vec4(fragPosition, 1.0);
}
