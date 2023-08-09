#pragma once
#include <GL/glew.h>
#include <vector>
#include <glm/glm.hpp>
#include<stdexcept>

struct RenderTexture
{
	RenderTexture(int _width, int _height);
	~RenderTexture();

	void bind();
	void unbind();

	GLuint getTexture();

private:
	GLuint m_fboId;
	GLuint m_texId;
	GLuint m_rboId;

	bool m_dirty;
	int m_width;
	int m_height;
};

