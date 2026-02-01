#pragma once

#include <glm.hpp>

struct DirectionalLight
{
	glm::vec3 direction;
	glm::mat4 lightSpaceMatrix;
};