#pragma once
#include "Shader.h"
#include <bugl.h>
struct Model
{
public:
	Model(std::string _name);
	GLuint getId();
	size_t getVerts();
	glm::mat4 getModelMat() { return m_modelMatrix; }
	void updateMatrix(glm::vec3 _position, glm::vec3 _scale, glm::vec3 _rotation, glm::mat4 _view, glm::mat4 _projection);

private:
	std::string m_name;
	GLuint m_model;
	size_t m_verts;
	glm::mat4 m_modelMatrix;
	glm::mat4 m_viewingMatrix;
	glm::mat4 m_projectionMatrix;
	glm::vec3 m_scale;
};

