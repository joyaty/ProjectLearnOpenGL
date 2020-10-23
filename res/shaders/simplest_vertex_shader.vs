#version 330 core

layout(location = 0) in vec3 a_position;
layout(location = 1) in vec3 a_vertexColor;

out vec3 v_vertexColor;

void main()
{
    gl_Position = vec4(a_position, 1.0);
    v_vertexColor = a_vertexColor;
}