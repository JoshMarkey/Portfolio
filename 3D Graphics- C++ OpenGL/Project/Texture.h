#pragma once
#include <GL/glew.h>
#include<stdexcept>
#include <stb_image.h>
#include <glm/glm.hpp>

struct Texture
{
	Texture();
	Texture(const char* _name);
	Texture(GLuint _id);
	~Texture();
	unsigned char* m_data;

	int m_width;
	int m_height;

	GLuint m_textureId;

	void uploadToGPU();
	void load(const char* _name);
	GLuint getID();
};