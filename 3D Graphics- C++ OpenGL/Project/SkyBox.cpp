#include "SkyBox.h"
#include "Game.h"

SkyBox::SkyBox(Game* _game) :
GameObject(_game->m_skyBoxTexture, _game->m_SkyModel), m_game(_game)
{
	m_position = glm::vec3(0, 0, 0);
	m_scale = glm::vec3(90, 90, 90);
}

void SkyBox::render(glm::mat4 _view, glm::mat4 _projection)
{
	updateMatrix(m_position, m_scale, glm::vec3(0, 0, 180), _view, _projection);
	m_game->m_SkyBoxShader->bindMatrix("u_Projection", _projection);
	m_game->m_SkyBoxShader->bindMatrix("u_Viewing", _view);
	glm::mat4 tempMat = m_model->getModelMat();
	m_game->m_SkyBoxShader->bindMatrix("u_Model", tempMat);
	m_game->m_SkyBoxShader->bindFloat("u_Brightness", 0.3);
	m_game->m_SkyBoxShader->render(m_model.get(), m_texture.get(),false);
}
