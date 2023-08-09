#include "MatrixCube.h"


//Constructor

MatrixCube::MatrixCube(
	glm::vec3 point1,
	glm::vec3 point2,
	glm::vec3 point3,
	glm::vec3 point4,
	glm::vec3 point5,
	glm::vec3 point6,
	glm::vec3 point7,
	glm::vec3 point8)
{

	corners.push_back(point1);
	corners.push_back(point2);
	corners.push_back(point3);
	corners.push_back(point4);
	corners.push_back(point5);
	corners.push_back(point6);
	corners.push_back(point7);
	corners.push_back(point8);

}



void MatrixCube::drawCube(glm::vec3 colour,  float rotation)
{
	glm::mat4x4 rotationx = glm::mat4x4(glm::vec4(1.0f, 0.0f, 0.0f, 0.0f), glm::vec4(0.0f, std::cosf(rotation * 0.5f), -(std::sinf(rotation * 0.5f)), 0.0f),
		glm::vec4(0.0f, std::sinf(rotation * 0.5f), std::cos(rotation * 0.5f), 0.0f), glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));

	glm::mat4x4 rotationz = glm::mat4x4(glm::vec4(std::cosf(rotation*0.5), -(std::sinf(rotation*0.5)), 0.0f, 0.0f), glm::vec4(std::sinf(rotation*0.5), std::cosf(rotation*0.5), 0.0f, 0.0f),
		glm::vec4(0.0f, 0.0f, 1.0f, 0.0f), glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));

	glm::mat4x4 rotationy = glm::mat4x4(glm::vec4(std::cosf(rotation*0.5f), 0.0f, std::sinf(rotation * 0.5f), 0.0f),
																			glm::vec4(0.0f, 1.0f, 0.0f, 0.0f),
																			glm::vec4(-std::sinf(rotation * 0.5f), 0.0f, std::cosf(rotation * 0.5f), 0.0f),
																			glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
			

	//creating vector of triangles. this way i am able to edit the poinits temporarily
	//so that i can use the original ones again next frame
	//it also lets me hide the triangles i want to be hidden based on the prospective
	std::vector<Triangle> projectedCube;

	Triangle t;
	t.p1 = corners[3];
	t.p2 = corners[0];
	t.p3 = corners[1];
	projectedCube.push_back(t);
	t.p1 = corners[3];
	t.p2 = corners[1];
	t.p3 = corners[2];
	projectedCube.push_back(t);
	t.p1 = corners[0];
	t.p2 = corners[4];
	t.p3 = corners[5];
	projectedCube.push_back(t);
	t.p1 = corners[0];
	t.p2 = corners[5];
	t.p3 = corners[1];
	projectedCube.push_back(t);
	t.p1 = corners[7];
	t.p2 = corners[4];
	t.p3 = corners[0];
	projectedCube.push_back(t);
	t.p1 = corners[7];
	t.p2 = corners[0];
	t.p3 = corners[3];
	projectedCube.push_back(t);
	t.p1 = corners[2];
	t.p2 = corners[1];
	t.p3 = corners[5];
	projectedCube.push_back(t);
	t.p1 = corners[2];
	t.p2 = corners[5];
	t.p3 = corners[6];
	projectedCube.push_back(t);
	t.p1 = corners[7];
	t.p2 = corners[3];
	t.p3 = corners[2];
	projectedCube.push_back(t);
	t.p1 = corners[7];
	t.p2 = corners[2];
	t.p3 = corners[6];
	projectedCube.push_back(t);
	t.p1 = corners[5];
	t.p2 = corners[4];
	t.p3 = corners[7];
	projectedCube.push_back(t);
	t.p1 = corners[6];
	t.p2 = corners[5];
	t.p3 = corners[7];
	projectedCube.push_back(t);

	

	for (int i = 0; i < projectedCube.size(); i++)
	{
		//multiply by rotation matrix
		projectedCube[i].p1 = multiplyMatrix(projectedCube[i].p1, rotationz);
		projectedCube[i].p2 = multiplyMatrix(projectedCube[i].p2, rotationz);
		projectedCube[i].p3 = multiplyMatrix(projectedCube[i].p3, rotationz);

		projectedCube[i].p1 = multiplyMatrix(projectedCube[i].p1, rotationx);
		projectedCube[i].p2 = multiplyMatrix(projectedCube[i].p2, rotationx);
		projectedCube[i].p3 = multiplyMatrix(projectedCube[i].p3, rotationx);

		projectedCube[i].p1 = multiplyMatrix(projectedCube[i].p1, rotationy);
		projectedCube[i].p2 = multiplyMatrix(projectedCube[i].p2, rotationy);
		projectedCube[i].p3 = multiplyMatrix(projectedCube[i].p3, rotationy);
		//translating by 3 in the z to move it onto the screen
		projectedCube[i].p1.z += 3.0f;
		projectedCube[i].p2.z += 3.0f;
		projectedCube[i].p3.z += 3.0f;
		//find the normal
		glm::vec3 normal;
		normal = glm::normalize(glm::cross(projectedCube[i].p2 - projectedCube[i].p1, projectedCube[i].p3 - projectedCube[i].p1));
		//find dot product
		float dotProduct = glm::dot(projectedCube[i].p1, normal);

		//if the dot product of normal is a negative it means the face is pointing towards the camera 
		if (dotProduct < 0.0f)
		{
			//multiply by projection matrix to make it 2d
			projectedCube[i].p1 = multiplyMatrix(projectedCube[i].p1, projectionMatrix);
			projectedCube[i].p2 = multiplyMatrix(projectedCube[i].p2, projectionMatrix);
			projectedCube[i].p3 = multiplyMatrix(projectedCube[i].p3, projectionMatrix);
			//scale into screen view
			projectedCube[i].p1.x += 1.0f;
			projectedCube[i].p2.x += 1.0f;
			projectedCube[i].p3.x += 1.0f;

			projectedCube[i].p1.y += 1.0f;
			projectedCube[i].p2.y += 1.0f;
			projectedCube[i].p3.y += 1.0f;

			projectedCube[i].p1.x *= 0.5f * 640.0f;
			projectedCube[i].p2.x *= 0.5f * 640.0f;
			projectedCube[i].p3.x *= 0.5f * 640.0f;

			projectedCube[i].p1.y *= 0.5f * 480.0f;
			projectedCube[i].p2.y *= 0.5f * 480.0f;
			projectedCube[i].p3.y *= 0.5f * 480.0f;
			//draw triangle
			drawTriangle(projectedCube[i], colour);
		}
	}

	
}

