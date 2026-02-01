#include <UILayer.h>

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <Components.h>
#include <GLFW/glfw3.h>
#include <ResourceManager.h>

UILayer::UILayer(entt::registry* registry) : registry(registry) 
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(glfwGetCurrentContext(), true);
    ImGui_ImplOpenGL3_Init("#version 460");
}

UILayer::~UILayer() 
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void UILayer::onUpdate(float deltaTime)
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGui::Begin("Scene Hierarchy", nullptr, ImGuiWindowFlags_NoMove 
        | ImGuiWindowFlags_NoResize);
    drawHierarchy();
    ImGui::End();

    ImGui::Begin("Inspector", nullptr, ImGuiWindowFlags_NoMove
        | ImGuiWindowFlags_NoResize);
    drawInspector();
    ImGui::End();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void UILayer::onEvent(Event& e)
{

}

void UILayer::drawHierarchy()
{
    if (!registry) return;

    if (ImGui::BeginTabBar("MyTabs"))
    {
        if (ImGui::BeginTabItem("Camera"))
        {
            auto view = registry->view<CameraComponent>();
            for (auto entity : view)
            {
                bool isSelected = (entity == selectedEntity);
                if (ImGui::Selectable(("Camera " + std::to_string((uint32_t)entity)).c_str(), isSelected))
                {
                    selectedEntity = entity;
                }
            }
            ImGui::EndTabItem();
        }

        if (ImGui::BeginTabItem("Ray"))
        {
            auto view = registry->view<rayInfo>();
            for (auto entity : view)
            {
                bool isSelected = (entity == selectedEntity);
                if (ImGui::Selectable(("Ray " + std::to_string((uint32_t)entity)).c_str(), isSelected))
                {
                    selectedEntity = entity;
                }
            }
            ImGui::EndTabItem();
        }

        if (ImGui::BeginTabItem("PointLights"))
        {
            if (ImGui::Button("Add PointLight"))
            {
                newEntity = registry->create();
                registry->emplace<PointLight>(newEntity,
                    glm::vec3(0.0f, 5.0f, 0.0f),
                    glm::vec3(1.0f, 1.0f, 1.0f),
                    glm::vec3(0.1)
                );
                selectedEntity = newEntity;
            }


            if (ImGui::Button("Remove PointLight"))
            {
                if (selectedEntity != entt::null && registry->all_of<PointLight>(selectedEntity))
                    registry->destroy(selectedEntity);
            }

			ImGui::Separator();
            auto view = registry->view<PointLight>();
            for (auto entity : view)
            {
                bool isSelected = (entity == selectedEntity);
                if (ImGui::Selectable(("PointLight " + std::to_string((uint32_t)entity)).c_str(), isSelected))
                {
                    selectedEntity = entity;
                }
            }
            ImGui::EndTabItem();
        }

        if (ImGui::BeginTabItem("Planes"))
        {
            if (ImGui::Button("Add Plane"))
            {
                newEntity = registry->create();
                registry->emplace<Plane>(newEntity,
                    glm::vec3(0.0f, 1.0f, 0.0f), // normal
                    glm::vec3(0.0f),             // point
                    glm::vec3(1.0f),             // color
                    0.0f
                );
                selectedEntity = newEntity;
            }

            if (ImGui::Button("Remove Plane"))
            {
                if (selectedEntity != entt::null && registry->all_of<Plane>(selectedEntity))
                    registry->destroy(selectedEntity);
            }

            ImGui::Separator();

            auto view = registry->view<Plane>();
            for (auto entity : view)
            {
                bool isSelected = (entity == selectedEntity);
                if (ImGui::Selectable(("Plane " + std::to_string((uint32_t)entity)).c_str(), isSelected))
                {
                    selectedEntity = entity;
                }
            }
            ImGui::EndTabItem();
        }

        if (ImGui::BeginTabItem("Spheres"))
        {
            if (ImGui::Button("Add Sphere"))
            {
                newEntity = registry->create();
                registry->emplace<Sphere>(newEntity,
                    glm::vec3(0.0f), // center
                    0.5f,            // radius
					0.5f,            // reflectivity
                    glm::vec3(1.0f)  // color
                );
                selectedEntity = newEntity;
            }

            if (ImGui::Button("Remove Sphere"))
            {
				if (selectedEntity != entt::null && registry->all_of<Sphere>(selectedEntity))
                    registry->destroy(selectedEntity);
            }

            ImGui::Separator();

            auto view = registry->view<Sphere>();
            for (auto entity : view)
            {
                bool isSelected = (entity == selectedEntity);
                if (ImGui::Selectable(("Sphere " + std::to_string((uint32_t)entity)).c_str(), isSelected))
                {
                    selectedEntity = entity;
                }
            }
            ImGui::EndTabItem();
        }
		ImGui::EndTabBar();
    }
	
}

void UILayer::drawInspector()
{
	if (!registry || selectedEntity == entt::null) return;

    if (registry->all_of<CameraComponent>(selectedEntity))
    {
        auto& cam = registry->get<CameraComponent>(selectedEntity);
        ImGui::DragFloat("Speed", &cam.camera.speed, 0.1f);
        ImGui::DragFloat3("Position", &cam.camera.position.x, 0.1f);
    }

    if (registry->all_of<rayInfo>(selectedEntity))
    {
        auto& r = registry->get<rayInfo>(selectedEntity);
        ImGui::DragInt("MaxBounces", &r.maxBounces, 1.0f, 1.0f, 100.0f);

    }

    if (registry->all_of<PointLight>(selectedEntity))
    {
        auto& light = registry->get<PointLight>(selectedEntity);
        ImGui::ColorEdit3("Color", &light.color.x, 0.1f);
        ImGui::DragFloat3("Position", &light.position.x, 0.1f);
		ImGui::DragFloat3("Ambient", &light.ambient.x, 0.1f);   
    }

    if (registry->all_of<Plane>(selectedEntity))
    {
        auto& plane = registry->get<Plane>(selectedEntity);
        ImGui::DragFloat3("Normal", &plane.normal.x, 0.1f);
        ImGui::DragFloat3("Point", &plane.point.x, 0.1f);
        ImGui::ColorEdit3("Color", &plane.color.x);
		ImGui::DragFloat("Reflectivity", &plane.reflectivity, 0.1f, 0.0f, 1.0f);
    }

    if (registry->all_of<Sphere>(selectedEntity))
    {
        auto& sphere = registry->get<Sphere>(selectedEntity);
        ImGui::DragFloat3("Center", &sphere.center.x, 0.1f);
        ImGui::DragFloat("Radius", &sphere.radius, 0.1f);
        ImGui::ColorEdit3("Color", &sphere.color.x);
		ImGui::DragFloat("Reflectivity", &sphere.reflectivity, 0.1f, 0.0f, 1.0f);

        if(registry->all_of<Rotator>(selectedEntity))
        {
            auto& rotator = registry->get<Rotator>(selectedEntity);
            //ImGui::Button("Rotate", &rotator.enabled);
            ImGui::DragFloat("Speed", &rotator.speed, 0.1f);
		}

    }
}

