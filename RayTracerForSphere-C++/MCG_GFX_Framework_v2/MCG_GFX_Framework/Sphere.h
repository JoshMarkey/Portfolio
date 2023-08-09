#pragma once
#include <GLM/glm.hpp>
#include "RayClass.h"

struct intersectionInfomation
{
	glm::vec3  intersection;
	glm::vec3  normal;
	bool hasIntersection;
};

class Sphere
{
private:
	glm::vec3 centre;
	float radius;
	glm::vec3 colour;
	

public:
	Sphere(glm::vec3 c, float r, glm::vec3 rgb);
	glm::vec3 getCentre();
	float getRadius();
	void setRadius(float r);
	void setCentre(glm::vec3 c);
	void setColour(glm::vec3 rgb);
	glm::vec3 getColour();
	float shortestDistance(Ray ray);
	glm::vec3 closestPoint(Ray ray, glm::vec3 p);
	bool hasIntersection(float distance);
	glm::vec3 raySphereIntersection(Ray ray);
	intersectionInfomation intersectSphere(Ray ray);
};

