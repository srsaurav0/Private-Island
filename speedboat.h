#define speedboat_h

#include <glad/glad.h>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "shader.h"
#include "cube.h"
#include "cylinder.h"
#include "curve.h"
#include "halfcurve.h"

float ang = 0.0;
float tang = 0.0;

void speedboat(HalfCurve& body, HalfCurve& back, Cube& cube, Curve& throttler, Cylinder& bcyl, Shader& lightingShader, glm::mat4 als, float bx, float by, bool rot, bool rotinv, float tOn) {
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model, tm2;

    if (!rot and !rotinv)
    {
        if(tOn>0)
        {
            tang += 30;
        }
        else if(tOn<0)
        {
            tang -= 30;
        }
        tm2 = glm::translate(identityMatrix, glm::vec3(0.0f, bx, 0.0f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(90.0f+ang), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrix = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.0f, 2.5f, 1.0f));
        model = als  * rotateYMatrix * rotateZMatrix * scaleMatrix * tm2;
        body.draw(lightingShader, model, glm::vec3(1.0f, 0.0f, 0.0f));

        tm2 = glm::translate(identityMatrix, glm::vec3(0.0f, 125.23 * bx, 0.0f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(90.0f+ang), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrix = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.81f, 0.02f, 0.81f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-5.23f, 0.0f, 0.0));
        model = als * rotateYMatrix * translateMatrix * rotateZMatrix * scaleMatrix * tm2;
        back.draw(lightingShader, model, glm::vec3(1.0f, 0.0f, 0.0f));

        //Throttler
        tm2 = glm::translate(identityMatrix, glm::vec3(0.0f, 50.23 * bx, 0.0f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(90.0f + ang), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrix = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.2f, 0.05f, 0.2f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-5.3f, -1.0f, 0.0));
        model = als * rotateYMatrix * translateMatrix * rotateZMatrix * scaleMatrix * tm2;
        bcyl.drawCylinderWithTexture(lightingShader, model);

        //Blade 1
        tm2 = glm::translate(identityMatrix, glm::vec3(-bx * 2.5, 0.0f, 0.0f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(90.0f + ang), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateXMatrix = glm::rotate(identityMatrix, glm::radians(0.0f + tang), glm::vec3(1.0f, 0.0f, 0.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.02f, 0.4f, 0.20f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-5.30f, -1.0f, 0.0));
        model = als * rotateYMatrix * translateMatrix * tm2 * rotateXMatrix * scaleMatrix ;
        throttler.draw(lightingShader, model, glm::vec3(1.0f, 0.0f, 0.0f));

        //Blade 2
        tm2 = glm::translate(identityMatrix, glm::vec3(-bx * 2.5, 0.0f, 0.0f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(90.0f + ang), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateXMatrix = glm::rotate(identityMatrix, glm::radians(120.0f + tang), glm::vec3(1.0f, 0.0f, 0.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.02f, 0.4f, 0.20f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-5.30f, -1.0f, 0.0));
        model = als * rotateYMatrix * translateMatrix * tm2 * rotateXMatrix * scaleMatrix;
        throttler.draw(lightingShader, model, glm::vec3(1.0f, 0.0f, 0.0f));

        //Blade 3
        tm2 = glm::translate(identityMatrix, glm::vec3(-bx * 2.5, 0.0f, 0.0f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(90.0f + ang), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateXMatrix = glm::rotate(identityMatrix, glm::radians(240.0f + tang), glm::vec3(1.0f, 0.0f, 0.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.02f, 0.4f, 0.20f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-5.30f, -1.0f, 0.0));
        model = als * rotateYMatrix * translateMatrix * tm2 * rotateXMatrix * scaleMatrix;
        throttler.draw(lightingShader, model, glm::vec3(1.0f, 0.0f, 0.0f));
    }
    else if (rot)
    {
        ang += 2.5;
        tang += 2.5;
        tm2 = glm::translate(identityMatrix, glm::vec3(0.0f, bx, 0.0f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(90.0f+ang), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrix = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.0f, 2.5f, 1.0f));
        model = als * rotateYMatrix * rotateZMatrix * scaleMatrix * tm2;
        body.draw(lightingShader, model, glm::vec3(1.0f, 0.0f, 0.0f));

        tm2 = glm::translate(identityMatrix, glm::vec3(0.0f, 125.23 * bx, 0.0f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(90.0f+ang), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrix = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.81f, 0.02f, 0.81f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-5.23f, 0.0f, 0.0));
        model = als * rotateYMatrix * translateMatrix * rotateZMatrix * scaleMatrix * tm2;
        back.draw(lightingShader, model, glm::vec3(1.0f, 0.0f, 0.0f));

        //Throttler
        tm2 = glm::translate(identityMatrix, glm::vec3(0.0f, 50.23 * bx, 0.0f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(90.0f + ang), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrix = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.2f, 0.05f, 0.2f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-5.3f, -1.0f, 0.0));
        model = als * rotateYMatrix * translateMatrix * rotateZMatrix * scaleMatrix * tm2;
        bcyl.drawCylinderWithTexture(lightingShader, model);

        //Blade 1
        tm2 = glm::translate(identityMatrix, glm::vec3(-bx * 2.5, 0.0f, 0.0f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(90.0f + ang), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateXMatrix = glm::rotate(identityMatrix, glm::radians(0.0f + tang), glm::vec3(1.0f, 0.0f, 0.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.02f, 0.4f, 0.20f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-5.30f, -1.0f, 0.0));
        model = als * rotateYMatrix * translateMatrix * tm2 * rotateXMatrix * scaleMatrix;
        throttler.draw(lightingShader, model, glm::vec3(1.0f, 0.0f, 0.0f));

        //Blade 2
        tm2 = glm::translate(identityMatrix, glm::vec3(-bx * 2.5, 0.0f, 0.0f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(90.0f + ang), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateXMatrix = glm::rotate(identityMatrix, glm::radians(120.0f + tang), glm::vec3(1.0f, 0.0f, 0.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.02f, 0.4f, 0.20f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-5.30f, -1.0f, 0.0));
        model = als * rotateYMatrix * translateMatrix * tm2 * rotateXMatrix * scaleMatrix;
        throttler.draw(lightingShader, model, glm::vec3(1.0f, 0.0f, 0.0f));

        //Blade 3
        tm2 = glm::translate(identityMatrix, glm::vec3(-bx * 2.5, 0.0f, 0.0f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(90.0f + ang), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateXMatrix = glm::rotate(identityMatrix, glm::radians(240.0f + tang), glm::vec3(1.0f, 0.0f, 0.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.02f, 0.4f, 0.20f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-5.30f, -1.0f, 0.0));
        model = als * rotateYMatrix * translateMatrix * tm2 * rotateXMatrix * scaleMatrix;
        throttler.draw(lightingShader, model, glm::vec3(1.0f, 0.0f, 0.0f));
    }
    else if (rotinv)
    {
        ang -= 2.5;
        tang -= 2.5;
        tm2 = glm::translate(identityMatrix, glm::vec3(0.0f, bx, 0.0f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(90.0f + ang), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrix = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.0f, 2.5f, 1.0f));
        model = als * rotateYMatrix * rotateZMatrix * scaleMatrix * tm2;
        body.draw(lightingShader, model, glm::vec3(1.0f, 0.0f, 0.0f));

        tm2 = glm::translate(identityMatrix, glm::vec3(0.0f, 125.23 * bx, 0.0f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(90.0f + ang), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrix = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.81f, 0.02f, 0.81f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-5.23f, 0.0f, 0.0));
        model = als * rotateYMatrix * translateMatrix * rotateZMatrix * scaleMatrix * tm2;
        back.draw(lightingShader, model, glm::vec3(1.0f, 0.0f, 0.0f));

        //Throttler
        tm2 = glm::translate(identityMatrix, glm::vec3(0.0f, 50.23 * bx, 0.0f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(90.0f + ang), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrix = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.2f, 0.05f, 0.2f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-5.3f, -1.0f, 0.0));
        model = als * rotateYMatrix * translateMatrix * rotateZMatrix * scaleMatrix * tm2;
        bcyl.drawCylinderWithTexture(lightingShader, model);

        //Blade 1
        tm2 = glm::translate(identityMatrix, glm::vec3(-bx * 2.5, 0.0f, 0.0f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(90.0f + ang), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateXMatrix = glm::rotate(identityMatrix, glm::radians(0.0f + tang), glm::vec3(1.0f, 0.0f, 0.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.02f, 0.4f, 0.20f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-5.30f, -1.0f, 0.0));
        model = als * rotateYMatrix * translateMatrix * tm2 * rotateXMatrix * scaleMatrix;
        throttler.draw(lightingShader, model, glm::vec3(1.0f, 0.0f, 0.0f));

        //Blade 2
        tm2 = glm::translate(identityMatrix, glm::vec3(-bx * 2.5, 0.0f, 0.0f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(90.0f + ang), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateXMatrix = glm::rotate(identityMatrix, glm::radians(120.0f + tang), glm::vec3(1.0f, 0.0f, 0.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.02f, 0.4f, 0.20f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-5.30f, -1.0f, 0.0));
        model = als * rotateYMatrix * translateMatrix * tm2 * rotateXMatrix * scaleMatrix;
        throttler.draw(lightingShader, model, glm::vec3(1.0f, 0.0f, 0.0f));

        //Blade 3
        tm2 = glm::translate(identityMatrix, glm::vec3(-bx * 2.5, 0.0f, 0.0f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(90.0f + ang), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateXMatrix = glm::rotate(identityMatrix, glm::radians(240.0f + tang), glm::vec3(1.0f, 0.0f, 0.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.02f, 0.4f, 0.20f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-5.30f, -1.0f, 0.0));
        model = als * rotateYMatrix * translateMatrix * tm2 * rotateXMatrix * scaleMatrix;
        throttler.draw(lightingShader, model, glm::vec3(1.0f, 0.0f, 0.0f));
    }
}



#pragma once
