// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>
GLFWwindow* window;

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glut.h> //
#include <iostream>

using namespace glm;

#include <common/controls.hpp>
#include <common/shader.hpp>
#include <common/objloader.hpp>
#include <common/vboindexer.hpp>
#include <common/texture.hpp>

#include "image_ppm.h"
#include "map_gen_noise.cpp"

void processInput(GLFWwindow *window);

// settings
//const unsigned int SCR_WIDTH = 800;
//const unsigned int SCR_HEIGHT = 600;
const unsigned int SCR_WIDTH = 1024;
const unsigned int SCR_HEIGHT = 768;
//const unsigned int SCR_WIDTH = 1920;
//const unsigned int SCR_HEIGHT = 1080;
bool manual = true;

// camera
//glm::vec3 camera_position   = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 camera_position   = glm::vec3(0.25f, 0.25f, 4.0f);
//glm::vec3 camera_target = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 camera_target = glm::vec3(0.0f, 0.0f, 0.0f);
glm::vec3 camera_front = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 camera_up    = glm::vec3(0.0f, 1.0f,  0.0f);

glm::vec3 cameraDirection = glm::normalize(camera_position - camera_target);
glm::vec3 cameraRight = glm::normalize(glm::cross(camera_up, cameraDirection));
glm::vec3 cameraUp = glm::cross(cameraDirection, cameraRight);


// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;
float speedy = 3.f;

float lastInputTime;


//rotation
float angle = 0.;
float zoom = 1.;

/* // Initial position : on +Z
glm::vec3 position = glm::vec3( 0, 0, 0 );
// Initial horizontal angle : toward -Z
float horizontalAngle = 3.14f;
// Initial vertical angle : none
float verticalAngle = 0.0f;
// Initial Field of View
float initialFoV = 45.0f;

float speed = 3.0f; // 3 units / second
float mouseSpeed = 0.005f; */

std::vector<unsigned short> indices; //Triangles concaténés dans une liste
std::vector<std::vector<unsigned short> > triangles;
std::vector<glm::vec3> indexed_vertices;
std::vector<glm::vec2> colored_indices;

float sizeX = 1.;
float sizeY = 1.;
unsigned int resolution = 16;


/*******************************************************************************/
float genZ(){
    return (float)rand()/RAND_MAX;
}

//genSurface = genIndexedVertices + genIndices
/* void genSurface(std::vector<glm::vec3> &coords, std::vector<glm::vec2> &colorcoords, std::vector<unsigned short> &indices, float sizeX, float sizeY, unsigned int resolution){
    coords.clear(); colorcoords.clear(); indices.clear(); 
    float stepX = sizeX/(float)resolution;
    float stepY = sizeY/(float)resolution;

    for(unsigned int i=0; i <= resolution; i ++){
        for(unsigned int j=0; j <= resolution; j ++){
            glm::vec3 coord_actuelle = glm::vec3(i*stepX, j*stepY, (float)0.);
            coords.push_back(coord_actuelle);

            glm::vec2 coord1 = glm::vec2(i*stepX, j*stepY);
            colorcoords.push_back(coord1);
        }
    }

    for(int i=0; i <= resolution-1; i++){        //nH
        for(int j=0; j <= resolution-1; j++){    //nW
            int p1 = i*(resolution+1)+j;
            int p2 = p1+1;
            int p3 = (i+1)*(resolution+1)+j;
            int p4 = p3+1;

            indices.push_back(p1);
            indices.push_back(p2);
            indices.push_back(p4);
            indices.push_back(p1);
            indices.push_back(p4);
            indices.push_back(p3);

        }
    }
} */

void genIndexedVertices(std::vector<glm::vec3> &coords, std::vector<glm::vec2> &colorcoords, float sizeX, float sizeY, unsigned int resolution){
    coords.clear(); colorcoords.clear();
    float stepX = sizeX/(float)resolution;
    float stepY = sizeY/(float)resolution;

    for(unsigned int i=0; i <= resolution; i ++){
        for(unsigned int j=0; j <= resolution; j ++){
            glm::vec3 coord_actuelle = glm::vec3(i*stepX, j*stepY, (float)0.);
            coords.push_back(coord_actuelle);

            glm::vec2 coord1 = glm::vec2(i*stepX, j*stepY);
            colorcoords.push_back(coord1);
        }
    }

};



void genIndices(std::vector<unsigned short> &indices, unsigned int resolution){
    indices.clear();
    for(int i=0; i <= resolution-1; i++){        //nH
        for(int j=0; j <= resolution-1; j++){    //nW
            int p1 = i*(resolution+1)+j;
            int p2 = p1+1;
            int p3 = (i+1)*(resolution+1)+j;
            int p4 = p3+1;

            indices.push_back(p1);
            indices.push_back(p2);
            indices.push_back(p4);
            indices.push_back(p1);
            indices.push_back(p4);
            indices.push_back(p3);

        }
    }
}


//**********************************************************************************************************************************************//
//                                                               MAIN BEGIN HERE
//**********************************************************************************************************************************************//

int main( void )
{
    srand(time(NULL));
    // Initialise GLFW
    if( !glfwInit() )
    {
        fprintf( stderr, "Failed to initialize GLFW\n" );
        getchar();
        return -1;
    }


    //Generation perlin noise
    int nH = 512, nW = 512, nTaille;
    char cNomImg[250];
    std::string perlinNoiseImage = "perlinNoise.pgm";
    strcpy(cNomImg, perlinNoiseImage.c_str());

    OCTET *ImgOut;

    nTaille = nH * nW;
    allocation_tableau(ImgOut, OCTET, nTaille);

    int octaves = 6;
    double frequency = 0.9;
    double persistence = 0.5;

    int seed = generateRandomSeed();

    for (int i = 0; i < nH; ++i) {
        for (int j = 0; j < nW; ++j) {

            double x = static_cast<double>(i) / nW;
            double y = static_cast<double>(j) / nH;

            double perlin = perlinNoise(octaves, frequency, persistence, x, y, seed) * 255;

            if (x < nW / 4) {
                perlin -= 25;
            } else if (x >= 3 * nW / 4) {
                perlin += 25;
            }

            if (perlin > 255) {
                perlin = 255;
            }
            else if (perlin < 0) {
                perlin = 0;
            }

            ImgOut[i*nW + j] = perlin;
        }
    }

    ecrire_image_pgm(cNomImg, ImgOut, nH, nW);
    free(ImgOut);


    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Open a window and create its OpenGL context
    //window = glfwCreateWindow( 1024, 768, "TP1 - GLFW", NULL, NULL);
    window = glfwCreateWindow( SCR_WIDTH, SCR_HEIGHT, "TP1 - GLFW", NULL, NULL);
    if( window == NULL ){
        fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
        getchar();
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // Initialize GLEW
    glewExperimental = true; // Needed for core profile
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        getchar();
        glfwTerminate();
        return -1;
    }

    // Ensure we can capture the escape key being pressed below
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    // Hide the mouse and enable unlimited mouvement
    //  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // Set the mouse at the center of the screen
    glfwPollEvents();
    glfwSetCursorPos(window, SCR_WIDTH/2, SCR_HEIGHT/2);

    // Dark blue background
    glClearColor(0.8f, 0.8f, 0.8f, 0.0f);

    // Enable depth test
    glEnable(GL_DEPTH_TEST);
    // Accept fragment if it closer to the camera than the former one
    glDepthFunc(GL_LESS);

    // Cull triangles which normal is not towards the camera
    //glEnable(GL_CULL_FACE);

    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

    // Create and compile our GLSL program from the shaders
    GLuint programID = LoadShaders( "vertex_shader.glsl", "fragment_shader.glsl");

    /*****************TODO***********************/
    // Get a handle for our "Model View Projection" matrices uniforms

    /****************************************/
    //std::vector<unsigned short> indices; //Triangles concaténés dans une liste
    //std::vector<std::vector<unsigned short> > triangles;
    //std::vector<glm::vec3> indexed_vertices;
    //std::vector<glm::vec2> colored_indices;

    //float sizeX = 1.;
    //float sizeY = 1.;
    //unsigned int resolution = 16;

    //genSurface(indexed_vertices,colored_indices,indices,sizeX,sizeY,resolution);
    genIndexedVertices(indexed_vertices,colored_indices,sizeX,sizeY,resolution);
    genIndices(indices,resolution);
    

    GLuint texturebuffer;
    glGenBuffers(1, &texturebuffer);
    glBindBuffer(GL_ARRAY_BUFFER, texturebuffer);
    glBufferData(GL_ARRAY_BUFFER, colored_indices.size() * sizeof(glm::vec2), &colored_indices[0], GL_STATIC_DRAW);

    bool setTex0 = 0, setTex1 = 0, setTex2 = 0, setTex3 = 0;

    GLuint vertexbuffer;
    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, indexed_vertices.size() * sizeof(glm::vec3), &indexed_vertices[0], GL_STATIC_DRAW);

    // Generate a buffer for the indices as well
    GLuint elementbuffer;
    glGenBuffers(1, &elementbuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned short), &indices[0] , GL_STATIC_DRAW);

    // Get a handle for our "LightPosition" uniform
    glUseProgram(programID);
    GLuint LightID = glGetUniformLocation(programID, "LightPosition_worldspace");



    // For speed computation
    double lastTime = glfwGetTime();
    int nbFrames = 0;
    lastInputTime = glfwGetTime();

    do{

        // Measure speed
        // per-frame time logic
        // --------------------
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // input
        // -----
        processInput(window);

        glGenBuffers(1, &texturebuffer);
        glBindBuffer(GL_ARRAY_BUFFER, texturebuffer);
        glBufferData(GL_ARRAY_BUFFER, colored_indices.size() * sizeof(glm::vec2), &colored_indices[0], GL_STATIC_DRAW);

        glGenBuffers(1, &vertexbuffer);
        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
        glBufferData(GL_ARRAY_BUFFER, indexed_vertices.size() * sizeof(glm::vec3), &indexed_vertices[0], GL_STATIC_DRAW);

        glGenBuffers(1, &elementbuffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned short), &indices[0] , GL_STATIC_DRAW);


        // Clear the screen
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Use our shader
        glUseProgram(programID);


        /*****************TODO***********************/
        // Model matrix : an identity matrix (model will be at the origin) then change
        glm::mat4 ModelMatrix;
        ModelMatrix = glm::translate(ModelMatrix, glm::vec3(0.,0.,0.));
        ModelMatrix = glm::scale(ModelMatrix, glm::vec3(1.f,1.f,1.f));
        // View matrix : camera/view transformation lookat() utiliser camera_position camera_target camera_up
        glm::mat4 ViewMatrix;
        //ViewMatrix = glm::lookAt(camera_position, camera_target, camera_up);
        if(manual){
            ViewMatrix = glm::lookAt(camera_position, camera_position + camera_front, camera_up);
        }else{
            const float radius = radians(45.0f);
            //const float radius = 10.0f;
            float camX = sin(glfwGetTime()) * radius;
            float camZ = cos(glfwGetTime()) * radius;
            //ViewMatrix = glm::lookAt(camera_position, camera_position + camera_front, camera_up);
            //ViewMatrix = glm::lookAt(glm::vec3(camX, 0.0, camZ), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
            ViewMatrix = glm::lookAt(glm::vec3(camX, 0.0, camZ), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
        }

        

        // Projection matrix : 45 Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
        glm::mat4 ProjectionMatrix;
        //ProjectionMatrix = glm::perspective(glm::radians(45.f), 4.f/3.f, 0.1f, 100.f);
        ProjectionMatrix = glm::perspective(glm::radians(45.f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.f);

        // Send our transformation to the currently bound shader,
        // in the "Model View Projection" to the shader uniforms

        glUniformMatrix4fv(glGetUniformLocation(programID, "model_transformation"), 1, GL_FALSE, &ModelMatrix[0][0]);
        glUniformMatrix4fv(glGetUniformLocation(programID, "view_transformation"), 1, GL_FALSE, &ViewMatrix[0][0]);
        glUniformMatrix4fv(glGetUniformLocation(programID, "projection_transformation"), 1, GL_FALSE, &ProjectionMatrix[0][0]);


        /****************************************/




        // 1rst attribute buffer : vertices
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
        glVertexAttribPointer(
                    0,                  // attribute
                    3,                  // size
                    GL_FLOAT,           // type
                    GL_FALSE,           // normalized?
                    0,                  // stride
                    (void*)0            // array buffer offset
                    );

        // Index buffer
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);

        //glEnableVertexAttribArray(1);

        //texture
        glBindBuffer(GL_ARRAY_BUFFER, texturebuffer);
        glVertexAttribPointer(
                    2, 
                    2, 
                    GL_FLOAT, 
                    GL_FALSE, 
                    0/* 2*sizeof(float) */, 
                    (void*)0);

        glEnableVertexAttribArray(2);
       
        if(!setTex0){
            glActiveTexture(GL_TEXTURE0);
            GLuint texture0 = loadBMP_custom("../texture/grass.bmp");
            glUniform1i(glGetUniformLocation(programID, "tex0"), 0); 
            glBindTexture (GL_TEXTURE_2D, texture0);
            setTex0 = true;
        }
        if(!setTex1){
            glActiveTexture(GL_TEXTURE1);
            GLuint texture1 = loadBMP_custom("../texture/rock.bmp");
            glUniform1i(glGetUniformLocation(programID, "tex1"), 1); 
            glBindTexture (GL_TEXTURE_2D, texture1);
            setTex1 = true;
        }
        if(!setTex2){
            glActiveTexture(GL_TEXTURE2);
            GLuint texture2 = loadBMP_custom("../texture/snowrocks.bmp");
            glUniform1i(glGetUniformLocation(programID, "tex2"), 2); 
            glBindTexture (GL_TEXTURE_2D, texture2);
            setTex2 = true;
        }
        if(!setTex3){
            glActiveTexture(GL_TEXTURE3);
            GLuint texture3 = loadBMP_custom("../texture/heightmap-1024x1024.bmp");
            glUniform1i(glGetUniformLocation(programID, "texheightMap"), 3); 
            glBindTexture (GL_TEXTURE_2D, texture3);
            setTex3 = true;
        }

        

        // Draw the triangles !
        glDrawElements(
                    GL_TRIANGLES,      // mode
                    indices.size(),    // count
                    GL_UNSIGNED_SHORT,   // type
                    (void*)0           // element array buffer offset
                    );

        glDisableVertexAttribArray(0);

    

        // Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();

    } // Check if the ESC key was pressed or the window was closed
    while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
           glfwWindowShouldClose(window) == 0 );

    // Cleanup VBO and shader
    glDeleteBuffers(1, &vertexbuffer);
    glDeleteBuffers(1, &elementbuffer);
    glDeleteBuffers(1, &texturebuffer);
    glDeleteProgram(programID);
    glDeleteVertexArrays(1, &VertexArrayID);

    // Close OpenGL window and terminate GLFW
    glfwTerminate();

    return 0;
}


// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{   
    std::vector<unsigned short> indices; //Triangles concaténés dans une liste
    std::vector<std::vector<unsigned short> > triangles;
    std::vector<glm::vec3> indexed_vertices;
    std::vector<glm::vec2> colored_indices;

    float sizeX = 1.;
    float sizeY = 1.;
    unsigned int resolution = 16;
    //bool manual = true;
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    
    //Fullscreen
    //if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    //    glViewport(0, 0, width, height);

    //Camera zoom in and out
    float cameraSpeed = 2.5 * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera_position += cameraSpeed * camera_front;//camera_target;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera_position -= cameraSpeed * camera_front;//camera_target;
    //TODO add translations
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera_position -= glm::normalize(glm::cross(camera_front, camera_up)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera_position += glm::normalize(glm::cross(camera_front, camera_up)) * cameraSpeed;

    if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS){
        if ((glfwGetTime() - lastInputTime) > 1.){
            if(manual == true){
                manual = false;
                std::cout << "manual is set to " << manual << std::endl;
            }else if(manual == false ){
                manual = true;
                std::cout << "manual is set to " << manual << std::endl;
            } 
        }
        
    }

    //Résolution
    if (glfwGetKey(window, GLFW_KEY_KP_ADD) == GLFW_PRESS){
        //if ((glfwGetTime() - lastInputTime) > 0.2) {
            resolution += 1;
            std::cout << "resolution++ :" << resolution << std::endl;
            //genSurface(indexed_vertices,colored_indices,indices,sizeX,sizeY,resolution);
            genIndexedVertices(indexed_vertices,colored_indices,sizeX,sizeY,resolution);
            genIndices(indices,resolution);
        //}
    }    
    if (glfwGetKey(window, GLFW_KEY_KP_SUBTRACT) == GLFW_PRESS){
        //if ((glfwGetTime() - lastInputTime) > 0.2) {
            resolution -= 1; 
            std::cout << "resolution-- :" <<resolution << std::endl;
            //genSurface(indexed_vertices,colored_indices,indices,sizeX,sizeY,resolution);
            genIndexedVertices(indexed_vertices,colored_indices,sizeX,sizeY,resolution);
            genIndices(indices,resolution);
        //}
    }
    

    if(!manual){
        if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS){
            
        }
        if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS){
            
        }
    }
    

}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}
