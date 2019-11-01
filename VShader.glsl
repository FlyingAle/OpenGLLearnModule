#version 330 core
layout (location = 0) in vec3 aPos;   // 位置变量的属性位置值为 0 
layout (location = 1) in vec3 aColor; // 颜色变量的属性位置值为 1
layout (location = 2) in vec2 aTexCoord;//纹理变量的属性位置为  2
layout (location = 3) in vec3 aNormal;//法向量变量的属性位置为  3

out vec3 ourColor; // 向片段着色器输出一个颜色
out vec2 ourTexCoord;//向片段着色器输出一个纹理

out vec3 Normal;

out vec3 outFragPos;

uniform float xOffset;
uniform float yOffset;

uniform mat4 transform;

uniform mat4 model;

uniform mat4 view;

uniform mat4 projection;

void main()
{
    ourColor = aColor; // 将ourColor设置为我们从顶点数据那里得到的输入颜色
	ourTexCoord = aTexCoord;
	Normal = aNormal;
	outFragPos = model * vec4(aPos,1.0);//变换为世界空间坐标
	gl_Position =  projection * view * outFragPos;
}