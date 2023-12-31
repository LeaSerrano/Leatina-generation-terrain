#version 330 core

uniform sampler2D textureHeightmap; //hauteurs

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inNormal;
layout(location = 2) in vec2 textureuv; //UV

out vec3 fragNormal;
out vec3 fragPosition;

out vec2 texCoord; // coordonnées
out vec4 heightmap; //hauteurs

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    //ajouts
    vec3 vertex = inPosition;
    heightmap = texture(textureHeightmap, textureuv);
    vertex.z = heightmap.r * 2.f;

    fragNormal = mat3(transpose(inverse(model))) * inNormal;
    fragPosition = vec3(model * vec4(inPosition, 1.0));
    //gl_Position = projection * view * vec4(fragPosition, 1.0);
    gl_Position = projection * view * model * vec4(vertex,1.);

    texCoord = textureuv; //texture
}
