#pragma once
#include <GLM/glm.hpp>
class Ray
{
private:
	glm::vec3 origin;
	glm::vec3 direction;
public:
	Ray(glm::vec3 _origin, glm::vec3 _direction);
	glm::vec3 getDirection();
	void setDirection(glm::vec3 _d);
	glm::vec3 getOrigin();
	void setOrigin(glm::vec3 _o);
	glm::vec3 lineEquation(float t);
};

