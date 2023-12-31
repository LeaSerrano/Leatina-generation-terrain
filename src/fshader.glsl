#version 330 core

in vec3 fragNormal;
in vec3 fragPosition;

in vec2 texCoord; // coordonnées de texture
in vec4 heightmap; // hauteurs

//uniform vec3 color;

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

uniform samplerCube cubemapTexture;

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
    float height = heightmap.r;  // La valeur de la hauteur est dans l'intervalle [0, 1]

    vec4 h_color;
    vec4 cE = texture(textureEau, texCoord);
    vec4 cH = texture(textureHerbe, texCoord);
    vec4 cR = texture(textureRoche, texCoord);
    vec4 cN = texture(textureNeige, texCoord);

    if (height < 0.05) {
        h_color = cE;
    } else if (height >= 0.05 && height <= 0.1) {
        h_color = mix(cE, cH, smoothstep(0.05, 0.1, height));
    } else if (height > 0.1 && height <= 0.5) {
        h_color = cH;
    } else if (height > 0.5 && height <= 0.6) {
        h_color = mix(cH, cR, smoothstep(0.5, 0.6, height));
    } else if (height > 0.6 && height <= 0.75) {
        h_color = cR;
    } else if (height > 0.75 && height <= 0.8) {
        h_color = mix(cR, cN, smoothstep(0.75, 0.8, height));
    } else {
        h_color = cN;
    }

    vec3 reflection = reflect(normalize(viewDir), normal);
    vec3 environmentColor = texture(cubemapTexture, reflection).rgb;
    vec3 result = (ambient + diffuse + specular) * h_color.rgb * environmentColor;

    //vec3 result = (ambient + diffuse + specular) * h_color;
    //vec3 result = (ambient + diffuse + specular) * h_color.rgb;
    FragColor = vec4(result, 1.0);
    //FragColor = h_color;

}


