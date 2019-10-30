#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <memory>
#include <stb_image.h>
#include "Shader.h"
#include "MatrixUtils.h"
#include "GLCamera.h"

#include <glm/glm.hpp>
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp>


float vertices[] = {
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f
};

float texCoords[] = {
	0.0f, 0.0f, // 左下角
	1.0f, 0.0f, // 右下角
	0.5f, 1.0f // 上中
};

unsigned int indices[] = {
	0, 1, 3, // first triangle
	1, 2, 3  // second triangle
};

GLFWwindow* createGLWindow() {
	//创建一个800*600名字为LearnOpenGLWindow的OpenGL窗口
	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGLTexWindow", nullptr, nullptr);

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


int main() {
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	GLFWwindow* current_window = createGLWindow();

	if (current_window == nullptr)
	{
		return -1;
	}
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -2;
	}
	glViewport(0, 0, 800, 600);

	glfwSetInputMode(current_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	auto glProgram = std::make_shared<Shader>("VShader-Light.glsl", "FShader.glsl");
	auto matrix_utils = std::make_shared<MatrixUtils>();

	auto gl_camera = std::make_shared<GLCamera>(0.0f, 0.0f, 3.0f, 400, 300);

	gl_camera->setCameraTarget(0.0f, 0.0f, 0.0f);

	unsigned int VBO;
	unsigned int VAO;
	unsigned int EBO;

	unsigned int transform_mat_loca;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &EBO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glEnable(GL_DEPTH_TEST);

	glm::vec3 lightColor = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 toyColor = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 resultColor = lightColor * toyColor;

	glProgram->use();

	transform_mat_loca = glGetUniformLocation(glProgram->ID, "transform");

	while (!glfwWindowShouldClose(current_window))
	{
		glClearColor(0.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glProgram->use();

		glm::mat4 view = gl_camera->lookAt();
		glUniformMatrix4fv(glGetUniformLocation(glProgram->ID, "view"), 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(glGetUniformLocation(glProgram->ID, "projection"), 1, GL_FALSE, glm::value_ptr(glm::perspective(45.0f, 800.0f / 600.0f, 0.1f, 100.0f)));

		glBindVertexArray(VAO);

	}
}

