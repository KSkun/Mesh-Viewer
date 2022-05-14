cmake_minimum_required(VERSION 3.22)
project(Mesh_Viewer)

set(CMAKE_CXX_STANDARD 20)

set(Glad_DIR 3rdparty/glad/cmake)
set(GLFW_DIR 3rdparty/glfw/cmake)
set(glm_DIR 3rdparty/glm/cmake/glm)

find_package(OpenGL REQUIRED)
find_package(Glad REQUIRED)
find_package(GLFW REQUIRED)
find_package(glm REQUIRED)

include_directories(${OPENGL_INCLUDE_DIRS})
include_directories(${Glad_INCLUDE_DIRS})
include_directories(${GLFW_INCLUDE_DIRS})
include_directories(${glm_INCLUDE_DIRS})
include_directories(3rdparty/plog/include)
include_directories(3rdparty/obj-loader)
include_directories(3rdparty/stb)

add_executable(${PROJECT_NAME}
        ${Glad_SOURCE}
        3rdparty/stb/stb_image.h

        src/main.cpp
        src/shader.h
        src/shader.cpp
        src/material.h
        src/material.cpp
        src/mesh.h
        src/mesh.cpp
        )

target_link_libraries(${PROJECT_NAME} PRIVATE ${OPENGL_LIBRARIES})
target_link_libraries(${PROJECT_NAME} PRIVATE ${GLFW_LIBRARIES})
target_link_libraries(${PROJECT_NAME} PRIVATE glm::glm)

file(COPY ${GLFW_DLL} DESTINATION ${CMAKE_BINARY_DIR})
