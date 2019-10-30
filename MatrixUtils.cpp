#include "MatrixUtils.h"
#include <glm/gtc/matrix_transform.hpp>

glm::mat4 MatrixUtils::trans(float x, float y, float z)
{
	glm::mat4 trans_mat4 = create_unit_mat4();
	trans_mat4 = glm::translate(trans_mat4, glm::vec3(x, y, z));
	return trans_mat4;
}

glm::mat4 MatrixUtils::trans(glm::vec3 vec)
{
	glm::mat4 trans_mat4 = create_unit_mat4();
	trans_mat4 = glm::translate(trans_mat4, vec);
	return trans_mat4;
}

glm::mat4 MatrixUtils::rotateX(float angle)
{
	return rotate(angle, glm::vec3(1.0f, 0.0f, 0.0f));
}

glm::mat4 MatrixUtils::rotateY(float angle)
{
	return rotate(angle, glm::vec3(0.0f, 1.0f, 0.0f));
}

glm::mat4 MatrixUtils::rotateZ(float angle)
{
	return rotate(angle, glm::vec3(0.0f, 0.0f, 1.0f));
}

glm::mat4 MatrixUtils::scale(float x, float y, float z)
{
	glm::mat4 scale_mat4 = create_unit_mat4();
	scale_mat4 = glm::scale(scale_mat4, glm::vec3(x, y, z));
	return scale_mat4;
}


glm::mat4 MatrixUtils::rotate(float angle, float x, float y, float z)
{
	glm::mat4 rotate_mat4 = create_unit_mat4();
	rotate_mat4 = glm::rotate(rotate_mat4, angle, glm::vec3(x,y,z));
	return rotate_mat4;
}

glm::mat4 MatrixUtils::create_unit_mat4()
{
	return glm::mat4(1.0f);
}

glm::mat4 MatrixUtils::rotate(float angle, glm::vec3 rotate_vec)
{
	glm::mat4 rotate_mat4 = create_unit_mat4();
	rotate_mat4 = glm::rotate(rotate_mat4,angle, rotate_vec);
	return rotate_mat4;
}
