#include "Shader.h"
#include <fstream>
#include <sstream>
#include <iostream>

Shader::Shader(const GLchar *vertextPath, const GLchar * fragmentPath)
{
	std::string vertexCode = readShaderFile(vertextPath);
	std::string fragmentCode = readShaderFile(fragmentPath);
	const GLchar *vShaderCode = vertexCode.c_str();
	const GLchar *fShaderCode = fragmentCode.c_str();
	GLuint vertex, fragment;
	GLint success;
	GLchar infoLog[512];
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertex, sizeof(infoLog), NULL, infoLog);
		std::cout << "ERRO::SHADER::VERTEX::COMPILATION_FAILED:\n	" << infoLog << std::endl;
	}
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragment, sizeof(infoLog), NULL, infoLog);
		std::cout << "ERRO::SHADER::FRAGMENT::COMPILATION_FAILED:\n	" << infoLog << std::endl;
	}

	m_program = glCreateProgram();
	glAttachShader(m_program, vertex);
	glAttachShader(m_program, fragment);
	glLinkProgram(m_program);
	glGetProgramiv(m_program, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(m_program, sizeof(infoLog), NULL, infoLog);
		std::cout << "ERRO::SHADER::PROGRAM::LINK_FAILED:\n		" << infoLog << std::endl;
	}
	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

void Shader::Use()
{
	glUseProgram(m_program);
}

GLuint Shader::GetProgram()
{
	return m_program;
}

std::string Shader::readShaderFile(const char * path)
{
	if (path == nullptr)
		return std::string();

	std::string content;
	std::ifstream ifs(path, std::ios::in);
	if (ifs.is_open())
	{
		std::stringstream os;
		os << ifs.rdbuf();
		ifs.close();
		content = os.str();
	}
	else
	{
		std::cout << "ERRO::SHADER::READ:FILE:FILED:	" << path << std::endl;
	}
	return content;
}
