#pragma once
#include "GameObject.h"

struct Game;

class SkyBox : GameObject
{
public:
	SkyBox(Game* _game);
	void render(glm::mat4 _view, glm::mat4 _projection);
	Game* m_game;

private:
	glm::vec3 m_scale;
};

