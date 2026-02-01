#include <Camera.h>
#include <math.h>
#include <trigonometric.hpp>
#include <geometric.hpp>
#include <ext/matrix_transform.hpp>
#include <ext/matrix_clip_space.hpp>
#include <iostream>
#include <Input.h>

Camera::Camera(int width, int height, const glm::vec3& pos): windowWidth{width},
windowHeight{height},
    position(pos),
    front(0.0f, 0.f, -1.f),
    up(0.f, 1.f, 0.f),
    yaw(-90.f),
    pitch(0.f),
    fov(45.f),
    nearPlane(0.1f),
    farPlane(500.0f),
    sensitivity(0.1f),
    firstMouse(true),
    lastX(0.f),
    lastY(0.f),
    speed {2.5f}
{
    recalcDirection();
	updateAspectRatio((float)windowWidth/windowHeight);
}

void Camera::recalcDirection()
{
    glm::vec3 f;
    f.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    f.y = sin(glm::radians(pitch));
    f.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

    front = glm::normalize(f);
    right = glm::normalize(glm::cross(front, { 0.f, 1.f, 0.f }));
    up = glm::normalize(glm::cross(right, front));
}

glm::mat4 Camera::getViewMatrix() const
{
    return glm::lookAt(position, position + front, up);
}

void Camera::updateAspectRatio(float aspectRatio)
{
    aspetRatio = aspectRatio;
    projection = glm::perspective(glm::radians(fov),
        aspectRatio,
        nearPlane,
		farPlane);
}

void Camera::updateFOV(float fov)
{
    this->fov = fov;
    projection = glm::perspective(glm::radians(fov),
        aspetRatio,
        nearPlane,
		farPlane);
}


void Camera::moveForward(float d) { position += front * d; }
void Camera::moveBackward(float d) { position -= front * d; }
void Camera::moveLeft(float d) { position -= right * d; }
void Camera::moveRight(float d) { position += right * d; }
void Camera::moveUp(float d) { position += up * d; }

void Camera::onMouseMove(float x, float y)
{
    if (Input::ResetCameraMouse)
    {
        lastX = x;
        lastY = y;
        firstMouse = false;
        Input::ResetCameraMouse = false;
        return;
    }

    if (firstMouse)
    {
        lastX = x;
        lastY = y;
        firstMouse = false;
        return;
    }

    float dx = x - lastX;
    float dy = lastY - y;

    lastX = x;
    lastY = y;

    dx *= sensitivity;
    dy *= sensitivity;

    yaw += dx;
    pitch += dy;

    if (pitch > 89.f)  pitch = 89.f;
    if (pitch < -89.f) pitch = -89.f;

    recalcDirection();
}

void Camera::onMouseScroll(float yoffset)
{   
    fov -= yoffset;
    if (fov < 45.0f) fov = 45.0f;
    if (fov > 90.f) fov = 90.f;

	updateFOV(this->fov);
}

void Camera::printCameraInfo() const
{
	std::cout << position.x << ", " << position.y << ", " << position.z << std::endl;
	std::cout << "Yaw: " << yaw << ", Pitch: " << pitch << std::endl;
	std::cout << "FOV: " << fov << std::endl;
}
