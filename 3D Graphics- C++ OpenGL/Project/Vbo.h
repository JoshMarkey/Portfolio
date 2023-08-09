#pragma once
#include <GL/glew.h>
#include <vector>
#include <glm/glm.hpp>
#include<stdexcept>

struct Vbo
{
		Vbo();
		void add(const glm::vec3& _value);
		void add(const glm::vec2& _value);
		GLuint getId();
		const int getComponents();

private:
		GLuint m_id;
		std::vector<float> m_data;
		bool m_dirty;
		int m_components;

};

