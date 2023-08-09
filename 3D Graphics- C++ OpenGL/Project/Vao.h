#pragma once
#include <GL/glew.h>
#include <vector>
#include <glm/glm.hpp>
#include<stdexcept>
#include "Vbo.h"
#include <memory>

struct Vao
{
	Vao();
	GLuint getId();
	void addVbo(std::shared_ptr<Vbo > _vbo);
private:
	GLuint m_id;
	std::vector<std::shared_ptr<Vbo>> m_vbos;
	bool m_dirty;
};