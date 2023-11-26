/*#version 150
in vec3 v_position;
in vec3 v_normal;

out vec4 fragColor;

uniform vec3 light_position;

void main() {
   vec3 L = normalize(light_position - v_position);
   float NL = max(dot(normalize(v_normal), L), 0.0);
   vec3 color = vec3(0.39, 1.0, 0.0);
   vec3 col = clamp(color * 0.2 + color * 0.8 * NL, 0.0, 1.0);
   fragColor = vec4(col, 1.0);
}
*/

#version 330 core

in vec3 fragNormal;

out vec4 fragColor;

void main() {
    // Your fragment shader code using fragNormal
    fragColor = vec4(1.0, 0.0, 0.0, 1.0); // Example color
}
