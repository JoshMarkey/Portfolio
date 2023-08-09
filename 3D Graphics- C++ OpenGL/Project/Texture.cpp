#include "Texture.h"

Texture::Texture() : m_width(0), m_height(0), m_textureId(0), m_data(0)
{
}

Texture::Texture(GLuint _id) : m_width(800), m_height(800), m_textureId(_id), m_data(0)
{
}

Texture::Texture(const char* name) : m_width(0), m_height(0), m_textureId(0), m_data(0)
{
	load(name);
}

Texture::~Texture()
{
	glDeleteTextures(1, &m_textureId);
}

void Texture::uploadToGPU()
{
	//Generate texture
	glGenTextures(1, &m_textureId);

	if (!m_textureId)
	{
		throw std::exception();
	}
	
	glBindTexture(GL_TEXTURE_2D, m_textureId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	// Upload the image data to the bound texture unit in the GPU
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA,
		GL_UNSIGNED_BYTE, m_data);

	// Free the loaded data because we now have a copy on the GPU
	free(m_data);

	// Generate Mipmap so the texture can be mapped correctly
	glGenerateMipmap(GL_TEXTURE_2D);                                                 

	// Unbind the texture because we are done operating on it
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::load(const char* name)
{
	//load png image as a texture
	m_data = stbi_load(name, &m_width, &m_height, NULL, 4);
	if (!m_data)
	{
		throw std::exception();
	}

	uploadToGPU();
}

GLuint Texture::getID()
{
	return m_textureId;
}
