
#include <string>
#include <iostream>
#include <glad/glad.h>
#include <glfw3.h>
#include "utils/Shader.h"
#define STB_IMAGE_IMPLEMENTATION
#include"utils/stb_image.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Image相对根目录
static const std::string strImageBasePath = "../../../res/images/";


// 绘制使用纹理的矩形
static unsigned int VAO_DrawRectangleWithTexture;
static Shader shaderWithTexture;
static unsigned int Texture_Id1;
static unsigned int Texture_Id2;

extern float s_fLinearParam;

unsigned int GenerateTexture(const std::string& strImageFile)
{
	// 创建纹理引用ID
	unsigned int nTextureId;
	glGenTextures(1, &nTextureId);
	// 绑定纹理到目标
	glBindTexture(GL_TEXTURE_2D, nTextureId);

	// 设置纹理环绕方式，超出范围的纹理坐标区域如何填充
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// 指定当环绕方式为CL_CLAMP_TO_BORDER时的边框颜色。
	float borderColor[] = { 0.0f, 1.0f, 1.0f, 1.0f };
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

	// 设置纹理过滤方式
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_REPEAT);

	// 加载图片数据
	int nWidth, nHeight, nNrChannel;
	std::string strImagePath = strImageBasePath + strImageFile;
	unsigned char* pImageData = stbi_load(strImagePath.c_str(), &nWidth, &nHeight, &nNrChannel, 0);
	if (pImageData)
	{
		// 填充图片数据
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, nWidth, nHeight, 0, nNrChannel == 4 ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, pImageData);
		// 自动生成Mipmap
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Load image failed" << std::endl;
		return 0;
	}
	// 加载完成，可以释放内存的纹理数据了
	stbi_image_free(pImageData);

	return nTextureId;
}

bool InitializeRectangleTexture()
{
	// 设置stb_image库加载图片时翻转Y轴
	stbi_set_flip_vertically_on_load(true);

	// 初始化Shader
	bool bSuccess = shaderWithTexture.initialize("vertex_shader_with_tex_coord.vs", "fragment_shader_with_tex_coord.fs");
	if (!bSuccess) { return false; }

	// 创建纹理引用ID
	Texture_Id1 = GenerateTexture("container.jpg");
	if (Texture_Id1 == 0) { return false; }
	Texture_Id2 = GenerateTexture("awesomeface.png");
	if (Texture_Id2 == 0) { return false; }

	// 顶点数据
	float vertices[] = {
		// 顶点坐标		   // 顶点颜色		  // 纹理坐标
		 0.5f,  0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  1.0f, 1.0f,	// 右上角
		 0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f,	// 右下角
		-0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f,  0.0f, 0.0f,	// 左下角
		-0.5f,  0.5f, 0.0f,  1.0f, 1.0f, 0.0f,  0.0f, 1.0f	// 左上角
	};

	// 索引
	unsigned int indices[] = {
		0, 1, 3,	// 第一个三角形
		2, 1, 3		// 第二个三角形		
	};

	// 创建并绑定VAO
	glGenVertexArrays(1, &VAO_DrawRectangleWithTexture);
	glBindVertexArray(VAO_DrawRectangleWithTexture);

	// 创建VBO
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	// 绑定VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// 填充顶点数据
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// 配置顶点属性指针并启用
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(0));					// 顶点坐标属性指针
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float))); // 顶点颜色属性指针
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float))); // 纹理坐标属性指针
	glEnableVertexAttribArray(2);

	// 创建EBO
	unsigned int EBO;
	glGenBuffers(1, &EBO);
	// 绑定EBO到目标
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	// 填充索引数据
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// 解绑VBO
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	// 解绑VAO
	glBindVertexArray(0);
	// 解绑EBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// 分配纹理采样器相应的纹理单元
	shaderWithTexture.use();
	shaderWithTexture.setInt("uTexture1", 0);
	shaderWithTexture.setInt("uTexture2", 1);

	return true;
}

void DrawRectangleTexture()
{
	// 启用Shader
	shaderWithTexture.use();
	shaderWithTexture.setFloat("ulinearParam", s_fLinearParam);

	// 通过Uniform传递变换矩阵
	glm::mat4 transMat{ glm::mat4(1.0f) };
	float fTime = glfwGetTime();
	transMat = glm::rotate(transMat, fTime, glm::vec3(0, 0, 1));
	transMat = glm::scale(transMat, glm::vec3(0.5f, 0.5f, 1.0f));
	transMat = glm::translate(transMat, glm::vec3(0.5f, -0.5f, 0.f));
	shaderWithTexture.setMatrix4f("u_transform", transMat);

	// 绑定纹理
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, Texture_Id1);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, Texture_Id2);

	// 绑定VAO
	glBindVertexArray(VAO_DrawRectangleWithTexture);
	// 绘制矩形
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


	// 通过Uniform传递变换矩阵
	transMat = glm::mat4(1.0f);
	transMat = glm::translate(transMat, glm::vec3(-0.5f, 0.5f, 0.f));
	transMat = glm::rotate(transMat, -fTime, glm::vec3(0, 0, 1));
	transMat = glm::scale(transMat, glm::vec3(glm::sin(fTime), glm::sin(fTime), 1.f));
	shaderWithTexture.setMatrix4f("u_transform", transMat);

	// 绘制矩形
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


	// 解绑VAO
	glBindVertexArray(0);
}

