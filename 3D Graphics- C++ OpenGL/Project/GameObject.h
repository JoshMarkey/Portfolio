#pragma once
#include "rend.h"


struct Game;

struct GameObject
{
	std::shared_ptr<Model> m_model;
	std::shared_ptr<Texture> m_texture;

	glm::vec3 m_position;
	
	GameObject(std::shared_ptr<Texture> _tex, std::shared_ptr<Model> _model);
	void updateMatrix(glm::vec3 _position, glm::vec3 _scale, glm::vec3 _rotation, glm::mat4 _view, glm::mat4 _projection);

	bool BoxCollision(glm::vec3 _position1, glm::vec3 _position2, glm::vec3 _scale1, glm::vec3 _scale2);

};

