#define tennis_h

#include <glad/glad.h>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "shader.h"
#include "cube.h"
#include "cylinder.h"
#include "curve.h"



void tennis(Cube& cube, Cylinder& cyl, Cube& cube2, Shader& lightingShader, glm::mat4 als) {
	glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
	glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;

	translateMatrix = glm::translate(identityMatrix, glm::vec3(-0.40f, -5.0f, -2.5));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(8.0f, 0.02f, 5.0f));
	rotateYMatrix = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model = identityMatrix * rotateYMatrix * scaleMatrix * translateMatrix;
	cube.drawCubeWithTexture(lightingShader, model);


	scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.05f, 1.0f, 0.05f));
	translateMatrix = glm::translate(identityMatrix, glm::vec3(-8.1f, 0.80f, -0.80f));
	model = identityMatrix * translateMatrix * scaleMatrix;
	cyl.drawCylinderWithTexture(lightingShader, model);

	scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.05f, 1.0f, 0.05f));
	translateMatrix = glm::translate(identityMatrix, glm::vec3(-11.91f, 0.80f, -0.80f));
	model = identityMatrix * translateMatrix * scaleMatrix;
	cyl.drawCylinderWithTexture(lightingShader, model);

	scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.02f, 0.15f, 0.02f));
	translateMatrix = glm::translate(identityMatrix, glm::vec3(-11.80f, 1.05f, -0.80f));
	rotateZMatrix = glm::rotate(identityMatrix, glm::radians(60.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	model = identityMatrix * translateMatrix * rotateZMatrix * scaleMatrix;
	cyl.drawCylinderWithTexture(lightingShader, model);

	scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.02f, 0.15f, 0.02f));
	translateMatrix = glm::translate(identityMatrix, glm::vec3(-11.80f, 0.3f, -0.80f));
	rotateZMatrix = glm::rotate(identityMatrix, glm::radians(120.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	model = identityMatrix * translateMatrix * rotateZMatrix * scaleMatrix;
	cyl.drawCylinderWithTexture(lightingShader, model);

	scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.02f, 0.15f, 0.02f));
	translateMatrix = glm::translate(identityMatrix, glm::vec3(-8.2f, 0.3f, -0.80f));
	rotateZMatrix = glm::rotate(identityMatrix, glm::radians(60.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	model = identityMatrix * translateMatrix * rotateZMatrix * scaleMatrix;
	cyl.drawCylinderWithTexture(lightingShader, model);

	scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.02f, 0.15f, 0.02f));
	translateMatrix = glm::translate(identityMatrix, glm::vec3(-8.2f, 1.05f, -0.80f));
	rotateZMatrix = glm::rotate(identityMatrix, glm::radians(120.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	model = identityMatrix * translateMatrix * rotateZMatrix * scaleMatrix;
	cyl.drawCylinderWithTexture(lightingShader, model);

	scaleMatrix = glm::scale(identityMatrix, glm::vec3(3.4f, 0.6f, 0.02f));
	translateMatrix = glm::translate(identityMatrix, glm::vec3(-11.7f, 0.37f, -0.80f));
	//rotateZMatrix = glm::rotate(identityMatrix, glm::radians(120.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	model = identityMatrix * translateMatrix * scaleMatrix ;
	cube2.drawCubeWithTexture(lightingShader, model);
}



#pragma once
