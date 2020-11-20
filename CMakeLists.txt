cmake_minimum_required(VERSION 3.17)
project(OpenGL)

set(CMAKE_CXX_STANDARD 20)

find_package(OpenGL REQUIRED)

# Turn off redundant targets
set(GLFW_BUILD_DOCS OFF CACHE BOOL "GLFW lib only" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "GLFW lib only" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "GLFW lib only" FORCE)

set(BUILD_UTILS OFF CACHE BOOL "GLEW lib only" FORCE)

add_subdirectory("vendor/glfw")
add_subdirectory("vendor/glew/build/cmake")
add_subdirectory("vendor/glm")

add_executable(OpenGL
               src/Application.cpp
               src/Renderer.cpp
               src/VertexBuffer.cpp
               src/IndexBuffer.cpp
               src/VertexArray.cpp
               src/Shader.cpp
               src/Texture.cpp
               src/Camera.cpp

               vendor/stb_image/stb_image.cpp
)

target_include_directories(OpenGL
                           PRIVATE "vendor/glwf/include"
                           PRIVATE "vendor/glew/include"
                           PRIVATE "vendor/stb_image"
                           PRIVATE "vendor/glm"
)

target_link_libraries(OpenGL ${OPENGL_LIBRARIES} glfw glew_s glm)

target_compile_definitions(OpenGL
                           PRIVATE "GLEW_NO_GLU=1"
                           PRIVATE "GLEW_STATIC=1"
)
