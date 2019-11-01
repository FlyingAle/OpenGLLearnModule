#include "GLCamera.h"
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/vec4.hpp>
#include <glm/matrix.hpp>
#include <glm/gtc/matrix_transform.hpp>


GLCamera::GLCamera(float x, float y, float z,float center_x,float center_y)
{
	this->cameraPos = glm::vec3(x, y, z);
	this->default_camera_up = glm::vec3(0.0f, 1.0f, 0.0f);
	this->cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	this->lastX = center_x;
	this->lastY = center_y;
}

void GLCamera::setCameraTarget(float x, float y, float z)
{
	//�����ָ���
	this->cameraTarget = glm::vec3(x, y, z);
	//�������������
	this->cameraDirection = glm::normalize(this->cameraPos - this->cameraTarget);
	//�������������(ָ����X��������)
	//glm::cross() ���� ��������������
	this->cameraRight = glm::normalize(glm::cross(this->default_camera_up, this->cameraDirection));
	//�������������(ָ����Y��������)
	this->cameraUp = glm::cross(this->cameraDirection, this->cameraRight);
	this->createLookAtMat();
}

void GLCamera::processInput(GLFWwindow* windows)
{
	float cameraSpeed = 2.5f * deltaTime;
	if (glfwGetKey(windows, GLFW_KEY_W) == GLFW_PRESS) {
		this->cameraPos += cameraSpeed * this->cameraFront;
	}
	else if (glfwGetKey(windows, GLFW_KEY_S) == GLFW_PRESS) {
		this->cameraPos -= cameraSpeed * this->cameraFront;
	}
	else if (glfwGetKey(windows, GLFW_KEY_A) == GLFW_PRESS) {
		this->cameraPos -= glm::normalize(glm::cross(this->cameraFront, this->cameraUp)) * cameraSpeed;
	}
	else if (glfwGetKey(windows, GLFW_KEY_D) == GLFW_PRESS) {
		this->cameraPos += glm::normalize(glm::cross(this->cameraFront, this->cameraUp)) * cameraSpeed;
	}

	cameraPos.y = 0;
	this->createLookAtMat();
}

void GLCamera::processMouseInput(GLFWwindow* windows, float xpos, float ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	//ע���������෴�� ��Ϊy�����Ǵӵײ��������������
	float yoffset = lastY - ypos;

	lastX = xpos;
	lastY = ypos;

	xoffset = sensitivity * xoffset;
	yoffset = sensitivity * yoffset;

	this->yaw += xoffset;
	this->pitch += yoffset;

	if (this->pitch > 89.0f)
	{
		this->pitch = 89.0;
	}
	else if (this->pitch < -89.0f)
	{
		this->pitch = -89.0;
	}

	glm::vec3 front = glm::vec3(0.0f,0.0f,0.0f);
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	cameraFront = glm::normalize(front);
}

glm::mat4 GLCamera::lookAt()
{

	return this->camera_look_at;
}

void GLCamera::setCameraPos(float x, float y, float z)
{
	this->cameraPos.x = x;
	this->cameraPos.y = y;
	this->cameraPos.z = z;
	this->createLookAtMat();
}

void GLCamera::setCurrentFrameTime(float currentFrameTime)
{
	if (lastTime != 0.0f)
	{
		deltaTime = currentFrameTime - lastTime;
	}
	lastTime = currentFrameTime;
}

void GLCamera::mouse_callback(float xpos, float ypos)
{
	float offsetX = xpos - this->lastX;
	float offsetY = this->lastY - ypos;

	this->lastX = xpos;
	this->lastY = ypos;

	float sensitivity = 0.05f;

	offsetX *= sensitivity;
	offsetY *= sensitivity;
}

void GLCamera::processScrollInput(GLFWwindow* windows, double xoffset, double yoffset)
{
	if (this->fov >=1.0f && this->fov <= 45.0f)
	{
		fov -= yoffset * 0.05f;
	}
	if (this->fov <= 1.0f)
	{
		fov = 1.0f;
	}
	if (this->fov >= 45.0f)
	{
		fov = 45.0f;
	}
}

float GLCamera::get_camera_fov()
{
	return this->fov;
}

void GLCamera::createLookAtMat()
{
	this->camera_look_at = glm::lookAt(this->cameraPos,(this->cameraPos + this->cameraFront),this->default_camera_up);
}
