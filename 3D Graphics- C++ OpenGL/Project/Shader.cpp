#include "Shader.h"
#include "Model.h"
#include "Texture.h"
#include "Vao.h"

Shader::Shader(std::string fragment, std::string vertex)
{
	//Initialise shader program
	m_id = glCreateProgram();
	//Load in shaders
	m_vertShader = createShader(vertex, GL_VERTEX_SHADER);
	m_fragShader = createShader(fragment, GL_FRAGMENT_SHADER);
	//link shaders to program
	link();
}

GLuint Shader::createShader(std::string filename, GLuint shader)
{
	//import shader code using a text file
	std::string line;
	std::string String = "";
	std::ifstream myfile(filename);
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			String += line + "\n";
		}
		myfile.close();
	}

	const GLchar* vertexShaderSrc = String.c_str();
	// Create a new vertex shader, attach source code, compile it and
	// check for errors.
	GLuint shaderId = glCreateShader(shader);
	glShaderSource(shaderId, 1, &vertexShaderSrc, NULL);
	glCompileShader(shaderId);
	GLint success = 0;
	glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		GLint maxLength = 0;
		glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH,
			&maxLength);
		std::vector<GLchar> errorLog(maxLength);
		glGetShaderInfoLog(shaderId, maxLength,+
			&maxLength, &errorLog[0]);
		std::cout << &errorLog.at(0) << std::endl;
		throw std::exception();
	}
	glAttachShader(m_id, shaderId);
	return shaderId;
}


void Shader::attrib(const GLchar* _name, int position)
{
	glBindAttribLocation(m_id, position, _name);
}

Shader::~Shader()
{
	glDetachShader(m_vertShader, m_id);
	glDetachShader(m_fragShader, m_id);
	glDeleteShader(m_vertShader);
	glDeleteShader(m_fragShader);
}

void Shader::link()
{
	// Ensure the VAO "position" attribute stream gets set as the first position
	// during the link.
	glBindAttribLocation(m_id, 0, "a_Position");
	glBindAttribLocation(m_id, 1, "a_TexCoord");
	glBindAttribLocation(m_id, 2, "a_Normal");

	// Perform the link and check for failure
	GLint success = 1;
	glLinkProgram(m_id);
	glGetProgramiv(m_id, GL_LINK_STATUS, &success);

	if (!success)
	{
		// get link status
		throw std::exception();
	}

}

GLuint Shader::getId()
{
	return m_id;
}

void Shader::bindFloat(const char* _name, float brightness)
{
	glUseProgram(getId());
	glProgramUniform1f(m_id, glGetUniformLocation(m_id, _name),brightness);
	glUseProgram(0);
}

void Shader::bindMatrix(const char* _name, glm::mat4& _mat)
{
	glProgramUniformMatrix4fv(m_id, glGetUniformLocation(m_id, _name), 1, GL_FALSE, glm::value_ptr(_mat));
}

void Shader::bindOrthoMatrix(glm::mat4 projection, glm::mat4 model)
{
	glProgramUniformMatrix4fv(m_id, glGetUniformLocation(m_id, "u_Projection"), 1, GL_FALSE, glm::value_ptr(projection));
	glProgramUniformMatrix4fv(m_id, glGetUniformLocation(m_id, "u_Model"), 1, GL_FALSE, glm::value_ptr(model));
}

void Shader::render2Textures(Vao* mesh, const char* _name1, GLuint tex1, const char* _name2, GLuint tex2)
{
	// Instruct OpenGL to use our shader program and our VAO
	glUseProgram(getId());

	glUniform1i(glGetUniformLocation(m_id, _name1), 0);
	glUniform1i(glGetUniformLocation(m_id, _name2), 1);
	//Bind 2 textures simultaniously so the can be added together in the frag shader
	glActiveTexture(GL_TEXTURE0 + 0);
	glBindTexture(GL_TEXTURE_2D, tex1);

	glActiveTexture(GL_TEXTURE0 + 1);
	glBindTexture(GL_TEXTURE_2D, tex2);


	glEnable(GL_BLEND);
	glBindVertexArray(mesh->getId());

	glDrawArrays(GL_TRIANGLES, 0, 6);
	glDisable(GL_BLEND);

	glActiveTexture(GL_TEXTURE0);


	// Reset the state
	glBindVertexArray(0);
	glUseProgram(0);
	//glBindTexture(GL_TEXTURE_2D, 0);
}



void Shader::renderOrtho(Vao* mesh, Texture* tex)
{
	// Instruct OpenGL to use our shader program and our VAO
	glUseProgram(getId());                 
	glBindVertexArray(mesh->getId());
	glBindTexture(GL_TEXTURE_2D, tex->getID());
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST); 
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glDisable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);


	// Reset the state
	glBindVertexArray(0);
	glUseProgram(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Shader::render(Model* mesh, Texture* tex, bool backface)
{
	// Instruct OpenGL to use our shader program and our VAO
	glUseProgram(getId());
	//glBindVertexArray(vaoId);                             
	glBindVertexArray(mesh->getId());
	//Draw Tex
	glBindTexture(GL_TEXTURE_2D, tex->getID());
	//allow option for disablling backface culling for the skybox
	if (backface)
	{
		glEnable(GL_CULL_FACE);
		glEnable(GL_DEPTH_TEST);
	}
	glDrawArrays(GL_TRIANGLES, 0, mesh->getVerts());
	if (backface)
	{
		glDisable(GL_CULL_FACE);
		glDisable(GL_DEPTH_TEST);
	}
	// Reset the state
	glBindVertexArray(0);
	glUseProgram(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}


void Shader::renderRT(Vao* mesh, GLuint _id)
{
	// Instruct OpenGL to use our shader program and our VAO
	glUseProgram(getId());
	//glBindVertexArray(vaoId);                             
	glBindVertexArray(mesh->getId());
	//Draw Tex
	glBindTexture(GL_TEXTURE_2D, _id);

	glDrawArrays(GL_TRIANGLES, 0, 6);


	// Reset the state
	glBindVertexArray(0);
	glUseProgram(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

//clear shader
void Shader::clear()
{
	glClearColor(0.5, 0, 1, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
