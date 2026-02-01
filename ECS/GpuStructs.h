#pragma once
#include <Components.h>
#include <Shader.h>
#include <ResourceManager.h>

namespace GPUStructs
{
	void sendSphere(const Sphere& sphere,
	uint32_t index);

	void sendPlane(const Plane& plane,
		uint32_t index);	

	void sendPointLight(const PointLight& light,
		uint32_t index);
};


