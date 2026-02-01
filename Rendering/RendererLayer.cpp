#include <RendererLayer.h>
#include <ResourceManager.h>
#include <GpuStructs.h>

static void printMat4(const glm::mat4& mat) {
    for (int i = 0; i < 4; ++i) {
        std::cout << "Row " << i + 1 << ": ";
        for (int j = 0; j < 4; ++j) {
            std::cout << mat[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

RendererLayer::RendererLayer(int windowWidth, int windowHeight): windowWidth{windowWidth}
, windowHeight{ windowHeight }, VAO{ 0 }, VBO{0}
{
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to initialize GLAD\n";
        exit(-1);
    }

    glEnable(GL_DEPTH_TEST);

    std::vector<quadVertex> vertices = 
    {
        {{-1.0f, -1.0f}},
        {{1.0f, -1.0f}},
        {{1.0f, 1.0f}},

        {{-1.0f, -1.0f}},
        {{1.0f, 1.0f}},
        {{-1.0f, 1.0f}}
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(quadVertex), &vertices[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(quadVertex), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void RendererLayer::onUpdate(float dt)
{
    glViewport(0, 0, windowWidth, windowHeight);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for (auto& cmd : renderQueue)
    {
        std::shared_ptr<Shader> rayShader = ResourceManager::loadShader("ray");
        rayShader->use();

        for (int i = 0; i < cmd.spheres.size(); i++)
            GPUStructs::sendSphere(cmd.spheres.at(i), i);

        for (int i = 0; i < cmd.planes.size(); i++)
            GPUStructs::sendPlane(cmd.planes.at(i), i);

		for (int i = 0; i < cmd.pointLights.size(); i++)
			GPUStructs::sendPointLight(cmd.pointLights.at(i), i);
        
        rayShader->setInt(cmd.raySettings.maxBounces, "maxBounces");
		rayShader->setInt(cmd.pointLights.size(), "pointLightCount");
        rayShader->setInt(cmd.spheres.size(), "sphereSize");
        rayShader->setInt(cmd.planes.size(), "planeSize"); 
        rayShader->setVec3(cmd.camera.getPosition(), "cameraPos");
        rayShader->setMat4(glm::inverse(cmd.camera.getProjectionMatrix()), "invProjection");
        rayShader->setMat4(glm::inverse(cmd.camera.getViewMatrix()), "invView");
        rayShader->setFloat(windowWidth, "resX");
        rayShader->setFloat(windowHeight, "resY");

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);
    }

    renderQueue.clear();
}

RendererLayer::~RendererLayer()
{
    renderQueue.clear();
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &VAO);
}

void RendererLayer::submit(const RenderCommand& renderCmd)
{
    renderQueue.push_back(renderCmd);
}

