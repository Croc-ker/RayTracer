#pragma once
#include <glm/glm.hpp>


template <typename T>
inline T lerp(const T& a, const T& b, float t)
{
	return (a * (1 - t)) + (t * b);
}

inline glm::vec3 cross(const glm::vec3& v1, const glm::vec3& v2)
{
	return glm::vec3{ v1.y * v2.z - v1.z * v1.y, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x };
}

inline float dot(const glm::vec3& v1, const glm::vec3& v2)
{
	return (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
}

inline glm::vec3 normalize(const glm::vec3 v)
{
	auto mag = sqrt(pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2));

	glm::vec3 normal = glm::vec3{ v.x / mag, v.y / mag, v.z / mag };
	return normal;
}

inline glm::vec3 reflect(const glm::vec3& v, const glm::vec3& n)
{
	return glm::reflect(v, n);
}