#include "Shader.h"


Shader::Shader(const GLchar* vertexPath, const GLchar* fragmentPath)
{
	// 1. 从文件路径中获取顶点/片段着色器
	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;

	// 保证ifstream对象可以抛出异常：
	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try
	{
		//打开文件
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);
		std::stringstream vShaderStream, fShaderStream;
		//读取文件数据内容到缓冲流中
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();
		//关闭文件
		vShaderFile.close();
		fShaderFile.close();

		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch (const std::exception&)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}
	//std::string转换为char指针
	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();

	ID = createGLProgram(loadShader(vShaderCode,GL_VERTEX_SHADER),loadShader(fShaderCode,GL_FRAGMENT_SHADER));
}

Shader::~Shader()
{
}

void Shader::use()
{
	glUseProgram(ID);
}

void Shader::setBool(const std::string& name, bool value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::setInt(const std::string& name, int value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat(const std::string& name, float value) const
{
	glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

unsigned int Shader::loadShader(const char* shader, GLint shader_type)
{
	unsigned int vertexShader;
	vertexShader = glCreateShader(shader_type);
	glShaderSource(vertexShader, 1, &shader, nullptr);
	glCompileShader(vertexShader);

	if (!checkSuccess(vertexShader))
	{
		return -1;
	}
	return vertexShader;
}

unsigned int Shader::createGLProgram(unsigned int shader_id, unsigned int fragment_id)
{
	unsigned int shader_program_id;
	int success;
	char infoLog[512];
	shader_program_id = glCreateProgram();
	glAttachShader(shader_program_id, shader_id);
	glAttachShader(shader_program_id, fragment_id);
	glLinkProgram(shader_program_id);
	glGetShaderiv(shader_program_id, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shader_program_id, 512, nullptr, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::COMPILATION_FAILED\n" << infoLog << std::endl;
		return -1;
	}
	return shader_program_id;
}

bool Shader::checkSuccess(unsigned int shader_id)
{
	int success;
	char infoLog[512];
	glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(shader_id, 512, nullptr, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		return false;

	}
	return true;
}
