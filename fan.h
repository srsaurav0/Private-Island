#define fan_h

#include <glad/glad.h>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "shader.h"
#include "cube.h"
#include "cylinder.h"
#include "curve.h"

float i = 0.0;

void fan(Cube& cube, Cube& cube2, Shader& lightingShader, glm::mat4 als, bool fanOn)
{
	glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
	glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;

	//Base
	translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0, 3.85, 0.0));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.25f, 0.20f, 0.25f));
	rotateYMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	model = als * translateMatrix * rotateYMatrix * scaleMatrix;
	for (int i = 0; i < 360; i++)
	{
		cube.drawCubeWithTexture(lightingShader, model * glm::rotate(identityMatrix, glm::radians(i*1.0f), glm::vec3(0.0f, 1.0f, 0.0f)));
	}

	translateMatrix = glm::translate(identityMatrix, glm::vec3(-0.02, 3.85, -0.03));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.07f, 0.6f, 0.07f));
	rotateYMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	model = als * translateMatrix * rotateYMatrix * scaleMatrix;
	cube2.drawCubeWithTexture(lightingShader, model);
	
	if(!fanOn)
	{
		//Plate 1
		translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0, 3.90, -0.075));
		scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.3f, 0.10f, 0.20f));
		rotateYMatrix = glm::rotate(identityMatrix, glm::radians(0.0f+i), glm::vec3(0.0f, 1.0f, 0.0f));
		model = als * translateMatrix * rotateYMatrix * scaleMatrix;
		cube2.drawCubeWithTexture(lightingShader, model );

		//Plate 2
		translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0, 3.90, -0.075));
		scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.3f, 0.10f, 0.20f));
		rotateYMatrix = glm::rotate(identityMatrix, glm::radians(120.0f+i), glm::vec3(0.0f, 1.0f, 0.0f));
		model = als * translateMatrix * rotateYMatrix * scaleMatrix;
		cube2.drawCubeWithTexture(lightingShader, model);

		//Plate 3
		translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0, 3.90, -0.075));
		scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.3f, 0.10f, 0.20f));
		rotateYMatrix = glm::rotate(identityMatrix, glm::radians(240.0f+i), glm::vec3(0.0f, 1.0f, 0.0f));
		model = als * translateMatrix * rotateYMatrix * scaleMatrix;
		cube2.drawCubeWithTexture(lightingShader, model);
	}

	else
	{
		i = i + 10.0;
		if (i > 360.0) {
			i = 0.0;
		}
		
		//Plate 1
		translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0, 3.90, -0.075));
		scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.3f, 0.10f, 0.20f));
		rotateYMatrix = glm::rotate(identityMatrix, glm::radians(0.0f+i), glm::vec3(0.0f, 1.0f, 0.0f));
		model = als * translateMatrix * rotateYMatrix * scaleMatrix;
		cube2.drawCubeWithTexture(lightingShader, model);

		//Plate 2
		translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0, 3.90, -0.075));
		scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.3f, 0.10f, 0.20f));
		rotateYMatrix = glm::rotate(identityMatrix, glm::radians(120.0f+i), glm::vec3(0.0f, 1.0f, 0.0f));
		model = als * translateMatrix * rotateYMatrix * scaleMatrix;
		cube2.drawCubeWithTexture(lightingShader, model);

		//Plate 3
		translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0, 3.90, -0.075));
		scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.3f, 0.10f, 0.20f));
		rotateYMatrix = glm::rotate(identityMatrix, glm::radians(240.0f+i), glm::vec3(0.0f, 1.0f, 0.0f));
		model = als * translateMatrix * rotateYMatrix * scaleMatrix;
		cube2.drawCubeWithTexture(lightingShader, model);
		
	}
}


#pragma once
