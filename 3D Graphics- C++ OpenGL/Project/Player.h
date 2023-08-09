#pragma once
#include "GameObject.h"


struct Player : GameObject
{
	Player(Game* game);
	bool tick(float deltaT);
	void render(glm::mat4 _view, glm::mat4 _projection);
	Game* m_game;

private:
	bool jumping2;
	bool jumping;
	float velocity;
};

