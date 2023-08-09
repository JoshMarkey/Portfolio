#include "OrthoCamera.h"
#include "Game.h"

OrthoCamera::OrthoCamera(Game* _game)
{
	m_game = _game;
	m_projection = glm::ortho(0.0f, 800.0f, 0.0f,
		800.0f, 0.0f, 10.0f);
}
