#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTextureCoord;

out vec3 vColor;
out vec2 vTexCoord;

uniform mat4 uMatModel;
uniform mat4 uMatView;
uniform mat4 uMatProjection;

void main()
{
    vColor = aColor;
    vTexCoord = aTextureCoord;

    gl_Position = uMatProjection * uMatView * uMatModel * vec4(aPos, 1.0f);
}