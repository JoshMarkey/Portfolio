#pragma once
#include <GLM/glm.hpp>
#include<cmath>
#include "MCG_GFX_Lib.h"
#include <vector>
#include <chrono>
#define _USE_MATH_DEFINES
#include <math.h>
class MatrixParent
{
protected:
	std::vector<glm::vec3> corners;
	glm::mat4x4 projectionMatrix;
	void drawLine(glm::vec2 p1, glm::vec2 p2, glm::vec3 colour);
	glm::vec3 multiplyMatrix(glm::vec3 inputVector, glm::mat4x4 multiplyMatrix);
	void drawTriangle(struct Triangle f, glm::vec3 colour);
public:
	MatrixParent();
};


struct Triangle
{
	glm::vec3 p1;
	glm::vec3 p2;
	glm::vec3 p3;
};
