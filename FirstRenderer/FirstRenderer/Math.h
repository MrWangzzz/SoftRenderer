#pragma once
#include<glm/glm.hpp>
glm::vec4 Lerp(const glm::vec4& v1, const glm::vec4& v2, const float factor)
{
	return (1.0f - factor) * v1 + v2 * factor;
}
glm::vec2 Lerp(const glm::vec2& v1, const glm::vec2& v2, const float factor)
{
	return (1.0f - factor) * v1 + v2 * factor;
}

glm::vec3 Lerp(const glm::vec3& v1, const glm::vec3& v2, const float factor)
{
	return (1.0f - factor) * v1 + v2 * factor;
}

glm::mat4 GetViewProtMatrix(int ox, int oy, int width, int height)
{
	glm::mat4 result = glm::mat4(1.0f);
	result[0][0] = width / 2.0f;
	result[3][0] = ox + (width / 2.0f);
	result[1][1] = height / 2.0f;
	result[3][1] = oy + (height / 2.0f);
	return result;
}