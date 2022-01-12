cmake_minimum_required(VERSION 3.21)
project(Puzzle_Game)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

add_executable(${PROJECT_NAME} src/main.cpp src/utils/print.h src/utils/shader.h src/utils/mesh.h src/utils/model.h src/utils/camera.h src/utils/stringutils.h src/engine/model/triangle.cpp src/engine/model/triangle.h src/engine/model/mesh.h src/engine/model/model.h src/engine/model/shader.h src/engine/model/simplemodel.cpp src/engine/model/simplemodel.h src/engine/instance/instance.cpp src/engine/instance/instance.h src/engine/model/model.cpp src/game/BlockInstance.cpp src/game/BlockInstance.h src/engine/factory/InstanceFactory.cpp src/engine/factory/InstanceFactory.h src/engine/state/state.cpp src/engine/state/state.h src/engine/model/mesh.cpp src/engine/renderer/renderer.cpp src/engine/renderer/renderer.h src/engine/camera/camera.h src/engine/camera/camera.cpp src/engine/window/window.cpp src/engine/window/window.h src/engine/model/lodmodel.cpp src/engine/model/lodmodel.h src/engine/collision/boundingbox.cpp src/engine/collision/boundingbox.h src/game/GameBasis.h src/game/DemoGame.cpp src/game/DemoGame.h src/game/PuzzleGame.cpp src/game/PuzzleGame.h src/game/Player.cpp src/game/Player.h)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules/")

set(LIBS glfw3 OpenGL::GL assimp SOIL2)
find_package(GLFW3 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(ASSIMP REQUIRED)
find_package(SOIL2 REQUIRED)
add_library(GLAD ${CMAKE_SOURCE_DIR}/dependencies/glad/src/glad.c)
set(LIBS ${LIBS} GLAD)

target_link_libraries(${PROJECT_NAME} ${LIBS})
include_directories(${PROJECT_SOURCE_DIR}/dependencies/glfw/include/)
include_directories(${PROJECT_SOURCE_DIR}/dependencies/glad/include/)
include_directories(${PROJECT_SOURCE_DIR}/dependencies/assimp/include/)
include_directories(${PROJECT_SOURCE_DIR}/dependencies/SOIL2/include/)
include_directories(${PROJECT_SOURCE_DIR}/dependencies/)

#message("LIB ${GLFW3_LIBRARY}")
#message("LIB ${ASSIMP_LIBRARY}")
#message("LIB ${ASSIMP_DLL}")

# Copy library binaries to output directory
add_custom_command(TARGET ${PROJECT_NAME}
        PRE_LINK COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${GLFW3_LIBRARY} ${CMAKE_BINARY_DIR})

add_custom_command(TARGET ${PROJECT_NAME}
        PRE_LINK COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${ASSIMP_LIBRARY} ${CMAKE_BINARY_DIR})

add_custom_command(TARGET ${PROJECT_NAME}
        PRE_LINK COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${SOIL2_LIBRARY} ${CMAKE_BINARY_DIR})

# Copy DLLs to output directory
add_custom_command(TARGET ${PROJECT_NAME}
        POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${ASSIMP_DLL} ${CMAKE_BINARY_DIR})

# Copy shaders to output directory
set(SHADER_DIR ${PROJECT_SOURCE_DIR}/src/shader)
add_custom_command(TARGET ${PROJECT_NAME}
        POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${SHADER_DIR} ${CMAKE_BINARY_DIR}/shader)

# Copy resources (textures, models, ..) to output directory
set(RESOURCES_DIR ${PROJECT_SOURCE_DIR}/resources)
add_custom_command(TARGET ${PROJECT_NAME}
        POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${RESOURCES_DIR} ${CMAKE_BINARY_DIR}/resources)