#pragma once

#include <glm.hpp>

class Camera
{
public:
    Camera(int windowHeight, int windowWidth, const glm::vec3& position = { 0.0f, 0.0f, 3.0f });

    glm::mat4 getViewMatrix() const;
    const glm::mat4& getProjectionMatrix() const { return projection; }

    inline glm::vec3 getPosition() const { return position; }
    inline void setPosition(const glm::vec3& pos) { position = pos; }

    inline glm::vec3 getFront() const { return front; }
    inline glm::vec3 getRight() const { return right; }
    inline glm::vec3 getUp() const { return up; }

	void updateAspectRatio(float aspectRatio);
	void updateFOV(float fov);

public:
    void moveForward(float delta);
    void moveBackward(float delta);
    void moveLeft(float delta);
    void moveRight(float delta);
    void moveUp(float delta);
    
    // mouse look
    void onMouseMove(float x, float y);
    void onMouseScroll(float yoffset);

    void printCameraInfo() const;

public:
    void recalcDirection();

public:
    glm::mat4 projection;

    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;

    float yaw;
    float pitch;

    float fov;
    float nearPlane;
    float farPlane;
	float aspetRatio;

    float sensitivity;
    bool firstMouse;
    float lastX, lastY;

    float speed;

    int windowHeight;
    int windowWidth;
};
