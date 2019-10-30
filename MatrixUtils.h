#pragma once
#include <glm/glm.hpp>
#include <glm/mat4x4.hpp>
class MatrixUtils
{
public:
	glm::mat4 trans(float x, float y, float z);

	glm::mat4 trans(glm::vec3 vec);

	glm::mat4 rotateX(float angle);

	glm::mat4 rotateY(float angle);

	glm::mat4 rotateZ(float angle);

	glm::mat4 scale(float x, float y, float z);

	glm::mat4 rotate(float angle, float x, float y, float z);

private:
	glm::mat4 create_unit_mat4();

	glm::mat4 rotate(float angle, glm::vec3 rotate_vec);
};

