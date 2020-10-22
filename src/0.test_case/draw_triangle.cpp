#include <iostream>
#include <glad/glad.h>

///////////////////////////////////////////////////////////////////////
// Debug

// 启用线框模型
void EnableWireframwMode()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

// 关闭线框模式
void DisableWireframwMode()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}


///////////////////////////////////////////////////////////////////////
// Shader

// Vertex Shader Code
const char* vertexShaderSource = "#version 330 core\n"
"layout(location = 0) in vec3 a_position;\n"
"out vec4 vertexColor;\n"
"void main()\n"
"{\n"
	"gl_Position = vec4(a_position, 1.0);\n"
	"vertexColor = vec4(0.5, 0.0, 0.0, 1.0);\n"
"}\0";

// Fragment Shader Code
const char* fragmentShaderSourceOrange = "#version 330 core\n"
"out vec4 FragColor;\n"
"in vec4 vertexColor;\n"
"void main()\n"
"{\n"
	"FragColor = vertexColor;\n"
"}\0";

// Fragment Shader Code
const char* fragmentShaderSourceYellow = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"FragColor = vec4(1.0f, 1.0f, 0.2f, 1.0f);\n"
"}\0";

// shaderProgram
unsigned int shaderProgram{};
unsigned int shaderProgramArray[2];
// 初始化Shader(创建VertexShader和FragmentShader，链接为ShaderProgram)
bool InitializeShader()
{
	// 1. 编译Vertex Shader
	// 生成Vertex Shader ID
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	// 绑定Shader源码字符串到生成的Vertext Shader ID
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	// 编译Shader
	glCompileShader(vertexShader);
	// 检查Shader编译的状态，如果错误，输出错误信息
	int nSuccess;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &nSuccess);
	if (!nSuccess)
	{
		char infoLog[512];
		// 获取Shader的信息日志
		glGetShaderInfoLog(vertexShader, sizeof(infoLog), NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED \n" << infoLog << std::endl;

		return false;
	}

	// 2. 编译Fragment Shader
	// 生成Fragment Shader ID
	unsigned int fragmentShaderOrange;
	unsigned int fragmentShaderYellow;
	fragmentShaderOrange = glCreateShader(GL_FRAGMENT_SHADER);
	fragmentShaderYellow = glCreateShader(GL_FRAGMENT_SHADER);
	// 绑定Shader源码字符串到生成的Fragment Shader ID
	glShaderSource(fragmentShaderOrange, 1, &fragmentShaderSourceOrange, NULL);
	glShaderSource(fragmentShaderYellow, 1, &fragmentShaderSourceYellow, NULL);
	// 编译Shader
	glCompileShader(fragmentShaderOrange);
	glCompileShader(fragmentShaderYellow);
	// 检查Shader编译状态，如果错误，输出错误信息
	glGetShaderiv(fragmentShaderOrange, GL_COMPILE_STATUS, &nSuccess);
	if (!nSuccess)
	{
		char infoLog[512];
		// 获取Shader的信息日志
		glGetShaderInfoLog(fragmentShaderOrange, sizeof(infoLog), NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED \n" << infoLog << std::endl;

		return false;
	}

	glGetShaderiv(fragmentShaderYellow, GL_COMPILE_STATUS, &nSuccess);
	if (!nSuccess)
	{
		char infoLog[512];
		// 获取Shader的信息日志
		glGetShaderInfoLog(fragmentShaderYellow, sizeof(infoLog), NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED \n" << infoLog << std::endl;

		return false;
	}

	// 3. 链接Vertex Shader和Fragment Shader为一个Shader Program，最终渲染时需要使用被激活的Shader Program渲染。
	// 创建Shader Program并生成一个Shader Program ID
	shaderProgram = glCreateProgram();
	unsigned int shaderProgramYellow = glCreateProgram();
	// 附加Vertex Shader和Fragment Shader
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShaderOrange);
	glAttachShader(shaderProgramYellow, vertexShader);
	glAttachShader(shaderProgramYellow, fragmentShaderYellow);
	// 链接Shader Program
	glLinkProgram(shaderProgram);
	glLinkProgram(shaderProgramYellow);
	// 检查Program链接状态，如果错误，输出错误信息
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &nSuccess);
	if (!nSuccess)
	{
		char infoLog[512];
		// 获取Shader Program的信息日志
		glGetProgramInfoLog(shaderProgram, sizeof(infoLog), NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINK_FAILED \n" << infoLog << std::endl;

		return false;
	}
	glGetProgramiv(shaderProgramYellow, GL_LINK_STATUS, &nSuccess);
	if (!nSuccess)
	{
		char infoLog[512];
		glGetProgramInfoLog(shaderProgramYellow, sizeof(infoLog), NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINK_FAILED \n" << infoLog << std::endl;

		return false;
	}

	// 4. 链接Shader Program成功，可以删除Vertex Shader和Fragment Shader，不在需要她们了。
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShaderOrange);
	glDeleteShader(fragmentShaderYellow);

	shaderProgramArray[0] = shaderProgram;
	shaderProgramArray[1] = shaderProgramYellow;

	return true;
}

///////////////////////////////////////////////////////////////////////
// Draw Triangle

// 定义VAO引用ID
unsigned int VAO;
// 初始化三角形顶点数据（绑定VAO，绑定VBO，拷贝顶点数据到VBO管理的内存中，配置顶点属性指针，最后可以解绑VAO）
void InitializeTriangleVertex()
{
	// 三角形的三个顶点，Normalized Device Coordinate
	float vertices[] =
	{
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.0f,  0.5f, 0.0f
	};

	// 定义VBO引用ID
	unsigned int VBO;
	// 创建VAO
	glGenVertexArrays(1, &VAO);
	// 创建VBO
	glGenBuffers(1, &VBO);

	// 绑定VAO
	glBindVertexArray(VAO);

	// 绑定VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// 拷贝顶点数据到VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// 配置顶点属性指针，启动顶点着色器顶点属性
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// 解绑VBO
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	// 解绑VAO
	glBindVertexArray(0);
}

// 绘制一个三角形
void DrawTriangle()
{
	// 启用要使用的ShaderProgram
	glUseProgram(shaderProgram);
	// 绑定相应的VAO
	glBindVertexArray(VAO);
	// 绘制
	glDrawArrays(GL_TRIANGLES, 0, 3);
	// 解绑VAO
	glBindVertexArray(0);
}


///////////////////////////////////////////////////////////////////////////////////
// Draw Rectangle

unsigned int VAO_Rectangle;
// 初始化绘制矩形，通过EBO存储索引，避免重复顶点重叠
void InitializeRectangle()
{
	// 顶点数据
	float vertices[] = {
		-0.5f, -0.5f, 0.0f,	 // left bottom
		 0.5f, -0.5f, 0.0f,  // right bottom
		 0.5f,  0.5f, 0.0f,	 // right top
		-0.5f,  0.5f, 0.0f   // left top
	};
	// 索引数据
	unsigned int indices[] = {
		0, 1, 3,		// first triangle
		1, 2, 3			// second triangle
	};

	// 生成VAO
	glGenVertexArrays(1, &VAO_Rectangle);

	// 生成VBO
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	// 创建EBO
	unsigned int EBO;
	glGenBuffers(1, &EBO);

	// 绑定VAO
	glBindVertexArray(VAO_Rectangle);

	// 绑定VBO，拷贝顶点数据
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// 绑定EBO，拷贝索引数据
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// 配置顶点属性指针
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// 解绑VBO
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// 解绑VAO
	glBindVertexArray(0);

	// 解绑EBO，目标是GL_ELEMENT_ARRAY_BUFFER时，需要先解绑VAO，避免解绑调用被VAO存储，导致VAO丢失EBO的配置。
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void DrawRectangle()
{
	// 启用相应的Shader
	glUseProgram(shaderProgram);
	// 绑定目标的VAO
	glBindVertexArray(VAO_Rectangle);
	// 绘制索引
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	// 解绑VAO
	glBindVertexArray(0);
}

/////////////////////////////////////////////////////////////////////////////////
// 练习1 通过一个VBO绘制两个三角形
unsigned int VAO_TwoTriangle;
void InitializeTwoTriangleWithOneVBO()
{
	float vertices[] = {
		// first triangle
		-0.9f, -0.5f, 0.0f,
		-0.0f, -0.5f, 0.0f,
		-0.4f,  0.5f, 0.0f,
		// second triangle
		 0.0f, -0.5f, 0.0f,
		 0.9f, -0.5f, 0.0f,
		 0.4f,  0.5f, 0.0f
	};

	glGenVertexArrays(1, &VAO_TwoTriangle);
	glBindVertexArray(VAO_TwoTriangle);

	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);
}

void DrawTwoTriangleWithOneVBO()
{
	glUseProgram(shaderProgram);
	glBindVertexArray(VAO_TwoTriangle);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
}

/////////////////////////////////////////////////////////////////////////////////
// 练习2 通过两个VBO绘制两个三角形

unsigned int VAO_Array[2];
void InitializeTwoTriangleWithTwoVBO()
{
	float vertices[2][9] = {
		// first triangle
		{
			-0.9f, -0.5f, 0.0f,
			-0.0f, -0.5f, 0.0f,
			-0.4f,  0.5f, 0.0f,
		},
		// second triangle
		{
			0.0f, -0.5f, 0.0f,
			0.9f, -0.5f, 0.0f,
			0.4f,  0.5f, 0.0f,
		}
	};

	// 生成两个VAO
	glGenVertexArrays(2, VAO_Array);

	unsigned int VBOs[2];
	glGenBuffers(2, VBOs);

	int nSize = sizeof(VBOs) / sizeof(unsigned int);
	for (int i = 0; i < nSize; ++i)
	{
		glBindVertexArray(VAO_Array[i]);

		glBindBuffer(GL_ARRAY_BUFFER, VBOs[i]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[i]), vertices[i], GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		glBindVertexArray(0);
	}
}

void DrawTwoTriangleWithTwoVBO()
{
	int nSize = sizeof(VAO_Array) / sizeof(unsigned int);
	for (int i = 0; i < nSize; ++i)
	{
		glUseProgram(shaderProgramArray[i]);
		glBindVertexArray(VAO_Array[i]);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);
	}
}