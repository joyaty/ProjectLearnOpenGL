#ifndef SHADER_H

#define SHADER_H

#include <string>
#include <glm/glm.hpp>

class Shader
{
public:
	Shader();
	bool initialize(const char* strVertexShaderPath, const char* strFragmentShaderPath);

	void use();

	void setBool(const std::string& strUniformName, bool bValue) const;
	void setInt(const std::string& strUniformName, int nValue) const;
	void setFloat(const std::string& strUniformName, float fValue) const;
	void setMatrix4f(const std::string& strUniformName, const glm::mat4& mat4Transform);

private:
	unsigned int m_nProgramId;
};

#endif // !SHADER_H