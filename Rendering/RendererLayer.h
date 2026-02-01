#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <Layer.h>
#include <vector>
#include <Model.h>
#include <Shader.h>
#include <Lights.h>
#include <vector>
#include <Camera.h>
#include <Components.h>

struct RenderCommand
{
    Camera& camera;
    std::vector<Sphere> spheres;
    std::vector<Plane> planes;
	std::vector<PointLight> pointLights;
	rayInfo raySettings;
};

class RendererLayer : public Layer
{
public:
    RendererLayer(int windowWidth, int windowHeight);
    ~RendererLayer();

    void onUpdate(float deltaTime) override;
    void submit (const RenderCommand& renderFunc);
private:
	std::vector<RenderCommand> renderQueue;

    GLuint VBO;
    GLuint VAO;
public: 
    int windowWidth;
    int windowHeight;
};
