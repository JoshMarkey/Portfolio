#include "MatrixHexagon.h"

void MatrixHexagon::drawHexagon(glm::vec3 colour, float rotation)
{
	glm::mat4x4 rotationx = glm::mat4x4(glm::vec4(1.0f, 0.0f, 0.0f, 0.0f), glm::vec4(0.0f, std::cosf(rotation * 0.5f), -(std::sinf(rotation * 0.5f)), 0.0f),
		glm::vec4(0.0f, std::sinf(rotation * 0.5f), std::cos(rotation * 0.5f), 0.0f), glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));

	glm::mat4x4 rotationz = glm::mat4x4(glm::vec4(std::cosf(rotation), -(std::sinf(rotation)), 0.0f, 0.0f), glm::vec4(std::sinf(rotation), std::cosf(rotation), 0.0f, 0.0f),
		glm::vec4(0.0f, 0.0f, 1.0f, 0.0f), glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));

	glm::mat4x4 rotationy = glm::mat4x4(glm::vec4(std::cosf(rotation * 0.5f), 0.0f, std::sinf(rotation * 0.5f), 0.0f),
			glm::vec4(0.0f, 1.0f, 0.0f, 0.0f),
			glm::vec4(-std::sinf(rotation * 0.5f), 0.0f, std::cosf(rotation * 0.5f), 0.0f),
			glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
	//creating vector of faces. this way i am able to edit the poinits temporarily
	//so that i can use them again next frame
	std::vector<Triangle> projectedShape;
	Triangle t;
	t.p1 = corners[5];
	t.p2 = corners[9];
	t.p3 = corners[8];
	projectedShape.push_back(t);
	t.p1 = corners[5];
	t.p2 = corners[8];
	t.p3 = corners[6];
	projectedShape.push_back(t);
	t.p1 = corners[6];
	t.p2 = corners[8];
	t.p3 = corners[7];
	projectedShape.push_back(t);
	t.p1 = corners[3];
	t.p2 = corners[4];
	t.p3 = corners[0];
	projectedShape.push_back(t);
	t.p1 = corners[3];
	t.p2 = corners[0];
	t.p3 = corners[1];
	projectedShape.push_back(t); 
	t.p1 = corners[3];
	t.p2 = corners[1];
	t.p3 = corners[2];
	projectedShape.push_back(t);

	t.p1 = corners[0];
	t.p2 = corners[5];
	t.p3 = corners[6];
	projectedShape.push_back(t);
	t.p1 = corners[0];
	t.p2 = corners[6];
	t.p3 = corners[1];
	projectedShape.push_back(t);
	t.p1 = corners[1];
	t.p2 = corners[6];
	t.p3 = corners[7];
	projectedShape.push_back(t);
	t.p1 = corners[1];
	t.p2 = corners[7];
	t.p3 = corners[2];
	projectedShape.push_back(t);
	t.p1 = corners[2];
	t.p2 = corners[7];
	t.p3 = corners[8];
	projectedShape.push_back(t);
	t.p1 = corners[2];
	t.p2 = corners[8];
	t.p3 = corners[3];
	projectedShape.push_back(t);
	t.p1 = corners[3];
	t.p2 = corners[8];
	t.p3 = corners[9];
	projectedShape.push_back(t);
	t.p1 = corners[3];
	t.p2 = corners[9];
	t.p3 = corners[4];
	projectedShape.push_back(t);
	t.p1 = corners[4];
	t.p2 = corners[9];
	t.p3 = corners[5];
	projectedShape.push_back(t);
	t.p1 = corners[4];
	t.p2 = corners[5];
	t.p3 = corners[0];
	projectedShape.push_back(t);

	for (int i = 0; i < projectedShape.size(); i++)
	{
		//multiply by rotation matrix
		projectedShape[i].p1 = multiplyMatrix(projectedShape[i].p1, rotationz);
		projectedShape[i].p2 = multiplyMatrix(projectedShape[i].p2, rotationz);
		projectedShape[i].p3 = multiplyMatrix(projectedShape[i].p3, rotationz);

		projectedShape[i].p1 = multiplyMatrix(projectedShape[i].p1, rotationx);
		projectedShape[i].p2 = multiplyMatrix(projectedShape[i].p2, rotationx);
		projectedShape[i].p3 = multiplyMatrix(projectedShape[i].p3, rotationx);

		projectedShape[i].p1 = multiplyMatrix(projectedShape[i].p1, rotationy);
		projectedShape[i].p2 = multiplyMatrix(projectedShape[i].p2, rotationy);
		projectedShape[i].p3 = multiplyMatrix(projectedShape[i].p3, rotationy);
		
		//translating by 3 in the z to move it onto the screen
		projectedShape[i].p1.z += 3.0f;
		projectedShape[i].p2.z += 3.0f;
		projectedShape[i].p3.z += 3.0f;

		glm::vec3 normal;
		glm::vec3 line1;
		glm::vec3 line2;
		//find 2 lines
		line1.x = projectedShape[i].p2.x - projectedShape[i].p1.x;
		line1.y = projectedShape[i].p2.y - projectedShape[i].p1.y;
		line1.z = projectedShape[i].p2.z - projectedShape[i].p1.z;

		line2.x = projectedShape[i].p3.x - projectedShape[i].p1.x;
		line2.y = projectedShape[i].p3.y - projectedShape[i].p1.y;
		line2.z = projectedShape[i].p3.z - projectedShape[i].p1.z;
		//find normal from the 2 lines
		normal.x = (line1.y * line2.z) - (line1.z * line2.y);
		normal.y = (line1.z * line2.x) - (line1.x * line2.z);
		normal.z = (line1.x * line2.y) - (line1.y * line2.x);
		//normalise the normal
		float length = std::sqrtf(normal.x * normal.x + normal.y * normal.y + normal.z * normal.z);
		normal.x /= length; normal.y /= length; normal.z /= length;

		float dotProduct = normal.x * (projectedShape[i].p1.x) +
						   normal.y * (projectedShape[i].p1.y) +
						   normal.z * (projectedShape[i].p1.z);
		//if the dot product of normal is a negative it means the face is pointing towards the camera
		if (dotProduct < 0.0f)
		{
		//multiply by projection matrix to make it 2d
		projectedShape[i].p1 = multiplyMatrix(projectedShape[i].p1, projectionMatrix);
		projectedShape[i].p2 = multiplyMatrix(projectedShape[i].p2, projectionMatrix);
		projectedShape[i].p3 = multiplyMatrix(projectedShape[i].p3, projectionMatrix);
		//scale into screen view
		projectedShape[i].p1.x += 1.0f;
		projectedShape[i].p2.x += 1.0f;
		projectedShape[i].p3.x += 1.0f;

		projectedShape[i].p1.y += 1.0f;
		projectedShape[i].p2.y += 1.0f;
		projectedShape[i].p3.y += 1.0f;

		projectedShape[i].p1.x *= 0.5f * 640.0f;
		projectedShape[i].p2.x *= 0.5f * 640.0f;
		projectedShape[i].p3.x *= 0.5f * 640.0f;

		projectedShape[i].p1.y *= 0.5f * 480.0f;
		projectedShape[i].p2.y *= 0.5f * 480.0f;
		projectedShape[i].p3.y *= 0.5f * 480.0f;
		//draw triangle
		
		drawTriangle(projectedShape[i], colour);
		}	
	}
}




MatrixHexagon::MatrixHexagon(
		glm::vec3 point1,
		glm::vec3 point2,
		glm::vec3 point3,
		glm::vec3 point4,
		glm::vec3 point5,
		glm::vec3 point6,
		glm::vec3 point7,
		glm::vec3 point8,
		glm::vec3 point9,
		glm::vec3 point10)
{
	corners.push_back(point1);
	corners.push_back(point2);
	corners.push_back(point3);
	corners.push_back(point4);
	corners.push_back(point5);
	corners.push_back(point6);
	corners.push_back(point7);
	corners.push_back(point8);
	corners.push_back(point9);
	corners.push_back(point10);
	//corners.push_back(point5);
}