#include "MatrixParent.h"

glm::vec3 MatrixParent::multiplyMatrix(glm::vec3 inputVector, glm::mat4x4 multiplyMatrix)
{
	glm::vec4 vector;
	vector.x = inputVector.x;
	vector.y = inputVector.y;
	vector.z = inputVector.z;
	vector.w = 1.0f;

	glm::vec4 result;
	result = multiplyMatrix * vector;

	if (result.w != 0)
	{
		result.x /= result.w;
		result.y /= result.w;
		result.z /= result.w;
	}
	return glm::vec3(result.x, result.y, result.z);
}

void MatrixParent::drawTriangle(struct Triangle f, glm::vec3 colour)
{
	drawLine(f.p1, f.p2, colour);
	drawLine(f.p1, f.p3, colour);
	drawLine(f.p3, f.p2, colour);
}

void MatrixParent::drawLine(glm::vec2 p1, glm::vec2 p2, glm::vec3 colour)
{
	float x1 = p1.x;
	float y1 = p1.y;
	float x2 = p2.x;
	float y2 = p2.y;
	float rise = y2 - y1;
	float run = x2 - x1;
	int x, y;
	float m;
	float adjust;
	float offset;
	float threshold;
	float delta;
	int temp;
	if (run == 0)
	{
		if (y2 < y1)
		{
			temp = y2;
			y2 = y1;
			y1 = temp;
		}
		for (y = y1; y <= y2 + 1; y++)
		{
			MCG::DrawPixel(glm::ivec2(x1, y), colour);
		}
	}
	else
	{
		m = float(rise / run);
		adjust = 1;
		if (m <= 0)
		{
			adjust = -1;
		}
		offset = 0;
		threshold = 0.5;
		if (m <= 1 && m >= -1)
		{
			delta = std::abs(m);
			y = y1;
			if (x2 < x1)
			{
				temp = x2;
				x2 = x1;
				x1 = temp;
				y = y2;
			}
			for (x = x1; x <= x2 + 1; x++)
			{
				MCG::DrawPixel(glm::ivec2(x, y), colour);
				offset += delta;
				if (offset >= threshold)
				{
					y += adjust;
					threshold++;
				}
			}
		}
		else
		{
			delta = std::abs(float(run) / rise);
			x = x1;
			if (y2 < y1)
			{
				temp = y2;
				y2 = y1;
				y1 = temp;
				x = x2;
			}
			for (y = y1; y <= y2 + 1; y++)
			{
				MCG::DrawPixel(glm::ivec2(x, y), colour);
				offset += delta;
				if (offset >= threshold)
				{
					x += adjust;
					threshold++;
				}
			}
		}
	}


}

MatrixParent::MatrixParent()
{
	float near = 0.1f;
	float far = 1000.0f;
	float fov = 90.0f;
	//  height/width
	float aspectRatio = (float)480 / 640;

	projectionMatrix[0] = glm::vec4(aspectRatio * (1 / (std::tanf(fov / 2 / 180.0f * M_PI))), 0.0f, 0.0f, 0.0f);
	projectionMatrix[1] = glm::vec4(0.0f, 1 / (std::tanf(fov / 2 / 180.0f * M_PI)), 0.0f, 0.0f);
	projectionMatrix[2] = glm::vec4(0.0f, 0.0f, far / (far - near), 1.0f);
	projectionMatrix[3] = glm::vec4(0.0f, 0.0f, (-far * near) / (far - near), 0.0f);
}