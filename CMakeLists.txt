cmake_minimum_required(VERSION 3.21)
project(Puzzle_Game)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

add_executable(${PROJECT_NAME} src/main.cpp src/utils/print.h src/utils/shader.h)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules/")

set(LIBS glfw3 OpenGL::GL)
find_package(GLFW3 REQUIRED)
find_package(OpenGL REQUIRED)
add_library(GLAD ${CMAKE_SOURCE_DIR}/dependencies/glad/src/glad.c)
set(LIBS ${LIBS} GLAD)

target_link_libraries(${PROJECT_NAME} ${LIBS})
include_directories(${PROJECT_SOURCE_DIR}/dependencies/glfw/include/)
include_directories(${PROJECT_SOURCE_DIR}/dependencies/glad/include/)
include_directories(${PROJECT_SOURCE_DIR}/dependencies/)

# Copy library binaries to output directory
add_custom_command(TARGET ${PROJECT_NAME}
        POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${GLFW3_LIBRARY} ${CMAKE_BINARY_DIR})

# Copy shaders to output directory
set(SHADER_DIR ${PROJECT_SOURCE_DIR}/src/shader)
add_custom_command(TARGET ${PROJECT_NAME}
        POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${SHADER_DIR} ${CMAKE_BINARY_DIR}/shader)