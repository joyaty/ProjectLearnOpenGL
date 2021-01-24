
#include<string>
#include <glad/glad.h>
#include <glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "utils/Shader.h"
#include"utils/stb_image.h"


unsigned int GenerateTexture(const std::string& strImageFile);


static unsigned int VAO_DrawTest3DTransformation;
static unsigned int Texture_Id1;
static unsigned int Texture_Id2;
static Shader shaderTestTransform;

glm::vec3 s_vec3CameraPosition = glm::vec3(0.0f, 0.0f, 5.0f);
glm::vec3 s_vec3CameraDirection = glm::vec3(0.0f, 0.0f, -1.0f);
float s_fFov = 45.0f;

bool InitializeTest3DTransformation()
{
	// 初始化使用的Shader
	bool bInitSuccess = shaderTestTransform.initialize("vertex_shader_with_mvp.vs", "fragment_shader_with_tex_coord.fs");
	if (!bInitSuccess) { return false; }
	// 创建纹理引用ID
	Texture_Id1 = GenerateTexture("container.jpg");
	if (Texture_Id1 == 0) { return false; }
	Texture_Id2 = GenerateTexture("awesomeface.png");
	if (Texture_Id2 == 0) { return false; }

	// 顶点数据
	float vertices[] = {
		// 顶点坐标          // 纹理坐标
		// 前面
		 0.5f,  0.5f,  0.5f, 1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f, 1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f, 0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f, 0.0f, 1.0f,
		// 后面
		 0.5f,  0.5f, -0.5f, 1.0f, 1.0f,		
		 0.5f, -0.5f, -0.5f, 1.0f, 0.0f,		
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,		
		-0.5f,  0.5f, -0.5f, 0.0f, 1.0f,		
		// 左面
		-0.5f,  0.5f,  0.5f, 1.0f, 1.0f,
		-0.5f, -0.5f,  0.5f, 1.0f, 0.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f, 0.0f, 1.0f,
		// 右面
		 0.5f,  0.5f,  0.5f, 1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f, 1.0f, 0.0f,
		 0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
		 0.5f,  0.5f, -0.5f, 0.0f, 1.0f,
		 // 上面
		 0.5f,  0.5f,  0.5f, 1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f, 0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f, 0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f, 1.0f, 1.0f,
		 // 下面
		 0.5f, -0.5f,  0.5f, 1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f, 0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
	};

	// 索引数据
	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0,

		4, 5, 6,	
		6, 7, 4,

		8, 9, 10,
		10, 11, 8,

		12, 13, 14,
		14, 15, 12,

		19, 16, 17,
		17, 18, 19,

		23, 20, 21,
		21, 22, 23,
	};

	// 创建并绑定VAO
	glGenVertexArrays(1, &VAO_DrawTest3DTransformation);
	glBindVertexArray(VAO_DrawTest3DTransformation);

	// 创建绑定VBO，填充数据到VBO指向的显存
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// 配置顶点属性解析指针并启用
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(2);

	// 创建绑定EBO，填充数据到EBO指向的显存
	unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// 解绑VBO, VAO, EBO
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// 分派纹理采样器
	shaderTestTransform.use();
	shaderTestTransform.setInt("uTexture1", 0);
	shaderTestTransform.setInt("uTexture2", 1);

	return true;
}

void DrawTest3DTransformation()
{
	shaderTestTransform.use();
	shaderTestTransform.setFloat("ulinearParam", 0.2f);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, Texture_Id1);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, Texture_Id2);

	glBindVertexArray(VAO_DrawTest3DTransformation);
	// 观察矩阵
	glm::mat4 matView = glm::mat4(1.0f);
	// 摄像机位置, 观察位置, 世界坐标Y轴正方向, 构建变换观察空间的View Matrix
	matView = glm::lookAt(s_vec3CameraPosition, s_vec3CameraPosition + s_vec3CameraDirection, glm::vec3(0.0f, 1.0f, 0.0f));
	shaderTestTransform.setMatrix4f("uMatView", matView);
	// 投影矩阵
	glm::mat4 matProjection = glm::perspective(glm::radians(s_fFov), 16.0f / 9.0f, 0.1f, 100.0f);
	shaderTestTransform.setMatrix4f("uMatProjection", matProjection);

	glm::vec3 cubePositions[] = {
		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
	};

	for (int i = 0; i < 10; ++i)
	{
		// 模型矩阵
		glm::mat4 matModel = glm::mat4(1.0f);
		matModel = glm::translate(matModel, cubePositions[i]);
		matModel = glm::rotate(matModel, (float)glfwGetTime() * (i % 5 + 1) * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0));
		shaderTestTransform.setMatrix4f("uMatModel", matModel);

		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}

	glBindVertexArray(0);
}