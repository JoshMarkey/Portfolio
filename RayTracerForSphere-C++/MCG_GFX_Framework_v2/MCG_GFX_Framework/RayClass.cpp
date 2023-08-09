#include "RayClass.h"

Ray::Ray(glm::vec3 _origin, glm::vec3 _direction)
{
	origin = _origin;
	direction = _direction;
}

glm::vec3 Ray::getDirection()
{
	return direction;
}
void Ray::setDirection(glm::vec3 _d)
{
	direction = _d;
}
glm::vec3 Ray::getOrigin()
{
	return origin;
}
void Ray::setOrigin(glm::vec3 _o)
{
	origin = _o;
}

glm::vec3 Ray::lineEquation(float t)
{
	glm::vec3 p;
	p = origin + (direction * t);
	return p;
}