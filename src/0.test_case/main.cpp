#include<iostream>

#include<glad/glad.h>
#include<glfw3.h>

void Framebuffer_size_callback(GLFWwindow*, int, int);
void ProcessInput(GLFWwindow*);

bool InitializeShader();
void DrawTriangle();

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

	if (!InitializeShader())
	{
		std::cout << "Failed to intialize shaders." << std::endl;
		glfwTerminate();

		return -1;
	}

	while (!glfwWindowShouldClose(pWindow))
	{
		// 处理输入
		ProcessInput(pWindow);

		// 渲染指令
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		DrawTriangle();

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