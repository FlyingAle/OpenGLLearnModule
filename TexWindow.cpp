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




//回调函数声明
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

void mouse_callback(GLFWwindow* window, double xpos, double ypos);

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

GLFWwindow* createGLWindow();

void processInput(GLFWwindow* window);

unsigned int createTexId();

unsigned int createTexture(std::string imgPath);

float texCoords[] = {
	0.0f, 0.0f, // 左下角
	1.0f, 0.0f, // 右下角
	0.5f, 1.0f // 上中
};

//float vertices[] = {
//	// positions          // colors           // texture coords
//	 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
//	 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
//	-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
//	-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
//};

float vertices[] = {
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};


glm::vec3 cubePositions[] = {
  glm::vec3(0.0f,  0.0f,  0.0f),
  glm::vec3(2.0f,  5.0f, -15.0f),
  glm::vec3(-1.5f, -2.2f, -2.5f),
  glm::vec3(-3.8f, -2.0f, -12.3f),
  glm::vec3(2.4f, -0.4f, -3.5f),
  glm::vec3(-1.7f,  3.0f, -7.5f),
  glm::vec3(1.3f, -2.0f, -2.5f),
  glm::vec3(1.5f,  2.0f, -2.5f),
  glm::vec3(1.5f,  0.2f, -1.5f),
  glm::vec3(-1.3f,  1.0f, -1.5f)
};

unsigned int indices[] = {
	0, 1, 3, // first triangle
	1, 2, 3  // second triangle
};

std::shared_ptr<GLCamera> current_camera;


int main() {
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

	glfwSetInputMode(current_window,GLFW_CURSOR,GLFW_CURSOR_DISABLED);




	auto glProgram = std::make_shared<Shader>("VShader.glsl", "FShader.glsl");

	auto matrix_utils = std::make_shared<MatrixUtils>();

	auto gl_camera = std::make_shared<GLCamera>(0.0f,0.0f,3.0f,400,300);

	current_camera = gl_camera;

	gl_camera->setCameraTarget(0.0f,0.0f,0.0f);
	//设置鼠标位置捕捉回调
	glfwSetCursorPosCallback(current_window, mouse_callback);

	glfwSetScrollCallback(current_window, scroll_callback);

	unsigned int VBO;
	unsigned int VAO;
	unsigned int EBO;
	unsigned int textureId_1;
	unsigned int textureId_2;

	unsigned int transform_mat_loca;

	textureId_1 = createTexture("test_texture.jpg");
	textureId_2 = createTexture("test_texture2.jpg");

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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	//glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	//改变绘制模式
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glEnable(GL_DEPTH_TEST);

	float timeValue;
	float greenColor;
	float redColor;
	float blueColor;

	glProgram->use();
	glUniform1i(glGetUniformLocation(glProgram->ID, "texture1"), 0); // 手动设置
	glProgram->setInt("texture2", 1);

	transform_mat_loca = glGetUniformLocation(glProgram->ID, "transform");

	float opacityPercent = 0.1f;


	while (!glfwWindowShouldClose(current_window)) {
		processInput(current_window);
		gl_camera->processInput(current_window);
		//设置清屏颜色,并执行清屏
		glClearColor(0.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		gl_camera->setCurrentFrameTime(glfwGetTime());

		timeValue = glfwGetTime();
		greenColor = (sin(timeValue) / 2.0f) + 0.5f;
		redColor = (sin(timeValue) / 3.0f) + 0.5f;
		blueColor = (sin(timeValue) / 4.0f) + 0.5f;

		int vertexColorLocation = glGetUniformLocation(glProgram->ID, "ourFColor");
		int opacityPercentLocation = glGetUniformLocation(glProgram->ID, "opacityPercent");
		//std::cout << "opacityPercent : " << opacityPercent << std::endl;
		glUniform4f(vertexColorLocation, redColor, greenColor, blueColor, 1.0f);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textureId_1);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, textureId_2);
		glProgram->use();
		glUniform1f(opacityPercentLocation, opacityPercent/10);

		//matrix = matrix * matrix_utils->trans(opacityPercent / 40, 0.0f, 0.0f);
		//glUniformMatrix4fv(transform_mat_loca, 1, GL_FALSE, glm::value_ptr(matrix));
		
		//glUniformMatrix4fv(glGetUniformLocation(glProgram->ID, "view"), 1, GL_FALSE, glm::value_ptr(matrix_utils->trans(0.0f, 0.0f, -3.0f)));
		float radius = 15.0f;
		float camX = sin(glfwGetTime()) * radius;
		float camZ = cos(glfwGetTime()) * radius;
		//glm::mat4 view = glm::lookAt(glm::vec3(camX,0.0,camZ),glm::vec3(0.0f,0.0f,0.0f),glm::vec3(0.0f,4.0f,0.0f));
		//gl_camera->setCameraPos(camX,0.0f,camZ);
		glm::mat4 view = gl_camera->lookAt();
		glUniformMatrix4fv(glGetUniformLocation(glProgram->ID, "view"), 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(glGetUniformLocation(glProgram->ID, "projection"), 1, GL_FALSE, glm::value_ptr(glm::perspective(gl_camera->get_camera_fov(), 800.0f / 600.0f, 0.1f, 100.0f)));
		glBindVertexArray(VAO);
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		for (unsigned int i = 0; i < 10; i++)
		{
			glm::mat4 matrix = matrix_utils->rotate(glm::radians((i+1) * (i+1) * 0.1f * 20.0f) * glfwGetTime() , 1.0f, 0.3f, 0.5f);
			matrix = matrix * matrix_utils->trans(cubePositions[i]);
			glUniformMatrix4fv(glGetUniformLocation(glProgram->ID, "model"), 1, GL_FALSE, glm::value_ptr(matrix));
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		opacityPercent = opacityPercent + 0.1;
		if (opacityPercent > 1.1f)
		{
			opacityPercent = 0.1f;
		}

		glUseProgram(0);

		glfwSwapBuffers(current_window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	int i[5][5];

	return 0;
}

unsigned int createTexture(std::string imgPath) {
	unsigned int textureId = createTexId();

	int width, height, nrChannels;
	unsigned char* data = stbi_load(imgPath.c_str(), &width, &height, &nrChannels, 0);

	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
		return -1;
	}
	stbi_image_free(data);
	return textureId;

}

unsigned int createTexId() {

	unsigned int textureId;
	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	float borderColor[] = { 1.0f,1.0f,0.0f,1.0f };
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
	return textureId;
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

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	current_camera->processMouseInput(window, xpos, ypos);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	current_camera->processScrollInput(window, xoffset, yoffset);
}

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