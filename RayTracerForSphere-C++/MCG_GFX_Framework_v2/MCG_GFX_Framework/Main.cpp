#include <cmath>
#include "RayClass.h"
#include "MCG_GFX_Lib.h"
#include "MatrixCube.h"
#include <chrono>
#include "MatrixHexagon.h"
#include <iostream>

void cubeMatrix();
void hexagonMatrix();
void rayTracer();

int main(int argc, char* argv[])
{
	int menu;
	bool valid = true;
	while (valid)
	{
		std::cout << ("----------------------") << std::endl;
		std::cout << ("         MENU         ") << std::endl;
		std::cout << ("----------------------") << std::endl;
		std::cout << std::endl;
		std::cout << std::endl;
		std::cout << ("1) Ray Tracer Sphere") << std::endl;
		std::cout << ("2) 3D Cube") << std::endl;
		std::cout << ("3) 3D Triangle Pyramid") << std::endl;
		std::cin >> (menu);

		switch (menu)
		{
		case 1:
			rayTracer();
			valid = false;
			break;
		case 2:
			cubeMatrix();
			valid = false;
			break;
		case 3:
			hexagonMatrix();
			valid = false;
			break;
		default:
			std::cout << ("Invalid Input") << std::endl;
			break;
		}
	}
}

void cubeMatrix()
{
	glm::ivec2 windowSize(640, 480);
	MCG::Init(windowSize);	
	MCG::SetBackground(glm::vec3(0, 0, 0));

	auto start = std::chrono::steady_clock::now();
	auto end = std::chrono::steady_clock::now();
	float rotation = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

	glm::vec3 colour = glm::vec3(1, 1, 1);

	glm::vec3 p1 = { -0.5f, 0.5f, -0.5f };
	glm::vec3 p2 = { 0.5f, 0.5f, -0.5f };
	glm::vec3 p3 = { 0.5f, -0.5f,-0.5f };
	glm::vec3 p4 = { -0.5f, -0.5f, -0.5f };
	glm::vec3 p5 = { -0.5f, 0.5f, 0.5f };
	glm::vec3 p6 = { 0.5f, 0.5f, 0.5f };
	glm::vec3 p7 = { 0.5f, -0.5f, 0.5f };
	glm::vec3 p8 = { -0.5f, -0.5f, 0.5f };

	MatrixCube cube = MatrixCube(p1, p2, p3, p4, p5, p6, p7, p8);

	while (true)
	{
		end = std::chrono::steady_clock::now();
		rotation = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
		cube.drawCube(colour, rotation / 500);
		MCG::ProcessFrame();
		MCG::SetBackground(glm::vec3(0, 0, 0));
	}
}

void hexagonMatrix()
{
	glm::ivec2 windowSize(640, 480);
	MCG::Init(windowSize);
	MCG::SetBackground(glm::vec3(0, 0, 0));

	auto start = std::chrono::steady_clock::now();
	auto end = std::chrono::steady_clock::now();
	float rotation = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

	glm::vec3 colour = glm::vec3(1, 1, 1);

	glm::vec3 p1 = { -0.5f, -1.0f, -1.0f };
	glm::vec3 p2 = { 0.5f, -1.0f, -1.0f };
	glm::vec3 p3 = { 1.0f, -1.0f, 0.0f };
	glm::vec3 p4 = { 0.0f, -1.0f, 1.0f };
	glm::vec3 p5 = { -1.0f, -1.0f, 0.0f };
	glm::vec3 p6 = { -0.5f, 1.0f, -1.0f };
	glm::vec3 p7 = { 0.5f, 1.0f, -1.0f };
	glm::vec3 p8 = { 1.0f, 1.0f, 0.0f };
	glm::vec3 p9 = { 0.0f, 1.0f, 1.0f };
	glm::vec3 p10 = { -1.0f, 1.0f, 0.0f };

	MatrixHexagon hexagon = MatrixHexagon(p1, p2, p3, p4,p5,p6,p7,p8,p9,p10);

	while (true)
	{
		end = std::chrono::steady_clock::now();
		rotation = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
		hexagon.drawHexagon(colour, rotation / 1000);
		MCG::ProcessFrame();
		MCG::SetBackground(glm::vec3(0, 0, 0));
	}
}

void rayTracer()
{
	glm::ivec2 windowSize(640, 480);
	MCG::Init(windowSize);
	MCG::SetBackground(glm::vec3(0, 0, 0));
}


