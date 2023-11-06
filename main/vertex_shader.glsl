#version 330 core

uniform sampler2D texheightMap;


// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 vertices_position_modelspace;  //vertex
layout(location = 1) in vec3 normals_color;                 //normal
layout(location = 2) in vec2 textureuv;                       //uv

//out vec3 o_color;
out vec2 o_tex;
out vec4 heightmap;


//TODO create uniform transformations matrices Model View Projection
// Values that stay constant for the whole mesh.
uniform mat4 model_transformation;
uniform mat4 view_transformation;
uniform mat4 projection_transformation;

void main(){
        vec3 vertex = vertices_position_modelspace;
        heightmap = texture(texheightMap, textureuv);
        vertex.z = heightmap.r * 2.f;
        
        // TODO : Output position of the vertex, in clip space : MVP * position
        //gl_Position = vec4(vertices_position_modelspace,1);
        gl_Position = projection_transformation*view_transformation*model_transformation*vec4(vertex,1.);

        
        //o_color = normals_color;
        o_tex = textureuv;


}

