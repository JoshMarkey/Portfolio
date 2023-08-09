#include "Model.h"

Model::Model(std::string _name) : 
	m_name(_name),
	m_model(0),
	m_modelMatrix(1.0),
	m_projectionMatrix(glm::perspective(glm::radians(45.0f), 1.0f, 0.01f, 100.0f)),
	m_viewingMatrix(glm::mat4(1.0)),
	m_verts(0),
	m_scale(glm::vec3(0,0,0))

{
	
}

GLuint Model::getId()
{
	//If no current ID, load the model
	if (!m_model)
	{
		m_model = buLoadModel(m_name, m_verts);
	}
	return m_model;
}

size_t Model::getVerts()
{
	//return total number of verts
	return m_verts;
}

void Model::updateMatrix(glm::vec3 position, glm::vec3 scale, glm::vec3 rotation, glm::mat4 view, glm::mat4 projection)
{
	//update all matrices with given scale, rotation and position
	m_viewingMatrix = view;
	m_projectionMatrix = projection;
	m_modelMatrix = glm::scale(glm::mat4(1.0),scale);
	m_modelMatrix = glm::translate(m_modelMatrix, position);
	if (rotation.x != 0)
	{
		m_modelMatrix = glm::rotate(m_modelMatrix, glm::radians(rotation.x), glm::vec3(1, 0, 0));
	}
	if (rotation.y != 0)
	{
		m_modelMatrix = glm::rotate(m_modelMatrix, glm::radians(rotation.y), glm::vec3(0, 1, 0));
	}
	if (rotation.z != 0)
	{
		m_modelMatrix = glm::rotate(m_modelMatrix, glm::radians(rotation.z), glm::vec3(0, 0, 1));
	}
}



