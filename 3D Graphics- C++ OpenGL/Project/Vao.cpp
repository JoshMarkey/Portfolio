#include "Vao.h"

Vao::Vao() : m_id(0), m_dirty(false)
{

}

GLuint Vao::getId()
{
	if (!m_id)
	{
		// Create a new VAO on the GPU and bind it
		glGenVertexArrays(1, &m_id);

		if (!m_id) throw std::runtime_error("Failed to allocate VAO");

	}

	//dirty
	if (m_dirty)
	{
		m_dirty = false;
		glBindVertexArray(m_id);

		for (int i = 0; i < m_vbos.size(); i++)
		{
			glBindBuffer(GL_ARRAY_BUFFER, m_vbos[i]->getId());

			glVertexAttribPointer(i, m_vbos[i]->getComponents(), GL_FLOAT, GL_FALSE,0, (void*)0);

			glEnableVertexAttribArray(i);

			// Reset the state
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}

		glBindVertexArray(0);
	}

	return m_id;
}

void Vao::addVbo(std::shared_ptr<Vbo> _vbo)
{
	//Tell the object that its state has changed so it can be updated
	m_vbos.push_back(_vbo);
	m_dirty = true;
}

