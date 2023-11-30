#define sidewall_h

#include <glad/glad.h>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "shader.h"
#include "cube.h"
#include "cylinder.h"
#include "curve.h"

void sidewall(Cube& cube, Shader& lightingShader, glm::mat4 als)
{
	glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
	glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;

	//Left portion
	translateMatrix = glm::translate(identityMatrix, glm::vec3(2.0, 0.0, -15.0));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(11.0f, 1.0f, 0.02f));
	rotateYMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	model = als * translateMatrix * scaleMatrix * rotateYMatrix;
	cube.drawCubeWithTexture(lightingShader, model);

	translateMatrix = glm::translate(identityMatrix, glm::vec3(2.0, 0.0, -15.25));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.5f, 1.3f, 0.5f));
	rotateYMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	model = als * translateMatrix * scaleMatrix * rotateYMatrix;
	cube.drawCubeWithTexture(lightingShader, model);

	translateMatrix = glm::translate(identityMatrix, glm::vec3(13.0, 0.0, -15.25));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.5f, 1.3f, 0.5f));
	rotateYMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	model = als * translateMatrix * scaleMatrix * rotateYMatrix;
	cube.drawCubeWithTexture(lightingShader, model);

	translateMatrix = glm::translate(identityMatrix, glm::vec3(-15.0, 0.0, -13.25));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(25.0f, 1.0f, 0.02f));
	rotateYMatrix = glm::rotate(identityMatrix, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model = als * rotateYMatrix * translateMatrix * scaleMatrix;
	cube.drawCubeWithTexture(lightingShader, model);

	translateMatrix = glm::translate(identityMatrix, glm::vec3(13.0, 0.0, 10.0));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.5f, 1.3f, 0.5f));
	rotateYMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	model = als * translateMatrix * scaleMatrix * rotateYMatrix;
	cube.drawCubeWithTexture(lightingShader, model);

	//Right portion
	translateMatrix = glm::translate(identityMatrix, glm::vec3(-2.0, 0.0, -15.0));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(11.0f, 1.0f, 0.02f));
	rotateYMatrix = glm::rotate(identityMatrix, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model = als * translateMatrix * scaleMatrix * rotateYMatrix;
	cube.drawCubeWithTexture(lightingShader, model);

	translateMatrix = glm::translate(identityMatrix, glm::vec3(-2.0, 0.0, -15.25));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.5f, 1.3f, 0.5f));
	rotateYMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	model = als * translateMatrix * scaleMatrix * rotateYMatrix;
	cube.drawCubeWithTexture(lightingShader, model);

	translateMatrix = glm::translate(identityMatrix, glm::vec3(-13.0, 0.0, -15.25));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.5f, 1.3f, 0.5f));
	rotateYMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model = als * translateMatrix * scaleMatrix * rotateYMatrix;
	cube.drawCubeWithTexture(lightingShader, model);

	translateMatrix = glm::translate(identityMatrix, glm::vec3(-10.0, 0.0, -12.75));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(25.0f, 1.0f, 0.02f));
	rotateYMatrix = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model = als * rotateYMatrix * translateMatrix * scaleMatrix;
	cube.drawCubeWithTexture(lightingShader, model);

	translateMatrix = glm::translate(identityMatrix, glm::vec3(-13.0, 0.0, 10.0));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.5f, 1.3f, 0.5f));
	rotateYMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model = als * translateMatrix * scaleMatrix * rotateYMatrix;
	cube.drawCubeWithTexture(lightingShader, model);

	//Center behind
	translateMatrix = glm::translate(identityMatrix, glm::vec3(-13.0, 0.0, 10.25));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(26.0f, 1.0f, 0.02f));
	rotateYMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	model = als * translateMatrix * scaleMatrix * rotateYMatrix;
	cube.drawCubeWithTexture(lightingShader, model);
}




#pragma once
