#version 330 core

out vec4 FragColor;
in vec3 v_vertexColor;

void main() 
{
    FragColor = vec4(v_vertexColor, 1.0f);
}