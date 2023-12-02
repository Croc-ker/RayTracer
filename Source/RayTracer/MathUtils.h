#pragma once
#include <glm/glm.hpp>
inline glm::vec3 cross(const glm::vec3& v1, const glm::vec3& v2)
{
	//https://nic-gamedev.blogspot.com/2011/11/using-vector-mathematics-cross-products.html
	return glm::vec3(
		v1.y * v2.z - v1.z * v2.y,
		v1.z * v2.x - v1.x * v2.z,
		v1.x * v2.y - v1.y * v2.x);
}

template <typename T>
inline T lerp(const T& a, const T& b, float t) {
	return a + t * (b - a);
}

inline float dot(const glm::vec3& v1, const glm::vec3& v2) {
	return v1.x * v2.x +
		v1.y * v2.y +
		v1.z * v2.z;
}