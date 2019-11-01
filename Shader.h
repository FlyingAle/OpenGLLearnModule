#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>; // 包含glad来获取所有的必须OpenGL头文件

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glm\fwd.hpp>
#pragma once
class Shader
{
public:

	unsigned int ID;

	Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
	~Shader();
	void use();

	void setBool(const std::string &name,bool value) const;
	void setInt(const std::string &name, int value) const;
	void setFloat(const std::string& name, float value) const;

	void setVec3(const std::string& name, float x, float y, float z) const;
	
private:

	unsigned int loadShader(const char* shader, GLint shader_type);
	unsigned int createGLProgram(unsigned int shader_id, unsigned int fragment_id);
	bool checkSuccess(unsigned int shader_id);
};

#endif

