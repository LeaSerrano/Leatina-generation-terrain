#version 330 core

in vec3 fragNormal;
in vec3 fragPosition;

in vec2 texCoord; // coordonnées de texture
in vec4 heightmap; // hauteurs

uniform vec3 color;

uniform vec3 cameraPos;

uniform vec3 lightColor;
uniform vec3 lightPos;

uniform vec3 ambientMaterial;
uniform vec3 diffuseMaterial;
uniform vec3 specularMaterial;
uniform float shininessMaterial;

uniform sampler2D textureEau;      // Texture pour la hauteur < 10
uniform sampler2D textureHerbe;    // Texture pour la hauteur entre 10 et 100
uniform sampler2D textureRoche;    // Texture pour la hauteur entre 100 et 200
uniform sampler2D textureNeige;    // Texture pour la hauteur > 200

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

    // Obtient la hauteur du terrain à partir de la texture de mélange
    float height = heightmap.r ;//* 255.0;  // Si la valeur de la hauteur est dans l'intervalle [0, 1]

    vec4 color;

    if (height < 10.0) {
        color = texture(textureEau, texCoord);
    } else if (height >= 10.0 && height <= 100.0) {
        vec4 c0 = texture(textureEau, texCoord);
        vec4 c1 = texture(textureHerbe, texCoord);
        color = mix(c0, c1, smoothstep(10.0, 100.0, height));
    } else if (height > 100.0 && height <= 200.0) {
        vec4 c1 = texture(textureHerbe, texCoord);
        vec4 c2 = texture(textureRoche, texCoord);
        color = mix(c1, c2, smoothstep(100.0, 200.0, height));
    } else {
        color = texture(textureRoche, texCoord);
    }

    //vec3 result = (ambient + diffuse + specular) * color;
    vec3 result = (ambient + diffuse + specular) * color.rgb;
    FragColor = vec4(result, 1.0);


}


