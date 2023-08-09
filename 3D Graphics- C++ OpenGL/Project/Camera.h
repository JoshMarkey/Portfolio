#pragma once
#include "rend.h"

struct Game;

struct Camera
{
	Camera(Game* _game);
	glm::mat4 getView() { return m_view; }
	glm::mat4 getProjection() { return m_projection; }
	void tick(float _deltaTs);

private:
	Game* m_game;
	int m_posx;
	int m_posy;
	glm::mat4 m_projection;
	glm::mat4 m_view;
	glm::vec3 m_position;
	glm::mat4 m_rotation;
	float m_speed;
	float m_cameraAnglex;
	float m_cameraAngley;
	float m_mouseSpeed;
	glm::vec3 m_translate;
};

