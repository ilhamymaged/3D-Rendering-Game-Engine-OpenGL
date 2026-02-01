#pragma once

#include <glm.hpp>
#include <Model.h>
#include <Terrain/Terrain.h>
#include <Camera.h>

struct rayInfo
{
    int maxBounces;
};

struct PointLight
{
    glm::vec3 position;
    glm::vec3 color;
    glm::vec3 ambient;
};

struct Sphere
{
    glm::vec3 color;
    glm::vec3 center;
    float radius;
	float reflectivity;

    Sphere(const glm::vec3& c, float r, float reflect, const glm::vec3& col)
        : center(c), radius(r), color(col), reflectivity(reflect) {}
};

struct Plane
{
    glm::vec3 normal;
    glm::vec3 color;
    glm::vec3 point;
    float reflectivity;
};

struct CameraComponent
{
    Camera& camera;
};

struct BoxCollider
{
    glm::vec3 size;
    glm::vec3 center;   
    bool debug = false;
};

struct TerrainCollider
{
    std::shared_ptr<Terrain> terrain;
};

struct RigidBody
{
    float mass = 1.0f;
    glm::vec3 velocity{ 0.0f };
    float radius = 0.5f; 
};

struct Rotator
{
    bool enabled = false;
    float speed = 10.0f;
};

struct Transform 
{
    glm::vec3 position{ 0.0f };
    glm::vec3 rotation{ 0.0f };
    glm::vec3 scale{ 1.0f };

    glm::mat4 getModelMatrix() const 
    {
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, position);
        model = glm::rotate(model, rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
        model = glm::rotate(model, rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::rotate(model, rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
        model = glm::scale(model, scale);
        return model;
	}
};

struct Player
{
    Transform t;
};

struct Renderable
{
    std::shared_ptr<Model> model;
};

