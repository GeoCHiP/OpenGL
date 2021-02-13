cmake_minimum_required(VERSION 3.17)
project(ImGui)

set(IMGUI_SOURCES
    imgui/imgui_demo.cpp
    imgui/imgui_draw.cpp
    imgui/imgui_impl_glfw.cpp
    imgui/imgui_impl_opengl3.cpp
    imgui/imgui_widgets.cpp
    imgui/imgui.cpp)

set(IMGUI_HEADERS
    imgui/imconfig.h
    imgui/imgui_impl_glfw.h
    imgui/imgui_impl_opengl3.h
    imgui/imgui_internal.h
    imgui/imgui.h
    imgui/imstb_rectpack.h
    imgui/imstb_textedit.h
    imgui/imstb_truetype.h)

add_library(imgui SHARED ${IMGUI_SOURCES} ${IMGUI_HEADERS})

target_include_directories(imgui
                           PRIVATE "${CMAKE_SOURCE_DIR}/vendor/glfw/include"
                           PRIVATE "${CMAKE_SOURCE_DIR}/vendor/glew/include")

target_link_libraries(imgui PRIVATE glew glfw)

target_compile_definitions(imgui
                           PRIVATE "GLEW_NO_GLU=1")

message(STATUS "ImGui: v1.79")