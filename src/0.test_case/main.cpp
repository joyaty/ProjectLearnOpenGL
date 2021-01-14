#include<iostream>

#include<glad/glad.h>
#include<glfw3.h>

void Framebuffer_size_callback(GLFWwindow*, int, int);
void ProcessInput(GLFWwindow*);

// 初始化Shader
bool InitializeShader();
// 三角形 VAO和VBO
void InitializeTriangleVertex();
void DrawTriangle();
// 矩形 EBO
void InitializeRectangle();
void DrawRectangle();

// 调试
void EnableWireframwMode();
void DisableWireframwMode();

// 练习1 使用一个VAO和VBO绘制两个三角形
void InitializeTwoTriangleWithOneVBO();
void DrawTwoTriangleWithOneVBO();

// 练习2 使用两个VAO和VBO绘制三角形
void InitializeTwoTriangleWithTwoVBO();
void DrawTwoTriangleWithTwoVBO();

// 通过Uniform渲染三角形颜色
void DrawTriangleWithUniform();

// 添加顶点颜色属性，并绘制三角形
void InitializeTriangleWithMoreAttrib();
void DrawTriangleWithMoreAttrib();

// 绘制带有纹理的矩形
bool InitializeRectangleTexture();
void DrawRectangleTexture();

// 测试三维变换
bool InitializeTest3DTransformation();
void DrawTest3DTransformation();

float s_fLinearParam{ 0.2f };

int main()
{
	// std::cout << "Hello, CMake" << std::endl;

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* pWindow = glfwCreateWindow(1280, 720, "LearnOpenGL", NULL, NULL);
	if (pWindow == NULL)
	{
		std::cout << "Failed to create GLFW window." << std::endl;
		glfwTerminate();

		return -1;
	}

	glfwMakeContextCurrent(pWindow);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glViewport(0, 0, 1280, 720);
	glfwSetFramebufferSizeCallback(pWindow, Framebuffer_size_callback);

	//// 初始化Shader
	//if (!InitializeShader())
	//{
	//	std::cout << "Failed to intialize shaders." << std::endl;
	//	glfwTerminate();

	//	return -1;
	//}

	// 线框模式
	// EnableWireframwMode();

	// 初始化三角形的顶点
	//InitializeTriangleVertex();

	// 初始化矩形的顶点
	//InitializeRectangle();

	// 练习1 初始化两个三角形
	//InitializeTwoTriangleWithOneVBO();

	// 练习2 使用两个VAO和VBO绘制三角形
	//InitializeTwoTriangleWithTwoVBO();

	// 添加顶点颜色属性，并绘制三角形
	//InitializeTriangleWithMoreAttrib();

	// 绘制带有纹理的矩形
	//if (!InitializeRectangleTexture())

	// 测试三维变换
	if (!InitializeTest3DTransformation())
	{
		std::cout << "Failed to intialize draw." << std::endl;
		glfwTerminate();

		return -1;
	}

	glEnable(GL_DEPTH_TEST);
	// 渲染循环
	while (!glfwWindowShouldClose(pWindow))
	{
		// 处理输入
		ProcessInput(pWindow);

		// 渲染指令
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//// 绘制三角形
		//DrawTriangle();

		//// 绘制矩形
		//DrawRectangle();

		//// 练习1 绘制两个三角形
		//DrawTwoTriangleWithOneVBO();

		//// 练习2 使用两个VAO和VBO绘制三角形
		//DrawTwoTriangleWithTwoVBO();

		// 通过uniform渲染三角形颜色
		//DrawTriangleWithUniform();

		// 添加顶点颜色属性绘制三角形
		//DrawTriangleWithMoreAttrib();

		// 绘制带有纹理贴图的矩形
		//DrawRectangleTexture();

		// 测试三维变换
		DrawTest3DTransformation();

		// 检查并调用事件
		glfwPollEvents();

		// 交换缓冲
		glfwSwapBuffers(pWindow);
	}

	glfwTerminate();

	

	return 0;
}

void Framebuffer_size_callback(GLFWwindow* pWindow, int width, int height)
{
	glViewport(0, 0, width, height);
}

void ProcessInput(GLFWwindow* pWindow)
{
	if (glfwGetKey(pWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(pWindow, true);
	}
	else if (glfwGetKey(pWindow, GLFW_KEY_UP) == GLFW_PRESS)
	{
		s_fLinearParam += 0.005f;
		if (s_fLinearParam > 1.0f)
		{
			s_fLinearParam = 0.f;
		}
	}
	else if (glfwGetKey(pWindow, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		s_fLinearParam -= 0.005f;
		if (s_fLinearParam < 0.0f)
		{
			s_fLinearParam = 1.f;
		}
	}
}