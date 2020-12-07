#version 330 core

// 输出变量，片段颜色
out vec4 FragmentColor;

// 输入变量，颜色和纹理坐标
in vec3 vColor;
in vec2 vTexCoord;

// 纹理数据
uniform sampler2D uTexture1;
uniform sampler2D uTexture2;

uniform float ulinearParam;

void main()
{
    // 通过texture函数采样对应纹理坐标的颜色
    // FragmentColor = texture(uTexture1, vTexCoord); // * vec4(vColor, 1.0); 

    FragmentColor = mix(texture(uTexture1, vTexCoord), texture(uTexture2, vTexCoord), ulinearParam);
}