#include "Sphere.h"



Sphere::Sphere(glm::vec3 c, float r, glm::vec3 rgb)
{
	centre = c;
	radius = r;
	colour = rgb;

}


glm::vec3 Sphere::getCentre()
{
	return centre;
}
float Sphere::getRadius()
{
	return radius;
}
void Sphere::setRadius(float r)
{
	radius = r;
}
void Sphere::setCentre(glm::vec3 c)
{
	centre = c;
}

glm::vec3 Sphere::getColour()
{
	return colour;
}
void Sphere::setColour(glm::vec3 rgb)
{
	colour = rgb;
}

glm::vec3 Sphere::closestPoint(Ray ray, glm::vec3 p)
{
	//defining a and n
	glm::vec3 a = ray.getOrigin();
	glm::vec3 n = ray.getDirection();
	//doing maths
	glm::vec3 x = a + glm::dot((p - a), n) * n;
	//returning the maths
	return x;
}

float Sphere::shortestDistance(Ray ray)
{
	glm::vec3 x = closestPoint(ray, centre);
	float distance;

	distance = glm::length(centre - x);
	return distance;
}

bool Sphere::hasIntersection(float distance)
{
	if (distance > radius)
	{
		return false;
	}
	else
	{
		return true;
	}
}

glm::vec3 Sphere::raySphereIntersection(Ray ray)
	{
	float d = shortestDistance(ray);
	float x = sqrt(radius * radius - d * d);
	glm::vec3 intersection = ray.getOrigin() + (glm::dot((centre - ray.getOrigin()), ray.getDirection()) - x) * ray.getDirection();
	return intersection;
	}

intersectionInfomation Sphere::intersectSphere(Ray ray)
{
	//create struct
	struct intersectionInfomation intersectInfo;
	intersectInfo.hasIntersection = false;
	intersectInfo.normal = glm::vec3(0, 0, 0);
	intersectInfo.intersection = glm::vec3(0, 0, 0);
	//check if sphere is in origin
	if (glm::length(centre - ray.getOrigin()) < radius)
	{
		return intersectInfo;
	}

	glm::vec3 P = closestPoint(ray, centre);
	float t = glm::dot((P - ray.getOrigin()), ray.getDirection()) / glm::dot(ray.getDirection(), ray.getDirection());

	if (t < 0)
	{
		return intersectInfo;
	}

	if (hasIntersection(shortestDistance(ray)))
	{
		intersectInfo.hasIntersection = true;
	}
	else
	{
		return intersectInfo;
	}
	//intersection point - centre = normal
}
