#pragma once
#include "GameObject.h"

struct Block : GameObject
{
	Block(Game* _game,glm::vec3 _position);
	void tick();
	void render(glm::mat4 _view, glm::mat4 _projection);

private:
	Game* m_game;
};

