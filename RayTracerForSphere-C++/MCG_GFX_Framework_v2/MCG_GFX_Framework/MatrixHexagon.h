#pragma once
#include "MatrixParent.h"
class MatrixHexagon : MatrixParent
{
public:
	void drawHexagon(glm::vec3 colour, float rotation);
	MatrixHexagon(
		glm::vec3 point1,
		glm::vec3 point2,
		glm::vec3 point3,
		glm::vec3 point4,
		glm::vec3 point5,
		glm::vec3 point6,
		glm::vec3 point7,
		glm::vec3 point8,
		glm::vec3 point9,
		glm::vec3 point10);

	glm::vec3 p1;
	glm::vec3 p2;
	glm::vec3 p3;
	glm::vec3 p4;
	glm::vec3 p5;
	glm::vec3 p6;
	glm::vec3 p7;
	glm::vec3 p8;
	glm::vec3 p9;
	glm::vec3 p10;
	//glm::vec3 p5;
};

