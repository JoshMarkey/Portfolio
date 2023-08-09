#pragma once
#include "MatrixParent.h"
class MatrixCube : MatrixParent
{
public:
	void drawCube(glm::vec3 colour, float rotation);
	MatrixCube(glm::vec3 p1,
		glm::vec3 p2,
		glm::vec3 p3,
		glm::vec3 p4,
		glm::vec3 p5,
		glm::vec3 p6,
		glm::vec3 p7,
		glm::vec3 p8);	
};



