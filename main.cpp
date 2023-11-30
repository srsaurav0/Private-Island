//
//  main.cpp
//  3D Object Drawing
//
//  Created by Nazirul Hasan on 4/9/23.
//

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.h"
#include "camera.h"
#include "basic_camera.h"
#include "pointLight.h"
#include "sphere.h"
#include "cube.h"
#include "stb_image.h"
#include "curve.h"
#include "cylinder.h"
#include "fan.h"
#include "tennis.h"
#include "halfcurve.h"
#include "speedboat.h"
#include "stairs.h"
#include "sidewall.h"
#include "path.h"
#include "sphere2.h"


#include <iostream>
#include "swing.h"
#include<stdlib.h>
#include<windows.h>

using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);
void drawCube(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 model, float r, float g, float b, float a);
void bed(unsigned int& cubeVAO, Cube& cube1, Cube& cube2, Cube& cube3, Shader& lightingShader, Shader& lightingShaderWithTexture, glm::mat4 alTogether);


void drawTable(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether);
void drawSofa(unsigned int& cubeVAO, Cube& scube, Shader& lightingShaderWithTexture, Shader& lightingShader, glm::mat4 als);
void drawAlmirah(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether);
void drawTv(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether);
void drawWall(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether);
void drawTopFloorWall(unsigned int& cubeVAO, Cube& cube, Shader& lightingShader, Shader& lightingShaderWithTexture, glm::mat4 alTogether, bool doorOpen);
void drawShoeRack(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether);
void drawTable(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether);
void drawSpotLight(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether);
void door(Shader ourShader, glm::mat4 moveMatrix, glm::vec4 color);

unsigned int loadTexture(char const* path, GLenum textureWrappingModeS, GLenum textureWrappingModeT, GLenum textureFilteringModeMin, GLenum textureFilteringModeMax);
void load_texture2(unsigned int& texture, string image_name, GLenum format, bool repeat);




// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// modelling transform
float rotateAngle_X = 0.0;
float rotateAngle_Y = 0.0;
float rotateAngle_Z = 0.0;
float rotateAxis_X = 0.0;
float rotateAxis_Y = 0.0;
float rotateAxis_Z = 1.0;
float translate_X = 0.0;
float translate_Y = 0.0;
float translate_Z = 0.0;
float scale_X = 1.0;
float scale_Y = 1.0;
float scale_Z = 1.0;

float angle = -60.0;
float dv = 0.0f;

float r = 0.0f;
bool fanOn = false;
float throttlerOn = 0.0;

bool d_l_on = true;
bool d_a_on = true;
bool d_d_on = true;
bool d_s_on = true;

bool s_l_on = true;
bool s_a_on = true;
bool s_d_on = true;
bool s_s_on = true;
bool doorOpen = false;

float gravity = 9.81f;  // Acceleration due to gravity
float pendulumLength = 1.0f;
float swingAmplitude = 0.5f; // Adjust the amplitude of the swing motion
float swingFrequency = 1.0f; // Adjust the frequency of the swing motion

float bx = 0.0f;
float by = 0.0f;
bool rot = false;
bool rotinv = false;

// camera
Camera camera(glm::vec3(0.0f, 1.1f, -5.2f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

float eyeX = 0.0, eyeY = 0.0, eyeZ = 3.0;
float lookAtX = 0.0, lookAtY = 0.0, lookAtZ = 0.0;
glm::vec3 V = glm::vec3(0.0f, 1.0f, 0.0f);
BasicCamera basic_camera(eyeX, eyeY, eyeZ, lookAtX, lookAtY, lookAtZ, V);

glm::vec3 amb = glm::vec3(0.2f, 0.2f, 0.2f);
glm::vec3 dif = glm::vec3(0.5f, 0.5f, 0.5f);
glm::vec3 spec = glm::vec3(1.0f, 1.0f, 1.0f);


// positions of the point lights
glm::vec3 pointLightPositions[] = {
    glm::vec3(2.50f,  3.50f,  3.0f),
    glm::vec3(-2.5f,  7.5f,  3.0f),
    glm::vec3(-2.5f,  3.5f,  3.0f),
    glm::vec3(0.0f,   3.5f,  -5.5f),
    glm::vec3(2.50f,  7.5f,  3.0f),
    glm::vec3(-8.20f,  1.75f,  -0.90f),
    glm::vec3(-12.0f,  1.75f,  -0.90f),
    glm::vec3(2.15f,   1.35f,  -15.15f),
    glm::vec3(-1.85f,   1.35f,  -15.15f)
};
PointLight pointlight1(

    pointLightPositions[0].x, pointLightPositions[0].y, pointLightPositions[0].z,  // position
    0.05f, 0.05f, 0.05f,     // ambient
    0.5f, 0.5f, 0.5f,     // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    1       // light number
);
PointLight pointlight2(

    pointLightPositions[2].x, pointLightPositions[2].y, pointLightPositions[2].z,  // position
    0.05f, 0.05f, 0.05f,     // ambient
    0.5f, 0.5f, 0.5f,     // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    2       // light number
);
PointLight pointlight3(

    pointLightPositions[4].x, pointLightPositions[4].y, pointLightPositions[4].z,  // position
    0.05f, 0.05f, 0.05f,     // ambient
    0.5f, 0.5f, 0.5f,     // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    3       // light number
);
PointLight pointlight4(

    pointLightPositions[1].x, pointLightPositions[1].y, pointLightPositions[1].z,  // position
    0.05f, 0.05f, 0.05f,     // ambient
    0.5f, 0.5f, 0.5f,     // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    4       // light number
);
PointLight pointlight5(

    pointLightPositions[3].x, pointLightPositions[3].y, pointLightPositions[3].z,  // position
    0.05f, 0.05f, 0.05f,     // ambient
    0.8f, 0.8f, 0.8f,     // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    5       // light number
);
PointLight pointlight6(

    pointLightPositions[5].x, pointLightPositions[5].y, pointLightPositions[5].z,  // position
    0.05f, 0.05f, 0.05f,     // ambient
    0.8f, 0.8f, 0.8f,     // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    6       // light number
);
PointLight pointlight7(

    pointLightPositions[6].x, pointLightPositions[6].y, pointLightPositions[6].z,  // position
    0.05f, 0.05f, 0.05f,     // ambient
    0.8f, 0.8f, 0.8f,     // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    7       // light number
);
PointLight pointlight8(

    pointLightPositions[7].x, pointLightPositions[7].y, pointLightPositions[7].z,  // position
    0.2f, 0.2f, 0.2f,     // ambient
    0.8f, 0.8f, 0.8f,     // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    8       // light number
);
PointLight pointlight9(

    pointLightPositions[8].x, pointLightPositions[8].y, pointLightPositions[8].z,  // position
    0.2f, 0.2f, 0.2f,     // ambient
    0.8f, 0.8f, 0.8f,     // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    9       // light number
);


// light settings
bool pointLight1On = true;
bool pointLight2On = true;
bool pointambientToggle = true;
bool point2ambientToggle = true;
bool directionalambientToggle = true;
bool spotambientToggle = true;
bool pointdiffuseToggle = true;
bool point2diffuseToggle = true;
bool directionaldiffuseToggle = true;
bool spotdiffuseToggle = true;
bool pointspecularToggle = true;
bool point2specularToggle = true;
bool directionalspecularToggle = true;
bool spotspecularToggle = true;


// timing
float deltaTime = 0.0f;    // time between current frame and last frame
float lastFrame = 0.0f;

// Textures
unsigned int texture0, texture1, texture2, texture3, texture4, texture5, texture6, texture7, texture8, texture9;

unsigned int loadTexture(char const* path, GLenum textureWrappingModeS, GLenum textureWrappingModeT, GLenum textureFilteringModeMin, GLenum textureFilteringModeMax)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(path, &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, textureWrappingModeS);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, textureWrappingModeT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, textureFilteringModeMin);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, textureFilteringModeMax);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}


void load_texture2(unsigned int& texture, string image_name, GLenum format, bool repeat)
{
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);


    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    if (repeat) {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    }
    else {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    }

    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(image_name.c_str(), &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        cout << "Failed to load texture " << image_name << endl;
    }
    stbi_image_free(data);
}

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "CSE 4208: Computer Graphics Laboratory", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetKeyCallback(window, key_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    // build and compile our shader zprogram
    // ------------------------------------
    Shader lightingShader("vertexShaderForPhongShading.vs", "fragmentShaderForPhongShading.fs");
    //Shader lightingShader("vertexShaderForGouraudShading.vs", "fragmentShaderForGouraudShading.fs");
    Shader ourShader("vertexShader.vs", "fragmentShader.fs");

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------


    //////////////////////////////////////////////
    //Curve points

    //vector<float>Fish = {
    //    -0.4350, 1.4000, 5.1000,
    //    -0.5000, 1.4800, 5.1000,
    //    -0.6050, 1.5500, 5.1000,
    //    -0.7300, 1.5850, 5.1000,
    //    -0.8450, 1.5550, 5.1000,
    //    -0.9200, 1.5000, 5.1000,
    //    -1.0300, 1.4150, 5.1000,
    //    -1.1300, 1.3050, 5.1000,
    //    -1.2650, 1.2250, 5.1000,
    //    -1.3900, 1.1450, 5.1000,
    //    -1.5050, 1.0900, 5.1000,
    //    -1.6200, 1.0200, 5.1000,
    //    -1.6350, 0.9050, 5.1000,
    //    -1.5400, 0.8200, 5.1000,
    //    -1.3650, 0.7700, 5.1000,
    //    -1.2200, 0.7550, 5.1000,
    //    -1.0850, 0.7500, 5.1000,
    //    -0.9050, 0.7300, 5.1000,
    //    -0.7900, 0.7400, 5.1000,
    //    -0.6550, 0.7350, 5.1000,
    //    -0.4700, 0.6950, 5.1000,
    //    -0.3800, 0.6400, 5.1000,
    //    -0.3050, 0.5800, 5.1000,
    //    -0.2150, 0.5350, 5.1000,
    //    -0.1250, 0.5350, 5.1000,
    //    -0.0300, 0.5500, 5.1000
    //};


    vector<float> vase = {
        -0.5750, 2.0400, 5.1000,
        -0.5350, 1.9950, 5.1000,
        -0.4900, 1.9350, 5.1000,
        -0.4600, 1.8650, 5.1000,
        -0.4600, 1.7800, 5.1000,
        -0.5200, 1.6800, 5.1000,
        -0.6250, 1.5750, 5.1000,
        -0.6500, 1.5500, 5.1000,
        -0.7200, 1.4800, 5.1000,
        -0.7950, 1.3900, 5.1000,
        -0.8550, 1.2650, 5.1000,
        -0.8900, 1.0850, 5.1000,
        -0.8150, 0.9050, 5.1000,
        -0.7150, 0.7700, 5.1000,
        -0.6050, 0.6500, 5.1000,
        -0.5100, 0.5050, 5.1000,
        -0.4400, 0.3800, 5.1000,
        -0.3550, 0.3100, 5.1000,
        -0.2500, 0.2550, 5.1000,
        -0.1300, 0.2500, 5.1000,
        -0.0500, 0.2400, 5.1000,
        -0.0050, 0.2650, 5.1000,
    };


    vector<float> island = {
        0.0400, 0.2050, 5.1000,
        -0.0900, 0.2250, 5.1000,
        -0.2300, 0.2500, 5.1000,
        -0.3700, 0.2950, 5.1000,
        -0.4950, 0.3300, 5.1000,
        -0.6550, 0.4300, 5.1000,
        -0.8700, 0.5650, 5.1000,
        -1.0100, 0.7000, 5.1000,
        -1.1200, 0.8650, 5.1000,
        -1.2100, 1.0800, 5.1000,
        -1.2450, 1.2550, 5.1000,
        -1.2700, 1.4600, 5.1000,
        -1.2200, 1.7000, 5.1000,
        -1.0950, 1.8500, 5.1000,
        -0.9400, 1.9850, 5.1000,
        -0.7800, 2.1100, 5.1000,
        -0.5450, 2.2250, 5.1000,
        -0.4000, 2.2850, 5.1000,
        -0.2200, 2.3150, 5.1000,
        -0.1050, 2.3300, 5.1000,
        -0.0200, 2.3350, 5.1000,
        0.0300, 2.3350, 5.1000,
    };


    vector<float> boatbody = {
        -0.8650, 2.1050, 5.1000,
        -0.8700, 1.8450, 5.1000,
        -0.8800, 1.5300, 5.1000,
        -0.8550, 1.1400, 5.1000,
        -0.7550, 0.8600, 5.1000,
        -0.5850, 0.6250, 5.1000,
        -0.3650, 0.4150, 5.1000,
        -0.2400, 0.3300, 5.1000,
        -0.1000, 0.2600, 5.1000,
        -0.0150, 0.1950, 5.1000,
    };

    vector<float> boatback = {
        -0.0750, 1.9550, 5.1000,
        -0.2850, 1.9500, 5.1000,
        -0.5600, 1.9200, 5.1000,
        -0.7750, 1.8200, 5.1000,
        -0.9750, 1.6700, 5.1000,
        -1.1200, 1.4750, 5.1000,
        -1.1600, 1.2650, 5.1000,
        -1.1700, 1.0150, 5.1000,
        -1.1550, 0.7750, 5.1000,
        -1.0500, 0.5600, 5.1000,
        -0.9050, 0.4250, 5.1000,
        -0.6750, 0.3300, 5.1000,
        -0.4500, 0.2900, 5.1000,
        -0.2400, 0.2700, 5.1000,
        -0.1200, 0.2700, 5.1000,
        -0.0500, 0.2650, 5.1000,
    };

    vector<float> throttler = {
        -0.2150, 0.4950, 5.1000,
        -0.2700, 0.6750, 5.1000,
        -0.3250, 0.8250, 5.1000,
        -0.4200, 0.9650, 5.1000,
        -0.4800, 1.0850, 5.1000,
        -0.5500, 1.2600, 5.1000,
        -0.6000, 1.4300, 5.1000,
        -0.6600, 1.6150, 5.1000,
        -0.6650, 1.7750, 5.1000,
        -0.6200, 1.9600, 5.1000,
        -0.5400, 2.0700, 5.1000,
        -0.4100, 2.0850, 5.1000,
        -0.3100, 2.0900, 5.1000,
        -0.1650, 2.0800, 5.1000,
        -0.0350, 2.0800, 5.1000,
        -0.0200, 2.0800, 5.1000,
        0.0400, 2.0700, 5.1000,
    };


    float cube_vertices[] = {
        // positions      // normals
        0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f,
        1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f,
        1.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f,
        0.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f,

        1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f,
        1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,

        0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,

        0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,

        1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,

        0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f,
        1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f,
        1.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f
    };
    unsigned int cube_indices[] = {
        0, 3, 2,
        2, 1, 0,

        4, 5, 7,
        7, 6, 4,

        8, 9, 10,
        10, 11, 8,

        12, 13, 14,
        14, 15, 12,

        16, 17, 18,
        18, 19, 16,

        20, 21, 22,
        22, 23, 20
    };

    unsigned int cubeVAO, cubeVBO, cubeEBO;
    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &cubeVBO);
    glGenBuffers(1, &cubeEBO);

    glBindVertexArray(cubeVAO);

    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices), cube_vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cubeEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_indices), cube_indices, GL_STATIC_DRAW);


    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // vertex normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)12);
    glEnableVertexAttribArray(1);

    // second, configure the light's VAO (VBO stays the same; the vertices are the same for the light object which is also a 3D cube)
    unsigned int lightCubeVAO;
    glGenVertexArrays(1, &lightCubeVAO);
    glBindVertexArray(lightCubeVAO);

    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cubeEBO);
    // note that we update the lamp's position attribute's stride to reflect the updated buffer data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    Sphere sphere = Sphere();

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    Shader lightingShaderWithTexture("vertexShaderForPhongShadingWithTexture.vs", "fragmentShaderForPhongShadingWithTexture.fs");
    

    string diffuseMapPath = "container2.png";
    string specularMapPath = "container2_specular.png";
    unsigned int diffMap = loadTexture(diffuseMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap = loadTexture(specularMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube cube = Cube(diffMap, specMap, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);


    diffuseMapPath = "WoodTexture.jpg";
    specularMapPath = "WoodTexture.jpg";
    diffMap = loadTexture(diffuseMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    specMap = loadTexture(specularMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube cube2 = Cube(diffMap, specMap, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);

    //1st floor painting
    diffuseMapPath = "NaturePainting.png";
    specularMapPath = "NaturePainting.png";
    diffMap = loadTexture(diffuseMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    specMap = loadTexture(specularMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube cube3 = Cube(diffMap, specMap, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);

    //2nd floor wall texture
    diffuseMapPath = "grass2.jpg";
    specularMapPath = "grass2.jpg";
    diffMap = loadTexture(diffuseMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    specMap = loadTexture(specularMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube cube4 = Cube(diffMap, specMap, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);

    diffuseMapPath = "grass.jpg";
    specularMapPath = "grass.jpg";
    diffMap = loadTexture(diffuseMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    specMap = loadTexture(specularMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cylinder grass = Cylinder(diffMap, specMap, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);

    diffuseMapPath = "tv.jpg";
    specularMapPath = "tv.jpg";
    diffMap = loadTexture(diffuseMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    specMap = loadTexture(specularMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube cube5 = Cube(diffMap, specMap, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);

    diffuseMapPath = "sea.jpg";
    specularMapPath = "sea.jpg";
    diffMap = loadTexture(diffuseMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    specMap = loadTexture(specularMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube cube6 = Cube(diffMap, specMap, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);

    diffuseMapPath = "fan_center.png";
    specularMapPath = "fan_center.png";
    diffMap = loadTexture(diffuseMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    specMap = loadTexture(specularMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube cube7 = Cube(diffMap, specMap, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);

    diffuseMapPath = "bedsheet3.jpg";
    specularMapPath = "bedsheet3.jpg";
    diffMap = loadTexture(diffuseMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    specMap = loadTexture(specularMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube bsheet = Cube(diffMap, specMap, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);

    diffuseMapPath = "blanket3.jpg";
    specularMapPath = "blanket3.jpg";
    diffMap = loadTexture(diffuseMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    specMap = loadTexture(specularMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube plo = Cube(diffMap, specMap, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);

    diffuseMapPath = "blanket.jpg";
    specularMapPath = "blanket.jpg";
    diffMap = loadTexture(diffuseMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    specMap = loadTexture(specularMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube bkt = Cube(diffMap, specMap, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);

    diffuseMapPath = "blackwood.jpg";
    specularMapPath = "blackwood.jpg";
    diffMap = loadTexture(diffuseMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    specMap = loadTexture(specularMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube cube8 = Cube(diffMap, specMap, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);
    Cylinder cyl8 = Cylinder(diffMap, specMap, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);

    diffuseMapPath = "stonewall.png";
    specularMapPath = "stonewall.png";
    diffMap = loadTexture(diffuseMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    specMap = loadTexture(specularMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube cubeFrontWall = Cube(diffMap, specMap, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);

    diffuseMapPath = "marble.png";
    specularMapPath = "marble.png";
    diffMap = loadTexture(diffuseMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    specMap = loadTexture(specularMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube stair = Cube(diffMap, specMap, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);

    diffuseMapPath = "wall5.jpg";
    specularMapPath = "wall5.jpg";
    diffMap = loadTexture(diffuseMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    specMap = loadTexture(specularMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube fwcube = Cube(diffMap, specMap, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);

    diffuseMapPath = "whitebrick.png";
    specularMapPath = "whitebrick.png";
    diffMap = loadTexture(diffuseMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    specMap = loadTexture(specularMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube wbrcube = Cube(diffMap, specMap, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);


    diffuseMapPath = "wood2.jpg"; //loading image path for diffuse.
    specularMapPath = "black.png"; //loading image path for specular.

    diffMap = loadTexture(diffuseMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    specMap = loadTexture(specularMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube bcube = Cube(diffMap, specMap, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);
    Cylinder bcyl = Cylinder(diffMap, specMap, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);

    diffuseMapPath = "fabric2.jpg"; //loading image path for diffuse.
    specularMapPath = "whiteBackground.png"; //loading image path for specular.

    //wrapping           //mapping 
    diffMap = loadTexture(diffuseMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    specMap = loadTexture(specularMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube bcube2 = Cube(diffMap, specMap, 32.0f, 0.0f, 0.0f, 4.0f, 5.0f);
    Cylinder bcyl2 = Cylinder(diffMap, specMap, 32.0f, 0.0f, 0.0f, 4.0f, 5.0f);

    diffuseMapPath = "blanket3.jpg"; //loading image path for diffuse.
    specularMapPath = "whiteBackground.png"; //loading image path for specular.

    //wrapping           //mapping 
    diffMap = loadTexture(diffuseMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    specMap = loadTexture(specularMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube bcube3 = Cube(diffMap, specMap, 32.0f, 0.0f, 0.0f, 4.0f, 5.0f);



    diffuseMapPath = "wood4.jpg"; //loading image path for diffuse.
    specularMapPath = "black.png"; //loading image path for specular.

    //wrapping           //mapping 
    diffMap = loadTexture(diffuseMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    specMap = loadTexture(specularMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube rcube = Cube(diffMap, specMap, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);
    Cylinder rcyl = Cylinder(diffMap, specMap, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);

    diffuseMapPath = "computer_table.jpg"; //loading image path for diffuse.
    specularMapPath = "whiteBackground.png"; //loading image path for specular.

    //wrapping           //mapping 
    diffMap = loadTexture(diffuseMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    specMap = loadTexture(specularMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube ccube = Cube(diffMap, specMap, 32.0f, 0.0f, 0.0f, 2.0f, 6.0f);
    Cylinder ccyl = Cylinder(diffMap, specMap, 32.0f, 0.0f, 0.0f, 2.0f, 6.0f);

    diffuseMapPath = "tennis.jpg"; //loading image path for diffuse.
    specularMapPath = "tennis.jpg"; //loading image path for specular.
    diffMap = loadTexture(diffuseMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    specMap = loadTexture(specularMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube tennis_cube = Cube(diffMap, specMap, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);

    diffuseMapPath = "net.jpg"; //loading image path for diffuse.
    specularMapPath = "net.jpg"; //loading image path for specular.
    diffMap = loadTexture(diffuseMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    specMap = loadTexture(specularMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube net_cube = Cube(diffMap, specMap, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);

    diffuseMapPath = "swimmingpool.jpg"; //loading image path for diffuse.
    specularMapPath = "swimmingpool.jpg"; //loading image path for specular.
    diffMap = loadTexture(diffuseMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    specMap = loadTexture(specularMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube pool_cube = Cube(diffMap, specMap, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);

    diffuseMapPath = "redsofa.jpg"; //loading image path for diffuse.
    specularMapPath = "redsofa.jpg"; //loading image path for specular.
    diffMap = loadTexture(diffuseMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    specMap = loadTexture(specularMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube sofa_cube = Cube(diffMap, specMap, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);

    diffuseMapPath = "bluesky.jpg"; //loading image path for diffuse.
    specularMapPath = "bluesky.jpg"; //loading image path for specular.
    diffMap = loadTexture(diffuseMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    specMap = loadTexture(specularMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Sphere2 sky = Sphere2(50.0f, 36, 18, glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.5f, 0.5f, 0.5f), 32,
        0, 0, 0.0, 1.0, 0.0, 1.0);


    //diffuseMapPath = "container2.png";
    //specularMapPath = "container2_specular.png";
    //diffMap = loadTexture(diffuseMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    //specMap = loadTexture(specularMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    //Curve  curve = Curve(Fish, diffMap, specMap, 5);


    diffuseMapPath = "vase2.png";
    specularMapPath = "vase2.png";
    diffMap = loadTexture(diffuseMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    specMap = loadTexture(specularMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Curve  vase_curve = Curve(vase, diffMap, specMap, 5);

    diffuseMapPath = "sand.jpg";
    specularMapPath = "sand.jpg";
    diffMap = loadTexture(diffuseMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    specMap = loadTexture(specularMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Curve  island_curve = Curve(vase, diffMap, specMap, 5);

    diffuseMapPath = "tile3.jpg";
    specularMapPath = "tile3.jpg";
    diffMap = loadTexture(diffuseMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    specMap = loadTexture(specularMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube  center_path = Cube(diffMap, specMap, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);

    diffuseMapPath = "tile.jpg";
    specularMapPath = "tile.jpg";
    diffMap = loadTexture(diffuseMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    specMap = loadTexture(specularMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube  border_path = Cube(diffMap, specMap, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);


    diffuseMapPath = "wood5.jpg";
    specularMapPath = "wood5.jpg";
    diffMap = loadTexture(diffuseMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    specMap = loadTexture(specularMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    HalfCurve boat_body = HalfCurve(boatbody, diffMap, specMap, 5);
    HalfCurve boat_back = HalfCurve(boatback, diffMap, specMap, 5);

    diffuseMapPath = "blade.jpg";
    specularMapPath = "blade.jpg";
    diffMap = loadTexture(diffuseMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    specMap = loadTexture(specularMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Curve  throttle = Curve(throttler, diffMap, specMap, 5);

    load_texture2(texture7, "door2.png", GL_RGBA, true);
    load_texture2(texture0, "fan_center.png", GL_RGBA, true);


    //ourShader.use();
    //lightingShader.use();

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // per-frame time logic
        // --------------------
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // be sure to activate shader when setting uniforms/drawing objects
        lightingShader.use();
        lightingShader.setVec3("viewPos", camera.Position);

        // point light 1
        pointlight1.setUpPointLight(lightingShader);
        // point light 2
        pointlight2.setUpPointLight(lightingShader);
        // point light 3
        pointlight3.setUpPointLight(lightingShader);
        // point light 4
        pointlight4.setUpPointLight(lightingShader);
        // point light 5
        pointlight5.setUpPointLight(lightingShader);
        // point light 6
        pointlight6.setUpPointLight(lightingShader);
        // point light 7
        pointlight7.setUpPointLight(lightingShader);
        // point light 8
        pointlight8.setUpPointLight(lightingShader);
        // point light 9
        pointlight9.setUpPointLight(lightingShader);

        //Directional Light
        lightingShader.setVec3("directionalLight.direction", 0.0f, 3.0f, 0.0f);
        lightingShader.setVec3("directionalLight.ambient", 0.2f, 0.2f, 0.2f);
        lightingShader.setVec3("directionalLight.diffuse", 0.7f, 0.7f, 0.7f);
        lightingShader.setVec3("directionalLight.specular", 1.0f, 1.0f, 1.0f);

        lightingShader.setBool("dirLightOn", d_l_on);
        lightingShader.setBool("dirAmbientLightOn", d_a_on);
        lightingShader.setBool("dirDiffuseLightOn", d_d_on);
        lightingShader.setBool("dirSpecularLightOn", d_s_on);

        //Spot light
        lightingShader.setVec3("spotLight.position", -0.5f, 1.0f, -1.5f);
        lightingShader.setVec3("spotLight.direction", 0.0f, -1.0f, 0.0f);
        lightingShader.setVec3("spotLight.ambient", 0.3f, 0.3f, 0.3f);
        lightingShader.setVec3("spotLight.diffuse", 0.8f, 0.8f, 0.8f);
        lightingShader.setVec3("spotLight.specular", 1.0f, 1.0f, 1.0f);
        lightingShader.setFloat("spotLight.k_c", 1.0f);
        lightingShader.setFloat("spotLight.k_l", 0.09);
        lightingShader.setFloat("spotLight.k_q", 0.032);
        lightingShader.setFloat("cos_theta", glm::cos(glm::radians(5.0f)));



        lightingShader.setBool("spotLightOn", s_l_on);
        lightingShader.setBool("spotAmbientLightOn", s_a_on);
        lightingShader.setBool("spotDiffuseLightOn", s_d_on);
        lightingShader.setBool("spotSpecularLightOn", s_s_on);

        // activate shader
        lightingShader.use();

        // pass projection matrix to shader (note that in this case it could change every frame)
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        //glm::mat4 projection = glm::ortho(-2.0f, +2.0f, -1.5f, +1.5f, 0.1f, 100.0f);
        lightingShader.setMat4("projection", projection);

        // camera/view transformation
        glm::mat4 view = camera.GetViewMatrix();
        //glm::mat4 view = basic_camera.createViewMatrix();
        lightingShader.setMat4("view", view);

        // Modelling Transformation
        glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;
        translateMatrix = glm::translate(identityMatrix, glm::vec3(translate_X, translate_Y, translate_Z));
        rotateXMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(scale_X, scale_Y, scale_Z));
        model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
        lightingShader.setMat4("model", model);

        //previous............................................................


        //glBindVertexArray(cubeVAO);
        //glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
        //glDrawArrays(GL_TRIANGLES, 0, 36);


        /*translateMatrix = glm::translate(identityMatrix, glm::vec3(1.0, 0.4, -2.0));
        drawTable(cubeVAO, lightingShader, model*translateMatrix);*/

        //translateMatrix = glm::translate(identityMatrix, glm::vec3(2.0, 0.5, -2.0));
        //drawSofa(cubeVAO, lightingShader, model*translateMatrix);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(-2.0, 0.0, 1.0));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        drawAlmirah(cubeVAO, lightingShader, model * rotateYMatrix * translateMatrix);

        drawWall(cubeVAO, lightingShader, model);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0, 4.5, 0.0));
        drawTopFloorWall(cubeVAO, wbrcube, lightingShader, lightingShaderWithTexture, model* translateMatrix, doorOpen);

        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(2.0, 0.01, 0.0));
        drawShoeRack(cubeVAO, lightingShader, model * translateMatrix *rotateYMatrix );

        translateMatrix = glm::translate(identityMatrix, glm::vec3(-0.4, 0.0, -2.5));
        drawTable(cubeVAO, lightingShader, model*translateMatrix);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(-1.0, 4.5, 0.0));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        drawTv(cubeVAO, lightingShader, model * translateMatrix * rotateYMatrix);

        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(135.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(3.5, 0.0, 0.0));
        drawSpotLight(cubeVAO, lightingShader, model*rotateYMatrix*translateMatrix);




        glm::mat4 modelForSphere = glm::mat4(1.0f);
        modelForSphere = glm::translate(model, glm::vec3(4.5f, 1.2f, 0.5f));
        //sphere.drawSphere(lightingShader, modelForSphere);

        // also draw the lamp object(s)
        ourShader.use();
        ourShader.setMat4("projection", projection);
        ourShader.setMat4("view", view);

        // we now draw as many light bulbs as we have point lights.
        glBindVertexArray(lightCubeVAO);
        //for (unsigned int i = 0; i < 2; i++)
        //{
        //Light bulb 1
        model = glm::mat4(1.0f);
        model = glm::translate(model, pointLightPositions[0]);
        model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
        ourShader.setMat4("model", model);
        ourShader.setVec4("color", glm::vec4(0.8f, 0.8f, 0.8f, 1.0f));
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
            //glDrawArrays(GL_TRIANGLES, 0, 36);
        //}

        //Light bulb 2
        model = glm::mat4(1.0f);
        model = glm::translate(model, pointLightPositions[2]);
        model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
        ourShader.setMat4("model", model);
        ourShader.setVec4("color", glm::vec4(0.8f, 0.8f, 0.8f, 1.0f));
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

        //Light bulb 3
        model = glm::mat4(1.0f);
        model = glm::translate(model, pointLightPositions[4]);
        model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
        ourShader.setMat4("model", model);
        ourShader.setVec4("color", glm::vec4(0.8f, 0.8f, 0.8f, 1.0f));
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

        //Light bulb 4
        model = glm::mat4(1.0f);
        model = glm::translate(model, pointLightPositions[1]);
        model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
        ourShader.setMat4("model", model);
        ourShader.setVec4("color", glm::vec4(0.8f, 0.8f, 0.8f, 1.0f));
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

        //Light bulb 5
        model = glm::mat4(1.0f);
        model = glm::translate(model, pointLightPositions[3]);
        model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
        ourShader.setMat4("model", model);
        ourShader.setVec4("color", glm::vec4(0.8f, 0.8f, 0.8f, 1.0f));
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
        
        //Light bulb 6
        model = glm::mat4(1.0f);
        model = glm::translate(model, pointLightPositions[5]);
        model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
        ourShader.setMat4("model", model);
        ourShader.setVec4("color", glm::vec4(0.8f, 0.8f, 0.8f, 1.0f));
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
        
        //Light bulb 7
        model = glm::mat4(1.0f);
        model = glm::translate(model, pointLightPositions[6]);
        model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
        ourShader.setMat4("model", model);
        ourShader.setVec4("color", glm::vec4(0.8f, 0.8f, 0.8f, 1.0f));
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
        
        //Light bulb 8
        model = glm::mat4(1.0f);
        model = glm::translate(model, pointLightPositions[7]);
        model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
        ourShader.setMat4("model", model);
        ourShader.setVec4("color", glm::vec4(0.8f, 0.8f, 0.8f, 1.0f));
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
        
        //Light bulb 9
        model = glm::mat4(1.0f);
        model = glm::translate(model, pointLightPositions[8]);
        model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
        ourShader.setMat4("model", model);
        ourShader.setVec4("color", glm::vec4(0.8f, 0.8f, 0.8f, 1.0f));
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);


        lightingShaderWithTexture.use();
        lightingShaderWithTexture.setVec3("viewPos", camera.Position);

        // pass projection matrix to shader (note that in this case it could change every frame)
        //glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        //glm::mat4 projection = glm::ortho(-2.0f, +2.0f, -1.5f, +1.5f, 0.1f, 100.0f);
        lightingShaderWithTexture.setMat4("projection", projection);

        // camera/view transformation
        //glm::mat4 view = camera.GetViewMatrix();
        //glm::mat4 view = basic_camera.createViewMatrix();
        lightingShaderWithTexture.setMat4("view", view);

        lightingShaderWithTexture.use();
        // point light 1
        pointlight1.setUpPointLight(lightingShaderWithTexture);
        // point light 2
        pointlight2.setUpPointLight(lightingShaderWithTexture);
        //point light 3
        pointlight3.setUpPointLight(lightingShaderWithTexture);
        // point light 4
        pointlight4.setUpPointLight(lightingShaderWithTexture);
        // point light 5
        pointlight5.setUpPointLight(lightingShaderWithTexture);
        // point light 6
        pointlight6.setUpPointLight(lightingShaderWithTexture);
        // point light 7
        pointlight7.setUpPointLight(lightingShaderWithTexture);
        // point light 8
        pointlight8.setUpPointLight(lightingShaderWithTexture);
        // point light 9
        pointlight9.setUpPointLight(lightingShaderWithTexture);


        glm::mat4 modelMatrixForContainer = glm::mat4(1.0f);
        //modelMatrixForContainer = glm::translate(identityMatrix, glm::vec3(-0.45f, 1.0f, 2.8f));
        //cube.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer);

        modelMatrixForContainer = glm::mat4(1.0f);
        modelMatrixForContainer = glm::translate(identityMatrix, glm::vec3(-4.2f, 0.0f, 3.49f));
        modelMatrixForContainer = modelMatrixForContainer * glm::scale(identityMatrix, glm::vec3(8.4f, 4.5f, 0.01f));
        cube2.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer);

        modelMatrixForContainer = glm::mat4(1.0f);
        modelMatrixForContainer = modelMatrixForContainer * glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        modelMatrixForContainer = modelMatrixForContainer * glm::translate(identityMatrix, glm::vec3(-0.45f, 1.0f, 4.1f));
        modelMatrixForContainer = modelMatrixForContainer * glm::scale(identityMatrix, glm::vec3(2.0f, 2.0f, 0.01f));
        cube3.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer);

        modelMatrixForContainer = glm::mat4(1.0f);
        modelMatrixForContainer = glm::translate(identityMatrix, glm::vec3(-4.2f, 4.4f, 3.48f));
        modelMatrixForContainer = modelMatrixForContainer * glm::scale(identityMatrix, glm::vec3(8.4f, 4.5f, 0.01f));
        cube4.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer);


        modelMatrixForContainer = glm::mat4(1.0f);
        modelMatrixForContainer = modelMatrixForContainer * glm::rotate(identityMatrix, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        modelMatrixForContainer = modelMatrixForContainer * glm::translate(identityMatrix, glm::vec3(-1.4f, 5.7f, 3.49f));
        modelMatrixForContainer = modelMatrixForContainer * glm::scale(identityMatrix, glm::vec3(2.8f, 1.65f, 0.01f));
        cube5.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer);


        modelMatrixForContainer = glm::mat4(1.0f);
        modelMatrixForContainer = glm::translate(identityMatrix, glm::vec3(-50.2f, -1.0f, -50.49f));
        modelMatrixForContainer = modelMatrixForContainer * glm::scale(identityMatrix, glm::vec3(100.0f, 0.01f, 100.0f));
        cube6.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer);


        glActiveTexture(GL_TEXTURE0);
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-3.1f, 0.2f, -8.8));
        //rotateYMatrix = glm::rotate(identityMatrix, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.5f, 0.5f, 0.5f));

        glm::vec4 color1 = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
        glBindTexture(GL_TEXTURE_2D, texture7);
        door(ourShader, translateMatrix* scaleMatrix, color1);
        
        
        //glm::vec4 color1 = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
        glBindTexture(GL_TEXTURE_2D, texture2);
        fan(cube7, cube8, lightingShaderWithTexture, identityMatrix, fanOn);


        //curve.draw(lightingShaderWithTexture, modelMatrixForContainer, glm::vec3(1.0f, 0.0f, 0.0f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(7.5f, 6.13f, 7.0));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.5f, 0.7f, 0.5f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        vase_curve.draw(lightingShaderWithTexture, identityMatrix * rotateYMatrix * scaleMatrix * translateMatrix, glm::vec3(1.0f, 0.0f, 0.0f));

        
        //Island sand
        translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f,-1.0f, 4.0));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(30.0f, 30.00f, 0.05f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        model = identityMatrix * rotateYMatrix * scaleMatrix * translateMatrix;
        island_curve.draw(lightingShaderWithTexture, model , glm::vec3(1.0f, 0.0f, 0.0f));


        //Boat
        translateMatrix = glm::translate(identityMatrix, glm::vec3(3.0f, 0.0f, -30.0));
        model = identityMatrix * translateMatrix;
        speedboat(boat_body, boat_back, cube, throttle, bcyl2, lightingShaderWithTexture, model, bx, by, rot, rotinv, throttlerOn);
        
        //Stairs
        stairs(stair, lightingShaderWithTexture, identityMatrix);

        //Front wall
        translateMatrix = glm::translate(identityMatrix, glm::vec3(0.42f, -0.015f, -101.0));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(3.0f, 4.5f, 0.05f));
        model = identityMatrix *  scaleMatrix * translateMatrix;
        wbrcube.drawCubeWithTexture(lightingShaderWithTexture, model);
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-1.42f, -0.015f, -101.0));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(3.0f, 4.5f, 0.05f));
        model = identityMatrix * scaleMatrix * translateMatrix;
        wbrcube.drawCubeWithTexture(lightingShaderWithTexture, model);
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-0.50f, 0.80f, -101.0));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(2.55f, 2.45f, 0.05f));
        model = identityMatrix * scaleMatrix * translateMatrix;
        wbrcube.drawCubeWithTexture(lightingShaderWithTexture, model);

        tennis(tennis_cube, cyl8, net_cube, lightingShaderWithTexture, identityMatrix);


        translateMatrix = glm::translate(identityMatrix, glm::vec3(-1, 4.3, -3));
        model = identityMatrix * translateMatrix;
        swing(bcube3, rcube, bcyl, ourShader, lightingShaderWithTexture, model);

        float time = glfwGetTime();
        float theta = glm::radians(30.0f) * std::sin(2 * time);

        glm::mat4 rotateMatrix, modelMatrix;

        rotateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 1.7f, 0.0f)) *
            glm::rotate(identityMatrix, theta, glm::vec3(1.0f, 0.0, 0.0f)) *
            glm::translate(identityMatrix, glm::vec3(0.0f, -1.7f, 0.0f));
        modelMatrix = identityMatrix * translateMatrix * rotateMatrix;
        dolna(rcube, ccube, ccyl, ourShader, lightingShaderWithTexture, modelMatrix);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(5.0, 0, -12.0));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        model = identityMatrix * translateMatrix * rotateYMatrix;
        swing(bcube3, rcube, bcyl, ourShader, lightingShaderWithTexture, model);

        rotateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 1.7f, 0.0f)) *
            glm::rotate(identityMatrix, theta, glm::vec3(1.0f, 0.0, 0.0f)) *
            glm::translate(identityMatrix, glm::vec3(0.0f, -1.7f, 0.0f));
        modelMatrix = identityMatrix * translateMatrix * rotateYMatrix * rotateMatrix;
        dolna(rcube, ccube, ccyl, ourShader, lightingShaderWithTexture, modelMatrix);

        //Swimming pool
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-12.0f, -0.15f, -11.0));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(6.0f, 0.02f, 3.5f));
        model = identityMatrix * translateMatrix * scaleMatrix;
        pool_cube.drawCubeWithTexture(lightingShaderWithTexture, model);
        
        //Top floor front wall
        model = glm::mat4(1.0f);
        glm::mat4 translate = glm::mat4(1.0f);
        glm::mat4 translate2 = glm::mat4(1.0f);
        glm::mat4 scale = glm::mat4(1.0f);
        scale = glm::scale(model, glm::vec3(8.5f, 4.5f, 0.05f));
        translate = glm::translate(model, glm::vec3(-4.25f, 4.4f, -5.05f));
        model = identityMatrix * translate * scale;
        wbrcube.drawCubeWithTexture(lightingShaderWithTexture, model);

        //Sofa
        model = glm::mat4(1.0f);
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.5f, 1.5f, 1.5f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-0.5, 0.0, -2.0));
        drawSofa(cubeVAO, sofa_cube, lightingShaderWithTexture, lightingShader, model* rotateYMatrix* translateMatrix* scaleMatrix);

        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-3.0, 0.0, -3.5));
        drawSofa(cubeVAO, sofa_cube, lightingShaderWithTexture, lightingShader, model* rotateYMatrix* translateMatrix* scaleMatrix);

        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-1.0, 4.5, -3.5));
        drawSofa(cubeVAO, sofa_cube, lightingShaderWithTexture, lightingShader, model* rotateYMatrix* translateMatrix* scaleMatrix);

        model = glm::mat4(1.0f);
        translateMatrix = glm::translate(identityMatrix, glm::vec3(2.2, 0.0, 2.5));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.5f, 1.5f, 1.5f));
        bed(cubeVAO, bsheet, plo, bkt, lightingShader, lightingShaderWithTexture, model* rotateYMatrix* translateMatrix* scaleMatrix);

        model = glm::mat4(1.0f);
        translateMatrix = glm::translate(identityMatrix, glm::vec3(5.5, 0.0, -10.5));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(4.0f, 0.01f, 4.0f));
        grass.drawCylinderWithTexture(lightingShaderWithTexture, model * translateMatrix * scaleMatrix);

        model = glm::mat4(1.0f);
        path(center_path,border_path, lightingShaderWithTexture, model);

        sidewall(fwcube, lightingShaderWithTexture, identityMatrix);

        //sky.drawSphereWithTexture(lightingShaderWithTexture, identityMatrix);
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &cubeVAO);
    glDeleteVertexArrays(1, &lightCubeVAO);
    glDeleteBuffers(1, &cubeVBO);
    glDeleteBuffers(1, &cubeEBO);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

void drawCube(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 model = glm::mat4(1.0f), float r = 1.0f, float g = 1.0f, float b = 1.0f, float a = 1.0f)
{
    lightingShader.use();

    lightingShader.setVec3("material.ambient", glm::vec3(r, g, b));
    lightingShader.setVec3("material.diffuse", glm::vec3(r, g, b));
    lightingShader.setVec3("material.specular", glm::vec3(0.5f, 0.5f, 0.5f));
    lightingShader.setFloat("material.shininess", 32.0f);

    lightingShader.setMat4("model", model);

    glBindVertexArray(cubeVAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}

void bed(unsigned int& cubeVAO, Cube& cube1, Cube& cube2, Cube& cube3, Shader& lightingShader, Shader& lightingShaderWithTexture, glm::mat4 alTogether)
{

    float baseHeight = 0.3;
    float width = 1;
    float length = 2;
    float pillowWidth = 0.3;
    float pillowLength = 0.15;
    float blanketWidth = 0.8;
    float blanketLength = 0.7;
    float headHeight = 0.6;

    //base
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 translate = glm::mat4(1.0f);
    glm::mat4 translate2 = glm::mat4(1.0f);
    glm::mat4 scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(width, baseHeight, length));
    translate = glm::translate(model, glm::vec3(-0.5, 0, -0.5));
    model = alTogether * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 0.545, 0.271, 0.075, 1.0);

    //foam
    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    translate2 = glm::translate(model, glm::vec3(0, baseHeight, 0));
    scale = glm::scale(model, glm::vec3(width, 0.06, length));
    translate = glm::translate(model, glm::vec3(-0.5, 0, -0.5));
    model = alTogether * translate2 * scale * translate;
    //drawCube(cubeVAO, lightingShader, model, 0.804, 0.361, 0.361, 1.0);
    cube1.drawCubeWithTexture(lightingShaderWithTexture, model);

    //pillow 1
    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    translate2 = glm::translate(model, glm::vec3((width / 2) - (0.1 + pillowWidth / 2), baseHeight + 1 * 0.06, (length / 2) - (0.025 + pillowWidth / 2)));
    scale = glm::scale(model, glm::vec3(pillowWidth, 0.04, pillowLength));
    translate = glm::translate(model, glm::vec3(-0.5, 0, -0.5));
    model = alTogether * translate2 * scale * translate;
    //drawCube(cubeVAO, lightingShader, model, 1, 0.647, 0, 1.0);
    cube2.drawCubeWithTexture(lightingShaderWithTexture, model);

    //pillow 2
    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    translate2 = glm::translate(model, glm::vec3((-width / 2) + (0.1 + pillowWidth / 2), baseHeight + 1 * 0.06, (length / 2) - (0.025 + pillowWidth / 2)));
    scale = glm::scale(model, glm::vec3(pillowWidth, 0.04, pillowLength));
    translate = glm::translate(model, glm::vec3(-0.5, 0, -0.5));
    model = alTogether * translate2 * scale * translate;
    //drawCube(cubeVAO, lightingShader, model, 1, 0.647, 0, 1.0);
    cube2.drawCubeWithTexture(lightingShaderWithTexture, model);

    //blanket
    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    translate2 = glm::translate(model, glm::vec3(0, baseHeight + 1 * 0.06, -(length / 2 - 0.025) + blanketLength / 2));
    scale = glm::scale(model, glm::vec3(blanketWidth, 0.015, blanketLength));
    translate = glm::translate(model, glm::vec3(-0.5, 0, -0.5));
    model = alTogether * translate2 * scale * translate;
    //drawCube(cubeVAO, lightingShader, model, 0.541, 0.169, 0.886, 1.0);
    cube3.drawCubeWithTexture(lightingShaderWithTexture, model);

    //head
    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    translate2 = glm::translate(model, glm::vec3(0, 0, (length / 2 - 0.02 / 2) + 0.02));
    scale = glm::scale(model, glm::vec3(width, headHeight, 0.02));
    translate = glm::translate(model, glm::vec3(-0.5, 0, -0.5));
    model = alTogether * translate2 * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 0.545, 0.271, 0.075, 1.0);

}

//previous draw furniture...all functions.............................



void drawAlmirah(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether) {

    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 translate = glm::mat4(1.0f);
    glm::mat4 translate2 = glm::mat4(1.0f);
    glm::mat4 scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(0.85f, 1.8f, 0.6f));
    translate = glm::translate(model, glm::vec3(-0.5, 0.0, 3.8));
    model = alTogether * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 0.545, 0.271, 0.075, 1.0);

    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(0.41f, 1.8f, 0.03f));
    translate = glm::translate(model, glm::vec3(0.05, 0.0, 75.0));
    model = alTogether * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 0.245, 0.171, 0.175, 1.0);

    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(0.41f, 1.8f, 0.03f));
    translate = glm::translate(model, glm::vec3(-1.05, 0.0, 75.0));
    model = alTogether * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 0.245, 0.171, 0.175, 1.0);

    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(0.05f, 0.2f, 0.05f));
    translate = glm::translate(model, glm::vec3(0.8, 5.4, 44.5));
    model = alTogether * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 0.0245, 0.0171, 0.0175, 1.0);

    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(0.05f, 0.2f, 0.05f));
    translate = glm::translate(model, glm::vec3(-1.8, 5.4, 44.5));
    model = alTogether * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 0.0245, 0.0171, 0.0175, 1.0);

}


void drawTv(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether) {

    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 translate = glm::mat4(1.0f);
    glm::mat4 translate2 = glm::mat4(1.0f);
    glm::mat4 scale = glm::mat4(1.0f);
    glm::mat4 rotateZMatrix;
    scale = glm::scale(model, glm::vec3(3.5f, 1.0f, 0.6f));
    translate = glm::translate(model, glm::vec3(-0.5, 0.0, 3.8));
    model = alTogether * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 0.545, 0.271, 0.075, 1.0);

    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(0.9f, 0.9f, 0.03f));
    translate = glm::translate(model, glm::vec3(0.85, 0.05, 75.0));
    model = alTogether * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 0.245, 0.171, 0.175, 1.0);

    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(0.9f, 0.9f, 0.03f));
    translate = glm::translate(model, glm::vec3(-1.85, 0.05, 75.0));
    model = alTogether * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 0.245, 0.171, 0.175, 1.0);

    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(1.35f, 0.35f, 0.03f));
    translate = glm::translate(model, glm::vec3(-0.5, 0.15, 75.0));
    model = alTogether * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 0.245, 0.171, 0.175, 1.0);

    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(1.35f, 0.35f, 0.03f));
    translate = glm::translate(model, glm::vec3(-0.5, 1.6, 75.0));
    model = alTogether * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 0.245, 0.171, 0.175, 1.0);

    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(0.05f, 0.2f, 0.05f));
    translate = glm::translate(model, glm::vec3(-17.8, 2.0, 44.5));
    model = alTogether * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 0.0245, 0.0171, 0.0175, 1.0);

    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(0.05f, 0.2f, 0.05f));
    translate = glm::translate(model, glm::vec3(17.0, 2.0, 44.5));
    model = alTogether * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 0.0245, 0.0171, 0.0175, 1.0);

    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(3.0f, 1.85f, 0.10f));
    translate = glm::translate(model, glm::vec3(-0.5, 0.6, 25.0));
    model = alTogether * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 0.0, 0.0, 0.0, 1.0);

    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(0.05f, 0.2f, 0.05f));
    translate = glm::translate(model, glm::vec3(24.0, 1.0, 50.5));
    rotateZMatrix = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    model = alTogether *rotateZMatrix *  scale * translate;
    drawCube(cubeVAO, lightingShader, model, 0.749, 0.749, 0.745, 1.0);

    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(0.05f, 0.2f, 0.05f));
    translate = glm::translate(model, glm::vec3(25.0, -2.0, 50.5));
    rotateZMatrix = glm::rotate(model, glm::radians(-225.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    model = alTogether * rotateZMatrix * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 0.749, 0.749, 0.745, 1.0);
}

void drawWall(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether) {

    //Front
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 translate = glm::mat4(1.0f);
    glm::mat4 translate2 = glm::mat4(1.0f);
    glm::mat4 scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(8.5f, 4.5f, 0.05f));
    translate = glm::translate(model, glm::vec3(-0.5f, -0.01f, 70.0f));
    model = alTogether * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 0.765, 0.992, 1.000, 1.0);

    //Left
    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(0.05f, 4.5f, 8.5f));
    translate = glm::translate(model, glm::vec3(84.0f, -0.01f, -0.59f));
    model = alTogether * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 1.0, 0.922, 0.796, 0.1);

    //Right
    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(0.05f, 4.5f, 8.5f));
    translate = glm::translate(model, glm::vec3(-85.0f, -0.01f, -0.59f));
    model = alTogether * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 1.0, 0.922, 0.796, 1.0);


    //Ceiling

    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(8.5f, 0.05f, 8.5f));
    translate = glm::translate(model, glm::vec3(-0.5f, 88.0f, -0.59f));
    model = alTogether * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 0.71, 0.71, 0.71, 1.0);


    //Floor

    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(8.5f, 0.01f, 8.5f));
    translate = glm::translate(model, glm::vec3(-0.5f, -5.0f, -0.59f));
    model = alTogether * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 1.0, 1.0, 1.0, 1.0);


    for (int i = 0; i <= 16; i++) {
        for (int j = 0; j < 16; j++) {
            model = glm::mat4(1.0f);
            translate = glm::mat4(1.0f);
            translate2 = glm::mat4(1.0f);
            scale = glm::mat4(1.0f);
            scale = glm::scale(model, glm::vec3(0.479f, 0.013f, 0.5f));
            translate = glm::translate(model, glm::vec3((-8.9 + 1.05 * i), -4.0f, (-10.0 + 1.05 * j)));
            model = alTogether * scale * translate;
            drawCube(cubeVAO, lightingShader, model, 0.839, 0.725, 0.725, 1.0);
        }
    }
}

void drawTopFloorWall(unsigned int& cubeVAO, Cube& fwcube, Shader& lightingShader, Shader& lightingShaderWithTexture, glm::mat4 alTogether, bool dOpen) {

    //Front
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 translate = glm::mat4(1.0f);
    glm::mat4 translate2 = glm::mat4(1.0f);
    glm::mat4 scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(8.5f, 4.5f, 0.05f));
    translate = glm::translate(model, glm::vec3(-0.5f, -0.01f, 70.0f));
    model = alTogether * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 0.765, 0.992, 1.000, 1.0);

    //Left
    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(0.05f, 4.5f, 6.0f));
    translate = glm::translate(model, glm::vec3(84.0f, -0.01f, -0.835f));
    model = alTogether * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 1.0, 0.922, 0.796, 0.1);

    //Front
    /*model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(8.5f, 4.5f, 0.05f));
    translate = glm::translate(model, glm::vec3(-0.5f, -0.01f, -100.0f));
    model = alTogether * scale * translate;
    fwcube.drawCubeWithTexture(lightingShaderWithTexture, model);*/
    //drawCube(cubeVAO, lightingShader, model, 0.573, 0.902, 0.882, 0.1);

    //Left Door
    if(dOpen)
    {
        dv += 0.03;
        if (dv > 1.0) {
            dv = 1.0;
        }
    }
    if (!dOpen)
    {
        dv -= 0.03;
        if (dv < 0.0) {
            dv = 0.0;
        }
    }
    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(0.05f, 4.5f, 2.6f));
    translate = glm::translate(model, glm::vec3(84.0f, -0.01f, 0.35f-dv));
    model = alTogether * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 0.573, 0.902, 0.882, 0.1);

    //Right
    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(0.05f, 4.5f, 8.5f));
    translate = glm::translate(model, glm::vec3(-85.0f, -0.01f, -0.59f));
    model = alTogether * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 1.0, 0.922, 0.796, 1.0);


    //Ceiling

    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(8.5f, 0.05f, 8.5f));
    translate = glm::translate(model, glm::vec3(-0.5f, 88.0f, -0.59f));
    model = alTogether * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 0.71, 0.71, 0.71, 1.0);


    //Floor

    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(8.5f, 0.01f, 8.5f));
    translate = glm::translate(model, glm::vec3(-0.5f, -5.0f, -0.59f));
    model = alTogether * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 1.0, 1.0, 1.0, 1.0);


    for (int i = 0; i <= 16; i++) {
        for (int j = 0; j < 16; j++) {
            model = glm::mat4(1.0f);
            translate = glm::mat4(1.0f);
            translate2 = glm::mat4(1.0f);
            scale = glm::mat4(1.0f);
            scale = glm::scale(model, glm::vec3(0.479f, 0.013f, 0.5f));
            translate = glm::translate(model, glm::vec3((-8.9 + 1.05 * i), -4.0f, (-10.0 + 1.05 * j)));
            model = alTogether * scale * translate;
            drawCube(cubeVAO, lightingShader, model, 0.839, 0.725, 0.725, 1.0);
        }
    }
}


void drawShoeRack(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether)
{
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 translate = glm::mat4(1.0f);
    glm::mat4 translate2 = glm::mat4(1.0f);
    glm::mat4 scale = glm::mat4(1.0f);
    glm::mat4 rotate = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(1.5f, 1.0f, 0.05f));
    translate = glm::translate(model, glm::vec3(-0.5f, -0.01f, -60.0f));
    rotate = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    model = alTogether  * scale * translate ;
    drawCube(cubeVAO, lightingShader, model, 0.49, 0.18, 0.012, 1.0);

    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(0.7f, 0.95f, 0.05f));
    translate = glm::translate(model, glm::vec3(-1.0f, 0.025f, -54.99f));
    rotate = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    model = alTogether * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 0.05, 0.05, 0.05, 1.0);

    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(0.7f, 0.95f, 0.05f));
    translate = glm::translate(model, glm::vec3(0.07f, 0.025f, -54.99f));
    rotate = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    model = alTogether * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 0.05, 0.05, 0.05, 1.0);


    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(0.05f, 1.0f, 0.3f));
    translate = glm::translate(model, glm::vec3(-15.0f, -0.01f, -10.0f));
    model = alTogether * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 0.49, 0.18, 0.012, 1.0);

    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(0.05f, 1.0f, 0.3f));
    translate = glm::translate(model, glm::vec3(15.0f, -0.01f, -10.0f));
    model = alTogether * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 0.49, 0.18, 0.012, 1.0);


    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(1.5f, 1.0f, 0.05f));
    translate = glm::translate(model, glm::vec3(-0.5f, -0.01f, -55.0f));
    rotate = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    model = alTogether * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 0.49, 0.18, 0.012, 1.0);

    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(1.5f, 0.05f, 0.3f));
    translate = glm::translate(model, glm::vec3(-0.5f, 19.0f, -10.0f));
    rotate = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    model = alTogether * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 0.49, 0.18, 0.012, 1.0);

}


void drawSofa(unsigned int& cubeVAO, Cube& scube, Shader& lightingShaderWithTexture, Shader& lightingShader, glm::mat4 als)
{
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;


    //Sofa Seat
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.05, 0.1 + 0.15, 0.876));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.0f, .125f, 0.55f));
    model = als * translateMatrix * scaleMatrix;
    scube.drawCubeWithTexture(lightingShaderWithTexture, model);

    //Sofa Head
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.05, 0.1 + 0.5 * 0.2, 0.8));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.0f, .5f, 0.1f));
    model = als * translateMatrix * scaleMatrix;
    scube.drawCubeWithTexture(lightingShaderWithTexture, model);

    //frame
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.05 - 0.1, 0.1, 0.72));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.15f, .25f, 0.7f));
    model = als * translateMatrix * scaleMatrix;
    drawCube(cubeVAO, lightingShader, model, 0.05, 0.1f, 0.125f, 1.0);

    //Sofa leg1
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.05, 0.1 + 0.5 * 0.2, 0.8));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.025f, -0.23f, 0.05f));
    model = als * translateMatrix * scaleMatrix;
    drawCube(cubeVAO, lightingShader, model, 0.05, 0.1f, 0.125f, 1.0);

    //Sofa leg3
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.05, 0.1 + 0.5 * 0.2, 0.8 + 0.5 - 0.05));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.025f, -0.23f, 0.05f));
    model = als * translateMatrix * scaleMatrix;
    drawCube(cubeVAO, lightingShader, model, 0.05, 0.1f, 0.125f, 1.0);

    //Sofa leg2
    translateMatrix = glm::translate(identityMatrix, glm::vec3(1.05 - 0.25, 0.1 + 0.5 * 0.2, 0.8));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.025f, -0.23f, 0.05f));
    model = als * translateMatrix * scaleMatrix;
    drawCube(cubeVAO, lightingShader, model, 0.05, 0.1f, 0.125f, 1.0);

    //Sofa leg4
    translateMatrix = glm::translate(identityMatrix, glm::vec3(1.05 - 0.025, 0.1 + 0.5 * 0.2, 0.8 + 0.5 - 0.05));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.025f, -0.23f, 0.05f));
    model = als * translateMatrix * scaleMatrix;
    drawCube(cubeVAO, lightingShader, model, 0.05, 0.1f, 0.125f, 1.0);

    //handle1
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.05 - 0.1, 0.1, 0.72));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(.125f, .3f, 0.7f));
    model = als * translateMatrix * scaleMatrix;
    drawCube(cubeVAO, lightingShader, model, 0.05, 0.1f, 0.125f, 1.0);

    //handle2
    translateMatrix = glm::translate(identityMatrix, glm::vec3(1.1 + 0.025, 0.1, 0.72));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(-.125f, .3f, 0.7f));
    model = als * translateMatrix * scaleMatrix;
    drawCube(cubeVAO, lightingShader, model, 0.05, 0.1f, 0.125f, 1.0);

}


void drawTable(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether)
{

    float rotateAngle_Y = 0.0;


    glm::mat4 rotateY = glm::mat4(1.0f);
    glm::mat4 rotateZ = glm::mat4(1.0f);
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;

    //Round table
    for (float i = 0.0f; i < 360.0f; i += 1.0f) {

        translateMatrix = glm::translate(identityMatrix, glm::vec3(0.125, 0.6, 0.0));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Y + i), glm::vec3(0.0f, 1.0f, 0.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.5, 0.15, 0.5));
        model = alTogether * translateMatrix * rotateYMatrix * scaleMatrix;
        drawCube(cubeVAO, lightingShader, model, 1.0, 0.98, 0.98, 1.0); //this model is later sent to the vertex shader. //altogether is a matrix that is multiplied with every parts of the bed, so everything is part of Altogether. when rotated, everything is rotated AllTogether
        //glBindVertexArray(VAO);

    }

    //leg
    for (float i = 0.0f; i < 360.0f; i += 1.0f) {
        translateMatrix = glm::translate(identityMatrix, glm::vec3(0.125, 0.7, 0.0));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Y + i), glm::vec3(0.0f, 1.0f, 0.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.05, -0.70, 0.05));
        model = alTogether * translateMatrix * rotateYMatrix * scaleMatrix;
        drawCube(cubeVAO, lightingShader, model, 1.0, 1.0, 0.0, 1.0);
    }


    //Base
    for (float i = 0.0f; i < 360.0f; i += 1.0f) {
        translateMatrix = glm::translate(identityMatrix, glm::vec3(0.125, 0.7, 0.0));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Y + i), glm::vec3(0.0f, 1.0f, 0.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.15, -0.20, 0.15));
        model = alTogether * translateMatrix * rotateYMatrix * scaleMatrix;
        drawCube(cubeVAO, lightingShader, model, 1.0, 1.0, 0.0, 1.0);
    }

    for (float i = 0.0f; i < 360.0f; i += 1.0f) {
        translateMatrix = glm::translate(identityMatrix, glm::vec3(0.125, 0.05, 0.0));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Y + i), glm::vec3(0.0f, 1.0f, 0.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.15, -0.10, 0.15));
        model = alTogether * translateMatrix * rotateYMatrix * scaleMatrix;
        drawCube(cubeVAO, lightingShader, model, 0.1, 0.1, 0.1, 1.0);
    }

}


void drawSpotLight(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether)
{
    float rotateAngle_Y = 0.0;

    glm::mat4 rotateY = glm::mat4(1.0f);
    glm::mat4 rotateZ = glm::mat4(1.0f);
    float rotateAngle_Z = 0.0f;
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;

    //base
    for (float i = 0.0f; i < 360.0f; i += 2.50f) {
        //Center

        translateMatrix = glm::translate(identityMatrix, glm::vec3(-2.0f, 2.80f, -2.0f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Z + i), glm::vec3(-.2f, -1.0f, 1.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(-0.005, -0.05, 0.7));
        model = alTogether * translateMatrix * rotateYMatrix * scaleMatrix;
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(-3.5, 0.09, 0.9));
        model = model * scaleMatrix;
        drawCube(cubeVAO, lightingShader, model, 0.0, 0.5, 1.0, 1.0); //this model is later sent to the vertex shader. //altogether is a matrix that is multiplied with every parts of the bed, so everything is part of Altogether. when rotated, everything is rotated AllTogether
        //glBindVertexArray(VAO);
    }
    //body
    for (float i = 0.0f; i < 360.0f; i += 2.50f) {
        //Center

        translateMatrix = glm::translate(identityMatrix, glm::vec3(-2.0f, 2.80f, -2.15f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Z + i), glm::vec3(0.0f, 1.0f, 0.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(-0.055, -2.75, 0.005));
        model = alTogether * translateMatrix * rotateYMatrix * scaleMatrix;

        drawCube(cubeVAO, lightingShader, model, 0.9, 0.9, 0.9, 1.0); //this model is later sent to the vertex shader. //altogether is a matrix that is multiplied with every parts of the bed, so everything is part of Altogether. when rotated, everything is rotated AllTogether
        //glBindVertexArray(VAO);
    }
    //light
    translateMatrix = glm::translate(identityMatrix, glm::vec3(-2.05f, 2.65f, -2.0f ));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.09, 0.09, 0.09));
    model = alTogether * translateMatrix * scaleMatrix;
    drawCube(cubeVAO, lightingShader, model, 1.0, 1.0, 1.0, 1.0);

}


void door(Shader ourShader, glm::mat4 moveMatrix, glm::vec4 color)
{
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, scaleMatrix, model, rotateYMatrix;

    glBindTexture(GL_TEXTURE_2D, texture7);
    //Left Side
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
    translateMatrix = glm::translate(identityMatrix, glm::vec3(3.70f, -0.46f, 7.51f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(2.5f, 4.0f, 0.2f));
    model = translateMatrix * rotateYMatrix * scaleMatrix;
    ourShader.setMat4("model", moveMatrix * model);
    ourShader.setVec4("material.ambient", color);
    ourShader.setVec4("material.diffuse", color);
    ourShader.setVec4("material.specular", color * 0.5f);
    ourShader.setFloat("material.shininess", 32.0f);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    glBindTexture(GL_TEXTURE_2D, texture7);
    /*translateMatrix = glm::translate(identityMatrix, glm::vec3(7.1f, -0.42f, 7.5f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(2.5f, 3.2f, 0.2f));
    model = translateMatrix * scaleMatrix;*/
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(-angle + 180), glm::vec3(0.0f, 1.0f, 0.0f));
    translateMatrix = glm::translate(identityMatrix, glm::vec3(8.7f, -0.46f, 7.71f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(2.5f, 4.0f, 0.2f));
    model = translateMatrix * rotateYMatrix * scaleMatrix;
    ourShader.setMat4("model", moveMatrix * model);
    ourShader.setVec4("material.ambient", color);
    ourShader.setVec4("material.diffuse", color);
    ourShader.setVec4("material.specular", color * 0.5f);
    ourShader.setFloat("material.shininess", 32.0f);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}


// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        camera.ProcessKeyboard(FORWARD, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        camera.ProcessKeyboard(LEFT, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        camera.ProcessKeyboard(RIGHT, deltaTime);
    }

    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
    {
        if (rotateAxis_X) rotateAngle_X -= 0.1;
        else if (rotateAxis_Y) rotateAngle_Y -= 0.1;
        else rotateAngle_Z -= 0.1;
    }
    if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS) translate_Y += 0.001;
    if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS) translate_Y -= 0.001;
    if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) translate_X += 0.001;
    if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS) translate_X -= 0.001;
    if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS) translate_Z += 0.001;
    if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS) translate_Z -= 0.001;
    //if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS) scale_X += 0.001;
    //if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS) scale_X -= 0.001;
    if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS) scale_Y += 0.001;
    if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS) scale_Y -= 0.001;
    if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS) scale_Z += 0.001;
    //if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS) scale_Z -= 0.001;

    if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS)
    {
        rotateAngle_X += 0.1;
        rotateAxis_X = 1.0;
        rotateAxis_Y = 0.0;
        rotateAxis_Z = 0.0;
    }
    if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
    {
        rotateAngle_X -= 0.1;
        rotateAxis_X = 1.0;
        rotateAxis_Y = 0.0;
        rotateAxis_Z = 0.0;
    }
    if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS)
    {
        rotateAngle_Y += 0.1;
        rotateAxis_X = 0.0;
        rotateAxis_Y = 1.0;
        rotateAxis_Z = 0.0;
    }
    if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS)
    {
        rotateAngle_Y -= 0.1;
        rotateAxis_X = 0.0;
        rotateAxis_Y = 1.0;
        rotateAxis_Z = 0.0;
    }
    if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
    {
        rotateAngle_Z += 0.1;
        rotateAxis_X = 0.0;
        rotateAxis_Y = 0.0;
        rotateAxis_Z = 1.0;
    }
    if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
    {
        rotateAngle_Z -= 0.1;
        rotateAxis_X = 0.0;
        rotateAxis_Y = 0.0;
        rotateAxis_Z = 1.0;
    }

    if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS)
    {
        eyeX += 2.5 * deltaTime;
        basic_camera.changeEye(eyeX, eyeY, eyeZ);
    }
    if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
    {
        eyeX -= 2.5 * deltaTime;
        basic_camera.changeEye(eyeX, eyeY, eyeZ);
    }
    if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS)
    {
        eyeZ += 2.5 * deltaTime;
        basic_camera.changeEye(eyeX, eyeY, eyeZ);
    }
    if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS)
    {
        eyeZ -= 2.5 * deltaTime;
        basic_camera.changeEye(eyeX, eyeY, eyeZ);
    }
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
    {
        eyeY += 2.5 * deltaTime;
        basic_camera.changeEye(eyeX, eyeY, eyeZ);
    }
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
    {
        eyeY -= 2.5 * deltaTime;
        basic_camera.changeEye(eyeX, eyeY, eyeZ);
    }

}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_1 && action == GLFW_PRESS)
    {
        if (pointLight1On)
        {
            pointlight1.turnOff();
            pointlight2.turnOff();
            pointlight5.turnOff();
            pointLight1On = !pointLight1On;
        }
        else
        {
            pointlight1.turnOn();
            pointlight2.turnOn();
            pointlight5.turnOn();
            pointLight1On = !pointLight1On;
        }
    }

    if (key == GLFW_KEY_2 && action == GLFW_PRESS)
    {
        if (pointLight2On)
        {
            pointlight3.turnOff();
            pointlight4.turnOff();
            pointLight2On = !pointLight2On;
        }
        else
        {
            pointlight3.turnOn();
            pointlight4.turnOn();
            pointLight2On = !pointLight2On;
        }
    }

    if (key == GLFW_KEY_3 && action == GLFW_PRESS)
    {
        if (d_l_on)
        {
            d_l_on = false;
        }
        else
        {
            d_l_on = true;
        }
    }

    if (key == GLFW_KEY_4 && action == GLFW_PRESS)
    {
        if (s_l_on)
        {
            s_l_on = false;
        }
        else
        {
            s_l_on = true;
        }
    }

    if (key == GLFW_KEY_5 && action == GLFW_PRESS)
    {
        if(pointambientToggle)
        {
            pointlight1.turnAmbientOff();
            pointlight3.turnAmbientOff();
            //pointlight2.turnAmbientOff();
            pointambientToggle = !pointambientToggle;

        }
                
        else
        {
            pointlight1.turnAmbientOn();
            pointlight3.turnAmbientOn();
            //pointlight2.turnAmbientOn();
            pointambientToggle = !pointambientToggle;
        }
        
    }

    if (key == GLFW_KEY_6 && action == GLFW_PRESS)
    {
        if (pointdiffuseToggle)
        {
            pointlight1.turnDiffuseOff();
            //pointlight2.turnDiffuseOff();
            //d_d_on = false;
            //s_d_on = false;
            pointdiffuseToggle = !pointdiffuseToggle;
        }

        else
        {
            pointlight1.turnDiffuseOn();
            //pointlight2.turnDiffuseOn();
            //d_d_on = true;
            //s_d_on = true;
            pointdiffuseToggle = !pointdiffuseToggle;
        }

    }

    if (key == GLFW_KEY_7 && action == GLFW_PRESS)
    {
        if (pointspecularToggle)
        {
            pointlight1.turnSpecularOff();
            //pointlight2.turnSpecularOff();
            //d_s_on = false;
            //s_s_on = false;
            pointspecularToggle = !pointspecularToggle;
        }

        else
        {
            pointlight1.turnSpecularOn();
            //pointlight2.turnSpecularOn();
            //d_s_on = true;
            //s_s_on = true;
            pointspecularToggle = !pointspecularToggle;
        }

    }

    if (key == GLFW_KEY_J && action == GLFW_PRESS)
    {
        if (point2ambientToggle)
        {
            //pointlight1.turnAmbientOff();
            pointlight2.turnAmbientOff();
            point2ambientToggle = !point2ambientToggle;

        }

        else
        {
            //pointlight1.turnAmbientOn();
            pointlight2.turnAmbientOn();
            point2ambientToggle = !point2ambientToggle;
        }

    }

    if (key == GLFW_KEY_K && action == GLFW_PRESS)
    {
        if (point2diffuseToggle)
        {
            //pointlight1.turnDiffuseOff();
            pointlight2.turnDiffuseOff();
            //d_d_on = false;
            //s_d_on = false;
            point2diffuseToggle = !point2diffuseToggle;
        }

        else
        {
            //pointlight1.turnDiffuseOn();
            pointlight2.turnDiffuseOn();
            //d_d_on = true;
            //s_d_on = true;
            point2diffuseToggle = !point2diffuseToggle;
        }

    }

    if (key == GLFW_KEY_L && action == GLFW_PRESS)
    {
        if (point2specularToggle)
        {
            //pointlight1.turnSpecularOff();
            pointlight2.turnSpecularOff();
            //d_s_on = false;
            //s_s_on = false;
            point2specularToggle = !point2specularToggle;
        }

        else
        {
            //pointlight1.turnSpecularOn();
            pointlight2.turnSpecularOn();
            //d_s_on = true;
            //s_s_on = true;
            point2specularToggle = !point2specularToggle;
        }

    }

    if (key == GLFW_KEY_8 && action == GLFW_PRESS)
    {
        if (directionalambientToggle)
        {
            
            d_a_on = false;
            //s_s_on = false;
            directionalambientToggle = !directionalambientToggle;
        }

        else
        {
            //pointlight1.turnSpecularOn();
            //pointlight2.turnSpecularOn();
            d_a_on = true;
            //s_s_on = true;
            directionalambientToggle = !directionalambientToggle;
        }

    }

    if (key == GLFW_KEY_9 && action == GLFW_PRESS)
    {
        if (directionaldiffuseToggle)
        {
            //pointlight1.turnSpecularOff();
            //pointlight2.turnSpecularOff();
            d_d_on = false;
            //s_s_on = false;
            directionaldiffuseToggle = !directionaldiffuseToggle;
        }

        else
        {
            //pointlight1.turnSpecularOn();
            //pointlight2.turnSpecularOn();
            d_d_on = true;
            //s_s_on = true;
            directionaldiffuseToggle = !directionaldiffuseToggle;
        }

    }

    if (key == GLFW_KEY_0 && action == GLFW_PRESS)
    {
        if (directionalspecularToggle)
        {
            //pointlight1.turnSpecularOff();
            //pointlight2.turnSpecularOff();
            d_s_on = false;
            //s_s_on = false;
            directionalspecularToggle = !directionalspecularToggle;
        }

        else
        {
            //pointlight1.turnSpecularOn();
            //pointlight2.turnSpecularOn();
            d_s_on = true;
            //s_s_on = true;
            directionalspecularToggle = !directionalspecularToggle;
        }

    }

    if (key == GLFW_KEY_I && action == GLFW_PRESS)
    {
        if (spotambientToggle)
        {

            s_a_on = false;
            //s_s_on = false;
            spotambientToggle = !spotambientToggle;
        }

        else
        {
            //pointlight1.turnSpecularOn();
            //pointlight2.turnSpecularOn();
            s_a_on = true;
            //s_s_on = true;
            spotambientToggle = !spotambientToggle;
        }

    }

    if (key == GLFW_KEY_O && action == GLFW_PRESS)
    {
        if (spotdiffuseToggle)
        {
            //pointlight1.turnSpecularOff();
            //pointlight2.turnSpecularOff();
            s_d_on = false;
            //s_s_on = false;
            spotdiffuseToggle = !spotdiffuseToggle;
        }

        else
        {
            //pointlight1.turnSpecularOn();
            //pointlight2.turnSpecularOn();
            s_d_on = true;
            //s_s_on = true;
            spotdiffuseToggle = !spotdiffuseToggle;
        }

    }

    if (key == GLFW_KEY_P && action == GLFW_PRESS)
    {
        if (spotspecularToggle)
        {
            //pointlight1.turnSpecularOff();
            //pointlight2.turnSpecularOff();
            s_s_on = false;
            //s_s_on = false;
            spotspecularToggle = !spotspecularToggle;
        }

        else
        {
            //pointlight1.turnSpecularOn();
            //pointlight2.turnSpecularOn();
            s_s_on = true;
            //s_s_on = true;
            spotspecularToggle = !spotspecularToggle;
        }

    }

    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)                   //Door open-close
    {
        angle -= 1;
        angle = max(angle, -180);

    }
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)                   //Door open-close
    {
        angle += 1;
        angle = min(angle, 0);

    }


    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)                   //Door open-close
    {
        fanOn = !fanOn;
    }

    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS)                   //Door open-close
    {
        if (throttlerOn == 0.0)
        {
            throttlerOn = 1.0;
        }
        else
        {
            throttlerOn = 0.0;
        }
    }
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)                   //Boat accelerate
    {
        bx -= 0.05;
        throttlerOn = 1.0;
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)                   //Boat accelerate
    {
        bx += 0.05;
        throttlerOn = -1.0;
    }
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)                   //Boat accelerate
    {
        rot = !rot;
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)                   //Boat accelerate
    {
        rotinv = !rotinv;
    }

    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)                   //Door open-close
    {
        doorOpen = !doorOpen;
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


// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}

//unsigned int loadTexture1(char const* path, GLenum textureWrappingModeS, GLenum textureWrappingModeT, GLenum textureFilteringModeMin, GLenum textureFilteringModeMax)
//{
//    unsigned int textureID;
//    glGenTextures(1, &textureID);
//
//    int width, height, nrComponents;
//    stbi_set_flip_vertically_on_load(true);
//    unsigned char* data = stbi_load(path, &width, &height, &nrComponents, 0);
//    if (data)
//    {
//        GLenum format;
//        if (nrComponents == 1)
//            format = GL_RED;
//        else if (nrComponents == 3)
//            format = GL_RGB;
//        else if (nrComponents == 4)
//            format = GL_RGBA;
//
//        glBindTexture(GL_TEXTURE_2D, textureID);
//        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
//        glGenerateMipmap(GL_TEXTURE_2D);
//
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, textureWrappingModeS);
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, textureWrappingModeT);
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, textureFilteringModeMin);
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, textureFilteringModeMax);
//
//        stbi_image_free(data);
//    }
//    else
//    {
//        std::cout << "Texture failed to load at path: " << path << std::endl;
//        stbi_image_free(data);
//    }
//
//    return textureID;
//}
