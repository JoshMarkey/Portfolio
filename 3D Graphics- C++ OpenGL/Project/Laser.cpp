#include "Laser.h"
#include "Game.h"

Laser::Laser(Game* game) : m_game(game),GameObject(game->m_LaserTexture,game->m_LaserModel)
{
	m_position = glm::vec3(50,1,1);

	m_speed = 10;

}

void Laser::render(glm::mat4 _view, glm::mat4 _projection)
{
	// Render Laser by updating and binding the matrices then rendering to the light shader
	m_model->updateMatrix(m_position, glm::vec3(0.3,0.3,0.3), glm::vec3(0, 0, 0), _view, _projection);
	m_game->m_lightShader->bindMatrix("u_Projection", _projection);
	m_game->m_lightShader->bindMatrix("u_Viewing", _view);
	glm::mat4 tempMat = m_model->getModelMat();
	m_game->m_lightShader->bindMatrix("u_Model", tempMat);
	m_game->m_lightShader->bindFloat("u_Brightness", 1);
	m_game->m_lightShader->render(m_model.get(), m_texture.get());
}

void Laser::tick(float deltaT)
{
	//Move laser slightly each tick based on the speed
	m_position.x = m_position.x - m_speed * deltaT;

	if (m_position.x <= -10)
	{
		m_position.x = 50;
		m_speed += 1;
	}
}
