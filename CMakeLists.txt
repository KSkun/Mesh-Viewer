cmake_minimum_required(VERSION 3.22)
project(Mesh_Viewer)

set(CMAKE_CXX_STANDARD 20)

add_executable(${PROJECT_NAME}
        glad/src/glad.c
        src/main.cpp
        )

find_package(OpenGL REQUIRED)

include_directories(glfw/include)
target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/glfw/lib/glfw3.lib)

include_directories(glad/include)
