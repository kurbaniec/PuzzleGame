cmake_minimum_required(VERSION 3.21)
project(Puzzle_Game)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

#add_subdirectory(${PROJECT_SOURCE_DIR}/dependencies/glfw/lib-vc2022/)
#target_link_libraries(${PROJECT_NAME} glfw)
#find_package(glfw3 3.3 REQUIRED)

set(GLFW3_LIBRARY ${PROJECT_SOURCE_DIR}/dependencies/glfw/lib-vc2022/glfw3.lib)
set(GLFW3_INCLUDE_PATH ${PROJECT_SOURCE_DIR}/dependencies/glfw/include)
include_directories(${GLFW3_INCLUDE_PATH})
#find_package(GLFW3 REQUIRED)
#link_libraries(${CMAKE_SOURCE_DIR}/dependencies/glfw/lib-vc2022/glfw3.lib)

#find_package(GLFW3 REQUIRED)
#message(STATUS "Found GLFW3 in ${GLFW3_INCLUDE_DIR}")


add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} ${GLFW3_LIBRARY})

add_custom_command(TARGET ${PROJECT_NAME}
        POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${GLFW3_LIBRARY} ${CMAKE_BINARY_DIR})