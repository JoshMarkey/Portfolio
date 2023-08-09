#include "Vbo.h"

Vbo::Vbo() : m_id(0), m_dirty(false),m_components(0)
{

}
//Add vec3
void Vbo::add(const glm::vec3& _value)
{
		m_data.push_back(_value.x);
		m_data.push_back(_value.y);
		m_data.push_back(_value.z);
		m_dirty = true;
		m_components = 3;
}
//add vec2
void Vbo::add(const glm::vec2& _value)
{
		m_data.push_back(_value.x);
		m_data.push_back(_value.y);
		m_dirty = true;
		m_components = 2;
}

GLuint Vbo::getId()
{
	//allocate VBO if not already done
		if (!m_id)
		{
				glGenBuffers(1, &m_id);
				if (!m_id) throw std::runtime_error("Failed to allocate VBO");
		}
		//Update VAO if it has been modified
		if (m_dirty)
		{
				glBindBuffer(GL_ARRAY_BUFFER, m_id);
				glBufferData(GL_ARRAY_BUFFER, sizeof(float) * m_data.size(),&m_data.at(0), GL_STATIC_DRAW);
				glBindBuffer(GL_ARRAY_BUFFER, m_id);
		}
		//return ID
		return m_id;
}

const int Vbo::getComponents()
{
		return m_components;
}
