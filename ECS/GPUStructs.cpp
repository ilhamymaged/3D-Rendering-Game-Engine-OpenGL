#include <GpuStructs.h>

void GPUStructs::sendSphere(const Sphere& sphere, uint32_t index)
{
	std::shared_ptr<Shader> shader = ResourceManager::loadShader("ray");
	shader->setVec3(sphere.color, "spheres[" + std::to_string(index) + "].color");
	shader->setVec3(sphere.center, "spheres[" + std::to_string(index) + "].center");
	shader->setFloat(sphere.radius, "spheres[" + std::to_string(index) + "].radius");
	shader->setFloat(sphere.reflectivity, "spheres[" + std::to_string(index) + "].reflectivity");
}

void GPUStructs::sendPlane(const Plane& plane, uint32_t index)
{
	std::shared_ptr<Shader> shader = ResourceManager::loadShader("ray");
	shader->setVec3(plane.color, "planes[" + std::to_string(index) + "].color");
	shader->setVec3(plane.normal, "planes[" + std::to_string(index) + "].normal");
	shader->setVec3(plane.point, "planes[" + std::to_string(index) + "].point");
	shader->setFloat(plane.reflectivity, "planes[" + std::to_string(index) + "].reflectivity");
}

void GPUStructs::sendPointLight(const PointLight& light, uint32_t index)
{
	std::shared_ptr<Shader> shader = ResourceManager::loadShader("ray");
	shader->setVec3(light.position, "pointLights[" + std::to_string(index) + "].position");
	shader->setVec3(light.color, "pointLights[" + std::to_string(index) + "].color");
	shader->setVec3(light.ambient, "pointLights[" + std::to_string(index) + "].ambient");
}
