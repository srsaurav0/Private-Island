#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "shader.h"
#include "cube.h"
#include "cylinder.h"

void dolna(Cube& cube, Cube& cube2, Cylinder& cyl, Shader& ourShader, Shader& lightingShader, glm::mat4 als) {

    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;
    //swing-seat
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.25, 0.75, 0.0));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.95f, .025f, 0.5f));
    model = als * translateMatrix * scaleMatrix;
    cube2.drawCubeWithTexture(lightingShader, model);

    //dori1
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.25, 0.95, 0.0));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.025f, .8f, 0.025f));
    model = als * translateMatrix * scaleMatrix;
    cube.drawCubeWithTexture(lightingShader, model);
    //dori2
    translateMatrix = glm::translate(identityMatrix, glm::vec3(1.2, 0.95, 0.0));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.025f, .8f, 0.025f));
    model = als * translateMatrix * scaleMatrix;
    cube.drawCubeWithTexture(lightingShader, model);

    //handle1
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.25, 0.95, 0.0));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.025f, .025f, 0.5f));
    model = als * translateMatrix * scaleMatrix;
    cube.drawCubeWithTexture(lightingShader, model);

    //handle12
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.25, 0.95, 0.5 - 0.025));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.025f, -.1750f, 0.025f));
    model = als * translateMatrix * scaleMatrix;
    cube.drawCubeWithTexture(lightingShader, model);

    //handle2
    translateMatrix = glm::translate(identityMatrix, glm::vec3(1.2, 0.95, 0.0));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.025f, .025f, 0.5f));
    model = als * translateMatrix * scaleMatrix;
    cube.drawCubeWithTexture(lightingShader, model);

    //handle22
    translateMatrix = glm::translate(identityMatrix, glm::vec3(1.2, 0.95, 0.5 - 0.025));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.025f, -.1750f, 0.025f));
    model = als * translateMatrix * scaleMatrix;
    cube.drawCubeWithTexture(lightingShader, model);

    //Sofa Head
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.25, 0.75 + 0.025 * 0.2, 0.0));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.95f, .5f, 0.05f));
    model = als * translateMatrix * scaleMatrix;
    cube2.drawCubeWithTexture(lightingShader, model);
}

void swing(Cube& cube, Cube& cube2, Cylinder& cyl, Shader& ourShader, Shader& lightingShader, glm::mat4 als)
{
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;

    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0, 1.75,0.0));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.5f, .05f, 0.05f));
    model = als * translateMatrix * scaleMatrix;
    cube.drawCubeWithTexture(lightingShader, model);

    //standleft
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0, 1.75, 0.0));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(.05f, -1.75f, 0.05f));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(30.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    model = als*translateMatrix * rotateYMatrix*scaleMatrix;
    cube.drawCubeWithTexture(lightingShader, model);

    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0, 1.75, 0.0));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(.05f, -1.75f, 0.05f));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(-30.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    model = als * translateMatrix * rotateYMatrix * scaleMatrix;
    cube.drawCubeWithTexture(lightingShader, model);

    //stand right
    translateMatrix = glm::translate(identityMatrix, glm::vec3(1.5-0.05, 1.75, 0.0));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(.05f, -1.75f, 0.05f));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(30.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    model = als * translateMatrix * rotateYMatrix * scaleMatrix;
    cube.drawCubeWithTexture(lightingShader, model);

    translateMatrix = glm::translate(identityMatrix, glm::vec3(1.5 - 0.05, 1.75, 0.0));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(.05f, -1.75f, 0.05f));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(-30.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    model = als * translateMatrix * rotateYMatrix * scaleMatrix;
    cube.drawCubeWithTexture(lightingShader, model);

 
}




#pragma once
