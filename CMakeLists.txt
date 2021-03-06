cmake_minimum_required(VERSION 3.17)
project(OpenGL)

set(CMAKE_CXX_STANDARD 20)

find_package(OpenGL REQUIRED)

set(BUILD_SHARED_LIBS ON CACHE BOOL "" FORCE)

# Turn off redundant targets
set(GLFW_BUILD_DOCS OFF CACHE BOOL "GLFW lib only" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "GLFW lib only" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "GLFW lib only" FORCE)

set(BUILD_UTILS OFF CACHE BOOL "GLEW lib only" FORCE)

set(ASSIMP_NO_EXPORT ON CACHE BOOL "Importers only" FORCE)
set(ASSIMP_BUILD_TESTS OFF CACHE BOOL "Lib only" FORCE)
set(ASSIMP_BUILD_ALL_IMPORTERS_BY_DEFAULT OFF CACHE BOOL "Too much" FORCE)
set(ASSIMP_BUILD_OBJ_IMPORTER ON CACHE BOOL "" FORCE)

# Third-party libraries
add_subdirectory("vendor/glfw")
add_subdirectory("vendor/glew/build/cmake")
add_subdirectory("vendor/glm")
add_subdirectory("vendor/stb_image")
add_subdirectory("vendor/imgui")
add_subdirectory("vendor/assimp")

set(OPENGL_SOURCES
    src/Application.cpp
    src/Renderer.cpp
    src/VertexBuffer.cpp
    src/ElementBuffer.cpp
    src/VertexArray.cpp
    src/Shader.cpp
    src/Texture.cpp
    src/PerspectiveCamera.cpp
    src/OrthographicCamera.cpp
    src/Mesh.cpp
    src/Model.cpp
    tests/Test.cpp
    tests/TestMultipleLights.cpp
    tests/TestTriangle.cpp
    tests/TestBatchRendering.cpp
    tests/TestModelLoading.cpp)

set(OPENGL_HEADERS
    src/Renderer.h
    src/VertexBuffer.h
    src/VertexBufferLayout.h
    src/ElementBuffer.h
    src/VertexArray.h
    src/Shader.h
    src/Texture.h
    src/Camera.h
    src/PerspectiveCamera.h
    src/OrthographicCamera.h
    src/Mesh.h
    src/Model.h
    tests/Test.h
    tests/TestMultipleLights.h
    tests/TestTriangle.h
    tests/TestBatchRendering.h
    tests/TestModelLoading.h)

add_executable(OpenGL ${OPENGL_SOURCES} ${OPENGL_HEADERS})

target_include_directories(OpenGL
                           PRIVATE "./"
                           PRIVATE "src/"
                           PRIVATE "vendor/glfw/include"
                           PRIVATE "vendor/glew/include"
                           PRIVATE "vendor/stb_image"
                           PRIVATE "vendor/glm"
                           PRIVATE "vendor/imgui"
                           PRIVATE "vendor/assimp/include")

target_link_libraries(OpenGL ${OPENGL_LIBRARIES} glfw glew stb_image glm imgui assimp)

target_compile_definitions(OpenGL
                           PRIVATE "GLEW_NO_GLU=1")

if (MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall)
endif()

if (BUILD_SHARED_LIBS)
    add_custom_command(TARGET OpenGL COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:glfw> ${PROJECT_BINARY_DIR}/$<TARGET_FILE_NAME:glfw>)
    add_custom_command(TARGET OpenGL COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:glew> ${PROJECT_BINARY_DIR}/$<TARGET_FILE_NAME:glew>)
    add_custom_command(TARGET OpenGL COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:stb_image> ${PROJECT_BINARY_DIR}/$<TARGET_FILE_NAME:stb_image>)
    add_custom_command(TARGET OpenGL COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:glm_shared> ${PROJECT_BINARY_DIR}/$<TARGET_FILE_NAME:glm_shared>)
    add_custom_command(TARGET OpenGL COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:imgui> ${PROJECT_BINARY_DIR}/$<TARGET_FILE_NAME:imgui>)
    add_custom_command(TARGET OpenGL COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:assimp> ${PROJECT_BINARY_DIR}/$<TARGET_FILE_NAME:assimp>)
endif()