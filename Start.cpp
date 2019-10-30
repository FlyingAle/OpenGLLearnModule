#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <memory>
#include "Shader.h"

//回调函数声明
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

GLFWwindow* createGLWindow();

void processInput(GLFWwindow* window);

unsigned int createVBO(const float vertice[]);

unsigned int loadShader(const char* shader, GLint shader_type);

bool checkSuccess(unsigned int shader_id);

unsigned int createGLProgram(unsigned int shader_id, unsigned int fragment_id);

unsigned int createVAO();



//float vertices[] = {
//	   -0.5f, -0.5f, 0.0f, // left  
//		0.5f, -0.5f, 0.0f, // right 
//		0.0f,  0.5f, 0.0f  // top   
//};

float vertices[] = {
	0.5f, 0.5f, 0.0f,  1.0f,0.0f,0.0f,  // 右上角
	0.5f, -0.5f, 0.0f, 0.0f,1.0f,0.0f, // 右下角
	-0.5f, -0.5f, 0.0f, 0.0f,0.0f,1.0f, // 左下角
	-0.5f, 0.5f, 0.0f  ,1.0f,1.0f,1.0f // 左上角
};

float y_vertices[] = {
	0.4f,0.3f,0.0f,
	0.1f,-0.1f,0.0f,
	-0.6f,-0.6f,0.0f,
	-0.8f,0.4f,0.0f
};

unsigned int indices[] = { // 注意索引从0开始! 
	0, 1, 3, // 第一个三角形
	1, 2, 3  // 第二个三角形
};

const char* vertex_shader = "#version 330 core\n layout (location = 0) in vec3 aPos;\n layout (location = 1) in vec3 aColor;\n out vec3 ourColor;\n void main()\n {\n gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n ourColor = aColor;\n}";

const char* fragment_shader = "#version 330 core\n out vec4 FragColor;\n in vec3 ourColor;\n void main()\n {\n  FragColor = vec4(ourColor,1.0f);\n } ";

const char* yellow_fragment_shader = "#version 330 core\n out vec4 FragColor;\n  void main()\n {\n  FragColor = vec4(0.5f, 0.2f, 0.5f, 1.0f);\n } ";




int main() {

	unsigned int VBO;
	unsigned int VAO;
	unsigned int EBO;
	unsigned int vertex_shader_id;
	unsigned int fragment_shader_id;
	unsigned int program_shader_id;

	unsigned int y_vertex_shader_id;
	unsigned int y_fragment_shader_id;
	unsigned int y_program_shader_id;

	//初始化GLFW
	glfwInit();
	//设置主版本号为3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	//设置次版本号为3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	GLFWwindow* current_window = createGLWindow();
	if (current_window == nullptr)
	{
		return -1;
	}
	//调用任何OpenGL的函数之前我们需要初始化GLAD GLAD管理OpenGL函数指针
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -2;
	}
	//设置视口 
	glViewport(0, 0, 800, 600);

	glfwSetFramebufferSizeCallback(current_window, framebuffer_size_callback);

	int nrAttributes;
	//获取顶点属性数量,至少有16个包含4分量的顶点属性,通常会返回16,有些硬件也会支持更多的顶点属性数量	
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS,&nrAttributes); 

	std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;

	vertex_shader_id = loadShader(vertex_shader, GL_VERTEX_SHADER);
	fragment_shader_id = loadShader(fragment_shader, GL_FRAGMENT_SHADER);
	program_shader_id = createGLProgram(vertex_shader_id, fragment_shader_id);

	y_vertex_shader_id = loadShader(vertex_shader, GL_VERTEX_SHADER);
	y_fragment_shader_id = loadShader(yellow_fragment_shader, GL_FRAGMENT_SHADER);
	y_program_shader_id = createGLProgram(y_vertex_shader_id,y_fragment_shader_id);

	auto glProgram = std::make_shared<Shader>("VShader.glsl","FShader.glsl");




	unsigned int YVAO;
	unsigned int YEBO;
	unsigned int YVBO;



	////着色器对象链接成功后 删除着色器对象
	glDeleteShader(vertex_shader_id);
	glDeleteShader(fragment_shader_id);
	glDeleteShader(y_vertex_shader_id);
	glDeleteShader(y_fragment_shader_id);

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &EBO);
	glGenBuffers(1, &VBO);
	//// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);



	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


	//链接顶点属性
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	glGenVertexArrays(2, &YVAO);
	glGenBuffers(2,&YEBO);
	glGenBuffers(2, &YVBO);

	glBindVertexArray(YVAO);

	glBindBuffer(GL_ARRAY_BUFFER,YVBO);
	glBufferData(GL_ARRAY_BUFFER,sizeof(y_vertices),y_vertices,GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, YEBO);

	glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices),indices,GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	//改变绘制模式
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	float timeValue;
	float greenColor;
	float redColor;
	float blueColor;

	while (!glfwWindowShouldClose(current_window)) {
		processInput(current_window);
		//设置清屏颜色,并执行清屏
		glClearColor(0.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		timeValue = glfwGetTime();
		greenColor = (sin(timeValue) / 2.0f) + 0.5f;
		redColor = (sin(timeValue) / 3.0f) + 0.5f;
		blueColor = (sin(timeValue) / 4.0f) + 0.5f;

		int vertexColorLocation = glGetUniformLocation(program_shader_id, "ourColor");

		glUseProgram(program_shader_id);
		glUniform4f(vertexColorLocation, redColor, greenColor,blueColor, 1.0f);
		glBindVertexArray(VAO);
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glUseProgram(y_program_shader_id);
		glBindVertexArray(YVAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glProgram->use();
		glProgram->setFloat("xOffset", 0.3);
		glProgram->setFloat("yOffset",-0.6);
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glUseProgram(0);

		glfwSwapBuffers(current_window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteVertexArrays(2, &YVAO);
	glDeleteBuffers(2, &YVBO);
	glDeleteBuffers(2, &YEBO);

	//正确的回收资源
	glfwTerminate();

	return 0;
}

unsigned int createVAO() {
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	return VAO;
}

unsigned int createGLProgram(unsigned int shader_id, unsigned int fragment_id) {
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


bool checkSuccess(unsigned int shader_id) {
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

unsigned int loadShader(const char* shader, int shader_type) {
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

unsigned int createVBO(const float vertice[]) {
	unsigned int VBO;

	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertice), vertice, GL_STATIC_DRAW);

	return VBO;
}

void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		//改变视窗状态
		glfwSetWindowShouldClose(window, true);
	}
}

//回调函数
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

GLFWwindow* createGLWindow() {
	//创建一个800*600名字为LearnOpenGLWindow的OpenGL窗口
	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGLWindow", nullptr, nullptr);

	if (window == nullptr)
	{
		//如果窗口创建失败 输出log
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return nullptr;
	}
	//通知GLFW将当前窗口的上下文设置为当前线程的主上下文
	glfwMakeContextCurrent(window);
	return window;
}