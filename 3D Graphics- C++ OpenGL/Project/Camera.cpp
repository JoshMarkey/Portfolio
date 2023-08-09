#include "Camera.h"
#include "Game.h"


Camera::Camera(Game* _game)
{
	m_game = _game;
	m_position = glm::vec3(5, 3,-30);
	glm::vec3 initTarget = glm::vec3(5, 0.0f, -30);

	m_cameraAnglex = 0.0f;
	m_cameraAngley = 0.0f;

	m_speed = 5;
	m_mouseSpeed = 0.5f;


	//Create matrix
	m_projection = glm::perspective(glm::radians(45.0f), 1.0f, 0.01f, 150.0f);
	m_view = glm::lookAt(m_position, initTarget, glm::vec3(0,1,0));
}

void Camera::tick(float deltaT)
{
	m_translate = glm::vec3(0,0,0);
	//calculate mouse movement using raw data
	m_cameraAnglex += m_game->m_mouseDelta.x * -m_mouseSpeed * deltaT;
	m_cameraAngley -= m_game->m_mouseDelta.y * m_mouseSpeed * deltaT;

	//Calculate different directions for dynamic tranlation
	glm::vec3 direction(cos(m_cameraAngley) * sin(m_cameraAnglex), sin(m_cameraAngley), cos(m_cameraAngley) * cos(m_cameraAnglex));
	glm::vec3 right = glm::vec3(sin(m_cameraAnglex - 3.14f / 2.0f), 0, cos(m_cameraAnglex - 3.14f / 2.0f));
	glm::vec3 up = glm::cross( right, direction);

	// Move camera
	if (m_game->pressW)
	{
		m_translate = direction * m_speed * deltaT;
		m_position += m_translate;

	}
	if (m_game->pressS)
	{
		m_translate = -(direction * m_speed * deltaT);
		m_position += m_translate;
	}
	if (m_game->pressA)
	{
		m_translate = (right * m_speed * deltaT);
		m_position -= m_translate;

	}
	if (m_game->pressD)
	{
		m_translate = right * m_speed * deltaT;
		m_position += m_translate;
	}
	//update view matrix
	m_view = glm::lookAt(m_position, m_position + direction, up);
}
