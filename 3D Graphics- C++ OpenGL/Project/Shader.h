#pragma once
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

struct Model;
struct Texture;
struct Vao;

struct Shader
{
private:
	GLuint m_id;
	GLuint m_fragShader;
	GLuint m_vertShader;
	GLuint createShader(std::string _filename, GLuint _shader);
	void attrib(const GLchar* _name, int _position);

public:
	Shader(std::string _fragment,std::string _vertex);
	~Shader();
	void link();
	GLuint getId();
	void bindMatrix(const char* _name, glm::mat4& _mat);
	void bindFloat(const char* _name, float _brightness);
	void bindOrthoMatrix(glm::mat4 _projection, glm::mat4 _model);
	void render(Model* _mesh, Texture* _tex,bool _backface = true);
	void renderOrtho(Vao* _mesh, Texture* _tex);
	void render2Textures(Vao* _mesh, const char* _name1, GLuint _tex1, const char* _name2, GLuint _tex2);
	void renderRT(Vao* _mesh, GLuint _id);
	void clear();
};

