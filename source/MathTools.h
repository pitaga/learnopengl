#pragma once
#include <glm/glm/glm.hpp>
#include <glm/glm/ext.hpp>

namespace GLMath
{
	glm::mat4 createTransformMatrix(const glm::vec3& translate, const float rx, const float ry, const float rz, const float scale)
	{
		glm::mat4 matrix = glm::mat4(1.0f);
		matrix = glm::rotate(matrix, glm::radians(rx), glm::vec3(1.0f, 0.0f, 0.0f));
		matrix = glm::rotate(matrix, glm::radians(ry), glm::vec3(0.0f, 1.0f, 0.0f));
		matrix = glm::rotate(matrix, glm::radians(rz), glm::vec3(0.0f, 0.0f, 1.0f));
		matrix = glm::scale(matrix, scale * glm::vec3(1.0f));
		return matrix;
	}
}