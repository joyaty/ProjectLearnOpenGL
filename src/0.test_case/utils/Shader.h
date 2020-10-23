#ifndef SHADER_H

#define SHADER_H

#include <string>

class Shader
{
public:
	Shader();
	bool initialize(const char* strVertexShaderPath, const char* strFragmentShaderPath);

	void use();

	void setBool(const std::string& strUniformName, bool bValue) const;
	void setInt(const std::string& strUniformName, int nValue) const;
	void setFloat(const std::string& strUniformName, float fValue) const;

private:
	unsigned int m_nProgramId;
};

#endif // !SHADER_H