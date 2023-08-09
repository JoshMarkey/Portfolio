#include "Block.h"
#include "Game.h"

Block::Block(Game* game,glm::vec3 _position) : m_game(game),
GameObject(game->m_blockTextures[0], game->m_blockModel)
{
	m_position = _position;
}

void Block::tick()
{
}

void Block::render(glm::mat4 _view, glm::mat4 _projection)
{
	// Render Block by updating and binding the matrices then rendering to the light shader
	updateMatrix(m_position,glm::vec3(1.5,1.5,1.5),glm::vec3(0,0,0),_view,_projection);
	m_game->m_lightShader->bindMatrix("u_Projection", _projection);
	m_game->m_lightShader->bindMatrix("u_Viewing", _view);
	glm::mat4 tempMat = m_model->getModelMat();
	m_game->m_lightShader->bindMatrix("u_Model", tempMat);
	m_game->m_lightShader->bindFloat("u_Brightness", 0.65);
	m_game->m_lightShader->render(m_model.get(), m_texture.get());
}
