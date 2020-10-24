
#include "Shader.h"
#include <glad/glad.h>
#include <fstream>
#include <sstream>
#include <iostream>

Shader::Shader()
{
}

bool Shader::initialize(const char* strVertexShaderPath, const char* strFragmentShaderPath)
{
	// 1. 在文件中编写顶点着色器和片段着色器，传入顶点着色器和片段着色器的文件路径，读入到字符串中
	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;
	// 定义异常
	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try 
	{
		// 打开Shader文件
		vShaderFile.open(strVertexShaderPath);
		fShaderFile.open(strFragmentShaderPath);
		std::stringstream vShaderStream, fShaderStream;
		// 将文件读入流
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();
		// 关闭文件
		vShaderFile.close();
		fShaderFile.close();
		// 流转换为字符串
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCESSFULLY_READ" << std::endl;
		return false;
	}

	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();
	// 2. 将Shader字符串编译为Shader
	unsigned int vertexShader, fragmentShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(vertexShader, 1, &vShaderCode, NULL);
	glShaderSource(fragmentShader, 1, &fShaderCode, NULL);
	glCompileShader(vertexShader);
	glCompileShader(fragmentShader);
	int nSuccess;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &nSuccess);
	if (!nSuccess)
	{
		char infoLog[512];
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		return false;
	}
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &nSuccess);
	if (!nSuccess)
	{
		char infoLog[512];
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		return false;
	}
	// 3. 链接Shader为Program
	m_nProgramId = glCreateProgram();
	glAttachShader(m_nProgramId, vertexShader);
	glAttachShader(m_nProgramId, fragmentShader);
	glLinkProgram(m_nProgramId);
	glGetProgramiv(m_nProgramId, GL_LINK_STATUS, &nSuccess);
	if (!nSuccess)
	{
		char infoLog[512];
		glGetProgramInfoLog(m_nProgramId, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
		return false;
	}

	// 4. 链接成功，shader对象不再需要，可以删除
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	return true;
}

void Shader::use()
{
	glUseProgram(m_nProgramId);
}

void Shader::setBool(const std::string& strUniformName, bool bValue) const
{
	int nLocation = glGetUniformLocation(m_nProgramId, strUniformName.c_str());
	if (nLocation >= 0)
	{
		glUniform1i(nLocation, bValue);
	}
}

void Shader::setInt(const std::string& strUniformName, int nValue) const
{
	int nLocation = glGetUniformLocation(m_nProgramId, strUniformName.c_str());
	if (nLocation >= 0)
	{
		glUniform1i(nLocation, nValue);
	}
}

void Shader::setFloat(const std::string& strUniformName, float fValue) const
{
	int nLocation = glGetUniformLocation(m_nProgramId, strUniformName.c_str());
	if (nLocation >= 0)
	{
		glUniform1f(nLocation, fValue);
	}
}