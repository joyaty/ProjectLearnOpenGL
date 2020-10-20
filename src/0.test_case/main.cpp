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

int main()
{
	// std::cout << "Hello, CMake" << std::endl;

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* pWindow = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
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

	glViewport(0, 0, 800, 600);
	glfwSetFramebufferSizeCallback(pWindow, Framebuffer_size_callback);

	// 初始化Shader
	if (!InitializeShader())
	{
		std::cout << "Failed to intialize shaders." << std::endl;
		glfwTerminate();

		return -1;
	}
	//// 初始化三角形的顶点
	//InitializeTriangleVertex();

	//// 初始化矩形的顶点
	//InitializeRectangle();

	//// 练习1 初始化两个三角形
	//InitializeTwoTriangleWithOneVBO();

	// 练习2 使用两个VAO和VBO绘制三角形
	InitializeTwoTriangleWithTwoVBO();

	// 线框模式
	DisableWireframwMode();

	// 渲染循环
	while (!glfwWindowShouldClose(pWindow))
	{
		// 处理输入
		ProcessInput(pWindow);

		// 渲染指令
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//// 绘制三角形
		//DrawTriangle();

		//// 绘制矩形
		//DrawRectangle();

		//// 练习1 绘制两个三角形
		//DrawTwoTriangleWithOneVBO();

		// 练习2 使用两个VAO和VBO绘制三角形
		DrawTwoTriangleWithTwoVBO();

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
}