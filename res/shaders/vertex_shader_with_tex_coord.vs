#version 330 core

// 顶点属性
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aVertexCoord;

// 输出变量
out vec3 vColor;
out vec2 vTexCoord;

// Uniform
uniform mat4 u_transform;

void main()
{
    // 输出变量
    vColor = aColor;
    vTexCoord = aVertexCoord;

    // 内建变量
    gl_Position = u_transform * vec4(aPos, 1.0);
}