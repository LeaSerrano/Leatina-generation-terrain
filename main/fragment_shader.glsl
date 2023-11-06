#version 330 core


//uniform sampler2D texheightMap;
uniform sampler2D tex0;
uniform sampler2D tex1;
uniform sampler2D tex2;
uniform sampler2D texTransition;


// Ouput data
//out vec3 color;
out vec4 FragColor;

//in vec3 o_color;
in vec2 o_tex;
in vec4 heightmap;

void main(){

        //color =vec3(0.2, 0.2,0.4);
        //FragColor = vec4(o_tex,0.,1.);

        

        /* if(heightmap.r < 0.25){
            FragColor = texture(tex0,o_tex);
        } else if (heightmap.r >= 0.25 && heightmap.r <= 0.4){
            FragColor = texture(tex1,o_tex);
        } else if(heightmap.r > 0.4){
            FragColor = texture(tex2,o_tex);
        } */


        vec4 color;

        if (heightmap.r < 0.15) {
            color = texture(tex0, o_tex);
        } else if (heightmap.r >= 0.15 && heightmap.r <= 0.3) {
            vec4 c0 = texture(tex0, o_tex);
            vec4 c1 = texture(tex1, o_tex);
            color = mix(c0, c1, smoothstep(0.15, 0.3, heightmap.r));
        } else if (heightmap.r > 0.3 && heightmap.r <= 0.5) {
            vec4 c1 = texture(tex1, o_tex);
            vec4 c2 = texture(tex2, o_tex);
            color = mix(c1, c2, smoothstep(0.4, 0.5, heightmap.r));
        } else {
            color = texture(tex2, o_tex);
        }

        FragColor = color;

        
        
        //FragColor = texture(tex, o_tex);



}
