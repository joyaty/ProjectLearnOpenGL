
#include <string>
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