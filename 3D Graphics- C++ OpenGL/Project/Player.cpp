#include "Player.h"
#include "Game.h"

Player::Player(Game* game) : m_game(game),
	GameObject(game->m_playerTexture,game->m_playerModel)
	
{
	m_position = glm::vec3(0, 11, 0);
	jumping = true;
	jumping2 = true;
	velocity = 0;
}

bool Player::tick(float deltaT)
{
	if (m_game->pressSpace)
	{
		jumping = true;
	}

	if (jumping && !jumping2)
	{
		jumping2 = true;
		velocity = 300;
	}
	if(jumping)
		velocity += -900 * deltaT;

	if (BoxCollision(m_position, m_game->m_floor[0].m_position, glm::vec3(1, 19.75, 1), glm::vec3(1.5, 1.5, 1.5)) && jumping)
	{
		m_position.y = 9.8;
		velocity = 0;
		jumping = false;
		jumping2 = false;
	}

	if (BoxCollision(m_position, m_game->m_Laser->m_position, glm::vec3(1, 19.75, 1), glm::vec3(0.5, 19, 10)))
	{
		return false;
	}

	m_position.y += velocity * deltaT;

	return true;

}

void Player::render(glm::mat4 _view, glm::mat4 _projection)
{
	m_model->updateMatrix(m_position, glm::vec3(0.1, 0.1, 0.1), glm::vec3(0, 90, 0), _view, _projection);

	m_game->m_lightShader->bindMatrix("u_Projection", _projection);
	m_game->m_lightShader->bindMatrix("u_Viewing", _view);
	glm::mat4 tempMat = m_model->getModelMat();
	m_game->m_lightShader->bindMatrix("u_Model", tempMat);
	m_game->m_lightShader->bindFloat("u_Brightness", 0.9);
	m_game->m_lightShader->render(m_model.get(), m_texture.get());
	//do pos stuff

}
