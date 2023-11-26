/*#version 150
in vec4 vertex;
in vec3 normal;

out vec3 v_position;
out vec3 v_normal;

uniform mat4 mvp_matrix;
uniform mat3 normal_matrix;
void main() {
    v_position = vertex.xyz;
    v_normal = normal_matrix * normal;

    // Calculate vertex position in screen space
    gl_Position = mvp_matrix * vertex;
}
*/

#version 330 core

uniform mat4 MVP;

in vec3 inPosition; // Your vertex attribute
in vec3 inNormal;   // Your normal attribute

out vec3 fragNormal;

void main() {
    gl_Position = MVP * vec4(inPosition, 1.0);
    fragNormal = inNormal;
}
