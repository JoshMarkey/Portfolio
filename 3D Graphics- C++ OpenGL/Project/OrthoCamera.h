#pragma once
#include "rend.h"

struct Game;

struct OrthoCamera
{
	OrthoCamera(Game* _game);
	glm::mat4 getProjection() { return m_projection; }
private:
	Game* m_game;
	glm::mat4 m_projection;
};

