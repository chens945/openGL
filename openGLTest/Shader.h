#pragma once
#include <GL\glew.h>
#include <string>

class Shader
{
public:
	Shader(const GLchar *vertextPath, const GLchar *fragmentPath);
	void Use();

protected:
	std::string readShaderFile(const char *path);

private:
	GLuint m_program;
};

