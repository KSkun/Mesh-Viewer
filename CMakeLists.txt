cmake_minimum_required(VERSION 3.22)
project(Mesh_Viewer)

set(CMAKE_CXX_STANDARD 20)

add_executable(${PROJECT_NAME}
        src/main.cpp
        )

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${OPENGL_LIBRARIES})

include_directories(glfw/include)
target_link_libraries(${PROJECT_NAME} PRIVATE ${CMAKE_HOME_DIRECTORY}/glfw/lib/glfw3dll.lib)
file(COPY glfw/bin/glfw3.dll DESTINATION ${CMAKE_BINARY_DIR})
