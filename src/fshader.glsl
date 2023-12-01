#version 330 core

in vec3 fragNormal;
in vec3 fragPosition;

uniform vec3 color;

uniform vec3 cameraPos;

uniform vec3 lightColor;
uniform vec3 lightPos;

uniform vec3 ambientMaterial;
uniform vec3 diffuseMaterial;
uniform vec3 specularMaterial;
uniform float shininessMaterial;

out vec4 FragColor;

void main()
{
    vec3 normal = normalize(fragNormal);

    vec3 ambient = ambientMaterial * lightColor;

    vec3 lightDir = normalize(lightPos - fragPosition);

    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = (diff * diffuseMaterial) * lightColor;

    vec3 viewDir = normalize(cameraPos-fragPosition);
    vec3 reflectDir = reflect(-lightDir, normal);

    float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininessMaterial);
    vec3 specular = (specularMaterial * spec) * lightColor;

    vec3 result = (ambient + diffuse + specular) * color;
    FragColor = vec4(result, 1.0);
}


