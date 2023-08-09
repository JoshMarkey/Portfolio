#include "GameObject.h"

GameObject::GameObject(std::shared_ptr<Texture> _tex, std::shared_ptr<Model> _model) :
	m_texture(_tex), m_model(_model)
{

}

void GameObject::updateMatrix(glm::vec3 _position, glm::vec3 _scale , glm::vec3 _rotation, glm::mat4 _view, glm::mat4 _projection)
{
	m_model->updateMatrix(_position,_scale, _rotation,_view, _projection);

}

//Basic collision between 2 box objects

//Pass the hand made scale so that the boxes can be different sizes. Makes it generic
bool GameObject::BoxCollision(glm::vec3 _position1, glm::vec3 _position2, glm::vec3 _scale1, glm::vec3 _scale2)
{
	_scale1 /= 2;
	_scale2 /= 2;
	
	if (glm::abs(_position1.x - _position2.x) < _scale1.x + _scale2.x)
	{
		if (glm::abs(_position1.y - _position2.y) < _scale1.y + _scale2.y)
		{
			if (glm::abs(_position1.z - _position2.z) < _scale1.z + _scale2.z)
			{
				return true;
			}
		}
	}
	return false;
}


