#include<iostream>

#include<glad/glad.h>
#include<glfw3.h>
#include<glm/glm.hpp>

void Framebuffer_size_callback(GLFWwindow*, int, int);
void MouseMovementEvent_callback(GLFWwindow*, double posX, double posY);
void MouseMiddleScrollEvent_callback(GLFWwindow* pWindow, double offsetX, double offsetY);
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

float s_fLastFrameTime{ 0.f };
float s_fCameraSpeed{ 2.5f };
extern glm::vec3 s_vec3CameraPosition;
extern glm::vec3 s_vec3CameraDirection;
extern float s_fFov;

float s_fMouseLastPosX{ 1280 / 2 };
float s_fMouseLastPosY{ 720 / 2 };
static bool s_bInitializeMouse{ false };
float s_fMouseSensitivity = 0.01f;	// 鼠标灵敏度

// 摄像机俯仰角
float s_CameraPitch = 0.0f;
// 摄像机偏航角
float s_CameraYaw = -90.0f;


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

	// 设置GLFW窗口在Focus时隐藏光标
	// glfwSetInputMode(pWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	// 设置鼠标移动事件监听
	glfwSetCursorPosCallback(pWindow, MouseMovementEvent_callback);
	// 设置鼠标滑轮事件监听
	glfwSetScrollCallback(pWindow, MouseMiddleScrollEvent_callback);

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

void MouseMovementEvent_callback(GLFWwindow*, double posX, double posY)
{
	if (!s_bInitializeMouse)
	{
		s_fMouseLastPosX = posX;
		s_fMouseLastPosY = posY;

		s_bInitializeMouse = true;
	}

	float fOffsetX = posX - s_fMouseLastPosX;
	float fOffsetY = s_fMouseLastPosY - posY;
	s_fMouseLastPosX = posX;
	s_fMouseLastPosY = posY;

	fOffsetX *= s_fMouseSensitivity;
	fOffsetY *= s_fMouseSensitivity;

	s_CameraYaw += fOffsetX;
	s_CameraPitch += fOffsetY;

	// 限制俯仰角范围
	if (s_CameraPitch > 89.0f)
	{
		s_CameraPitch = 89.0f;
	}
	else if (s_CameraPitch < -89.0f)
	{
		s_CameraPitch= -89.0f;
	}

	float fDistance = glm::distance(glm::vec3(0, 0, 0), s_vec3CameraDirection);
	s_vec3CameraDirection.x = fDistance * cos(s_CameraPitch) * cos(s_CameraYaw);
	s_vec3CameraDirection.y = fDistance * sin(s_CameraPitch);
	s_vec3CameraDirection.z = fDistance * cos(s_CameraPitch) * sin(s_CameraYaw);

	s_vec3CameraDirection = glm::normalize(s_vec3CameraDirection);
}

void MouseMiddleScrollEvent_callback(GLFWwindow* pWindow, double offsetX, double offsetY)
{
	// 调整投影矩阵FOV角度大小
	s_fFov -= (float)offsetY;

	if (s_fFov > 60.0f)
	{
		s_fFov = 60.0f;
	}
	else if (s_fFov < 1.0f)
	{
		s_fFov = 1.0f;
	}
}

void ProcessInput(GLFWwindow* pWindow)
{
	float fCurrentFrameTime = glfwGetTime();
	float fDeltaTime = fCurrentFrameTime - s_fLastFrameTime;
	s_fLastFrameTime = fCurrentFrameTime;

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
	else if (glfwGetKey(pWindow, GLFW_KEY_W) == GLFW_PRESS)
	{
		float fCameraSpeed = s_fCameraSpeed * fDeltaTime;
		s_vec3CameraPosition += fCameraSpeed * glm::normalize(s_vec3CameraDirection);

	}
	else if (glfwGetKey(pWindow, GLFW_KEY_S) == GLFW_PRESS)
	{
		float fCameraSpeed = s_fCameraSpeed * fDeltaTime;
		s_vec3CameraPosition -= fCameraSpeed * glm::normalize(s_vec3CameraDirection);
	}
	else if (glfwGetKey(pWindow, GLFW_KEY_A) == GLFW_PRESS)
	{
		float fCameraSpeed = s_fCameraSpeed * fDeltaTime;
		glm::vec3 vec3Right = glm::normalize(glm::cross(s_vec3CameraDirection, glm::vec3(0.0f, 1.0f, 0.0f)));
		s_vec3CameraPosition -= fCameraSpeed * vec3Right;

	}
	else if (glfwGetKey(pWindow, GLFW_KEY_D) == GLFW_PRESS)
	{
		float fCameraSpeed = s_fCameraSpeed * fDeltaTime;
		glm::vec3 vec3Right = glm::normalize(glm::cross(s_vec3CameraDirection, glm::vec3(0.0f, 1.0f, 0.0f)));
		s_vec3CameraPosition += fCameraSpeed * vec3Right;
	}
}