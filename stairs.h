#define stairs_h

#include <glad/glad.h>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "shader.h"
#include "cube.h"
#include "cylinder.h"
#include "curve.h"


void stairs(Cube& cube, Shader& lightingShader, glm::mat4 als)
{
	glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
	glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;

	for (int i = 0; i < 9; i++)
	{
		translateMatrix = glm::translate(identityMatrix, glm::vec3(4.25, 0.0+.5*i, -3.0+.5*i));
		scaleMatrix = glm::scale(identityMatrix, glm::vec3(2.5f, 0.5f, 0.5f));
		rotateYMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = als * translateMatrix * rotateYMatrix * scaleMatrix;
		cube.drawCubeWithTexture(lightingShader, model);
	}
	translateMatrix = glm::translate(identityMatrix, glm::vec3(4.25, 4.0, 1.5));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(2.5f, 0.5f, 2.0f));
	rotateYMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model = als * translateMatrix * rotateYMatrix * scaleMatrix;
	cube.drawCubeWithTexture(lightingShader, model);
	
}


#pragma once
