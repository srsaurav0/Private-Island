#define path_h

#include <glad/glad.h>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "shader.h"
#include "cube.h"
#include "cylinder.h"
#include "curve.h"



void path(Cube& cube, Cube& cube2, Shader& lightingShader, glm::mat4 als) {
	glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
	glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;

	for (int i = 0; i < 9; i++)
	{
		translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0, 0.0, -6.0-i*1-i*0.02));
		scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.0f, 0.01f, 1.0f));
		rotateYMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = als * translateMatrix * scaleMatrix * rotateYMatrix;
		cube.drawCubeWithTexture(lightingShader, model);
	}
	for (int i = 0; i < 9; i++)
	{
		translateMatrix = glm::translate(identityMatrix, glm::vec3(-1.02, 0.0, -6.0 - i * 1 - i * 0.02));
		scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.0f, 0.01f, 1.0f));
		rotateYMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = als * translateMatrix * scaleMatrix * rotateYMatrix;
		cube.drawCubeWithTexture(lightingShader, model);
	}
	for (int i = 0; i < 9; i++)
	{
		translateMatrix = glm::translate(identityMatrix, glm::vec3(1.02, 0.0, -6.0 - i * 1 - i * 0.02));
		scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.15f, 0.01f, 1.0f));
		rotateYMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = als * translateMatrix * scaleMatrix * rotateYMatrix;
		cube2.drawCubeWithTexture(lightingShader, model);
	}
	for (int i = 0; i < 9; i++)
	{
		translateMatrix = glm::translate(identityMatrix, glm::vec3(-1.20, 0.0, -6.0 - i * 1 - i * 0.02));
		scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.15f, 0.01f, 1.0f));
		rotateYMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = als * translateMatrix * scaleMatrix * rotateYMatrix;
		cube2.drawCubeWithTexture(lightingShader, model);
	}
	//translateMatrix = glm::translate(identityMatrix, glm::vec3(1.02, 0.0, -6.0));
	//scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.15f, 0.01f, 1.0f));
	//rotateYMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	//model = als * translateMatrix * scaleMatrix * rotateYMatrix;
	//cube2.drawCubeWithTexture(lightingShader, model);
}

#pragma once
