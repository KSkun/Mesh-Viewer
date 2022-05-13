cmake_minimum_required(VERSION 3.22)
project(Mesh_Viewer)

set(CMAKE_CXX_STANDARD 20)

set(Glad_DIR 3rdparty/glad/cmake)
set(GLFW_DIR 3rdparty/glfw/cmake)
set(pthreads_DIR 3rdparty/pthreads-win32/cmake)

add_definitions(-D_TIMESPEC_DEFINED)

find_package(OpenGL REQUIRED)
find_package(Glad REQUIRED)
find_package(GLFW REQUIRED)
find_package(pthreads REQUIRED)
add_subdirectory(3rdparty/fbximport/importer)

include_directories(${OPENGL_INCLUDE_DIRS})
include_directories(${Glad_INCLUDE_DIRS})
include_directories(${GLFW_INCLUDE_DIRS})
include_directories(3rdparty/fbximport/importer/include)

add_executable(${PROJECT_NAME}
        ${Glad_SOURCE}
        src/main.cpp
        )

target_link_libraries(${PROJECT_NAME} PRIVATE ${OPENGL_LIBRARIES})
target_link_libraries(${PROJECT_NAME} PRIVATE ${GLFW_LIBRARIES})
target_link_libraries(${PROJECT_NAME} PRIVATE FBXImport)

file(COPY ${GLFW_DLL} DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${pthreads_DLL} DESTINATION ${CMAKE_BINARY_DIR})
file(COPY 3rdparty/zlib/bin/zlib.dll DESTINATION ${CMAKE_BINARY_DIR})
