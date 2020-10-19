#include <iostream>
#include <glad/glad.h>

// Vertex Shader Code
const char* vertexShaderSource = "#version 330 core\n"
"layout(location = 0) in vec3 a_position;\n"
"void main()\n"
"{\n"
	"gl_Position = vec4(a_position.x, a_position.y, a_position.z, 1.0);\n"
"}\0";

// Fragment Shader Code
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
	"FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\0";

// shaderProgram
unsigned int shaderProgram{};
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
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	// 绑定Shader源码字符串到生成的Fragment Shader ID
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	// 编译Shader
	glCompileShader(fragmentShader);
	// 检查Shader编译状态，如果错误，输出错误信息
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &nSuccess);
	if (!nSuccess)
	{
		char infoLog[512];
		// 获取Shader的信息日志
		glGetShaderInfoLog(fragmentShader, sizeof(infoLog), NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED \n" << infoLog << std::endl;

		return false;
	}

	// 3. 链接Vertex Shader和Fragment Shader为一个Shader Program，最终渲染时需要使用被激活的Shader Program渲染。
	// 创建Shader Program并生成一个Shader Program ID
	shaderProgram = glCreateProgram();
	// 附加Vertex Shader和Fragment Shader
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	// 链接Shader Program
	glLinkProgram(shaderProgram);
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

	// 4. 链接Shader Program成功，可以删除Vertex Shader和Fragment Shader，不在需要她们了。
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return true;
}

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