
#include <string>
#include <glad/glad.h>
#define STB_IMAGE_IMPLEMENTATION
#include"utils/stb_image.h"

// Image相对根目录
static const std::string strImageBasePath = "../../../res/images/";

bool LoadImage(const std::string& strImageFile, unsigned char* pData)
{
	int nWidth, nHeight, nNrChannel;
	std::string strImagePath = strImageBasePath + strImageFile;
	pData = stbi_load(strImagePath.c_str(), &nWidth, &nHeight, &nNrChannel, 0);

	return true;
}

bool InitializeTexture(const std::string& strImageFile)
{
	// 创建纹理引用ID
	unsigned int nTextureId;
	glGenTextures(1, &nTextureId);
	// 绑定纹理到目标
	glBindTexture(GL_TEXTURE_2D, nTextureId);

	// 设置纹理环绕方式，超出范围的纹理坐标区域如何填充
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// 设置纹理过滤方式
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	// 加载图片数据
	int nWidth, nHeight, nNrChannel;
	std::string strImagePath = strImageBasePath + strImageFile;
	unsigned char* pImageData = stbi_load(strImagePath.c_str(), &nWidth, &nHeight, &nNrChannel, 0);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, nWidth, nHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, pImageData);
}

bool DrawTexture()
{
	
}

