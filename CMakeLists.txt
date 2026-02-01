cmake_minimum_required(VERSION 3.10)
project("GameEngine")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Only build the core libraries
set(BUILD_SHARED_LIBS OFF)      # Optional: static libraries
set(BUILD_EXTRAS OFF)           # Don't build extras like demos/tests
set(BUILD_UNIT_TESTS OFF)       # Don't build tests

# -----------------------
# Dependencies
# -----------------------
add_subdirectory(Vendor/glfw)
add_subdirectory(Vendor/imgui)

# Glad (single C file)
set(GLAD_SRC Vendor/glad/src/glad.c)

# stb
set(STB_SRC Vendor/stb/stb_image.cpp)

# -----------------------
# Engine source files
# -----------------------
file(GLOB_RECURSE ENGINE_SRC
    Core/*.cpp
    ECS/*.cpp
    Systems/*.cpp
    Rendering/*.cpp
    Scene/*.cpp
    Editor/*.cpp
    GameEngine.cpp
)

add_executable(GameEngine
    ${ENGINE_SRC}
    ${GLAD_SRC}
    ${STB_SRC}
)

# -----------------------
# Include dirs
# -----------------------
target_include_directories(GameEngine PUBLIC
    Core
    ECS
    Systems
    Rendering
    Scene
    Editor

    Vendor/entt
    Vendor/glm
    Vendor/glad/include
    Vendor/KHR
    Vendor/stb
    Vendor/assimp/include
)

# -----------------------
# Link deps
# -----------------------
target_link_directories(GameEngine PUBLIC
    Vendor/assimp/lib
)

target_link_libraries(GameEngine PRIVATE
    glfw
    ImGui
    assimp-vc143-mt.lib
)

if (WIN32)
    target_compile_definitions(GameEngine PRIVATE ENGINE_EXPORTS)
    target_link_libraries(GameEngine PRIVATE opengl32)
endif()
