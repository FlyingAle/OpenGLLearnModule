#pragma once

#include <GLFW/glfw3.h>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

class GLCamera
{
public:
	GLCamera(float x, float y, float z,float center_x,float center_y);

	void setCameraTarget(float x, float y, float z);

	void processInput(GLFWwindow* windows);

	void processMouseInput(GLFWwindow* windows,float xpos,float ypos);

	glm::mat4 lookAt();

	void setCameraPos(float x, float y, float z);

	void setCurrentFrameTime(float currentFrameTime);

	void mouse_callback(float xpos, float ypos);

	void processScrollInput(GLFWwindow* windows, double xoffset, double yoffset);

	float get_camera_fov();
private:
	float deltaTime = 0.0f;
	float lastTime = 0.0f;

	float lastX = 400.0f;
	float lastY = 400.0f;

	// Û±Í¡È√Ù∂»
	float sensitivity = 0.05f;

	float yaw = 0;
	float pitch = 0;
	float fov = 45.0f;

	glm::vec3 cameraPos;
	glm::vec3 cameraTarget;
	glm::vec3 cameraDirection;
	glm::vec3 cameraRight;
	glm::vec3 cameraUp;
	glm::vec3 default_camera_up;
	glm::vec3 cameraFront;

	glm::mat4 camera_look_at = glm::mat4();

	bool firstMouse = true;


	void createLookAtMat();

};

