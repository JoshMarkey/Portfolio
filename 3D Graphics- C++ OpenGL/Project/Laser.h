#pragma once
#include "GameObject.h"

struct Laser : GameObject
{
	Laser(Game* _game);
	void render(glm::mat4 _view, glm::mat4 _projection);

	glm::vec3 m_position;

	void tick(float _deltaT);

private:
	Game* m_game;
	float m_speed;
};

